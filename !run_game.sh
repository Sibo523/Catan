echo "1 2 3\
    1 2 2\
    2 2 2\
    2 2 6\
    0 0 1\
    0 0 1\
    4 0 1\
    4 0 1\
    7\
    6" |./catan

#run valgrind
valgrind --leak-check=full --track-origins=yes echo "1 2 3\
          1 2 2\
          2 2 2\
          2 2 6\
          0 0 1\
          0 0 1\
          4 0 1\
          4 0 1\
          7\
          6
      "| ./catan