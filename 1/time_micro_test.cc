#include "catch.hpp"
#include "TimeMicro.h"

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      TimeMicro empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      TimeMicro t0{0,0,0};
      TimeMicro t1{12,30,30};
      TimeMicro t2{23,59,59};

      CHECK_THROWS( TimeMicro{13,35,60} );
      CHECK_THROWS( TimeMicro{13,60,35} );
      CHECK_THROWS( TimeMicro{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("String")
   {
      TimeMicro t0{"00:00:00"};
      TimeMicro t1{"12:30:30"};
      TimeMicro t2{"23:59:59"};

      CHECK_THROWS( TimeMicro{"13:35:60"} );
      CHECK_THROWS( TimeMicro{"13:60:35"} );
      CHECK_THROWS( TimeMicro{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
}
TEST_CASE("String constructor with milliseconds")
{
   SECTION("HH:MM:SS:TTT format")
   {
      TimeMicro t0{"00:00:00:000"};
      TimeMicro t1{"12:30:30:123"};
      TimeMicro t2{"23:59:59:999"};

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("Milliseconds validation")
   {
      // Valid milliseconds
      CHECK_NOTHROW( TimeMicro{"12:30:30:000"} );
      CHECK_NOTHROW( TimeMicro{"12:30:30:500"} );
      CHECK_NOTHROW( TimeMicro{"12:30:30:999"} );
      
      // Invalid milliseconds (> 999)
      CHECK_THROWS( TimeMicro{"12:30:30:1000"} );
   }

   SECTION("Both formats work")
   {
      TimeMicro t1{"12:30:30"};     // HH:MM:SS format
      TimeMicro t2{"12:30:30:000"}; // HH:MM:SS:TTT format with 0 milliseconds
      
      // These should be equivalent
      CHECK( t1.get_hour() == t2.get_hour() );
      CHECK( t1.get_minute() == t2.get_minute() );
      CHECK( t1.get_second() == t2.get_second() );
      CHECK( t1.to_string() == t2.to_string() );
   }

   SECTION("Milliseconds precision")
   {
      TimeMicro t1{"12:30:30:100"};
      TimeMicro t2{"12:30:30:200"};
      TimeMicro t3{"12:30:30:999"};
      TimeMicro t4{"12:30:30:000"};
      
      // Since milliseconds are truncated in this implementation,
      // times with milliseconds < 1000 should be equivalent to the base time
      CHECK( t1.get_hour() == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      
      // All should be equal since milliseconds are truncated
      CHECK( t1 == t2 );
      CHECK( t1 == t3 );
      CHECK( t1 == t4 );
   }
}
TEST_CASE ("is_am") 
{
   TimeMicro t0{"05:00:00"};
   TimeMicro t1{"14:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   CHECK       ( TimeMicro{"00:00:00"}.is_am() );   
   CHECK_FALSE ( TimeMicro{"12:00:00"}.is_am() );   
   CHECK_FALSE ( TimeMicro{"23:59:59"}.is_am() );   
   CHECK       ( TimeMicro{"11:59:59"}.is_am() );   
}

TEST_CASE ("to_string")
{
   TimeMicro t0{};
   TimeMicro t1{11, 59, 59};
   TimeMicro t2{12, 0, 0};
   TimeMicro t3{13, 0, 0};
   TimeMicro t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
      CHECK( TimeMicro{0,0,1}.to_string() == "00:00:01" );
      CHECK( TimeMicro{9,5,7}.to_string() == "09:05:07" );
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK( t0.to_string(false) == "00:00:00" );
      CHECK( t1.to_string(false) == "11:59:59" );
      CHECK( t2.to_string(false) == "12:00:00" );
      CHECK( t3.to_string(false) == "13:00:00" );
      CHECK( t4.to_string(false) == "23:59:59" );
      CHECK( TimeMicro{1,2,3}.to_string(false) == "01:02:03" );
   } 

   SECTION("12 hour format")
   {
      CHECK( t0.to_string(true) == "12:00:00am" );
      CHECK( t1.to_string(true) == "11:59:59am" );
      CHECK( t2.to_string(true) == "12:00:00pm" );
      CHECK( t3.to_string(true) == "1:00:00pm" );
      CHECK( t4.to_string(true) == "11:59:59pm" );
      CHECK( TimeMicro{0,0,1}.to_string(true) == "12:00:01am" );
      CHECK( TimeMicro{12,1,1}.to_string(true) == "12:01:01pm" );
      CHECK( TimeMicro{1,2,3}.to_string(true) == "1:02:03am" );
   }
}

TEST_CASE("operators") {
	SECTION("comparison") {
		TimeMicro t0{12, 30, 30};
		TimeMicro t1{12, 30, 30};
		TimeMicro t2{23, 59, 59};
		TimeMicro t3{23, 59, 58};

		CHECK( t0 == t1 );
		CHECK( t0 != t2 );
		CHECK( t0 < t2 );
		CHECK( t0 <= t1 );
		CHECK( t2 > t0 );
		CHECK( t2 >= t1 );

		CHECK( !(t0 < t1) );
		CHECK( !(t0 > t2) );
		CHECK( !(t2 < t3) );

	}
	SECTION("increment/decrement") {
		TimeMicro t0{12, 30, 30};
		TimeMicro t1{23, 59, 59};

		CHECK( (t0++).to_string() == "12:30:30" );
		CHECK( t0.to_string() == "12:30:31" );

		CHECK( (++t0).to_string() == "12:30:32" );
		CHECK( t0.to_string() == "12:30:32" );

		CHECK( (t1--).to_string() == "23:59:59" );
		CHECK( t1.to_string() == "23:59:58" );

		CHECK( (--t1).to_string() == "23:59:57" );
		CHECK( t1.to_string() == "23:59:57" );

		// Wrap around tests
		TimeMicro t2{23, 59, 59};
		CHECK( (++t2).to_string() == "00:00:00" );
		CHECK( t2.to_string() == "00:00:00" );
	}
	
	SECTION("subtraction") {
		TimeMicro t1{12, 30, 30};
		TimeMicro t2{12, 30, 35};
		TimeMicro t3{13, 30, 30};
		TimeMicro t4{12, 31, 30};

		// Simple difference in seconds
		CHECK( (t2 - t1) == 5.0f );
		CHECK( (t1 - t2) == -5.0f );
		
		// Difference in hours (3600 seconds)
		CHECK( (t3 - t1) == 3600.0f );
		CHECK( (t1 - t3) == -3600.0f );
		
		// Difference in minutes (60 seconds)
		CHECK( (t4 - t1) == 60.0f );
		CHECK( (t1 - t4) == -60.0f );
		
		// Same time should give 0
		TimeMicro t5{12, 30, 30};
		CHECK( (t1 - t5) == 0.0f );
		
		// Cross-day difference
		TimeMicro morning{6, 0, 0};
		TimeMicro evening{18, 0, 0};
		CHECK( (evening - morning) == 12 * 3600.0f ); // 12 hours = 43200 seconds
		
		// Test with string constructor
		TimeMicro str1{"10:15:30"};
		TimeMicro str2{"10:15:45"};
		CHECK( (str2 - str1) == 15.0f );
	}

}

