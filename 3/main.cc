#include <iostream>
#include "Expression.h"

using namespace std;

int main()
{
	string line;
	Expression e;
	while ( getline(cin, line) ) {
		if ( line.front() != ':' ) {
			e.parse_expression(line); // Update the expression with the new input
			e.set_mode(Expression::mode::INFIX);
			continue;
		}

		// Processing command
		if ( line == ":infix" ) {
			e.set_mode(Expression::mode::INFIX);
		} else if ( line == ":postfix" ) {
			e.set_mode(Expression::mode::POSTFIX);
		} else if ( line == ":prefix" ) {
			e.set_mode(Expression::mode::PREFIX);
		} else if ( line == ":quit" || line == ":exit" ) {
			break; // Exit the loop
		} else if ( line == ":calc" ) {
			cout << e.evaluate() << endl;
		} else {
			cout << "Unknown command: " << line << endl;
		}
	}
}
