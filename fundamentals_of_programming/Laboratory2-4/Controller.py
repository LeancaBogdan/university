from copy import deepcopy
from Domain import *


def generate_participant(participant_id, participant_name, participant_p1, participant_p2, participant_p3):
    """
    Generates a dictionary with the data of a participant
    Input: participant_id, participant_name and the scores at the 3 problems for a participant
    Output: A dictionary with the data from the Input
    Exceptions: -
    """
    participant = {
        'participant_id': participant_id,
        'participant_name': participant_name,
        'participant_p1': participant_p1,
        'participant_p2': participant_p2,
        'participant_p3': participant_p3
    }
    return participant


def add_participant(participants_list, participant):
    """
    Adds a participant to the list of participants
    Input: the list of participants and a participant
    Output: -
    Exceptions: -
    """
    participants_list.append(participant)


def add_participant_at_pos(participants_list, participant, pos):
    """
    Adds a participant to the list of participants at a given position.
    Input: the list of participants, a participant and the position on which it will pe added
    Output: -
    Exceptions: Given position is lower than 0 or greater than the lenght of the list.
    """
    if pos < 0 or pos > len(participants_list):
        raise ValueError("Invalid position!")

    participants_list.insert(pos, participant)


def remove_from_pos(participants_list, pos):
    """
    Removes the participant at the given position from the list of participants.
    Input: the list of participants and the position of the participant to be removed.
    Output: -
    Exceptions: -
    """
    del participants_list[pos]


def remove_start_stop(participants_list, pos1, pos2):
    """
    Removes all the participants from the starting position to the ending position from the list.
    Input: the list of participants, the starting and the ending position for delete.
    Output: -
    Exceptions: Ending position bigger than starting position.
    """
    del participants_list[pos1:pos2 + 1]


def update_score(participant, problem, score):
    """
    Updates the score of a given participant at a given problem.
    Input: The participant to be updated, the problem to be updated and the new score.
    Output: The updated participant
    Exceptions: -
    """
    participant[problem] = score

    return participant


def sort_participants(participants_list):
    """
    Generates a list of participant sorted descending by their average score.
    Input: The original list of participants.
    Output: The sorted list of participants.
    Exceptions: -
    """
    return sorted(participants_list, key=lambda k: avg_participant(k), reverse=True)


def generate_participants_higher(participants_list, score):
    """
    Generates a list containing the participants with an average score greater than the given score.
    Input: The original list of participants and the score.
    Output: The list of participants with an average score greater than the given score.
    Exceptions: -
    """
    participants_higher = []

    for p in participants_list:
        if avg_participant(p) > score:
            participants_higher.append(p)

    return participants_higher


def generate_participants_lower(participants_list, score):
    """
    Generates a list containing the participants with an average score lower than the given score.
    Input: The original list of participants and the score.
    Output: The list of participants with an average score lower than the given score.
    Exceptions: -
    """
    participants_lower = []

    for p in participants_list:
        if avg_participant(p) < score:
            participants_lower.append(p)

    return participants_lower


def generate_participants_equal(participants_list, score):
    """
    Generates a list containing the participants with an average score equal to the given score.
    Input: The original list of participants and the score.
    Output: The list of participants with an average score equal to the given score.
    Exceptions: -
    """
    participants_equal = []

    for p in participants_list:
        if avg_participant(p) == score:
            participants_equal.append(p)

    return participants_equal


def avg_participants(participants_list, pos1, pos2):
    """
    Computes the average of the average scores of the participants between two given positions.
    Input: The list of participants, the starting position and the ending position.
    Output: The average score.
    Exceptions: -
    """
    avg = 0

    for p in participants_list[pos1: pos2]:
        avg += avg_participant(p)

    avg /= (pos2 - pos1 + 1)

    return avg


def min_participants(participants_list, pos1, pos2):
    """
    Computes the average of the average scores of the participants between two given positions.
    Input: The list of participants, the starting position and the ending position.
    Output: The average score.
    Exceptions: -
    """
    min_avg = 10

    for p in participants_list[pos1: pos2]:
        if avg_participant(p) < min_avg:
            min_avg = avg_participant(p)

    return min_avg


def podium_by_avg(participants_list, no_of_participants):
    """
    Generates a list containing the given number of participants sorted descending by their average score.
    Input: The list of participants and the number of participants to be included in the list.
    Output: The list containing the given number of participants sorted descending by their average score.
    Exceptions: -
    """
    podium = []

    for _ in range(0, no_of_participants):
        podium.append(max_participant_by_avg(participants_list))
        participants_list.pop(max_participant_by_avg(participants_list))

    return podium


def podium_by_problem(participants_list, no_of_participants, problem):
    """
    Generates a list containing the given number of participants sorted descending by their score at a given problem.
    Input: The list of participants, the number of participants to be included in the list and
            the problem by which the participants are sorted.
    Output: The list containing the given number of participants sorted descending by their score at a given problem.
    Exceptions: -
    """
    podium = []

    for _ in range(0, no_of_participants):
        podium.append(max_participant_by_problem(participants_list, problem))
        participants_list.pop(max_participant_by_problem(participants_list, problem))

    return podium


def remove_lower_than(participants_list, score):
    """
    Sets the scores of all the participants with an average score lower than the given one from the list to 0.
    Input: The list of participants and the score.
    Output: -
    Exceptions: -
    """
    for p in participants_list:
        if avg_participant(p) < score:
            p['participant_p1'] = 0
            p['participant_p2'] = 0
            p['participant_p3'] = 0


def remove_greater_than(participants_list, score):
    """
    Sets the scores of all the participants with an average score greater than the given one from the list to 0.
    Input: The list of participants and the score.
    Output: -
    Exceptions: -
    """
    for p in participants_list:
        if avg_participant(p) > score:
            p['participant_p1'] = 0
            p['participant_p2'] = 0
            p['participant_p3'] = 0


def update_undo(undo_list, participants_list):
    """
    Updates the undo list by appending the given participants_list to it
    :param undo_list: The undo_list to be updated, consisting of copies of the list of participants
    :param participants_list: The current participants list
    :return: -
    """
    undo_list.append(deepcopy(participants_list))


def undo(undo_list):
    """
    Function that undoes the previous operation.
    Input: The list of participants and the list used for undo operations.
    Output: -
    Exceptions: There is no operation to undo.
    """
    try:
        if len(undo_list) == 0:
            raise EOFError("There is no operation to undo!")
        elif len(undo_list) == 1:
            return []
        else:
            return undo_list[len(undo_list) - 1]

    except EOFError as eof:
        print(eof)
