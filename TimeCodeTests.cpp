

#include <cassert>
#include <stdexcept>

#include "TimeCode.h"
#include "TimeCode_Tests.h"

using namespace std;


void TestComponentsToSeconds(){

	// test 1, Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// test 2
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	assert(t2 == 0);
	
	// test 3, t3 is bigger than a 32 bit signed int
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(900000, 0, 0);
	//cout << "t3: " << t3 << endl; 
	assert(t3 == 3240000000);
	
}


void TestDefaultConstructor(){

	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	

}


void TestComponentConstructor(){

	
	// test 1
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// test 2, Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	//cout << "tc2: " << tc2.ToString() << endl;
	assert(tc2.ToString() == "3:17:42");
	
	// test3, Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// test 4, default values
	TimeCode tc4 = TimeCode(3, 5);
	assert(tc4.ToString() == "3:5:0");
	TimeCode tc5 = TimeCode(3);
	assert(tc5.ToString() == "3:0:0");
	
	
	// test 6, Really really big seconds value
	TimeCode tc6 = TimeCode(0, 0, 13241341347);
	//cout << tc6.ToString() << endl;
	assert(tc6.ToString() == "3678150:22:27");
	
}


void TestGetComponents(){

	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// test 1, Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// test2, Rollover values
	TimeCode tc2 = TimeCode(6, 72, 89);
	tc2.GetComponents(h, m, s);
	assert(h == 7 && m == 13 && s == 29);
	
}


void TestGetTimeCodeAsSeconds(){

	TimeCode tc = TimeCode(7, 16, 18);
	long long unsigned int TotalSeconds = tc.GetTimeCodeAsSeconds();
	assert(TotalSeconds == 26178);
	
}
	

void TestCopyConstructor(){

	
	// test 1
	TimeCode tc = TimeCode(3, 17, 42);
	TimeCode tc2 = TimeCode(tc);
	assert(tc2.ToString() == "3:17:42");
	
	// test 2
	TimeCode tc3 = TimeCode(3, 71, 3801);
	TimeCode tc4 = TimeCode(tc3);
	assert(tc3.ToString() == "5:14:21");
	assert(tc4.ToString() == "5:14:21");
	
	// test 3
	tc3.SetHours(8);
	assert(tc3.ToString() == "8:14:21");
	assert(tc4.ToString() == "5:14:21");
	
}


void TestGetHours(){

	TimeCode tc = TimeCode(8, 5, 9);
	assert(tc.GetHours() == 8);

}


void TestGetMinutes(){

	TimeCode tc = TimeCode(8, 5, 9);
	assert(tc.GetMinutes() == 5);

}


void TestGetSeconds(){

	TimeCode tc = TimeCode(8, 5, 9);
	assert(tc.GetSeconds() == 9);

}


void TestSetHours(){

	TimeCode tc = TimeCode(8, 5, 9);
	
	// test 1
	tc.SetHours(18);
	assert(tc.ToString() == "18:5:9");
	
	// test 2
	tc.SetHours(600);
	assert(tc.ToString() == "600:5:9");	
	
}


void TestSetMinutes(){

	TimeCode tc = TimeCode(8, 5, 9);
	
	// test 1
	tc.SetMinutes(15);
	assert(tc.ToString() == "8:15:9");
	
	// test 2
	try{
		tc.SetMinutes(80);
	}
	catch( const invalid_argument& e ) {
		//cout << e.what() << endl;
	}
	assert(tc.ToString() == "8:15:9");
	
}


void TestSetSeconds(){

	TimeCode tc = TimeCode(8, 5, 9);
	
	// test 1
	tc.SetSeconds(19);
	assert(tc.ToString() == "8:5:19");
	
	// test 2
	try{
		tc.SetSeconds(80);
	}
	catch( const invalid_argument& e) {
	}
	assert(tc.ToString() == "8:5:19");
	
}


void TestReset(){

	
	TimeCode tc1 = TimeCode(57, 62, 39);
	assert(tc1.ToString() == "58:2:39");
	tc1.reset();
	assert(tc1.ToString() == "0:0:0");
	
}


