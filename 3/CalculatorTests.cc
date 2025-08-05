#include "catch.hpp"
#include <stdexcept>
#include <utility>
#include "Calculator.h"

using namespace std;

TEST_CASE("Calculator basic operations") {
    SECTION("Integer initialization") {
        Integer integer1;
        Integer integer2(1);
        
        CHECK(integer1.get_value() == 0);
        CHECK(integer2.get_value() == 1);
    }
}
