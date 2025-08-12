#include "Calculator.h"

#pragma once

class Expression {
public:
	enum class mode {
		INFIX,
		PREFIX,
		POSTFIX
	}; 

	Expression();
	Expression(const std::string& expr, mode m = mode::INFIX);
	~Expression();
	Expression(const Expression&) = delete;
	Expression& operator=(const Expression&) = delete;

	void parse_expression(const std::string& expr);

	std::string to_string() const;
	std::string evaluate() const;

	void set_mode(const mode& new_mode);
private:
	void parse_infix(const std::string& expr);
	void parse_postfix(const std::string& expr);
	void parse_prefix(const std::string& expr);

	Node* rootNode;
	mode curr_mode;
};

