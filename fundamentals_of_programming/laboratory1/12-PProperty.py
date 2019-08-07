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


def check_p_property(list1, list2):
    """
    Checks if two numbers represented as lists of existences have the property "p"
    The property "p" is that they are formed by the same digits
    :param list1: List, the list of existence corresponding to the first number
    :param list2: List, the list of existence corresponding to the second number
    :return: Boolean, True if the numbers have the property "p", False otherwise
    """
    for i in range(0, 10):
        if list1[i] != list2[i]:
            return False

    return True


def main():
    n1 = int(input("Dati n1: "))
    n2 = int(input("Dati n2: "))
    l1 = generate_list_of_existence(n1)
    l2 = generate_list_of_existence(n2)

    if check_p_property(l1, l2):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
