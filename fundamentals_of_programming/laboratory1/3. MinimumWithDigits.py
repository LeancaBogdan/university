"""
Created on Oct 6, 2016

@author: leancabogdan
"""


def generate_list_of_existence(n):
    """
    Generates a list where of existences where 1 on position pos means that the digit
    pos is present in the base 10 representation of the given number, and 0 means that it's not present.
    :param n: Integer, the given number
    :return: List, the result list
    """
    result_list = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    while n != 0:
        c = int(n % 10)
        result_list[c] = 1
        n = n//10

    return result_list


def read_data():
    """
    Reads a number from the user.
    :return: Integer, the read number
    """
    n = int(input("Give n: "))

    return n


def generate_minimum(l):
    """
    Generates the minimum number that can be constructed using the digits of a number, represented as a list of
    existences.
    :param l: list, the given list of existences
    :return: Integer, the resulting minimum number
    """
    n = 0

    for i in range(0, 10):
        if l[i] == 1:
            n = n * 10 + i

    return n


def print_minimum(n):
    """
    Prints an integer given as a parameter
    :param n: Integer, the number to be printed
    :return: None
    """
    print("The minimum number formed with the digits is: ", n)


def main():
    """
    Given a number n, finds the minimum number that can be formed with n's digits
    :return:
    """
    n = read_data()
    print(n)
    result_list = generate_list_of_existence(n)
    print(result_list)
    n2 = generate_minimum(result_list)
    print_minimum(n2)


if __name__ == "__main__":
    main()
