"""
Created on Oct 6, 2016

@author: leancabogdan
"""


def divides_by(number, divisor):
    """
    Checks if a number is divisible by another number
    :param number: integer, the number to be checked
    :param divisor: integer, the divisor
    :return: boolean, true if the division is successful, false otherwise
    """
    if number % divisor == 0:
        return True

    return False


def sum_of_divisors(n):
    """
    Computes the sum of the divisors of a given number
    :param n: integer, the given number
    :return: integer, the result
    """
    the_sum = 1
    divisor = 2

    while divisor < n:
        if divides_by(n, divisor):
            the_sum += divisor

        divisor += 1

    return the_sum


def is_perfect(n):
    """
    Checks if the given number is perfect or not (it is equal to its divisors sum
    :param n: integer, the given number
    :return: boolean, true if the number is perfect, false otherwise
    """
    the_sum = sum_of_divisors(n)
    if n == the_sum:
        return True

    return False


def read_data():
    """
    Reads an integer from the keyboard and returns it
    :return: integer, the read number
    :exception ValueError: if the user input is not an integer
    """
    number = int(input("Give n: "))
    return number


def print_data(n):
    """
    Prints a given number with surrounding text specific to the problem
    :param n: integer, the number to be printed
    """
    print("The searched number is: ", n)


def main():
    number = read_data()
    number += 1
    while not is_perfect(number):
        number += 1
    print_data(number)


if __name__ == "__main__":
    main()
