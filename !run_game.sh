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
    6\
    6" |./catan
#    resources = {{"wood", 8}, {"brick", 8}, {"sheep", 6}, {"wheat", 6}, {"ore", 1}}; // aight
#    these are the resources for the start to run the game and do stuff without being depended on the dice roll just to
#    show what I can do in the game, and try and experimnet technically the player should return 0

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