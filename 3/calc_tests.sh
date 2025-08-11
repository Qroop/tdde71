#!/bin/bash

if [[ ! -f test_main.o ]]; then
    g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.cc -c
fi

g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.o Calculator.cc CalculatorTests.cc -o calculator_tests.o && ./calculator_tests.o
