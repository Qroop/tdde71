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

}
// Fill with more tests of other functions and operators!

