#include <cmath>
#include <iomanip>
#include <stack>
#include <sstream>
#include <set>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include "Expression.h"
#include "Calculator.h"
#include "postfix.h"

Expression::Expression() : rootNode(nullptr), curr_mode(mode::INFIX) {}

Expression::Expression(const std::string& expr, mode m) : rootNode(nullptr), curr_mode(m) {
	parse_expression(expr);
}

Expression::~Expression() {
	delete rootNode;
}

Expression::Expression(Expression&& other) : rootNode(other.rootNode), curr_mode(other.curr_mode) {
	other.rootNode = nullptr; // Transfer ownership
}

Expression& Expression::operator=(Expression&& other) {
	swap(other);
	return *this;
}

std::string Expression::to_string() const {
	if (rootNode) {
		return rootNode->to_string();
	}

	return "";
}

std::string Expression::evaluate() const {
	if (!rootNode) {
		return "0"; // Default return if no expression is set
	}

	double value = rootNode->evaluate();

	if (value == std::floor(value)) {
		return std::to_string(static_cast<int>(value));
	} else {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << value;
		return oss.str();
	}
}

void Expression::set_mode(const mode& new_mode) {
	curr_mode = new_mode;
}

void Expression::parse_expression(const std::string& expr) {
	// Dispatch based on current mode
	switch (curr_mode) {
		case mode::INFIX:
			parse_infix(expr);
			break;
		case mode::POSTFIX:
			parse_postfix(expr);
			break;
		case mode::PREFIX:
			parse_prefix(expr);
			break;
	}
}

void Expression::swap(Expression& other) {
	std::swap(rootNode, other.rootNode);
	std::swap(curr_mode, other.curr_mode);
}

void Expression::parse_infix(const std::string& expr) {
	// Convert infix to postfix, then build tree
	std::string postfix = Postfix(expr).to_string();
	parse_postfix(postfix);
}

void Expression::parse_postfix(const std::string& expr) {

	std::istringstream stream(expr);
	std::string token;
	std::stack<Node*> nodes;

	try {
		while (stream >> token) {
			if ( std::all_of( begin(token), end(token), ::isdigit ) ) {
				nodes.push(new Integer(std::stoi(token)));
			}
			else if ( isdigit(token.at(0)) ) {
				nodes.push(new Real(std::stod(token)));
			}
			else if ( isalpha(token.at(0)) ) {
				// Variable names could be handled here (currently ignored)
			}
			else {
				if (nodes.size() < 2) {
					throw std::logic_error("Not enough operands for operator: " + token);
				}
				Node* right = nodes.top(); nodes.pop();
				Node* left = nodes.top(); nodes.pop();
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
					delete left;
					delete right;
					throw std::logic_error("Unknown operator: " + token);
				}
			}
		}

		if (nodes.empty()) {
			throw std::logic_error("Invalid expression: no operands found");
		}
		if (nodes.size() != 1) {
			throw std::logic_error("Invalid expression: too many operands left after parsing");
		}
		// Delete old tree if present
		delete rootNode;
		rootNode = nodes.top();
	} catch (...) {
		while (!nodes.empty()) {
			delete nodes.top();
			nodes.pop();
		}
		throw;
	}
}

void Expression::parse_prefix(const std::string& expr) {
	// Simple prefix to postfix conversion using a stack of strings.
	// Assumes tokens are space separated like other forms.
	std::istringstream iss(expr);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
	std::stack<std::string> st;
	// read tokens from right to left
	for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
		const std::string& t = *it;
		if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^" || t == "%") {
			if (st.size() < 2) {
				throw std::logic_error("Invalid prefix expression: insufficient operands");
			}
			std::string op1 = st.top(); st.pop();
			std::string op2 = st.top(); st.pop();
			st.push(op1 + " " + op2 + " " + t);
		} else {
			st.push(t);
		}
	}
	if (st.size() != 1) {
		throw std::logic_error("Invalid prefix expression");
	}
	parse_postfix(st.top());
}
