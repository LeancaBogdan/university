"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
from domain.DomainException import*


class StudentValidator:
    def __init__(self):
        pass

    @staticmethod
    def validate_id(student_id):
        if student_id == '':
            raise StudentException("Student ID cannot be empty!")

    @staticmethod
    def validate_name(student_name):
        if student_name == '':
            raise StudentException("Student discipline_name cannot be empty!")


class DisciplineValidator:
    def __init__(self):
        pass

    @staticmethod
    def validate_id(discipline_id):
        if discipline_id == '':
            raise DisciplineException("Discipline ID cannot be empty!")

    @staticmethod
    def validate_name(discipline_name):
        if discipline_name == '':
            raise DisciplineException("Discipline discipline_name cannot be empty!")


class GradeValidator:
    def __init__(self):
        pass

    @staticmethod
    def validate_student_id(student_id):
        if student_id == '':
            raise GradeException("Student ID cannot be empty!")

    @staticmethod
    def validate_discipline(discipline_id):
        if discipline_id == '':
            raise GradeException("Discipline ID or discipline_name cannot be empty!")

    @staticmethod
    def validate_grade_value(grade_value):
        if type(grade_value) != float and type(grade_value) != int:
            raise GradeException("Grade value must be a number!")
        if grade_value < 1:
            raise GradeException("Grade value must be greater than or equal to 1!")
        if grade_value > 10:
            raise GradeException("Grade value must be lower than or equal to 10!")
