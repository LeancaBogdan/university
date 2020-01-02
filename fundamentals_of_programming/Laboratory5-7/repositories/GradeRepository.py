"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
from domain.Validators import GradeValidator
from domain.Grade import Grade
from repositories.iterable import *
from repositories.RepositoryException import RepositoryException
from repositories.StudentRepository import StudentRepository
from repositories.DisciplineRepository import DisciplineRepository
import unittest
import pickle


class GradeRepository:
    """
    Class for storing Grade instances
    """
    def __init__(self, student_repository, discipline_repository):
        """
        Constructor
        """
        self.__grades_list = MyList()
        self.__grade_validator = GradeValidator()
        self.__student_repository = student_repository
        self.__discipline_repository = discipline_repository

    def set_list_of_grades(self, new_list_of_grades):
        """
        Setter for the list of grades
        :param new_list_of_grades: The list of grades
        :return: -
        """
        self.__grades_list = new_list_of_grades

    def test_add_grade(self, discipline_id, student_id, grade_value):
        """
        Simulates an add_grade, raises any eventual exceptions
        :param discipline_id: Discipline's ID
        :param student_id: Student's ID
        :param grade_value: Grade value
        :return: -
        """
        self.__grade_validator.validate_discipline(discipline_id)
        self.__grade_validator.validate_student_id(student_id)

        if self.__student_repository.find_by_id(student_id) is None:
            raise RepositoryException("Invalid student ID!")
        if self.__discipline_repository.find_by_id(discipline_id) is None:
            raise RepositoryException("Invalid discipline ID!")

        self.__grade_validator.validate_grade_value(grade_value)

    def add_grades(self, list_of_grades):
        """
        Adds every grade from a given list of grades to the repository
        :param list_of_grades: The list of grades
        :return: -
        """
        for grade in list_of_grades:
            self.__grades_list.append(grade)

    def store(self, discipline_id, student_id, grade_value):
        """
        Stores a Grade instance in the repository
        :param discipline_id: The ID of the discipline at which the grade is given
        :param student_id: The ID of the graded student
        :param grade_value: The value of the grade
        :return: -
        :exceptions: RepoException; GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)
        self.__grade_validator.validate_student_id(student_id)

        if self.__student_repository.find_by_id(student_id) is None:
            raise RepositoryException("Invalid student ID!")
        if self.__discipline_repository.find_by_id(discipline_id) is None:
            raise RepositoryException("Invalid discipline ID!")

        student_name = self.__student_repository.find_by_id(student_id).get_name()
        discipline_name = self.__discipline_repository.find_by_id(discipline_id).get_name()

        self.__grade_validator.validate_grade_value(grade_value)

        grade = Grade(discipline_id, discipline_name, student_id, student_name, grade_value)
        self.__grades_list.append(grade)

    def delete(self, grade):
        """
        Deletes a Grade instance from the repository
        :param grade: The Grade instance to be deleted
        :return: -
        """
        self.__grades_list.remove(grade)

    def delete_by_student(self, student_id):
        """
        Deletes all the grades of a student based on his/hers ID
        :param student_id: The ID of the student for which the delete will be done.
        :return:
        :exceptions: GradeException
        """
        self.__grade_validator.validate_student_id(student_id)

        for grade in self.__grades_list:
            if grade.get_student_id() == student_id:
                self.__grades_list.remove(grade)

    def get_by_student(self, student_id):
        """
        Getter for all the grades of a given student
        :param student_id: Student's ID
        :return: A list containing the grades of the given student
        """
        result = []

        for grade in self.get_all():
            if grade.get_student_id() == student_id:
                result.append(grade)

        return result

    def get_by_discipline(self, discipline_id):
        """
        Getter for all the grades at a given discipline
        :param discipline_id: Discipline's ID
        :return: A list containing the grades at a given discipline
        """
        result = []

        for grade in self.get_all():
            if grade.get_discipline_id == discipline_id:
                result.append(grade)

        return result

    def delete_by_discipline(self, discipline_id):
        """
        Deletes all the grades at a discipline based on its ID
        :param discipline_id: The ID of the discipline for which the delete will be done
        :return: -
        :exceptions: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)

        for grade in self.__grades_list:
            if grade.get_discipline_id() == discipline_id:
                self.__grades_list.remove(grade)

    def is_discipline_graded(self, discipline_id):
        """
        Checks whether a given discipline is graded or not
        :param discipline_id: The ID of the discipline to be checked
        :return: True if there exists a grade for the given discipline in the repository, False otherwise
        :exceptions: GradeException
        """
        self.__grade_validator.validate_discipline(discipline_id)

        for grade in self.__grades_list:
            if grade.get_discipline_id() == discipline_id:
                return True

        return False

    def is_student_graded(self, student_id):
        """
        Checks whether a given student is graded or not
        :param student_id: The ID of the student to be checked
        :return: True if there exists a grade for the given student in the repository, False otherwise
        :exceptions: GradeException
        """
        self.__grade_validator.validate_student_id(student_id)

        for grade in self.__grades_list:
            if grade.get_student_id() == student_id:
                return True

        return False

    def get_all(self):
        """
        Getter for the list of Grade instances in the repository
        :return: The list of Grade instances in the repository
        :exceptions: RepoException
        """
        return_list = []

        for grade in self.__grades_list:
            return_list.append(grade)

        if len(return_list) == 0:
            raise RepositoryException("The repository is empty!")

        return return_list
    
    def __str__(self):
        """
        Overrides the str method for the GradeRepository
        :return: A string containing the string form of all the Grade instances in the repository
        """
        grades = "Grades:\n"

        for grade in self.__grades_list:
            grades += str(grade)
            grades += "\n"

        return grades


