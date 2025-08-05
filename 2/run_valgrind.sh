#!/bin/bash
if [[ ! -f test_main.o ]]; then
    g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.cc -c
fi
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.o LinkedList.cc linkedlist_test.cc -o linkedlist_tests.o
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./linkedlist_tests.o
