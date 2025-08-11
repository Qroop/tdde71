#include "Expression.h"
#include "catch.hpp"

TEST_CASE("expression construction") {
	Expression e{"3 4 + 5 *", Expression::mode::POSTFIX};
	CHECK(e.to_string() == "((3 + 4) * 5)");
	CHECK(e.evaluate() == "35");
}

TEST_CASE("postfix multiple operators and precedence") {
	Expression e{"3 4 + 2 * 7 /", Expression::mode::POSTFIX}; // ((3 + 4) * 2) / 7 = 2
	CHECK(e.evaluate() == "2");
	CHECK(e.to_string() == "(((3 + 4) * 2) / 7)");
}

TEST_CASE("infix precedence without parentheses") {
	Expression e; 
	e.set_mode(Expression::mode::INFIX);
	e.parse_expression("3 + 4 * 2");
	CHECK(e.evaluate() == "11");
	CHECK(e.to_string() == "(3 + (4 * 2))");
}

TEST_CASE("infix with parentheses altering precedence") {
	Expression e; 
	e.set_mode(Expression::mode::INFIX);
	e.parse_expression("( 3 + 4 ) * 2");
	CHECK(e.evaluate() == "14");
	CHECK(e.to_string() == "((3 + 4) * 2)");
}

TEST_CASE("prefix parsing equivalent to infix") {
	Expression e; 
	e.set_mode(Expression::mode::PREFIX);
	e.parse_expression("+ 3 * 4 2");
	CHECK(e.evaluate() == "11");
	CHECK(e.to_string() == "(3 + (4 * 2))");
}

TEST_CASE("postfix real division formatting") {
	Expression e{"3 2 /", Expression::mode::POSTFIX};
	CHECK(e.evaluate() == "1.50");
	CHECK(e.to_string() == "(3 / 2)");
}

TEST_CASE("power right associativity") {
	Expression e; 
	e.set_mode(Expression::mode::INFIX);
	e.parse_expression("2 ^ 3 ^ 2"); // 2^(3^2)=512
	CHECK(e.evaluate() == "512");
	CHECK(e.to_string() == "(2 ^ (3 ^ 2))");
}

TEST_CASE("invalid postfix missing operand throws") {
	Expression e; e.set_mode(Expression::mode::POSTFIX);
	CHECK_THROWS_AS(e.parse_expression("3 +"), std::logic_error);
}

TEST_CASE("invalid infix missing operand throws") {
	Expression e; e.set_mode(Expression::mode::INFIX);
	CHECK_THROWS_AS(e.parse_expression("3 +"), std::logic_error);
}

