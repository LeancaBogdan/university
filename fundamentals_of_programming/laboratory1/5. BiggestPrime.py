"""
Created on Oct 6, 2016

@author: leancabogdan
"""


def prime(number):
    """
    Determines if a number is prime or not
    :param number: The number to be checked
    :return: boolean, True if the given number is prime, false otherwise
    """
    if number % 2 == 0:
        return False

    for d in range(3, number // 2, 2):
        if number % d == 0:
            return False

    return True


def read_data():
    """
    Reads a number from the user.
    :return: Integer, the read number
    """
    n = int(input("Give n: "))

    return n


def valid_input(n):
    """
    Validates that the given number is greater than 3
    :param n: Integer, the given number
    :return: Boolean, True if the given number is greater than 3, False otherwise
    """
    if n < 3:
        return False

    return True


def find_biggest_prime(n):
    """
    Finds the biggest prime number lower than the given number n
    :param n: Integer, the given number
    :return: Integer, the result
    """
    n -= 1
    while not prim(n):
        n -= 1

    return n


def print_result(n):
    """
    Prints the found number in a nice fashion
    :param n: Integer, the found number
    """
    print("The biggest prime smaller than the given number is ", str(n))


def main():
    """
    Reads a number from the keyboard and prints the biggest prime number lower than the given one
    :return:
    """
    n = read_data()

    if not valid_input(n):
        print("Wrong input!")

    n = find_biggest_prime(n)
    print_result(n)


if __name__ == '__main__':
    main()
