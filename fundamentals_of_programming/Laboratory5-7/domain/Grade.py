"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
import unittest


class Grade:
    """
    Class for storing grade objects
    """
    def __init__(self, discipline_id, discipline_name, student_id, student_name, grade_value):
        """
        Constructor
        """
        self.__discipline_id = discipline_id
        self.__discipline_name = discipline_name
        self.__student_id = student_id
        self.__student_name = student_name
        self.__grade_value = grade_value
        
    def get_grade(self):
        """
        Getter for the grade value of the current grade instance
        :return: The grade value of the current grade instance
        """
        return self.__grade_value
    
    def get_student_id(self):
        """
        Getter for the student ID of the current grade instance
        :return: The student ID of the current grade instance
        """
        return self.__student_id
    
    def get_discipline_id(self):
        """
        Getter for the discipline ID of the current grade instance
        :return: The discipline ID of the current grade instance
        """
        return self.__discipline_id

    def get_discipline_name(self):
        """
        Getter for the discipline's name for the current Grade instance
        :return: The discipline's name for the current Grade instance
        """
        return self.__discipline_name

    def get_student_name(self):
        """
        Getter for the student's name for the current Grade instance
        :return: The student's name for the current Grade instance
        """
        return self.__student_name

    def __str__(self):
        """
        Overrides the str function for grade instances
        :return: A string containing the information about a grade
        """
        return str(self.__student_name) + " has grade " + str(self.__grade_value) + " at " + str(self.__discipline_name)


class TestGrade(unittest.TestCase):
    """
    Class for testing the Grade class
    """
    def setUp(self):
        self.grade = Grade('1', 'FP', '1', 'Test', 10)

    def test_getters(self):
        self.assertEqual(self.grade.get_discipline_id(), '1')
        self.assertEqual(self.grade.get_grade(), 10)
        self.assertEqual(self.grade.get_student_id(), '1')

    def test_str(self):
        self.assertEqual(str(self.grade), 'Test has grade 10 at FP')