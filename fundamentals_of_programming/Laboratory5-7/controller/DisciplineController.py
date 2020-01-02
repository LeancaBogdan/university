"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
import unittest
from repositories.sort import *
from repositories.StudentRepository import StudentRepository
from repositories.GradeRepository import GradeRepository
from controller.UndoController import Operation, FunctionCall
from repositories.DisciplineRepository import DisciplineRepository


class DisciplineController:
    """
    Controller for Disciplines
    """
    def __init__(self, discipline_repository, grade_repository):
        """
        Constructor
        """
        self.__discipline_repository = discipline_repository
        self.__grade_repository = grade_repository

    def get_repository(self):
        """
        Getter for the entire discipline repository
        :return: The discipline repository
        """
        return self.__discipline_repository

    def create_discipline(self, discipline_id, discipline_name):
        """
        Simulates an add_discipline to raise any eventual error
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's discipline_name
        :return:
        """
        self.__discipline_repository.test_discipline(discipline_id, discipline_name)

    def add_discipline(self, discipline_id, discipline_name):
        """
        Stores a discipline in the repository
        :param discipline_id: The ID of the new discipline
        :param discipline_name: The name of the new discipline
        :return: -
        :raises: RepoException: Discipline having the given ID already in the repository
        """
        self.__discipline_repository.store(discipline_id, discipline_name)

    def test_remove_discipline(self, discipline_id):
        """
        Simulates a remove_discipline to raise any eventual error
        :param discipline_id: Discipline's ID
        :return: -
        """
        self.__discipline_repository.test_remove(discipline_id)

    def remove_discipline(self, discipline_id):
        """
        Deletes a stored discipline from the repository
        :param discipline_id: The ID of the Discipline instance to be removed
        :return: -
        :raises: RepoException: No Discipline instance with the given ID found in repository
        """
        self.__discipline_repository.delete(discipline_id)

    def test_update_discipline(self, discipline_id, discipline_name):
        """
        Simulates an update_discipline to raise any eventual error
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's Name
        :return:
        """
        self.__discipline_repository.test_update(discipline_id, discipline_name)

    def update_discipline(self, discipline_id, discipline_name):
        """
        Updates a Discipline instance
        :param discipline_id: The ID of the discipline to be updated
        :param discipline_name: The new name of the discipline to be updated
        :return: -
        :raises: RepoException: The Discipline instance to be updated was not found
        """
        self.__discipline_repository.update(discipline_id, discipline_name)

    def get_name_from_id(self, discipline_id):
        """
        Gets the name of the discipline with the given ID from the repository
        :param discipline_id: The ID of the discipline to be searched for
        :return: The name of the discipline that was searched
        :raises: RepoException: Discipline with the given ID not in the repository
        """
        return self.__discipline_repository.get_name_by_id(discipline_id)

    def get_id_from_name(self, discipline_name):
        """
        Gets the ID of the discipline with the given name from the repository
        :param discipline_name: The name of the discipline to be searched for
        :return: The ID of the searched discipline
        :raises: RepoException: Discipline with the given discipline_name not in the repository
        """
        return self.__discipline_repository.get_id_by_name(discipline_name)

    def find(self, discipline_id):
        """
        Gets the discipline with the given ID from the repository
        :param discipline_id: The ID of the discipline to be searched for
        :return: The Discipline instance if it exists, None otherwise
        """
        return self.__discipline_repository.find_by_id(discipline_id)
    
    def find_by_name(self, name):
        """
        Gets the discipline with the given name from the repository
        :param name: The name of the discipline to be searched for
        :return: The discipline instance if it exists, None otherwise
        """
        return self.__discipline_repository.find_by_name(name)

    def search_by_id(self, id_substring):
        """
        Searches in the repository for disciplines with an ID that contains the given substring
        :param id_substring: The substring to be contained by the ID attribute of the discipline
        :return: A list of all the Discipline instances that contain the given substring in
         the ID attribute
        :raises: RepoException: No discipline was found
        """
        return self.__discipline_repository.search_disciplines_by_id_substring(id_substring)

    def search_by_name(self, search_name):
        """
        Searches in the repository for disciplines with a name that contains the given substring
        :param search_name: The substring to be contained by the name attribute of the discipline
        :return: A list of all the Discipline instances that contain the given substring in
         the name attribute
        :raises: RepoException: No discipline was found
        """
        return self.__discipline_repository.search_disciplines_by_name_substring(search_name)

    def get_all(self):
        """
        Gets all the disciplines in the repository, sorted by name
        :return: A list of all the Discipline instances in the repository, sorted by name
        :raises: RepoException: The repository is empty
        """
        list_of_disciplines = self.__discipline_repository.get_all()

        def cmp_by_name(discipline_1, discipline_2):
            return discipline_1.get_name() < discipline_2.get_name()

        gnome_sort(list_of_disciplines, cmp_by_name)

        return list_of_disciplines
    
    def __str__(self):
        """
        Overrides the str method for DisciplineController instances
        :return: A string containing the string form of all the Discipline objects in the repository
        :exception: RepoException: The discipline repository is empty
        """
        return str(self.__discipline_repository)


