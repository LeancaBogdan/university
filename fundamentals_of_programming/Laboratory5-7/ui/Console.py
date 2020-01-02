"""
Created on 24 nov. 2016

@author: bogdanleanca
"""

from domain.Validators import *
from domain.DomainException import *
from repositories.RepositoryException import RepositoryException


class Console:
    """
    Class for defining the Console
    """

    def __init__(self, student_controller, discipline_controller, grade_controller, undo_controller):
        self.__student_controller = student_controller
        self.__discipline_controller = discipline_controller
        self.__grade_controller = grade_controller
        self.__undo_controller = undo_controller
        self.__student_validator = StudentValidator()
        self.__discipline_validator = DisciplineValidator()
        self.__grade_validator = GradeValidator()

    @staticmethod
    def __ui_read_command(message):
        """
        Reads a command from the console
        :param message: The message to be printed before reading the command
        :return: A string consisting in the command
        """
        print(message)
        return input("Please give a command: ")

    def main_menu(self):
        """
        The main menu of the application. Prints the available options and then reads the command from the user and
        calls the corresponding submenu method
        :return: -
        """
        menu_string = "Main menu\n"
        menu_string += "\t1. Modify a list\n"
        menu_string += "\t2. Grade submenu\n"
        menu_string += "\t3. Search for something\n"
        menu_string += "\t4. Get a statistic\n"
        menu_string += "\t5. Undo/Redo\n"
        menu_string += "\t0. Exit\n"
        stop = False

        while not stop:
            command_list = \
                {'0': self.__no_command,
                 '1': self.__modify_submenu,
                 '2': self.__grade_submenu,
                 '3': self.__search_submenu,
                 '4': self.__statistics_submenu,
                 '5': self.__undo_submenu
                 }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __modify_submenu(self):
        """
        Submenu corresponding to the first functionality of the app, working with the repositories. Prints the available
        options and then reads the command from the user
        and calls the corresponding method.
        :return: -
        """
        menu_string = "Modify submenu\n"
        menu_string += "\t1. Modify the list of students\n"
        menu_string += "\t2. Modify the list of disciplines\n"
        menu_string += "\t0. Exit\n"
        stop = False

        while not stop:
            command_list = \
                {
                    '1': self.__ui_modify_student,
                    '2': self.__ui_modify_discipline,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __ui_modify_student(self):
        """
        Submenu for modifying the students repository. Prints the available options and then reads the command from
        the user and calls the corresponding method
        :return:
        """
        menu_string = "Modify the list of students submenu\n"
        menu_string += "\t1. Add a student\n"
        menu_string += "\t2. Remove a student\n"
        menu_string += "\t3. Update a student\n"
        menu_string += "\t4. Print the list of students\n"
        menu_string += "\t0. Exit\n"
        stop = False

        while not stop:
            command_list = \
                {
                    '1': self.__ui_add_student,
                    '2': self.__ui_remove_student,
                    '3': self.__ui_update_student,
                    '4': self.__ui_list_students,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __ui_add_student(self):
        """
        Reads the information of a new student and then adds it to the repository using the controller
        :return: -
        """
        student_id = input("student_id: ")
        student_name = input("student_name: ")

        print("Give disciplines for student, enter for done")
        disciplines_list = []

        discipline_name = '0'
        while discipline_name != '':
            discipline_name = input("Discipline discipline_name: ")
            if discipline_name == '':
                break
            elif self.__discipline_controller.find_by_name(discipline_name) is not None:
                disciplines_list.append(discipline_name)
                print("Add discipline successful\n")
            else:
                print("Invalid discipline!")

        try:
            self.__student_controller.add_student(student_id, student_name, disciplines_list)
            print("Add student successful\n")
        except StudentException as se:
            print(se)
            return
        except RepositoryException as re:
            print(re)
            return

    def __ui_remove_student(self):
        """
        Reads the id of the student to be removed from the repository and then removes it from the repositories
        :return: -
        """
        student_id = input("student_id: ")

        try:
            self.__student_controller.remove_student(student_id)
            self.__grade_controller.delete_by_student(student_id)
            print("Remove successful\n")

        except StudentException as se:
            print(se)
            return

        except RepositoryException as re:
            print(re)
            return

        except GradeException as ge:
            print(ge)
            return

    def __ui_update_student(self):
        """
        Reads the new information for the student to be updated and updates it in the repositories
        :return:
        """
        student_id = input("student id: ")
        student_name = input("student discipline_name: ")
        disciplines_list = []

        discipline_name = None
        while discipline_name != '':
            discipline_name = input("Discipline discipline_name: ")
            if discipline_name == '':
                break
            elif self.__discipline_controller.find_by_name(discipline_name) is not None:
                disciplines_list.append(discipline_name)
                print("Add discipline successful\n")
            else:
                print("Invalid discipline!")

        try:
            self.__student_controller.update_student(student_id, student_name, disciplines_list)
            print("Update student successful\n")
        except StudentException as se:
            print(se)
            return
        except RepositoryException as re:
            print(re)
            return

    def __ui_list_students(self):
        """
        Prints the list of all the students in the repository
        :return: -
        """
        try:
            print(str(self.__student_controller))
        except RepositoryException as re:
            print(re)
            return

    def __ui_modify_discipline(self):
        """
        Submenu for modifying the discipline repository. Prints the available options and then reads the command from
        the user and calls the corresponding method
        :return:
        """
        menu_string = "Modify the list of disciplines submenu\n"
        menu_string += "\t1. Add a discipline\n"
        menu_string += "\t2. Remove a discipline\n"
        menu_string += "\t3. Update a discipline\n"
        menu_string += "\t4. Print the list of disciplines\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = \
                {
                    '1': self.__ui_add_discipline,
                    '2': self.__ui_remove_discipline,
                    '3': self.__ui_update_discipline,
                    '4': self.__ui_list_disciplines,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __ui_add_discipline(self):
        """
        Reads the information of a new discipline and then adds it to the repository
        :return: -
        """
        discipline_id = input("discipline id: ")
        discipline_name = input("discipline discipline_name: ")

        try:
            self.__discipline_controller.add_discipline(discipline_id, discipline_name)
            print("Add successful\n")
        except DisciplineException as de:
            print(de)
            return
        except RepositoryException as re:
            print(re)
            return

    def __ui_remove_discipline(self):
        """
        Reads the discipline_id of the discipline to be removed from the repository and then removes it
         from the repositories
        :return: -
        """
        discipline_id = input("discipline id: ")

        try:
            self.__discipline_controller.test_remove(discipline_id)
            self.__grade_controller.delete_by_discipline(discipline_id)
            print("Remove successful\n")
        except DisciplineException as de:
            print(de)
            return
        except RepositoryException as re:
            print(re)
            return

    def __ui_update_discipline(self):
        """
        Reads the new information for the discipline to be updated and updates it in the repositories
        :return:
        """
        discipline_id = input("discipline id: ")

        try:
            discipline_name = input("new discipline discipline_name: ")
            self.__discipline_controller.update_discipline(discipline_id, discipline_name)
            print("Update successful\n")
        except DisciplineException as de:
            print(de)
            return
        except RepositoryException as re:
            print(re)
            return

    def __ui_list_disciplines(self):
        """
        Prints the list of all the disciplines in the repository
        :return: -
        """
        try:
            print(str(self.__discipline_controller))

        except RepositoryException as re:
            print(re)
            return

    def __grade_submenu(self):
        """
        Submenu for modifying the grade repository. Prints the available options and then reads the command from the
        user and calls the corresponding method
        :return:
        """
        menu_string = "Grade submenu\n"
        menu_string += "\t1. Grade a student\n"
        menu_string += "\t2. List all grades of a student\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = \
                {
                    '1': self.__ui_grade_student,
                    '2': self.__ui_list_grades_by_student,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __ui_grade_student(self):
        """
        Reads the information about the graade to be added to the repository and, if valid,
        stores it.
        :return: -
        """
        student_id = input("Give student ID: ")
        discipline_name = input("Give discipline discipline_name: ")

        try:
            grade_value = input("Give grade: ")
            if not self.__student_controller.student_has_discipline(student_id, discipline_name):
                print("The student isn't enrolled at the given discipline!")
                return
            self.__grade_controller.add_grade(
                student_id,
                self.__discipline_controller.get_id_by_name(discipline_name),
                grade_value
            )
            print("Grade successful! \n")

        except GradeException as ge:
            print(ge)
            return
        except StudentException as se:
            print(se)
            return
        except RepositoryException as re:
            print(re)
            return
        except ValueError as ve:
            print(ve)
            return

    def __ui_list_grades_by_student(self):
        """
        Prints a list of all the grades of a student given by it's ID
        :return: -
        """
        student_id = input("Give student ID: ")
        try:
            list_of_grades = self.__grade_controller.get_grades_by_student(student_id)
            if len(list_of_grades) == 0:
                print("Student doesn't have any grade.")
                return

            for g in list_of_grades:
                print(str(g))

        except GradeException as ge:
            print(ge)
            return

    def __search_submenu(self):
        """
        Submenu for the search_substring functionality. Prints the available options and then reads the command
        from the user and calls the corresponding method
        :return: -
        """
        menu_string = "Search submenu\n"
        menu_string += "\t1. Search for a student\n"
        menu_string += "\t2. Search for a discipline\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = \
                {
                    '1': self.__search_student,
                    '2': self.__search_discipline,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()

            else:
                print("Invalid command!")

    def __search_student(self):
        """
        Submnenu for the search_substring functionality in the students repository. Prints the available options and
         then reads the command from the user and calls the corresponding method
        :return:
        """
        menu_string = "Search for a student:\n"
        menu_string += "\t1. by ID\n"
        menu_string += "\t2. by discipline_name\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = \
                {
                    '1': self.__ui_search_student_by_id,
                    '2': self.__ui_search_student_by_name,
                    '0': self.__no_command
                }
            command = self.__ui_read_command(menu_string)

            if command == '0':
                return

            search = input("Enter search_substring string: ")
            if len(search) == 0:
                print("Search string cannot be empty!")
                return

            if command in command_list.keys():
                command_list[command](search)
            else:
                print("Invalid command!")

    def __ui_search_student_by_id(self, search):
        """
        Searches students whose IDs match the given substring and prints them
        :param search: The search_substring string
        :return: -
        """
        try:
            result = self.__student_controller.search_by_id(search)
            for student in result:
                print(str(student))

        except RepositoryException as re:
            print(re)
            return

    def __ui_search_student_by_name(self, search):
        """
        Searches students whose Names match the given substring and prints them
        :param search: The search_substring string
        :return: -
        """
        try:
            result = self.__student_controller.search_by_name(search)
            for student in result:
                print(str(student))

        except RepositoryException as re:
            print(re)
            return

    def __search_discipline(self):
        """
        Submenu for the search_substring functionality in the discipline repository. Prints the available options and
        then reads the command from the user and calls the corresponding method
        :return:
        """
        menu_string = "Search for a discipline:\n"
        menu_string += "\t1. by ID\n"
        menu_string += "\t2. by discipline_name\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = {
                '1': self.__ui_search_discipline_by_id,
                '2': self.__ui_search_discipline_by_name,
                '0': self.__no_command
            }
            command = self.__ui_read_command(menu_string)

            if command == '0':
                return

            search = input("Enter search_substring string: ")
            if len(search) == 0:
                print("Search string cannot be empty!")
                return

            if command in command_list.keys():
                command_list[command](search)
            else:
                print("Invalid command!")

    def __ui_search_discipline_by_id(self, search):
        """
        Searches disciplines whose IDs match the given substring and prints them
        :param search: The search_substring string
        :return: -
        """
        try:
            result = self.__discipline_controller.search_by_id(search)
            for discipline in result:
                print(str(discipline))

        except RepositoryException as re:
            print(re)
            return

    def __ui_search_discipline_by_name(self, search):
        """
        Searches disciplines whose Names match the given substring and prints them
        :param search: The search_substring string
        :return: -
        """
        try:
            result = self.__discipline_controller.search_by_name(search)
            for discipline in result:
                print(str(discipline))

        except RepositoryException as re:
            print(re)
            return

    def __statistics_submenu(self):
        """
        Submenu for the statistics functionality. Prints the available options and then reads the command from the user
         and calls the corresponding method
        :return:
        """
        menu_string = "Statistics submenu\n"
        menu_string += "\t1. Students enrolled at a discipline\n"
        menu_string += "\t2. Students failing at a discipline\n"
        menu_string += "\t3. Students with best school situation\n"
        menu_string += "\t4. Disciplines with at least one grade\n"
        menu_string += "\t0. Exit\n"

        stop = False
        while not stop:
            command_list = {
                '1': self.__statistics_students_enrolled,
                '2': self.__statistics_students_failing,
                '3': self.__statistics_best_situation,
                '4': self.__statistics_disciplines_graded,
                '0': self.__no_command
            }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()
            else:
                print("Invalid command!")

    def __statistics_students_enrolled(self):
        """
        Submenu for the students enrolled sub-functionality of the statistics functionality.
        Prints the available options and then reads the command from the user and calls the corresponding method
        :return:
        """
        try:
            discipline_name = input("Give discipline discipline_name: ")
            self.__discipline_validator.validate_name(discipline_name)
        except DisciplineException as de:
            print(de)
            return

        menu_string = "\t1. Sort alphabetically \n\t" \
                      "2. Sort descending by average \n\t" \
                      "0. Exit"
        command = self.__ui_read_command(menu_string)

        if command == '1':
            self.__ui_statistics_sort_alpha(discipline_name)
        elif command == '2':
            self.__ui_statistics_sort_avg(discipline_name)
        elif command == '0':
            return

    def __ui_statistics_sort_alpha(self, discipline_name):
        """
        Prints all the student enrolled at the given discipline, sorted alphabetically by their names
        :param discipline_name: The discipline_name of the discipline for which the students are considered
        :return: -
        """
        sorted_list = self.__student_controller.get_sorted_students_for_discipline(discipline_name)
        if len(sorted_list) == 0:
            print("There is no student enrolled at the given discipline!")
            return

        for student in sorted_list:
            print(str(student) + "\n")

    def __ui_statistics_sort_avg(self, discipline_name):
        """
        Prints all the student enrolled at the given discipline, sorted descending by their average grade
         at the given discipline
        :param discipline_name: The discipline_name of the discipline for which the students are considered
        :return: -
        """
        try:
            sorted_list = self.__grade_controller.get_averages_at_discipline_sorted_descending(discipline_name)
            if len(sorted_list) == 0:
                print("There is no student graded at the given discipline!")
                return

            for student in sorted_list:
                print(str(student) + "\n")

        except GradeException as ge:
            print(ge)
            return

    def __statistics_students_failing(self):
        """
        Prints all the failing students
        :return: -
        """
        students_list = self.__grade_controller.get_list_of_failing_students()
        if len(students_list) == 0:
            print("There is no student failing!")
            return

        for student in students_list:
            print(str(student) + "\n")

    def __statistics_best_situation(self):
        """
        Prints the students with the best situation
        :return: -
        """
        students_list = self.__grade_controller.get_list_of_students_with_best_situation()
        if len(students_list) == 0:
            print("There is no student with a grade!")
            return

        for student in students_list:
            print(str(student) + "\n")

    def __statistics_disciplines_graded(self):
        """
        Prints a list of the disciplines at which at least a grade is stored
        :return: -
        """
        disciplines_list = self.__grade_controller.get_list_of_graded_disciplines()
        if len(disciplines_list) == 0:
            print("There is no graded discipline!")
            return

        for discipline in disciplines_list:
            print(str(discipline) + "\n")

    def __undo_submenu(self):
        """
        Submenu for the undo/redo functionality
        :return: -
        """
        menu_string = "Undo/Redo submenu\n"
        menu_string += "\t1. Undo the last performed operation\n"
        menu_string += "\t2. Redo the last undone operation\n"
        menu_string += "\t0. Exit\n"

        while True:
            command_list = {
                '1': self.__undo,
                '2': self.__redo,
                '0': self.__no_command
            }
            command = self.__ui_read_command(menu_string)

            if command in command_list.keys():
                if command == '0':
                    return
                else:
                    command_list[command]()
            else:
                print("Invalid command!")

    def __undo(self):
        """
        Undoes the last performed operation that can be undone
        :return: -
        """
        self.__undo_controller.undo()

    def __redo(self):
        """
        Redoes the last undone operation
        :return: -
        """
        self.__undo_controller.redo()

    def __no_command(*args):
        """
        Function that does nothing, but can be called in case the user wants to exit a certain submenu.
        Can have variable number of arguments
        :return: -
        """
        pass
