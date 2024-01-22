#!/usr/bin/python3
def safe_print_list_integers(my_list=None, x=0):
    if my_list is None:
        my_list = []

    count = 0
    for i in range(x):
        try:
            if isinstance(my_list[i], int):
                print("{:d}".format(my_list[i]), end="")
                count += 1
        except IndexError:
            break
    print()
    return count