class TestDisciplineController(unittest.TestCase):
    """
    Class for testing the DisciplineController class
    """
    def setUp(self):
        self.discRepo = DisciplineRepository()
        self.stRepo = StudentRepository()
        self.gradeRepo = GradeRepository(self.discRepo, self.stRepo)
        self.discCont = DisciplineController(self.discRepo, self.gradeRepo)
        self.discRepo.store('1', 'test1')

    def test_addDiscipline_find_findByName(self):
        self.discCont.add_discipline('2', 'test2')
        self.assertEqual(self.discCont.find('2'), self.discCont.find_by_name('test2'))
        self.assertEqual(self.discCont.find('1'), self.discCont.find_by_name('test1'))

    def test_removeDiscipline_getAll(self):
        self.assertEqual(self.discCont.get_all(), [self.discCont.find('1')])
        self.discCont.remove_discipline('1')
        self.assertIsNone(self.discCont.find('1'))

    def test_updateDiscipline(self):
        self.discCont.update_discipline('1', 't')
        self.assertEqual(self.discCont.find_by_name('t'), self.discCont.find('1'))

    def test_getNameID_getIDName(self):
        self.assertEqual(self.discCont.get_name_from_id('1'), 'test1')
        self.assertEqual(self.discCont.get_id_from_name('test1'), '1')

    def test_searchID_searchName(self):
        self.assertEqual(self.discCont.search_by_id('1'), self.discCont.search_by_name('test1'))
        self.assertEqual(self.discCont.search_by_id('1'), [self.discCont.find_by_name('test1')])
        self.assertEqual(self.discCont.search_by_name('test1'), [self.discCont.find('1')])

    def test_str(self):
        self.assertEqual(str(self.discCont), 'Disciplines:\nID: 1, Name: test1\n')


class DisciplineControllerWithUndo(DisciplineController):
    """
    Controller for disciplines with undo/redo functionality
    """
    def __init__(self, discipline_repository, grade_repository, undo_controller):
        """
        Constructor
        """
        DisciplineController.__init__(self, discipline_repository, grade_repository)
        self.__undoController = undo_controller

    def add_discipline(self, discipline_id, discipline_name):
        """
        Override for the add_discipline method in the super class, also records the corresponding methods and their
        params for undo/redo capability
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's name
        :return: -
        """
        self.create_discipline(discipline_id, discipline_name)
        self.__undoController.new_operation()
        undo_function = FunctionCall(self.get_repository().delete, discipline_id)
        redo_function = FunctionCall(self.get_repository().store, discipline_id, discipline_name)
        operation = Operation(redo_function, undo_function)
        self.__undoController.record_operation(operation)
        self.get_repository().store(discipline_id, discipline_name)

    def remove_discipline(self, discipline_id):
        """
        Override for the test_remove method in the super class, also records the corresponding methods and their
        params for undo/redo capability
        :param discipline_id: Discipline's ID
        :return: -
        """
        self.test_remove_discipline(discipline_id)
        self.__undoController.new_operation()
        discipline = self.find(discipline_id)
        undo_function = FunctionCall(self.get_repository().store, discipline.get_id(), discipline.get_name())
        redo_function = FunctionCall(self.get_repository().delete, discipline.get_id())
        operation = Operation(redo_function, undo_function)
        self.__undoController.record_operation(operation)
        self.__discipline_repository.delete(discipline_id)

    def update_discipline(self, discipline_id, discipline_name):
        """
        Override for the update_discipline method in the super class, also records the corresponding methods and their
        params for undo/redo capability
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's name
        :return:
        """
        self.test_update_discipline(discipline_id, discipline_name)
        self.__undoController.new_operation()
        discipline = self.find(discipline_id)
        undo_operation = FunctionCall(self.get_repository().update, discipline.get_id(), discipline.get_name())
        redo_operation = FunctionCall(self.get_repository().update, discipline_id, discipline_name)
        operation = Operation(redo_operation, undo_operation)
        self.__undoController.record_operation(operation)
        self.get_repository().update(discipline_id, discipline_name)
