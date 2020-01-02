"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
import unittest


class Discipline:
    """
    Class for storing discipline objects
    """
    def __init__(self, discipline_id, discipline_name):
        """
        Constructor
        """
        self.__discipline_id = discipline_id
        self.__discipline_name = discipline_name

    def get_id(self):
        """
        Getter for the ID of the current discipline instance
        :return: The ID of the current discipline instance
        """
        return self.__discipline_id

    def get_name(self):
        """
        Getter for the discipline_name of the current discipline instance
        :return: The name of the current discipline instance
        """
        return self.__discipline_name

    def set_name(self, new_discipline_name):
        """
        Setter for the name of the current discipline instance
        :param new_discipline_name: The new name for the discipline
        :return: -
        """
        self.__discipline_name = new_discipline_name

    def __str__(self):
        """
        Overrides the str function for Discipline objects
        :return: A string containing the information about a discipline
        """
        return "ID: " + str(self.__discipline_id) + ", Name: " + str(self.__discipline_name)


class DisciplineWithAvg(Discipline):
    """
    Class for storing discipline with average grade objects
    """
    def __init__(self, discipline_id, discipline_name, average):
        """
        Constructor
        """
        Discipline.__init__(self, discipline_id, discipline_name)
        self.__average = average

    def get_average(self):
        """
        Getter for the average grade of a discipline
        :return: The average grade of a discipline
        """
        return self.__average

    def __lt__(self, other_discipline):
        """
        Overrides the relational operator "lower than" to compare average grades
        :param other_discipline: The discipline with which the current instance will be compared
        :return: True if the current discipline's average grade is lower than the other's, False otherwise
        """
        return self.__average < other_discipline.get_average()

    def __str__(self):
        """
        Overrides the str function for DisciplineWithAvg objects
        :return: A string containing the information about a discipline with average grade
        """
        return_string = "ID: " + str(self.get_id()) + \
               ", Name: " + str(self.get_name()) + \
               ", Average: " + str(self.__average)

        return return_string


class TestDiscipline(unittest.TestCase):
    """
    Class for testing the Discipline class
    """
    def setUp(self):
        self.discipline = Discipline('1', 'Test')

    def test_getters(self):
        self.assertEqual(self.discipline.get_name(), 'Test')
        self.assertEqual(self.discipline.get_id(), '1')

    def test_setters(self):
        self.discipline.set_name('test2')
        self.assertEqual(self.discipline.get_name(), 'test2')

    def test_str(self):
        self.assertEqual(str(self.discipline), 'ID: 1, Name: Test')


class TestDisciplineWithAvg(unittest.TestCase):
    """
    Class for testing the DisciplineWithAvg class
    """
    def setUp(self):
        self.discipline = DisciplineWithAvg('1', 'Test', 10)

    def test_getters(self):
        self.assertEqual(self.discipline.get_name(), 'Test')
        self.assertEqual(self.discipline.get_id(), '1')
        self.assertEqual(self.discipline.get_average(), 10)

    def test_lt(self):
        dLt = DisciplineWithAvg('2', 'LT', 9)
        dNLt = DisciplineWithAvg('3', 'NLT', 10)
        self.assertTrue(dLt < self.discipline)
        self.assertFalse(dNLt < self.discipline)

    def test_str(self):
        self.assertEqual(str(self.discipline), 'ID: 1, Name: Test, Average: 10')
