"""
Created on 24 nov. 2016

@author: bogdanleanca
"""


class DisciplineException(Exception):
    """
    Class for exceptions regarding disciplines
    """
    def __init__(self, message):
        """
        Constructor
        """
        self._message = message

    def get_message(self):
        """
        Getter for the message
        :return: The message
        """
        return self._message

    def __str__(self):
        """
        Override for the str function
        :return: String containing the exception message
        """
        return self._message


class StudentException(Exception):
    """
    Class for exceptions regarding students
    """
    def __init__(self, message):
        """
        Constructor
        """
        self._message = message

    def get_message(self):
        """
        Getter for the message
        :return: The message
        """
        return self._message

    def __str__(self):
        """
        Override for the str function
        :return: String containing the exception message
        """
        return self._message


class GradeException(Exception):
    """
    Class for exceptions regarding grades
    """
    def __init__(self, message):
        """
        Constructor
        """
        self._message = message

    def get_message(self):
        """
        Getter for the message
        :return: The message
        """
        return self._message

    def __str__(self):
        """
        Override for the str function
        :return: String containing the exception message
        """
        return self._message
