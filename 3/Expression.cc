#include <stack>
#include <sstream>
#include <set>
#include <cctype>
#include <algorithm>

#include "Expression.h"
#include "Calculator.h"
#include "postfix.h"

Expression::Expression() : rootNode(nullptr) {}

Expression::Expression(const std::string& expr) : rootNode(nullptr) {

	std::string postfix = Postfix(expr).to_string();

	std::istringstream stream(postfix);
	std::string token;
	std::stack<Node*> nodes;


	while (stream >> token) {
		if ( std::all_of( begin(token), end(token), ::isdigit ) )
		{
			nodes.push(new Integer(std::stoi(token)));
		}

		else if ( isdigit(token.at(0)) )
		{
			nodes.push(new Real(std::stod(token)));
		}
		else if ( isalpha(token.at(0)) )
		{
		// Vi räknar ordet som variabelnamn
		}
		else 
		{
			if (nodes.size() < 2) {
				throw std::logic_error("Not enough operands for operator: " + token);
			}

			Node* right = nodes.top();
			nodes.pop();
			Node* left = nodes.top();
			nodes.pop();

			if (token == "+") {
				nodes.push(new Addition(left, right));
			} else if (token == "-") {
				nodes.push(new Subtraction(left, right));
			} else if (token == "*") {
				nodes.push(new Multiplication(left, right));
			} else if (token == "/") {
				nodes.push(new Division(left, right));
			} else if (token == "^") {
				nodes.push(new Power(left, right));
			} else if (token == "%") {
				nodes.push(new Modulus(left, right));
			} else {
				throw std::logic_error("Unknown operator: " + token);
			}
		}
	}

	if (nodes.size() != 1) {
		throw std::logic_error("Invalid expression: too many operands left after parsing");
	}
	if (nodes.empty()) {
		throw std::logic_error("Invalid expression: no operands found");
	}
	this->rootNode = nodes.top();
}

Expression::~Expression() {
	delete rootNode;
}

Expression::Expression(const Expression& other) : rootNode(nullptr) {
	// For now, we don't copy the rootNode (would need deep copy implementation)
	// This is a simplified implementation
}

Expression& Expression::operator=(const Expression& other) {
	if (this != &other) {
		delete rootNode;
		rootNode = nullptr; // Simplified - would need deep copy in real implementation
	}
	return *this;
}

std::string Expression::to_string() const {
	if (rootNode) {
		return rootNode->to_string();
	}

	return "";
}

std::string Expression::evaluate() const {
	if (rootNode) {
		return std::to_string(rootNode->evaluate());
	}

	return "0"; // Default return if no expression is set
}


