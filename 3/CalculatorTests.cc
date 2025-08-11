#include <limits>
#include <cmath> // abs
#include "Calculator.h"

#include "catch.hpp"

TEST_CASE("operand real")
{
	Operand* pi{ new Real{3.14} };

	CHECK( pi->evaluate() == 3.14 );
	CHECK( pi->prefix() == "3.140" );
	CHECK( pi->infix() == "3.140" );
	CHECK( pi->postfix() == "3.140" );
	
	delete pi;
}
// If catch report 0.42 != 0.42 you are likely to have a small
// rounding error in some invisible decimal place. In such case you
// can compare if the difference is small enough to consider two
// doubles equal anyway.
bool compare_equal(double a, double b)
{
    return std::abs(a - b) <= std::numeric_limits<double>::epsilon();
}

TEST_CASE("addition")
{
	Node* pi = new Real{3.14};
	Node* e = new Real{2.72};
	Node* pluslr = new Addition{pi, e};

	CHECK( compare_equal(pluslr->evaluate(), 5.86) );
	CHECK( pluslr->prefix() == "+ 3.140 2.720" );
	CHECK( pluslr->postfix() == "3.140 2.720 +" );
	CHECK( pluslr->infix() == "( 3.140 + 2.720 )" );

	delete pluslr;
}

TEST_CASE("subtraction")  
{
    Node* pi = new Real{3.14};
    Node* e = new Real{2.72};
    Node* minuslr = new Subtraction{pi, e};

    CHECK( compare_equal(minuslr->evaluate(), 0.42) );
    CHECK( minuslr->prefix() == "- 3.140 2.720" );
    CHECK( minuslr->postfix() == "3.140 2.720 -" );
    CHECK( minuslr->infix() == "( 3.140 - 2.720 )" );

	delete minuslr;
}


TEST_CASE("test case ignoring rounding errors")
{
	Node* a = new Real{0.01};
	Node* b = new Real{0.09};
	Node* plus = new Addition{a, b};

	CHECK( std::abs(-0.1) == 0.1 ); // make sure we use correct "abs"
	// CHECK( plus->evaluate() == 0.1 ); // Rounding error!!
	CHECK( compare_equal(plus->evaluate(), 0.1) );

	delete plus;
}



TEST_CASE("operand integer")
{
	Operand* i = new Integer{7};

	CHECK( i->evaluate() == 7 );
	CHECK( i->prefix() == "7" );
	CHECK( i->infix() == "7" );
	CHECK( i->postfix() == "7" );

	delete i;
}

TEST_CASE("conversion to string")
{
    Node* a = new Addition{ new Subtraction{ new Real{1.0},
                                             new Integer{1} },
                            new Multiplication{ new Integer{2},
                                                new Integer{5} }
    };
    SECTION("prefix")
    {
        CHECK( a->prefix() == "+ - 1.000 1 * 2 5" );
    }
    SECTION("infix")
    {
        CHECK( a->infix() == "( ( 1.000 - 1 ) + ( 2 * 5 ) )" );
    }
    SECTION("postfix")
    {
        CHECK( a->postfix() == "1.000 1 - 2 5 * +" );
    }

	delete a;
}

TEST_CASE("multiplication")
{
	Node* a = new Real{3.00};
	Node* b = new Real{2.50};
	Node* prod = new Multiplication{a, b};

	CHECK( compare_equal(prod->evaluate(), 7.5) );
	CHECK( prod->prefix() == "* 3.000 2.500" );
	CHECK( prod->postfix() == "3.000 2.500 *" );
	CHECK( prod->infix() == "( 3.000 * 2.500 )" );

	delete prod;
}

