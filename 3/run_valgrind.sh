#!/bin/bash
if [[ ! -f test_main.o ]]; then
    g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.cc -c
fi
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.o Calculator.cc CalculatorTests.cc -o calculator_tests.o
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./calculator_tests.o
