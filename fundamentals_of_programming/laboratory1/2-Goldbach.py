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

    for d in range(3, number//2, 2):
        if number % d == 0:
            return False

    return True


"""
Given a number n, finds all the pairs of prime numbers such that their sum is n
"""
if __name__ == '__main__':
    n = int(input("Give n: "))

    if n <= 2:
        print("Invalid number given")

    p1 = 3

    while p1 < n//2:
        while not(prime(p1) and prime(n-p1)):
            p1 += 1
        print(p1, " ", n-p1, "\n")
        p1 += 1