TEST_CASE("division")
{
	Node* a = new Real{7.50};
	Node* b = new Real{2.50};
	Node* div = new Division{a, b};

	CHECK( compare_equal(div->evaluate(), 3.0) );
	CHECK( div->prefix() == "/ 7.500 2.500" );
	CHECK( div->postfix() == "7.500 2.500 /" );
	CHECK( div->infix() == "( 7.500 / 2.500 )" );

	delete div;

	SECTION("division by zero throws")
	{
		Node* x = new Real{5.0};
		Node* zero = new Real{0.0};
		Node* divzero = new Division{x, zero};
		CHECK_THROWS_AS( divzero->evaluate(), std::logic_error );

		delete divzero;
	}
	SECTION("negative division and sign")
	{
		Node* neg = new Real{-7.5};
		Node* pos = new Real{2.5};
		Node* d1 = new Division{neg, pos};
		CHECK( compare_equal(d1->evaluate(), -3.0) );

		delete d1;
	}
	SECTION("negative division and sign reversed")
	{
		Node* pos = new Real{2.5};
		Node* neg = new Real{-7.5};
		Node* d2 = new Division{pos, neg};
		CHECK( compare_equal(d2->evaluate(), -1.0/3.0) );

		delete d2;
	}
	SECTION("small divisor precision")
	{
		Node* one = new Real{1.0};
		Node* tiny = new Real{1e-6};
		Node* d = new Division{one, tiny};
		CHECK( compare_equal(d->evaluate(), 1e6) );

		delete d;
	}
}

TEST_CASE("modulus")
{
	Node* a = new Real{7.50};
	Node* b = new Real{2.00};
	Node* mod = new Modulus{a, b};

	CHECK( compare_equal(mod->evaluate(), std::fmod(7.50, 2.00)) );
	CHECK( compare_equal(mod->evaluate(), 1.5) );
	CHECK( mod->prefix() == "% 7.500 2.000" );
	CHECK( mod->postfix() == "7.500 2.000 %" );
	CHECK( mod->infix() == "( 7.500 % 2.000 )" );

	delete mod;

	SECTION("negative left operand sign")
	{
		Node* negA = new Real{-7.50};
		Node* two = new Real{2.00};
		Node* m = new Modulus{negA, two};
		CHECK( compare_equal(m->evaluate(), std::fmod(-7.50, 2.00)) );
		CHECK( compare_equal(m->evaluate(), -1.5) );

		delete m;
	}
}

TEST_CASE("power")
{
	SECTION("positive base integer exponent")
	{
		Node* two = new Real{2.0};
		Node* three = new Real{3.0};
		Node* p = new Power{two, three};
		CHECK( compare_equal(p->evaluate(), 8.0) );
		CHECK( p->prefix() == "^ 2.000 3.000" );
		CHECK( p->postfix() == "2.000 3.000 ^" );
		CHECK( p->infix() == "( 2.000 ^ 3.000 )" );

		delete p;
	}
	SECTION("positive base fractional exponent")
	{
		Node* nine = new Real{9.0};
		Node* half = new Real{0.5};
		Node* p = new Power{nine, half};
		CHECK( compare_equal(p->evaluate(), 3.0) );

		delete p;
	}
	SECTION("negative base integer exponent")
	{
		Node* negtwo = new Real{-2.0};
		Node* three = new Real{3.0};
		Node* p = new Power{negtwo, three};
		CHECK( compare_equal(p->evaluate(), -8.0) );

		delete p;
	}
	SECTION("negative base non-integer exponent throws")
	{
		Node* negtwo = new Real{-2.0};
		Node* half = new Real{0.5};
		Node* p = new Power{negtwo, half};
		CHECK_THROWS_AS( p->evaluate(), std::logic_error );

		delete p;
	}
	SECTION("zero base non-positive exponent throws")
	{
		Node* zero = new Real{0.0};
		Node* negone = new Real{-1.0};
		Node* p = new Power{zero, negone};
		CHECK_THROWS_AS( p->evaluate(), std::logic_error );

		delete p;
	}
	SECTION("zero power zero throws")
	{
		Node* zero1 = new Real{0.0};
		Node* zero2 = new Real{0.0};
		Node* p = new Power{zero1, zero2};
		CHECK_THROWS_AS( p->evaluate(), std::logic_error );

		delete p;
	}
}

TEST_CASE("integer default constructor")
{
	Operand* i = new Integer{}; // default should be 0
	CHECK( i->evaluate() == 0 );
	CHECK( i->prefix() == "0" );
	CHECK( i->infix() == "0" );
	CHECK( i->postfix() == "0" );

	delete i;
}

