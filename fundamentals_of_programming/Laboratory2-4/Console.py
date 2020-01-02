from Controller import *
from Domain import *


def print_main_menu():
    menu_string = "\nAvailable commands: \n"
    menu_string += "\t1. Add the result of a new participant \n"
    menu_string += "\t2. Modify the scores from the list \n"
    menu_string += "\t3. Show participants whose scores have different properties \n"
    menu_string += "\t4. Show different characteristics of participants \n"
    menu_string += "\t5. Establish the podium \n"
    menu_string += "\t6. Undo the last operation that modified program data \n"
    menu_string += "\t0. Exit \n"
    print(menu_string)


def main_menu():
    participants_list = []
    undo_list = []
    stop = False
    while not stop:
        print_main_menu()

        try:
            command = int(input("Enter command: "))

            if command == 1:
                add_submenu(participants_list, undo_list)
            elif command == 2:
                modify_list_submenu(participants_list, undo_list)
            elif command == 3:
                list_submenu(participants_list)
            elif command == 4:
                list_properties_submenu(participants_list)
            elif command == 5:
                list_podium_submenu(participants_list, undo_list)
            elif command == 6:
                participants_list = undo_submenu(participants_list, undo_list)
            elif command == 0:
                stop = True
            else:
                print("Invalid command!")

        except ValueError:
            print("Invalid command!")


def print_add_submenu():
    menu_string = "\n Available commands: \n"
    menu_string += "\t 1. Add student with scores to the list \n"
    menu_string += "\t 2. Insert student with scores at a certain position in the list \n"
    menu_string += "\t 0. Exit \n"
    print(menu_string)


def add_submenu(participants_list, undo_list):
    stop = False

    while not stop:
        print_add_submenu()

        try:
            command = int(input("Enter command: "))

            if command == 1 or command == 2:
                update_undo(undo_list, participants_list)

            if command == 1:
                try:
                    participant = read_participant_data()
                    if find_by_id(participants_list, participant['participant_id']) != -1:
                        raise ValueError("Participant with the same participant_id already in the list.")
                    add_participant(participants_list, participant)
                except ValueError as ve:
                    print(ve)

            elif command == 2:
                pos = read_pos()
                participant = read_participant_data()
                try:    
                    if find_by_id(participants_list, participant['participant_id']) != -1:
                        raise ValueError("Participant with the same participant_id already in the list.")
                except ValueError as ve:
                    print(ve)

                try:
                    add_participant_at_pos(participants_list, participant, pos)

                except ValueError as ve:
                    print(ve)

            elif command == 0:
                stop = True
            else:
                print("Invalid command!")

        except ValueError:
            print("Command must be an integer!")


def print_modify_list_submenu():
    menu_string = "\t 1. Remove participant from a certain position. \n"
    menu_string += "\t 2. Remove participants between two given positions. \n"
    menu_string += "\t 3. Replace the score of a problem for a participant. \n"
    menu_string += "\t 0. Exit \n"
    print(menu_string)


def modify_list_submenu(participants_list, undo_list):
    stop = False

    while not stop:
        print_modify_list_submenu()

        try:
            command = int(input("Enter command: "))

            if command == 1 or command == 2 or command == 3:
                update_undo(undo_list, participants_list)

            if command == 1:
                try:
                    pos = read_pos()
                    if pos > len(participants_list)-1 or pos < 0:
                        raise ValueError("Position out of the domain!")
                    remove_from_pos(participants_list, pos)
                except ValueError as ve:
                    print(ve)

            if command == 2:
                try:
                    pos1 = int(input("Give the starting position for delete: "))
                    pos2 = int(input("Give the ending position for delete: "))
                    if pos1 > len(participants_list)-1 or pos1 < 0 or pos2 > len(participants_list)-1 or pos2 < 0:
                        raise ValueError("You have entered a position that is not in the list!")
                    if pos1 > pos2:
                        raise ValueError("Starting position bigger than ending position!")
                    remove_start_stop(participants_list, pos1, pos2)
                except ValueError as ve:
                    print(ve)

            if command == 3:
                pos = -1
                try:
                    pos = read_pos()
                    if pos > len(participants_list)-1:
                        raise ValueError("Position out of the domain!")
                except ValueError as ve:
                    print(ve)
                problem = read_problem()
                score = read_score()
                participants_list[pos] = update_score(participants_list[pos], problem, score)

            if command == 0:
                stop = True

        except ValueError:
            print("Invalid command!")