class GradeRepositoryCSV(GradeRepository):
    """
    Class for storing Grade instances in a CSV file
    """
    def __init__(self, student_repository, discipline_repository):
        GradeRepository.__init__(self, student_repository, discipline_repository)
        self.__filename = "GradeRepo.csv"

    def get_filename(self):
        return self.__filename

    def write_file(self):
        file_handle = None
        try:
            file_handle = open(self.get_filename(), "w")
            for grade in self.get_all():
                grade_string = grade.get_discipline_id() + ","\
                               + grade.get_discipline_name() + ","\
                               + grade.get_student_id() + ","\
                               + grade.get_student_name() + ","\
                               + str(grade.get_grade()) + "\n"
                file_handle.write(grade_string)

        except IOError as ie:
            print(ie)
        except RepositoryException:
            pass

        finally:
            if file_handle:
                file_handle.close()

    def read_file(self):
        file_handle = None
        try:
            file_handle = open(self.__filename, "r")
            line = file_handle.readline().strip()

            while len(line) > 0:
                line = line.split(',')
                self.store(line[0], line[2], int(line[4]))
                line = file_handle.readline().strip()

        except IOError as ie:
            print(ie)
        except RepositoryException:
            pass

        finally:
            if file_handle:
                file_handle.close()


class GradeRepositoryBinary(GradeRepository):
    def __init__(self, student_repository, discipline_repository):
        GradeRepository.__init__(self, student_repository, discipline_repository)
        self.__filename = "GradeRepo.pickle"

    def get_filename(self):
        return self.__filename

    def read_file(self):
        file_handle = None
        try:
            file_handle = open(self.get_filename(), "rb")
            self.set_list_of_grades(pickle.load(file_handle))

        except EOFError:
            self.__grades_list = []
        except IOError as e:
            print("An error occurred - " + str(e))

        finally:
            if file_handle:
                file_handle.close()

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


class TestGradeRepository(unittest.TestCase):
    """
    Class for testing the GradeRepo class
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
        self.grades.store('2', '1', 9)
        self.grades.store('3', '2', 10)
        self.grades.store('4', '2', 4)

    def test_all(self):
        self.assertTrue(self.grades.is_discipline_graded('1'))
        self.assertTrue(self.grades.is_student_graded('1'))
        self.grades.delete_by_discipline('3')
        self.grades.delete_by_discipline('4')
        self.assertEqual(self.grades.get_by_student('1'), self.grades.get_all())
        self.assertEqual(str(self.grades), 'Grades:\nBob has grade 10 at FP\nBob has grade 9 at CSA\n')
        self.grades.delete_by_student('1')
