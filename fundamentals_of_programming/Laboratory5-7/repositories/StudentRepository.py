"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
from domain.Student import Student
from repositories.iterable import *
from repositories.RepositoryException import RepositoryException
from domain.Validators import StudentValidator
import pickle
import unittest


class StudentRepository:
    """
    Class for storing Student instances
    """

    def __init__(self):
        """
        Constructor for the students repository
        """
        self.__students = MyList()
        self.__validator = StudentValidator()

    def set_list(self, new_list):
        """
        Setter for the list of students contained in the repository
        :param new_list: The new list of students
        :return: -
        """
        self.__students = new_list

    def find_by_id(self, student_id):
        """
        Searches for a student with the given ID in the list of stored students
        :param student_id: The ID to be searched for
        :return: Student instance with the given ID if found, None if not in the repository
        """
        self.__validator.validate_id(student_id)

        for student in self.__students:
            if student_id == student.get_id():
                return student

        return None

    def test_add_student(self, student_id, student_name, disciplines_list):
        """
        Simulates a store, raises any eventual exceptions
        :param student_id: Student's ID
        :param student_name: Student's name
        :param disciplines_list: list of Disciplines the new student is enrolled to
        :return: -
        """
        self.__validator.validate_name(student_name)
        self.__validator.validate_id(student_id)

        if self.find_by_id(student_id) is not None:
            raise RepositoryException("Student having id=" + str(student_id) + " already stored!")

    def store(self, student_id, student_name, disciplines_list):
        """
        Stores the student in the repository if a student with the same ID is not already stored
        :param student_id: Student's ID
        :param student_name: Student's name
        :param disciplines_list: The list of disciplines the student is enrolled to
        :return: -
        :exception RepoException, StudentException
        """
        self.__validator.validate_name(student_name)
        self.__validator.validate_id(student_id)

        if self.find_by_id(student_id) is not None:
            raise RepositoryException("Student having id=" + str(student_id) + " already stored!")

        student = Student(student_id, student_name, disciplines_list)
        self.__students.append(student)

    def test_update(self, student_id, new_name, new_disciplines_list):
        """
        Simulates an update, raises any eventual exceptions
        :param student_id: Student's ID
        :param new_name: Student's new name
        :param new_disciplines_list: The new discipline list for the student
        :return: -
        """
        self.__validator.validate_id(student_id)
        self.__validator.validate_name(new_name)

        student = self.find_by_id(student_id)
        if student is None:
            raise RepositoryException("Student not found!")

    def update(self, student_id, new_name, new_disciplines_list):
        """
        Updates the student with the new data if a student with the given ID exists in the repository
        :param student_id: ID of the student to be updated
        :param new_name: The new name of the student
        :param new_disciplines_list: The new discipline list for the student
        :return: -
        :exception RepoException, StudentException
        """
        self.__validator.validate_id(student_id)
        self.__validator.validate_name(new_name)

        old_student = self.delete(student_id)
        if old_student is None:
            raise RepositoryException("No student with the given ID!")

        self.store(student_id, new_name, new_disciplines_list)

    def test_remove_student(self, student_id):
        """
        Simulates a delete, raises any eventual exceptions
        :param student_id: Student's ID
        :return: -
        """
        self.__validator.validate_id(student_id)

        student = self.find_by_id(student_id)
        if student is None:
            raise RepositoryException("Student not in repository!")

    def delete(self, student_id):
        """
        Deletes the student with the given ID from the repository
        :param student_id: The ID of the student to be removed
        :return: The deleted student
        :exception RepoException, StudentException
        """
        self.__validator.validate_id(student_id)

        student = self.find_by_id(student_id)
        if student is None:
            raise RepositoryException("Student not in the repository!")

        self.__students.remove(student)
        return student

    def search_by_id(self, search_substring):
        """
        Creates a list of all the students with the search_substring string contained in the ID attribute
        :param search_substring: The string to be searched for in the ID attribute of each student
        :return: A list containing the searched students.
        :exception RepoException: No student found
        """
        result = []

        for st in self.__students:
            if search_substring in st.get_id():
                result.append(st)

        if len(result) == 0:
            raise RepositoryException("No student was found.")

        return result

    def search_by_name(self, search_substring):
        """
        Creates a new list of all students with the search_substring string contained in the Name attribute
        :param search_substring: The string to be searched for in the Name attribute of each student
        :return: A list containing the searched students
        :exception RepoException: No student found
        """
        result = []

        for student in self.__students:
            if search_substring in student.get_name():
                result.append(student)

        if len(result) == 0:
            raise RepositoryException("No student was found.")

        return result

    def get_all(self):
        """
        Gets a list of all the students contained in the repository
        :return: A list containing all students stored in the repository
        """
        return_list = []

        for st in self.__students:
            return_list.append(st)

        if len(return_list) == 0:
            raise RepositoryException("The repository is empty!")

        return return_list

    def __len__(self):
        """
        Override for the len function for the repository. Returns the number of stored students
        :return: The number of students stored in the repository
        """
        return len(self.__students)

    def __str__(self):
        """
        Override of the str function for the repository
        :return: A string containing all the students in the repository
        :exception RepoException: Student repository is empty
        """
        if len(self.__students) == 0:
            raise RepositoryException("Student repository is empty!")

        return_string = "Students:\n"
        for st in self.__students:
            return_string += str(st)
            return_string += "\n"
        return return_string