def print_list_submenu():
    menu_string = "\t 1. Print all the participants and their scores. \n"
    menu_string += "\t 2. Print all the participants sorted in the descending order of their average score. \n"
    menu_string += "\t 3. Print participants whose scores satisfy a certain property. \n"
    menu_string += "\t 0. Exit. \n"
    print(menu_string)


def list_submenu(participants_list):
    stop = False

    while not stop:
        print_list_submenu()

        try:
            command = int(input("Give a command: "))

            if command < 0 or command > 3:
                raise ValueError("Invalid command!")

            if command == 1:
                try:
                    print_list_of_participants(participants_list)
                except ValueError as ve:
                    print(ve)

            if command == 2:
                list_participants_sorted(participants_list)

            if command == 3:
                list_participants_with_properties_submenu(participants_list)

            if command == 0:
                stop = True

        except ValueError as ve:
            print(ve)


def list_participants_sorted(participants_list):
    """
    Prints all the participants sorted descending by their average score.
    Input: The list of participants.
    Output: -
    Execptions: The list of participants is empty.
    """
    if len(participants_list) == 0:
        print("The list of participants is empty!")
        return

    participants_sorted = sort_participants(participants_list)
    print_list_of_participants(participants_sorted)


def print_list_participants_with_properties_submenu():
    menu_string = "\t\tList participants whose average scores satisfy a certain property submenu. \n"
    menu_string += "\t1. Print participants whose average scores are greater than a given score. \n"
    menu_string += "\t2. Print participants whose average scores are lower than a given score. \n"
    menu_string += "\t3. Print participants whose average scores are equal to a given score. \n"
    menu_string += "\t0. Exit \n"
    print(menu_string)


def list_participants_with_properties_submenu(participants_list):
    """
    Prints all the participants with average scores satisfying a certain relation with a constant.
    Input: The list of participants.
    Output: -
    Exceptions: The list of participants is empty/
    """
    if len(participants_list) == 0:
        print("The list of participants is empty!")
        return

    stop = False
    while not stop:
        print_list_participants_with_properties_submenu()

        try:
            command = int(input("Choose an option: "))

            if command < 0 or command > 3:
                raise ValueError("Undefined command!")

            if command == 1:
                try:
                    score = read_score()
                    participants_higher = generate_participants_higher(participants_list, score)
                    print_list_of_participants(participants_higher)
                except ValueError as ve:
                    print(ve)

            if command == 2:
                try:
                    score = int(input("Choose the highest score: "))
                    if score < 0 or score > 10:
                        raise ValueError("Please give a valid score!")
                    participants_lower = generate_participants_lower(participants_list, score)
                    print_list_of_participants(participants_lower)
                except ValueError as ve:
                    print(ve)

            if command == 3:
                try:
                    score = int(input("Choose the desired score: "))
                    if score < 0 or score > 10:
                        raise ValueError("Please give a valid score!")
                    participants_equal = generate_participants_equal(participants_list, score)
                    print_list_of_participants(participants_equal)
                except ValueError as ve:
                    print(ve)

            if command == 0:
                stop = True

        except ValueError as ve:
            print(ve)


def print_list_properties_submenu():
    menu_string = "\tList different characteristics of a certain group of participants. \n"
    menu_string += "\t1. Print the average of the average scores of participants between two given positions. \n"
    menu_string += "\t2. Print the lowest average score of the participants between two given positions. \n"
    menu_string += "\t0. Exit. \n"
    print(menu_string)


