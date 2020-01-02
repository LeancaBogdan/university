"""
Created on 25 nov. 2016

@author: bogdanleanca
"""
from domain.Grade import Grade
from domain.Student import StudentWithAverage, StudentWithSituation
from domain.Discipline import DisciplineWithAvg
from domain.Validators import GradeValidator
from repositories.DisciplineRepository import DisciplineRepository
from repositories.StudentRepository import StudentRepository
from repositories.GradeRepository import GradeRepository
from controller.UndoController import FunctionCall, Operation
import unittest


class GradeController:
    """
    Controller for Grades
    """
    def __init__(self, grade_repository, student_repository, discipline_repository):
        """
        Constructor
        """
        self.__grade_repository = grade_repository
        self.__student_repository = student_repository
        self.__discipline_repository = discipline_repository
        self.__grade_validator = GradeValidator()

    def get_grade_repository(self):
        """
        Getter for the grade repository
        :return: The grade repository
        """
        return self.__grade_repository

    def get_student_repository(self):
        """
        Getter for the student repository
        :return: The student repository
        """
        return self.__student_repository

    def get_discipline_repository(self):
        """
        Getter for the discipline repository
        :return: The discipline repository
        """
        return self.__discipline_repository

    def add_grade(self, student_id, discipline_id, grade_value):
        """
        Stores a new grade for a given student, at a given discipline
        :param student_id: Student's ID
        :param discipline_id: Discipline's ID
        :param grade_value: The value of the grade
        :return: -
        :raises: GradeException, RepoException
        """
        self.__grade_validator.validate_student_id(student_id)
        self.__grade_validator.validate_discipline(discipline_id)
        self.__grade_validator.validate_grade_value(grade_value)
        self.__grade_repository.store(discipline_id, student_id, grade_value)

    def add_grades(self, list_of_grades):
        """
        Adds every grade from a given list of grades to the repository
        :param list_of_grades: The list of grades
        :return: -
        """
        self.__grade_repository.add_grades(list_of_grades)

    def get_grades_by_student(self, student_id):
        """
        Gets all the grades of a student, identified by his/hers ID, from the repository
        :param student_id: Student's ID
        :return: The list of grades
        :raises: GradeException
        """
        self.__grade_validator.validate_student_id(student_id)
        grades_list = []

        for grade in self.__grade_repository.get_all():
            if student_id == grade.get_student_id():
                grades_list.append(grade)

        return grades_list

    def get_grades_by_discipline(self, discipline_id):
        """
        Gets all the grades at a discipline, identified by it's ID, from the repository
        :param discipline_id: Discipline's ID
        :return: The list of grades
        :raises: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)
        grades_list = []

        for grade in self.__grade_repository.get_all():
            if discipline_id == grade.get_discipline_id():
                grades_list.append(grade)

        return grades_list

    def delete_by_student(self, student_id):
        """
        Deletes all the stored grades for the given student
        :param student_id: Student's ID
        :return: -
        :raises: GradeException
        """
        self.__grade_validator.validate_student_id(student_id)
        self.__grade_repository.delete_by_student(student_id)
        
    def delete_by_discipline(self, discipline_id):
        """
        Deletes all the stored grades for the given discipline
        :param discipline_id: Discipline's ID
        :return: -
        :raises: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)
        self.__grade_repository.delete_by_discipline(discipline_id)

    def is_student_graded(self, student_id):
        """
        Checks whether the given student has any stored grade
        :param student_id: Student's ID
        :return: True if the given student is graded, False otherwise
        :raises: GradeException
        """
        self.__grade_validator.validate_student_id(student_id)
        return self.__grade_repository.is_student_graded(student_id)

    def is_discipline_graded(self, discipline_id):
        """
        Checks whether the given discipline has any stored grade
        :param discipline_id: Discipline's ID
        :return: True if the given discipline is graded, False otherwise
        :raises: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)
        return self.__grade_repository.is_discipline_graded(discipline_id)

    def get_averages_at_discipline_sorted_descending(self, discipline_name):
        """
        Creates a sorted list of students in the descending order of the average grades of the students enrolled
         at a given discipline
        :param discipline_name: Discipline's name
        :return: The list of students
        :raises: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_name)
        list_of_students = []

        for student in self.__student_repository.get_all():
            if self.is_student_graded(student.get_id()):
                for discipline in student.get_disciplines():
                    if discipline == discipline_name:
                        avg = 0
                        counter = 0
                        for grade in self.get_grades_by_student(student.get_id()):
                            if self.__discipline_repository.get_name_by_id(grade.get_discipline_id()) == discipline_name:
                                avg += grade.get_grade()
                                counter += 1
                        avg /= float(counter)

                        student = StudentWithGrade(student.get_id(), student.get_name(), discipline_name, avg)
                        list_of_students.append(student)

        return sorted(list_of_students, reverse=True)

    def get_list_of_failing_students(self):
        """
        Creates a list of all the students failing at all the disciplines
        :return: The list of students
        """
        list_of_students = []

        for student in self.__student_repository.get_all():
            for discipline_name in student.get_disciplines():
                avg = 0
                counter = 0
                for grade in self.get_grades_by_student(student.get_id()):
                    if grade.get_discipline_id() == self.__discipline_repository.get_id_by_name(discipline_name):
                        avg += grade.get_grade()
                        counter += 1

                if counter > 0:
                    avg /= float(counter)
                    if avg < 5:
                        student = StudentWithGrade(student.get_id(), student.get_name(), discipline_name, avg)
                        list_of_students.append(student)

        return list_of_students

    def get_list_of_students_with_best_situation(self):
        """
        Creates a list with all the students sorted descending by their average grades at
         all the disciplines they are enrolled to
        :return: The list of students
        """
        list_of_students = []

        for student in self.__student_repository.get_all():
            if self.is_student_graded(student.get_id()):
                avg = 0
                counter = 0

                for discipline_name in student.get_disciplines():
                    discipline_average = 0
                    counter_discipline = 0

                    for grade in self.get_grades_by_student(student.get_id()):
                        if grade.get_discipline_id() == self.__discipline_repository.get_id_by_name(discipline_name):
                            discipline_average += grade.get_grade()
                            counter_discipline += 1

                    if counter_discipline > 0:
                        discipline_average /= float(counter_discipline)
                        avg += discipline_average
                        counter += 1

                if counter > 0:
                    avg /= float(counter)
                    student = StudentWithSituation(student.get_id(), student.get_name(), avg)
                    list_of_students.append(student)

        return sorted(list_of_students, reverse=True)

    def get_list_of_graded_disciplines(self):
        """
        Creates a new list with all the disciplines and the average grade at each one of them,
         sorted descending by the grade
        :return: The list of disciplines
        """
        list_of_disciplines = []

        for discipline in self.__discipline_repository.get_all():
            if self.is_discipline_graded(discipline.get_id()):
                avg = 0
                counter = 0
                for grade in self.get_grades_by_discipline(discipline.get_id()):
                    avg += grade.get_grade()
                    counter += 1

                if counter > 0:
                    avg /= float(counter)
                    discipline = DisciplineWithAvg(discipline.get_id(), discipline.get_name(), avg)
                    list_of_disciplines.append(discipline)

        return sorted(list_of_disciplines, reverse=True)

    def get_all_grades(self):
        """
        Gets a list of all the grades in the repository
        :return: A list of all the grades in the repository
        """
        return self.__grade_repository.get_all()


