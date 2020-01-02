"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
import unittest
from domain.DomainException import StudentException


class Student:
    """
    Class for storing Student instances
    """
    def __init__(self, student_id, student_name, disciplines_list):
        """
        Constructor
        """
        self.__student_id = student_id
        self.__student_name = student_name
        self.__disciplines = disciplines_list

    def get_id(self):
        """
        Getter for the ID of the current student instance
        :return: The ID of the current student instance
        """
        return self.__student_id

    def get_name(self):
        """
        Getter for the name of the current student instance
        :return: The name of the current student instance
        """
        return self.__student_name

    def get_disciplines(self):
        """
        Getter for the list of disciplines the current student is enrolled to
        :return: The list of disciplines the current student is enrolled to
        """
        if len(self.__disciplines) == 0:
            return None

        return self.__disciplines

    def set_name(self, new_name):
        """
        Setter for the name of the current student instance
        :param new_name: Th new name for the current student instance
        :return: -
        """
        self.__student_name = new_name

    def add_discipline(self, discipline_name):
        """
        Adds a discipline to the list of disciplines the current student is enrolled to
        :param discipline_name: The new discipline's name
        :return: -
        :exceptions: StudentException: Student already enrolled at the given discipline
        """
        if discipline_name in self.get_disciplines():
            raise StudentException("Student is already enrolled at the given discipline!")

        self.__disciplines.append(discipline_name)

    def remove_discipline(self, discipline_name):
        """
        Removes a discipline from the list of disciplines the current student is enrolled to
        :param discipline_name: The name of the discipline to be removed
        :return: -
        :exceptions: StudentException: Student isn't enrolled at the discipline to be removed
        """
        if discipline_name not in self.get_disciplines():
            raise StudentException("Student isn't enrolled at the discipline to be removed")

        self.__disciplines.remove(discipline_name)

    def __str__(self):
        """
        Overrides the str function for a Student instance
        :return: A string containing the information about a student
        """
        return_string = ("ID: " + str(self.get_id()) + ", Name: " + self.get_name())

        if self.get_disciplines() is not None:
            return_string += ", Disciplines: "

            for discipline in self.get_disciplines():
                return_string += discipline
                return_string += ", "

        return return_string

    def __eq__(self, other_student):
        """
        Overrides the equality relation between two students; Compares the ID's of the students
        :param other_student: The student with which the current one will be compared
        :return: True if the students have the same ID, False otherwise
        """
        if not isinstance(other_student, Student):
            return False

        return self.get_id() == other_student.get_id()


class StudentWithAverage(Student):
    """
    Class for storing students with their average grade at a discipline
    """
    def __init__(self, student_id, student_name, disciplines_list, average_grade):
        """
        Constructor
        """
        Student.__init__(self, student_id, student_name, [])
        self.__disciplines = disciplines_list
        self.__average_grade = average_grade

    def get_disciplines(self):
        return self.__disciplines

    def get_average_grade(self):
        """
        Getter for the average grade of the current StudentWithAverage instance
        :return: The average grade of the current student
        """
        return self.__average_grade

    def __lt__(self, other_student):
        """
        Overrides the "lower than" relation to compare StudentWithAverage instances by their average grade
        :param other_student: The StudentWithAverage instance with which the current one is compared
        :return: True if the current StudentWithAverage instance has a greater avg than the other, False otherwise
        """
        return self.get_average_grade() < other_student.get_average_grade()

    def __str__(self):
        """
        Overrides the str function for StudentWithAverage instances
        :return: A string containing the information about a StudentWithAverage instance
        """
        return_string = "ID: " + str(self.get_id()) + \
                        ", Name: " + str(self.get_name()) + \
                        ", Discipline: " + str(self.get_disciplines()) + \
                        ", Average grade: " + str(self.__average_grade)

        return return_string


class StudentWithSituation(Student):
    """
    Class for storing students with their average grades at all the disciplines they are enrolled to
    """
    def __init__(self, student_id, student_name, average_grade):
        """
        Constructor
        """
        Student.__init__(self, student_id, student_name, [])
        self.__average_grade = average_grade

    def get_average_grade(self):
        """
        Getter for the average grade of a student at all the disciplines he/she is enrolled to
        :return: The average grade of a student at all the disciplines he/she is enrolled to
        """
        return self.__average_grade

    def __lt__(self, student):
        """
        Overrides the "lower than" relation to compare StudentWithSituation instances by their average grade
        :param student: The StudentWithSituation instance with which the current one is compared
        :return: True if the current StudentWithSituation instance has a greater avg than the other, False otherwise
        """
        return self.get_average_grade() < student.get_average_grade()

    def __str__(self):
        """
        Overrides the str function for StudentWithSituation instances
        :return:A string containing the information about a StudentWithSituation instance
        """
        student = "ID: " + str(self.get_id()) + \
                  ", Name: " + str(self.get_name()) + \
                  ", Average grade: " + str(self.__average_grade)
        return student


