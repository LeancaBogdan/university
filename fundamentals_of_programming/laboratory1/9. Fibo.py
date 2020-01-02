"""
Created on Oct 6, 2016

@author: leancabogdan
"""


def fibo(n):
    """
    A function that returns the n-th element of the Fibonacci sequence
    :param n: Integer, the index of the searched element
    :return: Integer, f(n), the searched element
    """
    f1 = 1
    f2 = 1
    f3 = 2
    i = 3

    while i < n:
        f3 = f1 + f2
        f1 = f2
        f2 = f3
        i += 1

    return f3


def read_data():
    """
    Reads a number from the user.
    :return: Integer, the read number
    """
    n = int(input("Give n: "))

    return n


def print_data(f, i):
    """
    A function that prints the element of the sequence and it's index
    :param f: Integer, the element to pe printed
    :param i: Integer, the index of the element
    """
    print("The element is ", f, " with the index ", i)


def main():
    """
    Reads a number from the keyboard and prints the smallest number that is in the Fibonacci sequence and
    that is greater than the given number
    """
    n = read_data()
    f = fibo(2)
    i = 2

    while f <= n:
        i += 1
        f = fibo(i)

    print_data(f, i)


if __name__ == '__main__':
    main()