class TestGradeController(unittest.TestCase):
    """
    Class for testing the GradeController class
    """
    def setUp(self):
        self.students = StudentRepository()
        self.disciplines = DisciplineRepository()
        self.disciplines.store('1', 'FP')
        self.disciplines.store('2', 'CSA')
        self.disciplines.store('3', 'Math')
        self.disciplines.store('4', 'CDI')
        self.students.store('1', 'Bob', ['CSA', 'FP'])
        self.students.store('2', 'Bobita', ['Math', 'CDI'])
        self.grades = GradeRepository(self.students, self.disciplines)
        self.grades.store('1', '1', 10)
        self.gradeCont = GradeController(self.grades, self.students, self.disciplines)

    def test_addGrade_getByStudent_getByDiscipline_getAll_deleteByStudent_deleteByDiscipline_discIsGraded_stIsGraded(self):
        self.assertEqual(self.gradeCont.get_grades_by_discipline('1'), self.gradeCont.get_all_grades())
        self.gradeCont.add_grade('1', '2', 10)
        self.assertTrue(self.gradeCont.is_discipline_graded('2'))
        self.gradeCont.delete_by_discipline('2')
        self.assertEqual(self.gradeCont.get_grades_by_discipline('1'), self.gradeCont.get_all_grades())
        self.gradeCont.add_grade('2', '1', 10)
        self.assertTrue(self.gradeCont.is_student_graded('2'))
        self.gradeCont.delete_by_student('1')
        self.assertEqual(self.gradeCont.get_all_grades(), self.gradeCont.get_grades_by_student('2'))

    def test_lists(self):
        res1 = ''
        res2 = ''
        for disc in self.gradeCont.get_list_of_graded_disciplines():
            res1 += str(disc)
            res1 += ''
            res2 += str(self.disciplines.find_by_id('1'))
            res2 += ', Average: '
            res2 += str(disc.get_average())
        self.assertEqual(res1, res2)


