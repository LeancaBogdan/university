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
Reads a number from the keyboard and finds the lowest pair of twin prime numbers greater than the given n
Twin prime numbers means that their difference is 2
"""
if __name__ == '__main__':
    n = int(input("Give n: "))
    p1 = n+1
    p2 = n+3
    while not (prime(p1) and prime(p2) and p2-p1 == 2):
        p1 += 1
        p2 += 1

    print(p1, " ", p2)
