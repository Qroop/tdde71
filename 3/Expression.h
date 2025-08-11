#include "Calculator.h"

#pragma once

class Expression {
public:
	Expression();
	Expression(const std::string& expr);
	~Expression();
	Expression(const Expression& other);
	Expression& operator=(const Expression& other);

	std::string to_string() const;
	std::string evaluate() const;
private:
	Node* rootNode;
};