void TestAdd(){

	
	// test 1
	TimeCode tc1 = TimeCode(5, 58, 0);
	TimeCode tc2 = TimeCode(0, 1, 65);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "6:0:5");
	
	// test 2
	TimeCode tc4 = TimeCode(0, 0, 60);
	TimeCode tc5 = TimeCode(0, 0, 60);
	TimeCode tc6 = tc4 + tc5;
	assert(tc6.ToString() == "0:2:0");
	
}


void TestSubtract(){

	
	// test 1
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	// test 2
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	
}


void TestMultiply(){

	
	// test 1
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 * 2;
	assert(tc2.ToString() == "0:2:0");
	
	// test 2
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 * 5.5;
	//cout << "tc4: " << tc4.ToString() << endl;
	assert(tc4.ToString() == "16:59:3");
	
	// test 3
	TimeCode tc5 = TimeCode(0, 5, 0);
	TimeCode tc6 = tc5 * 2.5;
	assert(tc6.ToString() == "0:12:30");
	
	// test 4
	TimeCode tc7 = TimeCode(0, 5, 0);
	TimeCode tc8 = tc7 * 0.5;
	assert(tc8.ToString() == "0:2:30");

	// test 5, negative number test
	try{
		TimeCode tc10 = tc7 * -2;
		cout << "\t\t\ttc10:" << tc10.ToString() << endl;
		assert(false);
	} catch (const invalid_argument& e){
		
	}
	
	
	// test 6, multiply by 0
	TimeCode tc12 = tc7 * 0;
	assert(tc12.ToString() == "0:0:0");
	
}


void TestDivide(){

	
	// test 1
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = tc1 / 4;
	assert(tc2.ToString() == "0:15:0");
	
	// test 2
	TimeCode tc3 = TimeCode(0, 15, 0);
	TimeCode tc4 = tc3 / 0.5;
	assert(tc4.ToString() == "0:30:0");
	
	// test 3 (negative value test)
	try{
		TimeCode tc5 = tc3 / -3.0;
		//cout << "tc5:" << tc5.ToString() << endl;
		assert(false);
	} catch (const invalid_argument& e){
		
	}
	
}


void TestEquals(){

	TimeCode tc1 = TimeCode(87, 32, 64);
	TimeCode tc2 = TimeCode(87, 32, 64);
	TimeCode tc3 = TimeCode(1, 2, 3);
	
	assert(tc1 == tc2); // test 1
	assert(tc1 != tc3); // test 2
	
}


void TestLessThan(){
	TimeCode tc1 = TimeCode(2, 0, 0);
	TimeCode tc2 = TimeCode(0, 15, 0);
	TimeCode tc3 = TimeCode(2, 0, 0);
	
	assert( !(tc1 < tc2) ); // test 1
	assert(tc2 < tc1); // test 2
	assert(tc1 <= tc3); // 3
	assert(!(tc1 < tc3)); // 4
	
}


void TestGreaterThan(){

	TimeCode tc1 = TimeCode(3, 0, 0);
	TimeCode tc2 = TimeCode(0, 40, 0);
	TimeCode tc3 = TimeCode(3, 0, 0);
	
	assert( !(tc2 > tc1) ); // test 1
	assert(tc1 > tc2); // 2
	assert(tc1>=tc3); // 3
	assert(!(tc1>tc3)); // 4

}


void TestAverage(){
	
	// test 1
	TimeCode tc1 = TimeCode(5, 0, 0);
	TimeCode tc2 = TimeCode(6, 0, 0);
	TimeCode ans = TimeCode(5, 30, 0);
	assert( ((tc1 + tc2) / 2.0) == ans); // test 1
	
	// test 2
	TimeCode tc3 = TimeCode(2, 15, 30);
	TimeCode tc4 = TimeCode(3, 45, 5);
	TimeCode tc5 = TimeCode(1, 28, 31);
	ans = TimeCode(2, 29, 42);
	TimeCode res = (tc3 + tc4 + tc5) / 3.0; 
	assert(res == ans); // test 2
}


void ALL(){
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestGetTimeCodeAsSeconds();
	TestCopyConstructor();
	
	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();
	
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();
	
	TestReset();
	
	TestAdd();
	TestSubtract();
	TestMultiply();
	TestDivide();

	
	TestEquals();
	TestLessThan();
	TestGreaterThan();
	
	TestAverage();
}