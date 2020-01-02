def compare(a, b):
    return a < b 


def gnome_sort(iterator_object, compare_function=compare):
    i = j = 0
    n = len(iterator_object)

    while i < n:
        if i and compare_function(iterator_object[i], iterator_object[i - 1]):
            iterator_object[i], iterator_object[i - 1] = iterator_object[i - 1], iterator_object[i]
            i -= 1

        else:
            if i < j:
                i = j
            j = i = i + 1

    return


def filter_by(list_of_elements, test_function):
    result_list = []

    for iterator in list_of_elements:
        if test_function(iterator):
            result_list.append(iterator)

    return result_list