def list_properties_submenu(participants_list):
    stop = False
    pos1 = pos2 = -1

    while not stop:
        print_list_properties_submenu()

        try:
            command = int(input("Give a command: "))

            if command < 0 or command > 2:
                raise ValueError("Invalid command!")

            if command == 1:
                try:
                    print("Starting position: ")
                    pos1 = read_pos()
                    print("Ending position: ")
                    pos2 = read_pos()
                    if pos1 > pos2:
                        raise ValueError("Starting position greater than ending position!")
                except ValueError as ve:
                    print(ve)
                avg = avg_participants(participants_list, pos1, pos2)
                print_avg_participants(avg)

            if command == 2:
                try:
                    print("Starting position: ")
                    pos1 = read_pos()
                    print("Ending position: ")
                    pos2 = read_pos()
                    if pos1 > pos2:
                        raise ValueError("Starting position greater than ending position!")
                except ValueError as ve:
                    print(ve)

                min_avg = min_participants(participants_list, pos1, pos2)
                print_min_participants(min_avg)

            if command == 0:
                stop = True

        except ValueError as ve:
            print(ve)


def print_list_podium_submenu():
    """
    Prints the submenu for listing the podium.
    Input: -
    Output: -
    Exceptions: -
    """
    menu_string = "\tList the podium. \n"
    menu_string += "\t1. List the podium containing a certain number of participants, sorted descending by" \
                   " their average score. \n"
    menu_string += "\t2. List the podium containing a certain number of participants, sorted descending by" \
                   " their score at a certain problem. \n"
    menu_string += "\t3. Set the scores of participants with an average score lower than a certain score to 0. \n"
    menu_string += "\t4. Set the scores of participants with an average score higher than a certain score to 0. \n"
    menu_string += "\t0. Exit."
    print(menu_string)


def list_podium_submenu(participants_list, undo_list):
    """
    The submenu for listing the podium.
    Input: The list of participants and the undo list because the remove subfeature of this feature modifies the list.
    Output: -
    Exceptions: The list is empty.
    """
    stop = False

    while not stop:
        print_list_podium_submenu()

        try:
            command = int(input("Give a command: "))

            if command < 0 or command > 4:
                raise ValueError("Invalid command!")

            if command == 1:
                back_participants = participants_list
                nr_of_participants = read_no_of_participants(len(participants_list))
                podium = podium_by_avg(back_participants, nr_of_participants)
                print_list_of_participants(podium)

            if command == 2:
                back_participants = participants_list
                nr_of_participants = read_no_of_participants(len(participants_list))
                problem = read_problem()
                podium = podium_by_problem(back_participants, nr_of_participants, problem)
                print_list_of_participants(podium)

            if command == 3:
                update_undo(undo_list, participants_list)
                score = read_score()
                remove_lower_than(participants_list, score)

            if command == 4:
                update_undo(undo_list, participants_list)
                score = read_score()
                remove_greater_than(participants_list, score)

            if command == 0:
                stop = True

        except ValueError as ve:
            print(ve)


def print_avg_participants(avg):
    """
    Prints the average of the average scores of the participants between two given positions.
    Input: The average score
    Output: -
    Exceptions: -
    """
    print("The average of the participants between the given positions is: " + str(avg))


def print_min_participants(min_avg):
    """
    Prints the minimum of the average scores of the participants between two given positions.
    Input: The minimum score
    Output: -
    Exceptions: -
    """
    print("The minimum average of the participants between the given positions is: " + str(min_avg))


def read_participant_data():
    """
    Reads all the data of a participant
    Input: -
    Output: The read participant
    Exceptions: -
    """
    participant_id = input("Give participant participant_id: ")
    name = input("Give participant participant_name: ")
    p1 = p2 = p3 = 0
    stop = False

    while not stop:
        try:
            p1 = input("Give p1 score: ")
            p2 = input("Give p2 score: ")
            p3 = input("Give p3 score: ")

            if int(p1) > 10 or int(p2) > 10 or int(p3) > 10 or int(p1) < 0 or int(p2) < 0 or int(p3) < 0:
                raise ValueError("Scores should be between 0 and 10!")

            print("\n")
            stop = True

        except ValueError as ve:
            print(ve)

    participant = generate_participant(participant_id, name, p1, p2, p3)
    return participant


