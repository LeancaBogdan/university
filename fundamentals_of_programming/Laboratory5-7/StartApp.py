"""
Created on 25 nov. 2016

@author: bogdanleanca
"""

from controller.DisciplineController import DisciplineControllerWithUndo
from controller.GradeController import GradeControllerWithUndo
from controller.StudentController import StudentControllerWithUndo
from controller.UndoController import UndoController
from repositories.DisciplineRepository import *
from repositories.GradeRepository import *
from repositories.StudentRepository import *
from ui.Console import Console


def repo_choice():
    """
        Creates the repositories
    """
    choice_string = "Available options:\n"
    choice_string += "\t1. Use RAM repositories, will delete after app closes\n"
    choice_string += "\t2. Use CSV repositories\n"
    choice_string += "\t3. Use binary repositories\n"
    print(choice_string)
    command = input("Please choose an option: ")

    student_repository = None
    discipline_repository = None
    grade_repository = None

    if command == '1':

        student_repository = StudentRepository()
        discipline_repository = DisciplineRepository()
        grade_repository = GradeRepository(student_repository, discipline_repository)

    elif command == '2':
        student_repository = StudentRepositoryCSV()
        student_repository.read_file()
        discipline_repository = DisciplineRepositoryCSV()
        discipline_repository.read_file()
        grade_repository = GradeRepositoryCSV(student_repository, discipline_repository)
        grade_repository.read_file()

    elif command == '3':
        student_repository = StudentRepositoryBinary()
        student_repository.read_file()
        discipline_repository = DisciplineRepositoryBinary()
        discipline_repository.read_file()
        grade_repository = GradeRepositoryBinary(student_repository, discipline_repository)
        grade_repository.read_file()

    else:
        print("Invalid command!")
        repo_choice()

    return [student_repository, discipline_repository, grade_repository]


def add_mock_data_to_repos(student_repository, discipline_repository, grade_repository):
    """
        Adds some entries to the repositories
    """
    student_repository.store('2069', 'Bob Alexandra-Diana', ['FP', 'CSA', 'Algebra', 'Analysis'])
    student_repository.store('2148', 'Leanca Adrian-Bogdan', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2149', 'Leiti David', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2150', 'Luca Alex-Augustin', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2151', 'Lucaciu Catalin-Mihai', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2153', 'Lupascu Stefan', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2154', 'Macarie Cristian', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2156', 'Maier Bogdan', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2157', 'Maior Alexandra', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2159', 'Mali Imre-Gergely', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2161', 'Manciu Daniel', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2155', 'Maciuca Maria-Alexandra', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2158', 'Malai Emil-Sorin', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2160', 'Manaila Andrei Petrut', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])
    student_repository.store('2162', 'Marusca Tabita-Cora', ['FP', 'CSA', 'CDI', 'CercC', 'Algebra', 'Analysis'])

    discipline_repository.store('1', 'CSA')
    discipline_repository.store('2', 'FP')
    discipline_repository.store('3', 'CDI')
    discipline_repository.store('4', 'CercC')
    discipline_repository.store('5', 'Algebra')
    discipline_repository.store('6', 'Analysis')
    discipline_repository.store('7', 'Fundamentele programarii')
    discipline_repository.store('8', 'ASC')
    discipline_repository.store('9', 'Analiza')
    discipline_repository.store('10', 'Sport')

    grade_repository.store('1', '2069', 10)
    grade_repository.store('2', '2069', 10)
    grade_repository.store('5', '2069', 9)
    grade_repository.store('6', '2069', 10)
    grade_repository.store('1', '2148', 9)
    grade_repository.store('2', '2148', 10)
    grade_repository.store('3', '2148', 10)
    grade_repository.store('4', '2148', 10)
    grade_repository.store('5', '2148', 8)
    grade_repository.store('6', '2148', 3)


def get_controllers(student_repo, discipline_repo, grade_repo):
    """
    Creates the controllers
    """
    undo_controller = UndoController()
    student_controller = StudentControllerWithUndo(student_repo, undo_controller)
    discipline_controller = DisciplineControllerWithUndo(discipline_repo, grade_repo, undo_controller)
    grade_controller = GradeControllerWithUndo(grade_repo, student_repo, discipline_repo, undo_controller)

    return [student_controller, discipline_controller, grade_controller, undo_controller]


def main():
    list_of_repositories = repo_choice()
    student_repository = list_of_repositories[0]
    discipline_repository = list_of_repositories[1]
    grade_repository = list_of_repositories[2]
    add_mock_data_to_repos(student_repository, discipline_repository, grade_repository)

    list_of_controllers = get_controllers(student_repository, discipline_repository, grade_repository)
    student_controller = list_of_controllers[0]
    discipline_controller = list_of_controllers[1]
    grade_controller = list_of_controllers[2]
    undo_controller = list_of_controllers[3]

    console = Console(student_controller, discipline_controller, grade_controller, undo_controller)
    console.main_menu()

    if isinstance(student_repository, StudentRepositoryCSV) or isinstance(student_repository, StudentRepositoryBinary):
        student_repository.write_file()
        discipline_repository.write_file()
        grade_repository.write_file()


if __name__ == "__main__":
    main()
