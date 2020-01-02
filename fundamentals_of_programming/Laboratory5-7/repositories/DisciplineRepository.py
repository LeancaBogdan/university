"""
Created on 24 nov. 2016

@author: bogdanleanca
"""
import unittest
from repositories.iterable import*
from repositories.RepositoryException import RepositoryException
from domain.Validators import DisciplineValidator
from domain.Discipline import Discipline
import pickle
import os


class DisciplineRepository:
    """
    Repository for Discipline instances
    """
    def __init__(self):
        """
        Constructor
        """
        self.__disciplines = MyList()
        self.__validator = DisciplineValidator()

    def set_list_of_disciplines(self, new_list_of_disciplines):
        """
        Setter for the whole list of disciplines, used by the binary repository
        :param new_list_of_disciplines: The new list of disciplines
        :return: -
        """
        self.__disciplines = new_list_of_disciplines

    def find_by_id(self, discipline_id):
        """
        Searches for a Discipline instance with the given ID in the repository
        :param discipline_id: The ID of the Discipline instance to be searched for
        :return: The Discipline instance if it exists, None otherwise
        """
        self.__validator.validate_id(discipline_id)

        for discipline in self.__disciplines:
            if discipline.get_id() == discipline_id:
                return discipline

        return None
    
    def find_by_name(self, discipline_name):
        """
        Searches for a Discipline instance with the given name in the repository
        :param discipline_name: The name of the Discipline instance to be searched for
        :return: The discipline instance if it exists, None otherwise
        """
        self.__validator.validate_name(discipline_name)

        for discipline in self.__disciplines:
            if discipline_name == discipline.get_name():
                return discipline

        return None

    def get_name_by_id(self, discipline_id):
        """
        Getter for the discipline_name of the Discipline instance with the given ID
        :param discipline_id: The ID of the Discipline instance to be searched for
        :return: The name of the searched discipline if it exists
        :raises: RepoException: Discipline with the given ID not in the repository
        """
        self.__validator.validate_id(discipline_id)

        for discipline in self.__disciplines:
            if discipline.get_id() == discipline_id:
                return discipline.get_name()

        raise RepositoryException("Discipline with the given ID not in the repository!")

    def get_id_by_name(self, discipline_name):
        """
        Getter for the ID of the Discipline instance with the given discipline_name
        :param discipline_name: The name of the Discipline instance to be searched for
        :return: The ID of the searched discipline if it exists
        :raises: RepoException: Discipline with the given name not in the repository
        """
        self.__validator.validate_name(discipline_name)

        for discipline in self.__disciplines:
            if discipline_name == discipline.get_name():
                return discipline.get_id()

        raise RepositoryException("Discipline with the given discipline_name not in the repository!")

    def search_disciplines_by_id_substring(self, search_substring):
        """
        Searches for Discipline instances in the repository by a substring to be contained in the ID attribute
        :param search_substring: The substring to be contained by the ID attribute
        :return: A list of all the Discipline instances that contain the given substring in
         the ID attribute
        :exception: RepoException: No discipline was found
        """
        result = []

        for discipline in self.__disciplines:
            if search_substring in discipline.get_id():
                result.append(discipline)

        if len(result) == 0:
            raise RepositoryException("No discipline was found.")

        return result

    def search_disciplines_by_name_substring(self, search_substring):
        """
        Searches for Discipline instances in the repository by a substring to be contained
         in the name attribute
        :param search_substring: The substring to be contained by the name attribute
        :return: A list of all the Discipline instances that contain the given
         substring in the name attribute
        :raises: RepoException: No discipline was found
        """
        result = []

        for discipline in self.__disciplines:
            if search_substring in discipline.get_name():
                result.append(discipline)

        if len(result) == 0:
            raise RepositoryException("No discipline was found.")

        return result

    def store(self, discipline_id, discipline_name):
        """
        Stores a Discipline instance in the repository
        :param discipline_id: The ID of the discipline to be stored in the repository
        :param discipline_name: The name of the discipline to be stored in the repository
        :return: -
        :raises: RepoException: Discipline having the given ID already in the repository
        """
        self.__validator.validate_id(discipline_id)
        self.__validator.validate_name(discipline_name)

        if self.find_by_id(discipline_id) is not None:
            raise RepositoryException("Discipline having ID " + str(discipline_id) + " already in the repository!")

        self.__disciplines.append(Discipline(discipline_id, discipline_name))

    def test_discipline(self, discipline_id, discipline_name):
        """
        Simulates a store, raises any eventual exceptions
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's name
        :return: -
        """
        self.__validator.validate_id(discipline_id)
        self.__validator.validate_name(discipline_name)

        if self.find_by_id(discipline_id) is not None:
            raise RepositoryException("Discipline having ID " + str(discipline_id) + " already in the repository!")

    def test_remove(self, discipline_id):
        """
        Simulates a delete, raises any eventual exceptions
        :param discipline_id: Discipline's ID
        :return: -
        """
        self.__validator.validate_id(discipline_id)

        discipline = self.find_by_id(discipline_id)
        if discipline is None:
            raise RepositoryException("Discipline not found!")

    def test_update(self, discipline_id, discipline_name):
        """
        Simulates an update_discipline, raises any eventual exceptions
        :param discipline_id: Discipline's ID
        :param discipline_name: Discipline's name
        :return: -
        """
        self.__validator.validate_id(discipline_id)
        self.__validator.validate_name(discipline_name)

        discipline = self.find_by_id(discipline_id)
        if discipline is None:
            raise RepositoryException("Discipline not found!")

    def update(self, discipline_id, discipline_name):
        """
        Updates a Discipline instance in the repository
        :param discipline_id: The ID of the discipline in the repository to be updated
        :param discipline_name: The new name of the discipline to be updated
        :return: -
        :raises: RepoException: The Discipline instance to be updated was not found
        """
        self.__validator.validate_id(discipline_id)
        self.__validator.validate_name(discipline_name)

        old_discipline = self.delete(discipline_id)
        if old_discipline is None:
            raise RepositoryException("No discipline with the given ID!")

        self.store(discipline_id, discipline_name)

    def delete(self, discipline_id):
        """
        Deletes a Discipline instance from the repository based on the ID
        :param discipline_id: The ID of the Discipline instance to  be removed from the repository
        :return: The removed Discipline instance
        :raises: RepoException: No Discipline instance with the given ID found in repository
        """
        self.__validator.validate_id(discipline_id)

        discipline = self.find_by_id(discipline_id)
        if discipline is None:
            raise RepositoryException("Discipline not found!")
        self.__disciplines.remove(discipline)

        return discipline

    def get_all(self):
        """
        Getter for the list of Discipline instances in the repository
        :return: The list of Discipline instances in the repository
        :exceptions: RepoException: The repository is empty
        """
        return_list = []

        for discipline in self.__disciplines:
            return_list.append(discipline)

        if len(return_list) == 0:
            raise RepositoryException("The repository is empty!")
        return return_list

    def __len__(self):
        """
        Overrides the len function for DisciplineRepository objects
        :return: The number of Discipline instances contained by the repository
        """
        return len(self.__disciplines)

    def __str__(self):
        """
        Overrides the str function for DisciplineRepository objects
        :return: A string containing the string form of all the Discipline objects in the repository
        :raises: RepoException: The discipline repository is empty
        """
        if len(self.__disciplines) == 0:
            raise RepositoryException("Discipline repository is empty!")

        return_string = "Disciplines:\n"
        for disc in self.__disciplines:
            return_string += str(disc)
            return_string += "\n"

        return return_string


