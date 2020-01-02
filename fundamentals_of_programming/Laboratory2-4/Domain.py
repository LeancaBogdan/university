
def avg_participant(participant):
    """
    Returns the average score of a participant
    Input: the participant
    Output: the average
    Exceptions: -
    """
    return (participant['participant_p1'] + participant['participant_p2'] + participant['participant_p3'])//3


def avg_list(pos1, pos2, participants_list):
    """
    Returns the average score of a group of participants between 2 given positions in the list
    Input: Starting position, ending position and the list of participants.
    Output: The average score of the group of participants
    Exceptions: -
    """
    avg = 0

    for i in range(pos1, pos2):
        avg += avg_participant(participants_list[i])

    return avg / (pos2 + 1 - pos1)


def min_list(pos1, pos2, participants_list):
    """
    Returns the lowest average score of the participants between 2 given positions in the list
    Input: Starting position, ending position and the list of participants.
    Output: The minimum average score
    Exceptions: -
    """
    min_score = 10

    for i in range(pos1, pos2+1):
        if avg_participant(participants_list[i]) < min_score:
            min_score = avg_participant(participants_list[i])

    return min_score


def max_participant_by_avg(participants_list):
    """
    Returns the participant having the highest average score from the list.
    Input: The list of participants.
    Output: The participant if it exists or None in case of empty or invalid (scores lower than 0) list
    Exceptions: -
    """
    max_avg = 0
    max_participant = None

    for i in participants_list:
        if avg_participant(i) > max_avg:
            max_avg = avg_participant(i)
            max_participant = i

    return max_participant


def max_participant_by_problem(participants_list, problem):
    """
    Returns the participant having the highest score at a given problem.
    Input: the participants list and the problem by which to search for the maximum
    Output: the participant_id of the searched participant. -1 in case of error
    Exceptions: -
    """
    max_score = 0
    max_id = -1

    for i in participants_list:
        if i[problem] > max_score:
            max_score = i[problem]
            max_id = i['participant_id']

    return max_id


def find_by_id(participants_list, participant_id):
    """
    Searches for a participant with the given participant_id in the list.
    Input: The list of participants and the participant_id to look for
    Output: -1 if not found, position if found.
    Exceptions: -
    """
    for i in range(0, len(participants_list)):
        if participants_list[i]['participant_id'] == participant_id:
            return i

    return -1
