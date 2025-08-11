#include "Expression.h"
#include "catch.hpp"

// Helper to parse with a specific mode
static Expression make_expr(Expression::mode m, const std::string& s){
    Expression e; 
    e.set_mode(m); 
    e.parse_expression(s); 
    return e; 
}

TEST_CASE("postfix multiple operators and precedence") {
    Expression e{"3 4 + 2 * 7 /"}; // ((3 + 4) * 2) / 7 = 2
    CHECK(e.evaluate() == "2");
    CHECK(e.to_string() == "(((3 + 4) * 2) / 7)");
}

TEST_CASE("infix precedence without parentheses") {
    auto e = make_expr(Expression::mode::INFIX, "3 + 4 * 2");
    CHECK(e.evaluate() == "11");
    CHECK(e.to_string() == "(3 + (4 * 2))");
}

TEST_CASE("infix with parentheses altering precedence") {
    auto e = make_expr(Expression::mode::INFIX, "( 3 + 4 ) * 2");
    CHECK(e.evaluate() == "14");
    CHECK(e.to_string() == "((3 + 4) * 2)");
}

TEST_CASE("prefix parsing equivalent to infix") {
    auto e = make_expr(Expression::mode::PREFIX, "+ 3 * 4 2");
    CHECK(e.evaluate() == "11");
    CHECK(e.to_string() == "(3 + (4 * 2))");
}

TEST_CASE("postfix real division formatting") {
    Expression e{"3 2 /"};
    CHECK(e.evaluate() == "1.50");
    CHECK(e.to_string() == "(3 / 2)");
}

TEST_CASE("power right associativity") {
    auto e = make_expr(Expression::mode::INFIX, "2 ^ 3 ^ 2"); // 2^(3^2)=512
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
