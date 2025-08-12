#include <string>
#include <memory>

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
	// primary ctor taking ownership via unique_ptr
	Operator(std::unique_ptr<Node> left, std::unique_ptr<Node> right, const std::string& op);
	// compatibility ctor from raw pointers (takes ownership)
	Operator(Node* left, Node* right, const std::string& op);
	Operator(Operator const&) = delete;
	Operator& operator=(Operator const&) = delete;
	virtual ~Operator();

	std::string to_string() const override;
	std::string postfix() const override;
	std::string infix() const override;
	std::string prefix() const override;
	void add_lhs(Node* new_left);               // takes ownership
	void add_rhs(Node* new_right);               // takes ownership
	void add_lhs(std::unique_ptr<Node> new_left); // move ownership
	void add_rhs(std::unique_ptr<Node> new_right);// move ownership
protected:
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	std::string op;
};

class Addition : public Operator {
public:
	Addition(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Addition(Node* left, Node* right);
	double evaluate() const override;
};

class Subtraction : public Operator {
public:
	Subtraction(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Subtraction(Node* left, Node* right);
	double evaluate() const override;
};

class Multiplication : public Operator {
public:
	Multiplication(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Multiplication(Node* left, Node* right);
	double evaluate() const override;
};

class Division : public Operator {
public:
	Division(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Division(Node* left, Node* right);
	double evaluate() const override;
};

class Modulus : public Operator {
public:
	Modulus(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Modulus(Node* left, Node* right);
	double evaluate() const override;
};

class Power : public Operator {
public:
	Power(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	Power(Node* left, Node* right);
	double evaluate() const override;
};

