#include "Calculator.h"
#include <string>
#include <cmath>

Expression::Expression(std::string expr) : expression(std::move(expr)), rootNode(nullptr) {
	// Here you would typically parse the expression and build the rootNode
	// For now, we leave it uninitialized
}

Expression::~Expression() {
	delete rootNode;
}

Expression::Expression(const Expression& other) : expression(other.expression), rootNode(nullptr) {
	// For now, we don't copy the rootNode (would need deep copy implementation)
	// This is a simplified implementation
}

Expression& Expression::operator=(const Expression& other) {
	if (this != &other) {
		delete rootNode;
		expression = other.expression;
		rootNode = nullptr; // Simplified - would need deep copy in real implementation
	}
	return *this;
}

// Real implementation
Real::Real() : value(0.0) {}

Real::Real(const double value) : value(value) {}

double Real::get_value() const {
	return value;
}

std::string Real::toString() const {
	return std::to_string(value);
}

double Real::evaluate() const {
	return value;
}

// Integer implementation
Integer::Integer() : value(0) {}

Integer::Integer(const int value) : value(value) {}

int Integer::get_value() const {
	return value;
}

std::string Integer::toString() const {
	return std::to_string(value);
}

double Integer::evaluate() const {
	return static_cast<double>(value);
}

// Operator implementations
Operator::Operator(Node* left, Node* right) : left(left), right(right) {}

Operator::~Operator() {
	delete left;
	delete right;
}

// Addition
Addition::Addition(Node* left, Node* right) : Operator(left, right) {}

std::string Addition::toString() const {
	return "(" + left->toString() + " + " + right->toString() + ")";
}

double Addition::evaluate() const {
	return left->evaluate() + right->evaluate();
}

// Subtraction
Subtraction::Subtraction(Node* left, Node* right) : Operator(left, right) {}

std::string Subtraction::toString() const {
	return "(" + left->toString() + " - " + right->toString() + ")";
}

double Subtraction::evaluate() const {
	return left->evaluate() - right->evaluate();
}

// Multiplication
Multiplication::Multiplication(Node* left, Node* right) : Operator(left, right) {}

std::string Multiplication::toString() const {
	return "(" + left->toString() + " * " + right->toString() + ")";
}

double Multiplication::evaluate() const {
	return left->evaluate() * right->evaluate();
}

// Division
Division::Division(Node* left, Node* right) : Operator(left, right) {}

std::string Division::toString() const {
	return "(" + left->toString() + " / " + right->toString() + ")";
}

double Division::evaluate() const {
	return left->evaluate() / right->evaluate();
}

// Modulus
Modulus::Modulus(Node* left, Node* right) : Operator(left, right) {}

std::string Modulus::toString() const {
	return "(" + left->toString() + " % " + right->toString() + ")";
}

double Modulus::evaluate() const {
	return std::fmod(left->evaluate(), right->evaluate());
}

// Power
Power::Power(Node* left, Node* right) : Operator(left, right) {}

std::string Power::toString() const {
	return "(" + left->toString() + " ^ " + right->toString() + ")";
}

double Power::evaluate() const {
	return std::pow(left->evaluate(), right->evaluate());
}


