"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
from controller.UndoController import FunctionCall, Operation
from repositories.RepositoryException import RepositoryException
from repositories.sort import *
from repositories.StudentRepository import StudentRepository
import unittest


class StudentController:
    """
    Controller for Students
    """
    def __init__(self, student_repository):
        """
        Constructor
        """
        self.__student_repository = student_repository

    def get_repository(self):
        """
        Getter for the entire student repository
        :return: The student repository
        """
        return self.__student_repository

    def add_student(self, student_id, student_name, disciplines):
        """
        Creates a Student based on the given information and saves it in the repository
        :param student_id: Student's ID
        :param student_name: Student's name
        :param disciplines: List of disciplines the student is enrolled to
        :return: -
        :exceptions: RepoException, StudentException
        """
        self.__student_repository.store(student_id, student_name, disciplines)
        
    def remove_student(self, student_id):
        """
        Calls the delete method in the Student repository
        :param student_id: The ID of the student to be deleted
        :return: -
        :exceptions: StudentException, RepoException
        """
        self.__student_repository.delete(student_id)
    
    def update_student(self, student_id, new_name, disciplines_list):
        """
        Calls the update method in the Student repository
        :param student_id: Student's ID
        :param new_name: Student's new discipline_name
        :param disciplines_list: The new list of disciplines the student is enrolled to
        :return: -
        :exceptions: RepoException, StudentException
        """
        self.__student_repository.update(student_id, new_name, disciplines_list)
    
    def add_discipline_to_student(self, student_id, discipline_name):
        """
        Adds the given discipline to the list of disciplines the given student (by id) is enrolled to
        :param student_id: Student's ID
        :param discipline_name: New discipline's name
        :return: -
        :exceptions: StudentException, RepoException
        """
        if self.__student_repository.find_by_id(student_id) is None:
            raise RepositoryException("Student with the given ID not in the repository!")

        self.__student_repository.find_by_id(student_id).add_discipline(discipline_name)
        
    def remove_discipline_for_student(self, student_id, discipline_name):
        """
        Removes the given discipline from the list of disciplines the given student (by id) is enrolled to
        :param student_id: Student's ID
        :param discipline_name: Discipline's name
        :return: -
        :exceptions: RepoException, StudentException
        """
        if self.__student_repository.find_by_id(student_id) is None:
            raise RepositoryException("Student with the given ID not in the repository!")

        self.__student_repository.find_by_id(student_id).remove_discipline(discipline_name)
        
    def student_has_discipline(self, student_id, discipline_name):
        """
        Checks if the given students is enrolled at the given discipline
        :param student_id: Student's ID
        :param discipline_name: Discipline's name
        :return: True if the student is enrolled at the given discipline, False otherwise
        :exceptions: RepoException, StudentException
        """
        if self.__student_repository.find_by_id(student_id) is None:
            raise RepositoryException("Student with the given ID not in the repository!")

        for discipline in self.__student_repository.find_by_id(student_id).get_disciplines():
            if discipline_name == discipline:
                return True

        return False
    
    def find(self, student_id):
        """
        Finds a student in the repository, if it exists
        :param student_id: Student's ID
        :return: The student instance if it is found, None otherwise
        :exceptions: StudentException
        """
        return self.__student_repository.find_by_id(student_id)
    
    def search_by_id(self, search_substring):
        """
        Tries to find all the students whose IDs contain the given search substring
        :param search_substring: The search substring
        :return: The list of found students.
        :exception RepoException: No student found
        """
        return self.__student_repository.search_by_id(search_substring)

    def search_by_name(self, search_substring):
        """
        Tries to find all the students whose names contain the given search substring
        :param search_substring: The search substring
        :return: The list of searched students.
        :exception RepoException: No student found
        """
        return self.__student_repository.search_by_name(search_substring)

    def get_sorted_students_for_discipline(self, discipline_name):
        """
        Creates a list of all the students enrolled at the given discipline, sorted alphabetically by their names
        :param discipline_name: Discipline's name
        :return: The list of the searched students
        """
        return_list = []

        for student in self.__student_repository.get_all():
            for discipline in student.get_disciplines():
                if discipline == discipline_name:
                    return_list.append(student)

        return sorted(return_list, key=lambda st: st.get_name())

    def get_all(self):
        """
        Gets a list of all the students in the repository, sorted alphabetically
         by their names (using custom sorting algorithm)
        :return: The list of all students
        :exceptions: RepoException
        """
        list_of_students = self.__student_repository.get_all()

        def compare_by_name(student_1, student_2):
            return student_1.get_name() < student_2.get_name()

        gnome_sort(list_of_students, compare_by_name)

        return list_of_students
    
    def __str__(self):
        """
        Overrides the str method for StudentController instances
        :return: A string containing the string form of all the Student objects in the repository
        :exceptions: RepoException
        """
        return str(self.__student_repository)
        
    