def read_pos():
    """
    Reads a position in the list of participants.
    Input: -
    Output: an integer representing a position.
    Exceptions: Read something else than a natural number.
    """
    pos = -1
    stop = False

    while not stop:
        try:
            pos = int(input("Give a position: "))

            if pos < 0:
                raise ValueError("Position must be a positive number!")

            stop = True

        except ValueError as ve:
            print(ve)

    return pos


def read_problem():
    """
    Reads a problem, participant_p1, participant_p2 or participant_p3
    Input: -
    Output: the problem to be edited
    Exceptions: read something else than the participant_name of a problem
    """
    menu_string = "\n Choose a problem: \n"
    menu_string += "\t1. participant_p1 \n"
    menu_string += "\t2. participant_p2 \n"
    menu_string += "\t3. participant_p3 \n"
    menu_string += ""
    print(menu_string)
    cmd = ""

    try:
        cmd = input("Enter option: ")
        if cmd != 'participant_p1' and cmd != 'participant_p2' and cmd != 'participant_p3':
            raise ValueError

    except ValueError:
        print("Enter a valid problem!")

    return cmd


def read_score():
    """
    Reads the score for a problem, between 0 and 10
    Input: -
    Output: The read score
    Exceptions: Value out of the domain
    """
    stop = False
    score = 0

    while not stop:
        try:
            score = int(input("Please enter the score: "))
            if score < 0 or score > 10:
                raise ValueError("Value out of the domain!")

            stop = True

        except ValueError as ve:
            print(ve)

    return score


def read_no_of_participants(len_of_list):
    """
    Reads a valid number of participants.
    Input: The number of participants in the list.
    Output: The number of participants.
    Exceptions: Not a positive integer or number bigger than the number of participants in the list.
    """
    try:
        no_of_participants = int(input("Give the number of participants: "))

        if no_of_participants < 0:
            raise ValueError("The number of participants cannot be a negative number!")

        if no_of_participants > len_of_list:
            raise ValueError(
                "The number of participants cannot be greater than the number of participants from the list!"
            )

        return no_of_participants

    except ValueError as ve:
        print(ve)


def print_list_of_participants(list_of_participants):
    """
    Prints each of the participants in the given list, with their details
    Input: list_of_participants: list of participants
    Output: -
    Exceptions: ValueError if the given list is empty
    """
    if len(list_of_participants) == 0:
        raise ValueError("The list is empty!")

    for participant in list_of_participants:
        print("Participant participant_id: " + str(participant['participant_id']))
        print("Participant participant_name: " + str(participant['participant_name']))
        print("participant_p1: " + str(participant['participant_p1']))
        print("participant_p2: " + str(participant['participant_p2']))
        print("participant_p3: " + str(participant['participant_p3']) + "\n")


def print_undo_submenu():
    """
    Prints the submenu for the undo function.
    Input: -
    Output: -
    Exceptions: -
    """
    menu_string = "Undo submenu \n"
    menu_string += "\t1. Undo the last performed operation. \n"
    menu_string += "\t0. Exit."
    print(menu_string)


def undo_submenu(participants_list, undo_list):
    """
    Menu for the undo feature.
    Input: The list of participants and the list for undo operations.
    Output: -
    Exceptions: -
    """
    stop = False

    while not stop:
        print_undo_submenu()

        try:
            command = int(input("Give a command: "))
            if command < 0 or command > 1:
                raise ValueError("Invalid command!")
            if command == 1:
                participants_list = undo(undo_list)
            if command == 0:
                stop = True

        except ValueError as ve:
            print(ve)

    return participants_list
