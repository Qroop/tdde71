#include "Expression.h"

#include "catch.hpp"

TEST_CASE("expression construction")
{
	Expression e{"3 4 + 5 *"};
	CHECK( e.to_string() == "((3 + 4) * 5)" );
	CHECK( e.evaluate() == "35" );
}

