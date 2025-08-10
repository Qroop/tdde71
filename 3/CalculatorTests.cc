#include "catch.hpp"
#include <stdexcept>
#include <utility>
#include "Calculator.h"

using namespace std;

TEST_CASE("Calculator basic operations") {
    SECTION("Integer initialization") {
        Integer integer1;
        Integer integer2(1);
        
        CHECK(integer1.evaluate() == 0);
        CHECK(integer2.evaluate() == 1);
    }
    SECTION("Real number initialization") {
        Real real1;
        Real real2(1);
        
        CHECK(real1.evaluate() == 0);
        CHECK(real2.evaluate() == 1);
    }
}
