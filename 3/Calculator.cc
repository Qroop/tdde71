#include "Calculator.h"
#include <stdexcept>
#include <string>
#include <cmath>
#include <iomanip> 

// Operands
std::string Operand::postfix() const {
	return this->to_string();
}

std::string Operand::infix() const {
	return this->to_string();
}

std::string Operand::prefix() const {
	return this->to_string();
}

// Real
Real::Real(const double value) : value(value) {}

std::string Real::to_string() const {
	std::ostringstream output;
	output << std::fixed << std::setprecision(3) << this->value;
	return output.str();
}

double Real::evaluate() const {
	return value;
}

// Integer implementation
Integer::Integer() : value(0) {}

Integer::Integer(const int value) : value(value) {}

std::string Integer::to_string() const {
	std::ostringstream output;
	output << this->value;
	return output.str();
}

double Integer::evaluate() const {
	return static_cast<double>(value);
}

// Operator implementations
Operator::Operator(Node* left, Node* right, const std::string& op) 
    : left(left), right(right), op(op) {}

Operator::~Operator() {
	delete left;
	delete right;
}

void Operator::add_lhs(Node* new_left) {
	if (!new_left) {
		throw std::logic_error("Left operand cannot be null");
	}
	if (left != new_left) {
		delete left;
		left = new_left;
	}
}

void Operator::add_rhs(Node* new_right) {
	if (!new_right) {
		throw std::logic_error("Right operand cannot be null");
	}
	if (right != new_right) {
		delete right;
		right = new_right;
	}
}

std::string Operator::to_string() const {
	return "(" + left->to_string() + " " + op + " " + right->to_string() + ")";
}

std::string Operator::prefix() const {
	std::ostringstream output;
	output << op << " " << left->prefix() << " " << right->prefix();
	return output.str();
}

std::string Operator::infix() const {
	std::ostringstream output;
	output << "( " << left->infix() << " " << op << " " << right->infix() << " )";
	return output.str();
}

std::string Operator::postfix() const {
	std::ostringstream output;
	output << left->postfix() << " " << right->postfix() << " " << op;
	return output.str();
}

// Addition
Addition::Addition(Node* left, Node* right) : Operator(left, right, "+") {}

double Addition::evaluate() const {
	return left->evaluate() + right->evaluate();
}

// Subtraction
Subtraction::Subtraction(Node* left, Node* right) : Operator(left, right, "-") {}

double Subtraction::evaluate() const {
	return left->evaluate() - right->evaluate();
}

// Multiplication
Multiplication::Multiplication(Node* left, Node* right) : Operator(left, right, "*") {}

double Multiplication::evaluate() const {
	return left->evaluate() * right->evaluate();
}

// Division
Division::Division(Node* left, Node* right) : Operator(left, right, "/") {}

double Division::evaluate() const {
	if (right->evaluate() == 0) {
		throw std::logic_error("Division by zero");
	}
	return left->evaluate() / right->evaluate();
}

// Modulus
Modulus::Modulus(Node* left, Node* right) : Operator(left, right, "%") {}

double Modulus::evaluate() const {
	return std::fmod(left->evaluate(), right->evaluate());
}

// Power
Power::Power(Node* left, Node* right) : Operator(left, right, "^") {}

double Power::evaluate() const {
	if (left->evaluate() < 0 && right->evaluate() != static_cast<int>(right->evaluate())) {
		throw std::logic_error("Negative base with non-integer exponent");
	}

	if (left->evaluate() == 0 && right->evaluate() <= 0) {
		throw std::logic_error("Zero base with non-positive exponent");
	}

	return std::pow(left->evaluate(), right->evaluate());
}