class GradeControllerWithUndo(GradeController):
    """
    Controller for grades with undo/redo functionality
    """
    def __init__(self, grade_repository, student_repository, discipline_repository, undo_controller):
        """
        Constructor
        """
        GradeController.__init__(self, grade_repository, student_repository, discipline_repository)
        self.__undoController = undo_controller

    def add_grade(self, student_id, discipline_id, grade_value):
        """
        Override for the add_grade method in the super class, also records the corresponding methods and their
        parameters for undo/redo
        :param student_id: Student's ID
        :param discipline_id: Discipline's ID
        :param grade_value: Grade value
        :return: -
        """
        self.get_grade_repository().test_add_grade(discipline_id, student_id, grade_value)
        student_name = self.get_student_repository().find_by_id(student_id).get_name()
        discipline_name = self.get_discipline_repository().find_by_id(discipline_id).get_name()
        self.__undoController.new_operation()
        undo_function = FunctionCall(
            self.get_grade_repository().delete,
            Grade(
                discipline_id, discipline_name, student_id, student_name, grade_value
            )
        )
        redo_function = FunctionCall(self.get_grade_repository().store, discipline_id, student_id, grade_value)
        operation = Operation(redo_function, undo_function)
        self.__undoController.record_operation(operation)
        self.get_grade_repository().store(discipline_id, student_id, grade_value)

    def delete_by_student(self, student_id):
        """
        Override for the delete_by_student method in the super class, also records the corresponding methods and their
        parameters for undo/redo
        :param student_id: Student's ID
        :return: -
        """
        self.__grade_validator.validate_student_id(student_id)
        list_of_grades = self.get_grades_by_student(student_id)
        self.__undoController.new_operation()
        undo_function = FunctionCall(self.add_grades, list_of_grades)
        redo_function = FunctionCall(self.get_grade_repository().delete_by_student, student_id)
        operation = Operation(redo_function, undo_function)
        self.__undoController.record_operation(operation)
        self.get_grade_repository().delete_by_student(student_id)

    def delete_by_discipline(self, discipline_id):
        """
        Override for the delete_by_discipline method in the super class, also records the corresponding
         methods and their parameters for undo/redo
        :param discipline_id: Discipline's ID
        :return:
        """
        self.__grade_validator.validate_discipline(discipline_id)
        list_of_grades = self.get_grades_by_discipline(discipline_id)
        self.__undoController.new_operation()
        undo_function = FunctionCall(self.add_grades, list_of_grades)
        redo_function = FunctionCall(self.get_grade_repository().delete_by_discipline, discipline_id)
        operation = Operation(redo_function, undo_function)
        self.__undoController.record_operation(operation)
        self.get_grade_repository().delete_by_discipline(discipline_id)
