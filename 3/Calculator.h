#include <string>

#pragma once

class Node {
public:
	virtual ~Node() = default;
	virtual std::string to_string() const = 0;
	virtual double evaluate() const = 0;

	virtual std::string postfix() const = 0;
	virtual std::string infix() const = 0;
	virtual std::string prefix() const = 0;
protected:
	Node() = default;
};

// Operands
class Operand : public Node {
public:
	virtual ~Operand() = default;
	std::string postfix() const override;
	std::string infix() const override;
	std::string prefix() const override;

	std::string to_string() const override = 0;
};

class Real : public Operand {
public:
	Real(const double value);
	
	std::string to_string() const override;
	double evaluate() const override;
private:
	const double value;
};

class Integer : public Operand {
public:
	Integer();
	Integer(const int value);

	std::string to_string() const override;
	double evaluate() const override;
private:
	const int value;
};


// Operators
class Operator : public Node {
public:
	Operator(Node* left, Node* right, const std::string& op);
	Operator(Operator const&) = delete;
	Operator& operator=(Operator const&) = delete;
	virtual ~Operator();

	std::string to_string() const override;
	std::string postfix() const override;
	std::string infix() const override;
	std::string prefix() const override;
	void add_lhs(Node* new_left);
	void add_rhs(Node* new_right);
protected:
	Node* left;
	Node* right;
	std::string op;
};

class Addition : public Operator {
public:
	Addition(Node* left, Node* right);
	double evaluate() const override;
};

class Subtraction : public Operator {
public:
	Subtraction(Node* left, Node* right);
	double evaluate() const override;
};

class Multiplication : public Operator {
public:
	Multiplication(Node* left, Node* right);
	double evaluate() const override;
};

class Division : public Operator {
public:
	Division(Node* left, Node* right);
	double evaluate() const override;
};

class Modulus : public Operator {
public:
	Modulus(Node* left, Node* right);
	double evaluate() const override;
};

class Power : public Operator {
public:
	Power(Node* left, Node* right);
	double evaluate() const override;
};

