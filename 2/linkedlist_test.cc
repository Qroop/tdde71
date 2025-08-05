#include "catch.hpp"
#include "LinkedList.h"
#include <stdexcept>
#include <utility>

using namespace std;

TEST_CASE("Constructors and basic properties")
{
    SECTION("Default constructor")
    {
        LinkedList list;
        CHECK(list.is_empty() == true);
        CHECK(list.size() == 0);
        CHECK(list.to_string() == "[]");
    }

    SECTION("Copy constructor with empty list")
    {
        LinkedList original;
        LinkedList copy(original);
        CHECK(copy.is_empty() == true);
        CHECK(copy.size() == 0);
        CHECK(copy.to_string() == "[]");
    }

    SECTION("Copy constructor with populated list")
    {
        LinkedList original;
        original.insert(1);
        original.insert(2);
        original.insert(3);
        
        LinkedList copy(original);
        CHECK(copy.size() == 3);
        CHECK(copy.to_string() == "[3, 2, 1]");
        
        original.insert(4);
        CHECK(original.size() == 4);
        CHECK(copy.size() == 3);
        CHECK(copy.to_string() == "[3, 2, 1]");
    }

    SECTION("Move constructor")
    {
        LinkedList original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);
        
        LinkedList moved(std::move(original));
        CHECK(moved.size() == 3);
        CHECK(moved.to_string() == "[1, 2, 3]");
        CHECK(original.size() == 0);
        CHECK(original.is_empty());
    }

    SECTION("Move assignment operator")
    {
        LinkedList original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);
        
        LinkedList target;
        target.push_back(99);
        
        target = std::move(original);
        CHECK(target.size() == 3);
        CHECK(target.to_string() == "[1, 2, 3]");
        CHECK(original.size() == 0);
        CHECK(original.is_empty());
    }
}

TEST_CASE("Insert operations")
{
    SECTION("Insert to empty list")
    {
        LinkedList list;
        list.insert(42);
        CHECK(list.size() == 1);
        CHECK(list.front() == 42);
        CHECK(list.back() == 42);
        CHECK(list.to_string() == "[42]");
        CHECK_FALSE(list.is_empty());
    }

    SECTION("Insert multiple values (inserts at front)")
    {
        LinkedList list;
        list.insert(1);
        list.insert(2);
        list.insert(3);
        
        CHECK(list.size() == 3);
        CHECK(list.front() == 3);
        CHECK(list.back() == 1);
        CHECK(list.to_string() == "[3, 2, 1]");
    }

    SECTION("Push back to empty list")
    {
        LinkedList list;
        list.push_back(42);
        CHECK(list.size() == 1);
        CHECK(list.front() == 42);
        CHECK(list.back() == 42);
        CHECK(list.to_string() == "[42]");
    }

    SECTION("Push back multiple values")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        
        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
        CHECK(list.to_string() == "[1, 2, 3]");
    }

    SECTION("Mixed insert and push_back")
    {
        LinkedList list;
        list.push_back(2);
        list.insert(1);
        list.push_back(3);
        list.insert(0);
        
        CHECK(list.size() == 4);
        CHECK(list.front() == 0);
        CHECK(list.back() == 3);
        CHECK(list.to_string() == "[0, 1, 2, 3]");
    }
}

TEST_CASE("Access operations")
{
    SECTION("front() and back() on empty list throws")
    {
        LinkedList list;
        CHECK_THROWS_AS(list.front(), std::out_of_range);
        CHECK_THROWS_AS(list.back(), std::out_of_range);
    }

    SECTION("front() and back() on single element")
    {
        LinkedList list;
        list.insert(42);
        CHECK(list.front() == 42);
        CHECK(list.back() == 42);
    }

    SECTION("front() and back() on multiple elements")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
    }

    SECTION("get() with valid indices")
    {
        LinkedList list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        list.push_back(40);
        
        CHECK(list.get(0) == 10);
        CHECK(list.get(1) == 20);
        CHECK(list.get(2) == 30);
        CHECK(list.get(3) == 40);
    }

    SECTION("get() with invalid indices throws")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        
        CHECK_THROWS_AS(list.get(2), std::out_of_range);
        CHECK_THROWS_AS(list.get(100), std::out_of_range);
        
        LinkedList empty;
        CHECK_THROWS_AS(empty.get(0), std::out_of_range);
    }
}

