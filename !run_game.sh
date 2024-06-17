#!/bin/sh
#test for adjacent road for vertex 3
echo "1 2 3\
    1 2 2\
    2 2 2\
    2 2 6\
    0 0 1\
    0 0 1\
    4 0 1\
    4 0 3\
    4 0 1\
    3\
    1 2 3\
    1\
    2 2 3\
    1\
    4 2 1\
    2\
    8\
    9\
    "YearOfPlenty"\
    "wood"\
    "brick"\
    8\
    6" |./catan


# echo "1 2 3\
#     1 2 2\
#     2 2 2\
#     2 2 6\
#     0 0 1\
#     0 0 1\
#     4 0 1\
#     4 0 3\
#     4 0 1\
#     3\
#     1 2 3\
#     1\
#     2 2 3\
#     1\
#     4 2 1\
#     7\
#     6" |./catan

#run valgrind
# valgrind --leak-check=full --track-origins=yes echo "1 2 3\
#           1 2 2\
#           2 2 2\
#           2 2 6\
#           0 0 1\
#           0 0 1\
#           4 0 1\
#           4 0 1\
#           7\
#           6
#       "| ./catan