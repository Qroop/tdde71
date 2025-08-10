#include <string>
#pragma once

class Node;

class Expression {
public:
	Expression(std::string expr);
	~Expression();
	Expression(const Expression& other);
	Expression& operator=(const Expression& other);

private:
	std::string expression;
	Node* rootNode;
};

class Node {
public:
	virtual ~Node() = default;
	virtual std::string toString() const = 0;
	virtual double evaluate() const = 0;
protected:
	Node() = default;
};

// Operands
class Operand : public Node {
public:
	virtual ~Operand() = default;
};

class Real : public Operand {
public:
	Real();
	Real(const double value);
	
	std::string toString() const override;
	double evaluate() const override;
private:
	const double value;
};

class Integer : public Operand {
public:
	Integer();
	Integer(const int value);

	std::string toString() const override;
	double evaluate() const override;
private:
	const int value;
};


// Operators
class Operator : public Node {
public:
	Operator(Node* left, Node* right);
	virtual ~Operator();
protected:
	Node* left;
	Node* right;
};

class Addition : public Operator {
public:
	Addition(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

class Subtraction : public Operator {
public:
	Subtraction(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

class Multiplication : public Operator {
public:
	Multiplication(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

class Division : public Operator {
public:
	Division(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

class Modulus : public Operator {
public:
	Modulus(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

class Power : public Operator {
public:
	Power(Node* left, Node* right);
	std::string toString() const override;
	double evaluate() const override;
};