class StudentRepositoryCSV(StudentRepository):
    """
    Class for storing Student instances in a CSV file
    """

    def __init__(self):
        StudentRepository.__init__(self)
        self.__filename = "StudentRepo.csv"

    def get_filename(self):
        return self.__filename

    def read_file(self):
        file_handle = None
        try:
            file_handle = open(self.__filename, "r")
            line = file_handle.readline().strip()
            while len(line) > 0:
                line = line.split(',')
                if len(line[2]) > 0:
                    disciplines_list = line[2].split('.')
                    self.store(line[0], line[1], disciplines_list)
                else:
                    self.store(line[0], line[1], [])
                line = file_handle.readline().strip()
        except IOError as ie:
            print(ie)
        finally:
            if file_handle:
                file_handle.close()

    def write_file(self):
        file_handle = None
        try:
            file_handle = open(self.__filename, "w")
            for student in self.get_all():
                student_string = student.get_id() + "," + student.get_name() + ","
                if student.get_disciplines() is not None:
                    for discipline in student.get_disciplines():
                        student_string += discipline
                        student_string += "."
                student_string += "\n"
                file_handle.write(student_string)
        except IOError as ie:
            print(ie)
        except RepositoryException:
            pass
        finally:
            if file_handle:
                file_handle.close()


class StudentRepositoryBinary(StudentRepository):
    def __init__(self):
        StudentRepository.__init__(self)
        self.__filename = "StudentRepo.pickle"

    def get_filename(self):
        return self.__filename

    def write_file(self):
        file_handle = None
        try:
            file_handle = open(self.get_filename(), "wb")
            pickle.dump(self.get_all(), file_handle)
        except IOError as ie:
            print("An error occurred - " + str(ie))
        finally:
            if file_handle:
                file_handle.close()

    def read_file(self):
        file_handle = None
        try:
            file_handle = open(self.get_filename(), "rb")
            self.set_list(pickle.load(file_handle))
        except EOFError:
            self.__students = []
        except IOError as e:
            print("An error occurred - " + str(e))
        finally:
            if file_handle:
                file_handle.close()


class TestStudentRepository(unittest.TestCase):
    """
    Class for testing StudentRepo class
    """
    def setUp(self):
        self.students = StudentRepository()
        self.students.store('1', 'Bob', ['FP', 'CSA', 'CDI'])
        self.students.store('2', 'Test', ['FP', 'CSA'])

    def test_all(self):
        self.assertEqual(self.students.get_all(), [self.students.find_by_id('1'), self.students.find_by_id('2')])
        self.assertIsNone(self.students.find_by_id('abc'))
        self.assertEqual(self.students.search_by_id('1'), [self.students.find_by_id('1')])
        self.assertEqual(self.students.search_by_name('Test'), [self.students.find_by_id('2')])
        self.students.delete('2')
        self.assertEqual(self.students.get_all(), [self.students.find_by_id('1')])
        self.students.update('1', 'Test', ['FP', 'CSA'])
        self.assertEqual([self.students.find_by_id('1')], self.students.search_by_name('Test'))
        self.assertEqual(len(self.students), 1)
        self.assertEqual(str(self.students), 'Students:\nID: 1, Name: Test, Disciplines: FP, CSA, \n')