class DisciplineRepositoryCSV(DisciplineRepository):
    """
    Class for storing Discipline instances, using a CSV file for read/write
    """
    def __init__(self):
        DisciplineRepository.__init__(self)
        self.__filename = os.path.join(".", "DisciplineRepository.csv")

    def read_file(self):
        try:
            with open(self.__filename, 'r') as f:
                line = f.readline().strip()
                while len(line) > 0:
                    line = line.split(',')
                    self.store(line[0], line[1])
                    line = f.readline().strip()
        except IOError as ie:
            print(ie)

    def write_file(self):
        try:
            with open(self.__filename, 'w') as f:
                for discipline in self.get_all():
                    discipline_string = discipline.get_id() + "," + discipline.get_name() + "\n"
                    f.write(discipline_string)
        except IOError as ie:
            print(ie)
        except RepositoryException:
            pass


class DisciplineRepositoryBinary(DisciplineRepository):
    def __init__(self):
        DisciplineRepository.__init__(self)
        self.__filename =  "DisciplineRepository.pickle"

    def get_file_name(self):
        return self.__filename

    def write_file(self):
        try:
            with open(self.get_file_name(), 'wb') as f:
                pickle.dump(self.get_all(), f)
        except IOError as e:
            print("An error occured - " + str(e))
            raise e

    def read_file(self):
        try:
            with open(self.get_file_name(), 'rb') as f:
                self.set_list_of_disciplines(pickle.load(f))
        except EOFError:
            self.__disciplines = []
        except IOError as e:
            print("An error occurred - " + str(e))
            raise e


class TestDisciplineRepo(unittest.TestCase):
    """
    Class for testing the DisciplineRepo class
    """
    def setUp(self):
        self.disciplines = DisciplineRepository()
        self.disciplines.store('1', 'test1')
        self.disciplines.store('2', 'test2')

    def test_all(self):
        self.assertEqual(
            self.disciplines.get_all(),
            [self.disciplines.find_by_name('test1'), self.disciplines.find_by_id('2')]
        )
        self.assertEqual(self.disciplines.find_by_name('test1'), self.disciplines.find_by_id('1'))
        self.assertIsNone(self.disciplines.find_by_name('abc'))
        self.assertEqual(self.disciplines.find_by_id('2'), self.disciplines.find_by_name('test2'))
        self.disciplines.delete('2')
        self.assertIsNone(self.disciplines.find_by_id('2'))
        self.assertEqual(self.disciplines.get_name_by_id('1'), 'test1')
        self.assertEqual(self.disciplines.get_id_by_name('test1'), '1')
        self.assertEqual(self.disciplines.search_disciplines_by_id_substring('1'), [self.disciplines.find_by_id('1')])
        self.disciplines.update('1', 'FP')
        self.assertEqual(self.disciplines.find_by_id('1'), self.disciplines.find_by_name('FP'))
        self.assertEqual(
            self.disciplines.search_disciplines_by_name_substring('FP'),
            [self.disciplines.find_by_id('1')]
        )
        self.assertEqual(str(self.disciplines.find_by_id('1')), 'ID: 1, Name: FP')