class TestStudentController(unittest.TestCase):
    """
    Class for testing the StudentController class
    """
    def setUp(self):
        self.student_repository = StudentRepository()
        self.student_controller = StudentController(self.student_repository)
        self.student_repository.store('1', 'Bob', ['FP', 'CSA', 'CDI'])

    def test_addStudent_updateStudent_deleteStudent_find_searchID_searchName(self):
        self.student_controller.add_student('2', 'test', [])
        self.assertEqual([self.student_controller.find('2')], self.student_controller.search_by_name('test'))
        self.assertEqual(self.student_controller.search_by_name('test'), self.student_controller.search_by_id('2'))
        self.student_controller.update_student('1', 'test1', ['FP', 'CSA'])
        self.assertEqual([self.student_controller.find('1')], self.student_controller.search_by_name('test1'))
        self.student_controller.remove_student('2')
        self.assertIsNone(self.student_controller.find('2'))

    def test_addDiscipline_removeDiscipline_hasDiscipline(self):
        self.assertFalse(self.student_controller.student_has_discipline('1', 'ASC'))
        self.student_controller.add_discipline_to_student('1', 'ASC')
        self.assertTrue(self.student_controller.student_has_discipline('1', 'ASC'))
        self.student_controller.remove_discipline_for_student('1', 'ASC')
        self.assertFalse(self.student_controller.student_has_discipline('1', 'ASC'))

    def test_listSortAlpha_getAll_str(self):
        self.assertEqual(self.student_controller.get_all(), [self.student_controller.find('1')])
        self.student_controller.add_student('2', 'ATest', ['FP'])
        res1 = ''
        res2 = ''
        for st in self.student_controller.get_sorted_students_for_discipline('FP'):
            res1 += str(st)
            res1 += "\n"
        res2 += str(self.student_controller.find('2'))
        res2 += "\n"
        res2 += str(self.student_controller.find('1'))
        res2 += "\n"
        self.assertEqual(res1, res2)


class StudentControllerWithUndo(StudentController):
    """
    Controller for students with undo/redo functionality
    """
    def __init__(self, student_repository, undo_controller):
        """
        Constructor
        """
        StudentController.__init__(self, student_repository)
        self.__undo_controller = undo_controller

    def add_student(self, student_id, student_name, disciplines_list):
        """
        Override for the add_student method in the super class, also records the corresponding methods and their
        params for undo/redo
        :param student_id: Student's ID
        :param student_name: Student's discipline_name
        :param disciplines_list: The list of disciplines the new student is enrolled to
        :return: -
        """
        self.get_repository().test_add_student(student_id, student_name, disciplines_list)
        self.__undo_controller.new_operation()
        undo_function = FunctionCall(self.get_repository().delete, student_id)
        redo_function = FunctionCall(self.get_repository().store, student_id, student_name, disciplines_list)
        operation = Operation(redo_function, undo_function)
        self.__undo_controller.record_operation(operation)
        self.get_repository().store(student_id, student_name, disciplines_list)

    def remove_student(self, student_id):
        """
        Override for the removeStudent method in the super class, also records the corresponding methods and their
        params for undo/redo
        :param student_id: Student's ID
        :return: -
        """
        student = self.find(student_id)
        self.get_repository().test_remove_student(student_id)
        self.__undo_controller.new_operation()
        undo_function = FunctionCall(
            self.get_repository().store,
            student.get_id(), student.get_name(),
            student.get_disciplines()
        )
        redo_function = FunctionCall(self.get_repository().delete, student_id)
        operation = Operation(redo_function, undo_function)
        self.__undo_controller.record_operation(operation)
        self.get_repository().delete(student_id)

    def update_student(self, student_id, new_name, disciplines_list):
        """
        Override for the updateStudent method in the super class, also records the corresponding methods and their
        params for undo/redo
        :param student_id: Student's ID
        :param new_name: Student's new discipline_name
        :param disciplines_list: New disciplines list
        :return: -
        """
        student = self.find(student_id)
        self.get_repository().test_update(student_id, new_name, disciplines_list)
        self.__undo_controller.new_operation()
        undo_function = FunctionCall(
            self.get_repository().update,
            student.get_id(),
            student.get_name(),
            student.get_disciplines()
        )
        redo_function = FunctionCall(self.get_repository().update, student_id, new_name, disciplines_list)
        operation = Operation(redo_function, undo_function)
        self.__undo_controller.record_operation(operation)
        self.get_repository().delete(student_id)