class TestStudent(unittest.TestCase):
    """
    Class for testing the Student class
    """
    def setUp(self):
        self.student = Student('1', 'Test', ['CSA', 'FP'])

    def test_getters(self):
        self.assertEqual(self.student.get_id(), '1')
        self.assertEqual(self.student.get_name(), 'Test')
        self.assertEqual(self.student.get_disciplines(), ['CSA', 'FP'])

    def test_setters(self):
        self.student.set_name('bob')
        self.assertEqual(self.student.get_name(), 'bob')

    def test_addDiscipline(self):
        self.student.add_discipline('CDI')
        self.assertEqual(self.student.get_disciplines(), ['CSA', 'FP', 'CDI'])

    def test_removeDiscipline(self):
        self.student.remove_discipline('CSA')
        self.assertEqual(self.student.get_disciplines(), ['FP'])

    def test_str(self):
        self.assertEqual(str(self.student), 'ID: 1, Name: Test, Disciplines: CSA, FP, ')

    def test_eq(self):
        student_equal = Student('1', 'blah', [])
        student_not_equal = Student('2', 'blah2', ['Math'])
        self.assertEqual(self.student, student_equal)
        self.assertNotEqual(self.student, student_not_equal)


class TestStudentWithGrade(unittest.TestCase):
    """
    Class for testing the StudentWithGrade class
    """
    def setUp(self):
        self.student = StudentWithAverage('1', 'Test', 'CSA', 10)

    def test_getters(self):
        self.assertEqual(self.student.get_id(), '1')
        self.assertEqual(self.student.get_name(), 'Test')
        self.assertEqual(self.student.get_disciplines(), 'CSA')
        self.assertEqual(self.student.get_average_grade(), 10)

    def test_setters(self):
        self.student.set_name('bob')
        self.assertEqual(self.student.get_name(), 'bob')

    def test_str(self):
        self.assertEqual(str(self.student), 'ID: 1, Name: Test, Discipline: CSA, Average grade: 10')

    def test_eq(self):
        student_equal = StudentWithAverage('1', 'blah', [], 7)
        student_not_equal = StudentWithAverage('2', 'blah2', ['Math'], 4)
        self.assertEqual(self.student, student_equal)
        self.assertNotEqual(self.student, student_not_equal)

    def test_lt(self):
        student_lower_than = StudentWithAverage('2', 'LT', ['CSA'], 8)
        student_not_lower_than = StudentWithAverage('3', 'NLT', ['CDI'], 10)
        self.assertTrue(student_lower_than < self.student)
        self.assertFalse(student_not_lower_than < self.student)


class TestStudentWithSituation(unittest.TestCase):
    """
    Class for testing the StudentWithSituation class
    """

    def setUp(self):
        self.student = StudentWithSituation('1', 'Test', 10)

    def test_getters(self):
        self.assertEqual(self.student.get_id(), '1')
        self.assertEqual(self.student.get_name(), 'Test')
        self.assertEqual(self.student.get_average_grade(), 10)

    def test_setters(self):
        self.student.set_name('bob')
        self.assertEqual(self.student.get_name(), 'bob')

    def test_str(self):
        self.assertEqual(str(self.student), 'ID: 1, Name: Test, Average grade: 10')

    def test_eq(self):
        student_equal = StudentWithSituation('1', 'blah', 7)
        student_not_equal = StudentWithSituation('2', 'blah2', 4)
        self.assertEqual(self.student, student_equal)
        self.assertNotEqual(self.student, student_not_equal)

    def test_lt(self):
        student_lower_than = StudentWithAverage('2', 'LT', ['CSA'], 8)
        student_not_lower_than = StudentWithAverage('3', 'NLT', ['CDI'], 10)
        self.assertTrue(student_lower_than < self.student)
        self.assertFalse(student_not_lower_than < self.student)
