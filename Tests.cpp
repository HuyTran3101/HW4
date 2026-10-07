
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <climits>

#include "Sim_Math.h"
#include "TimeCode_Tests.h"
#include "BigInteger_Tests.h"

using namespace std;

void power_tests(){
	cout << "\tpower tests..." ;
	assert(power(2, 0) == 1);
	assert(power(2, 1) == 2);
	assert(power(2, 2) == 4);
	assert(power(0, 0) == 1);
	assert(power(0, 1) == 0);
	assert(power(1, 0) == 1);
	assert(power(2, 15) == 32768);
	assert(power(2, 30) == 1073741824);
	assert(power(2, 46) == 70368744177664);

	assert(power(e, -3) == 0.049787068367863951);
	cout << " PASSED!" << endl;
}



void poisson_tests(){
	cout << "\tpoisson tests...";

	//vector<int> samples;
	unordered_map<int, int> freq_counts;
	for(int i = 0; i < 100; i++){
		int tmp = poisson(3);
		//cout << "\t\t" << tmp << endl;
		freq_counts[tmp]++;
	}

	int most_frequent = -1;
	int largest_count = INT_MIN;
	for(const auto& p : freq_counts){
		if(p.second > largest_count){
			largest_count = p.second;
			most_frequent = p.first;
		}
	}
	
	assert(most_frequent == 3);

	cout << " PASSED!" << endl;
}


void timecode_tests(){
	cout << "\ttimecode tests...";

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

	cout << " PASSED!" << endl;
}


void biginteger_tests(){
	cout << "\tbiginteger tests..."; 
	
	TestConstructor();
	TestMakeNegative();
	CopyConstructorTests();
	AdditionTests();
	OverflowTests();

	cout << " PASSED!" << endl;
}


int main(){

	cout << "--- Running Tests ---" << endl;

	power_tests();
	poisson_tests();
	timecode_tests();
	biginteger_tests();

	cout << "--- ALL TESTS PASSED! ---" << endl;


	return 0;
}