TEST_CASE("Pop operations")
{
    SECTION("pop_front() on empty list throws")
    {
        LinkedList list;
        CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    }

    SECTION("pop_back() on empty list throws")
    {
        LinkedList list;
        CHECK_THROWS_AS(list.pop_back(), std::out_of_range);
    }

    SECTION("pop_front() on single element")
    {
        LinkedList list;
        list.insert(42);
        
        int value = list.pop_front();
        CHECK(value == 42);
        CHECK(list.is_empty());
        CHECK(list.size() == 0);
        CHECK(list.to_string() == "[]");
    }

    SECTION("pop_back() on single element")
    {
        LinkedList list;
        list.insert(42);
        
        int value = list.pop_back();
        CHECK(value == 42);
        CHECK(list.is_empty());
        CHECK(list.size() == 0);
        CHECK(list.to_string() == "[]");
    }

    SECTION("pop_front() on multiple elements")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        
        int value = list.pop_front();
        CHECK(value == 1);
        CHECK(list.size() == 2);
        CHECK(list.front() == 2);
        CHECK(list.back() == 3);
        CHECK(list.to_string() == "[2, 3]");
    }

    SECTION("pop_back() on multiple elements")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        
        int value = list.pop_back();
        CHECK(value == 3);
        CHECK(list.size() == 2);
        CHECK(list.front() == 1);
        CHECK(list.back() == 2);
        CHECK(list.to_string() == "[1, 2]");
    }

    SECTION("Alternating pop operations")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        
        CHECK(list.pop_front() == 1);
        CHECK(list.pop_back() == 4);
        CHECK(list.pop_front() == 2);
        CHECK(list.pop_back() == 3);
        
        CHECK(list.is_empty());
        CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
        CHECK_THROWS_AS(list.pop_back(), std::out_of_range);
    }
}

TEST_CASE("Clear operation")
{
    SECTION("Clear empty list")
    {
        LinkedList list;
        list.clear();
        CHECK(list.is_empty());
        CHECK(list.size() == 0);
    }

    SECTION("Clear populated list")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        
        list.clear();
        CHECK(list.is_empty());
        CHECK(list.size() == 0);
        CHECK(list.to_string() == "[]");
        
        list.push_back(42);
        CHECK(list.size() == 1);
        CHECK(list.front() == 42);
    }
}

TEST_CASE("to_string() formatting")
{
    SECTION("Empty list")
    {
        LinkedList list;
        CHECK(list.to_string() == "[]");
    }

    SECTION("Single element")
    {
        LinkedList list;
        list.insert(42);
        CHECK(list.to_string() == "[42]");
    }

    SECTION("Multiple elements")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        CHECK(list.to_string() == "[1, 2, 3]");
    }

    SECTION("Negative numbers")
    {
        LinkedList list;
        list.push_back(-5);
        list.push_back(0);
        list.push_back(10);
        CHECK(list.to_string() == "[-5, 0, 10]");
    }

    SECTION("Large numbers")
    {
        LinkedList list;
        list.push_back(1000);
        list.push_back(999999);
        CHECK(list.to_string() == "[1000, 999999]");
    }
}

TEST_CASE("Edge cases and stress tests")
{
    SECTION("Many insertions at front")
    {
        LinkedList list;
        for (int i = 0; i < 100; ++i) {
            list.insert(i);
        }
        
        CHECK(list.size() == 100);
        CHECK(list.front() == 99);
        CHECK(list.back() == 0);
        
        for (int i = 0; i < 100; ++i) {
            CHECK(list.get(i) == static_cast<int>(99 - i));
        }
    }

    SECTION("Many insertions at back")
    {
        LinkedList list;
        for (int i = 0; i < 100; ++i) {
            list.push_back(i);
        }
        
        CHECK(list.size() == 100);
        CHECK(list.front() == 0);
        CHECK(list.back() == 99);
        
        for (int i = 0; i < 100; ++i) {
            CHECK(list.get(i) == static_cast<int>(i));
        }
    }

    SECTION("Build up and tear down")
    {
        LinkedList list;
        
        for (int i = 0; i < 50; ++i) {
            list.push_back(i);
        }
        CHECK(list.size() == 50);
        
        for (int i = 0; i < 25; ++i) {
            CHECK(list.pop_front() == i);
        }
        CHECK(list.size() == 25);
        CHECK(list.front() == 25);
        
        for (int i = 49; i >= 25; --i) {
            CHECK(list.pop_back() == i);
        }
        CHECK(list.is_empty());
    }

    SECTION("Interleaved operations")
    {
        LinkedList list;
        
        list.push_back(1);
        list.insert(0);
        list.push_back(2);
        CHECK(list.pop_front() == 0);
        list.insert(-1);
        CHECK(list.pop_back() == 2);
        list.push_back(3);
        
        CHECK(list.size() == 3);
        CHECK(list.to_string() == "[-1, 1, 3]");
    }
}

