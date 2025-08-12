#include <iostream>
#include <vector>
#include "Expression.h"

using namespace std;

int main()
{
	string line;
	Expression curr_expr;
	vector<Expression> expressions;

	while ( getline(cin, line) ) {
		if ( line.front() != ':' ) {
			curr_expr.parse_expression(line); // Update the expression with the new input
			curr_expr.set_mode(Expression::mode::INFIX);
			continue;
		}

		// Processing command
		if ( line == ":infix" ) {
			curr_expr.set_mode(Expression::mode::INFIX);
		} 
		else if ( line == ":postfix" ) {
			curr_expr.set_mode(Expression::mode::POSTFIX);
		} 
		else if ( line == ":prefix" ) {
			curr_expr.set_mode(Expression::mode::PREFIX);
		} 
		else if ( line == ":quit" || line == ":exit" ) {
			break;
		} 
		else if ( line == ":calc" ) {
			cout << curr_expr.evaluate() << endl;
		} 
		else if ( line == ":save" ) {
			expressions.push_back(Expression(curr_expr.to_string(), curr_expr.get_mode()));
		} 
		else if ( line == ":list" ) {
			for ( int i = 0; i < int(expressions.size()); i++ ) {
				cout << i << ": " << expressions[i].to_string() << endl;
			}
		} 
		else if ( line.find(":activate") != string::npos ) {
			int i;
			try {
				i = stoi(line.substr(10, line.size() - 10));
			}
			catch (invalid_argument& e) {
				cout << "Invalid argument for :activate command." << endl;
				continue;
			} 

			if (i < 0 || i >= int(expressions.size())) {
				cout << "Invalid index for :activate command." << endl;
				cout << "Valid range is 0 to " << expressions.size() - 1 << endl;
				continue;
			}
			curr_expr = move(expressions[i]);
		} 
		else {
			cout << "Unknown command: " << line << endl;
		}
	}
}
