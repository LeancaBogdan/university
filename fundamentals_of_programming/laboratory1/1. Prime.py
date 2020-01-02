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
Finds the first prime number greater than the given n
"""
if __name__ == '__main__':
    n = int(input("Give n: "))

    while not prime(n+1):
        n += 1

    print(n+1)