TEST_CASE("Destructor and memory management")
{
    SECTION("Destructor called on scope exit")
    {
        {
            LinkedList list;
            for (int i = 0; i < 10; ++i) {
                list.push_back(i);
            }
            CHECK(list.size() == 10);
        }
        
        LinkedList another_list;
        another_list.push_back(42);
        CHECK(another_list.size() == 1);
    }

    SECTION("Copy constructor creates independent copy")
    {
        LinkedList original;
        original.push_back(1);
        original.push_back(2);
        
        {
            LinkedList copy(original);
            copy.push_back(3);
            CHECK(copy.size() == 3);
            CHECK(original.size() == 2);
        }
        
        CHECK(original.size() == 2);
        CHECK(original.to_string() == "[1, 2]");
    }
}

TEST_CASE("Sort function")
{
    SECTION("Sort empty list")
    {
        LinkedList list;
        sort(list);
        CHECK(list.is_empty());
        CHECK(list.to_string() == "[]");
    }

    SECTION("Sort single element")
    {
        LinkedList list;
        list.push_back(42);
        sort(list);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 42);
        CHECK(list.to_string() == "[42]");
    }

    SECTION("Sort already sorted list")
    {
        LinkedList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);
        
        sort(list);
        CHECK(list.size() == 5);
        CHECK(list.to_string() == "[1, 2, 3, 4, 5]");
    }

    SECTION("Sort reverse sorted list")
    {
        LinkedList list;
        list.push_back(5);
        list.push_back(4);
        list.push_back(3);
        list.push_back(2);
        list.push_back(1);
        
        sort(list);
        CHECK(list.size() == 5);
        CHECK(list.to_string() == "[1, 2, 3, 4, 5]");
    }

    SECTION("Sort randomly ordered list")
    {
        LinkedList list;
        list.push_back(3);
        list.push_back(1);
        list.push_back(4);
        list.push_back(1);
        list.push_back(5);
        list.push_back(9);
        list.push_back(2);
        list.push_back(6);
        
        sort(list);
        CHECK(list.size() == 8);
        CHECK(list.to_string() == "[1, 1, 2, 3, 4, 5, 6, 9]");
    }

    SECTION("Sort list with duplicates")
    {
        LinkedList list;
        list.push_back(5);
        list.push_back(2);
        list.push_back(5);
        list.push_back(1);
        list.push_back(2);
        list.push_back(1);
        
        sort(list);
        CHECK(list.size() == 6);
        CHECK(list.to_string() == "[1, 1, 2, 2, 5, 5]");
    }

    SECTION("Sort list with negative numbers")
    {
        LinkedList list;
        list.push_back(-3);
        list.push_back(1);
        list.push_back(-1);
        list.push_back(0);
        list.push_back(2);
        list.push_back(-5);
        
        sort(list);
        CHECK(list.size() == 6);
        CHECK(list.to_string() == "[-5, -3, -1, 0, 1, 2]");
    }

    SECTION("Sort two elements")
    {
        LinkedList list1;
        list1.push_back(2);
        list1.push_back(1);
        
        sort(list1);
        CHECK(list1.to_string() == "[1, 2]");
        
        LinkedList list2;
        list2.push_back(1);
        list2.push_back(2);
        
        sort(list2);
        CHECK(list2.to_string() == "[1, 2]");
    }

    SECTION("Sort maintains list structure")
    {
        LinkedList list;
        list.push_back(3);
        list.push_back(1);
        list.push_back(2);
        
        sort(list);
        
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
        CHECK(list.size() == 3);
        CHECK_FALSE(list.is_empty());
        
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    SECTION("Sort large list")
    {
        LinkedList list;
        for (int i = 20; i >= 1; --i) {
            list.push_back(i);
        }
        
        sort(list);
        CHECK(list.size() == 20);
        
        for (int i = 0; i < 20; ++i) {
            CHECK(list.get(i) == static_cast<int>(i + 1));
        }
    }

    SECTION("Sort preserves original functionality")
    {
        LinkedList list;
        list.push_back(5);
        list.push_back(1);
        list.push_back(3);
        
        sort(list);
        
        list.push_back(4);
        list.insert(0);
        
        CHECK(list.to_string() == "[0, 1, 3, 5, 4]");
        
        CHECK(list.pop_front() == 0);
        CHECK(list.pop_back() == 4);
        CHECK(list.to_string() == "[1, 3, 5]");
    }
}
