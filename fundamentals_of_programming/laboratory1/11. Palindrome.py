"""
Created on Oct 6, 2016

@author: leancabogdan
"""
import sys

def is_palindrome(n):
    """
    A function that generates the palindrome of a number n
    :param n: Integer, the given number
    :return: Boolean, True if the number is palindrome, False otherwise
    """
    copy = n
    inverse = 0

    while n != 0:
        inverse = inverse * 10 + n % 10
        n //= 10

    return inverse == copy


def read_data():
    """
    A function that reads an integer from the keyboard and returns it
    :return: Integer, the read number
    :except: ValueError: If the user inputs something that cannot be interpreted as an integer
    """
    n = int(input("Give n :"))

    return n


def main():
    try:
        n = read_data()
    except ValueError:
        print("Sorry, you did not enter an integer...")
        sys.exit(1)
    if is_palindrome(n):
        print("The number is palindrome! :)")
    else:
        print("The number is not palindrome! :(")


if __name__ == "__main__":
    main()
