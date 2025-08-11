#!/bin/bash

if [[ ! -f test_main.o ]]; then
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.cc -c
fi

g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast test_main.o Expression.cc Calculator.cc postfix.cc token.cc ExpressionTests.cc -o expression_tests.o && ./expression_tests.o
