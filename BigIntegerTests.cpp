
#include <cassert>
#include <iostream>

#include "BigInteger.h"
#include "BigInteger_Tests.h"

// author: Rahm
// 2nd author: Programmer Intern Jordan


using namespace std;
    

void TestConstructor(){
    // constructor tests
    BigInteger bi1 = BigInteger("56");
    //cout << "bi1: " << bi1.ToString() << endl;
    assert(bi1.ToString() == "56");
    
    BigInteger bi2 = BigInteger("123456789123456789");
    //cout << "bi2: " << bi2.ToString() << endl;
    assert(bi2.ToString() == "123456789123456789");
    
    BigInteger bi3 = BigInteger("18446744073709551627");
    //cout << "bi3: " << bi3.ToString() << endl;
    assert(bi3.ToString() == "18446744073709551627");

    BigInteger bi4 = BigInteger("-2112");
    //cout << "bi4: " << bi4.ToString() << endl;
    assert(bi4.ToString() == "-2112");
}


void TestMakeNegative(){
    // make negative tests

    BigInteger bi3 = BigInteger("18446744073709551627");
    bi3.MakeNegative();
    //cout << "bi3: " << bi3.ToString() << endl;
    assert(bi3.ToString() == "-18446744073709551627");

    bi3.MakeNegative();
    //cout << "bi3: " << bi3.ToString() << endl;
    assert(bi3.ToString() == "-18446744073709551627");


    // set digit tests
    bi3.SetDigit(0, 5);
    //cout << "bi3: " << bi3.ToString() << endl;
    assert(bi3.ToString() == "-58446744073709551627");
    try
    {
        bi3.SetDigit(0, 43);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
        // cout << e.what() << endl;
    }
}
     

void CopyConstructorTests(){
    // copy constructor tests

    BigInteger bi1 = BigInteger("56");
    BigInteger bi2 = BigInteger(bi1);
    //cout << "bi2: " << bi2.ToString() << endl;
    assert(bi2.ToString() == "56");
    
    BigInteger bi3 = BigInteger("18446744073709551617");
    //cout << "bi3: " << bi3.ToString() << endl;
    assert(bi3.ToString() == "18446744073709551617");

    bi2.MakeNegative();
    bi2.SetDigit(1, 3);
    assert(bi2.ToString() == "-53");
    assert(bi3.ToString() == "18446744073709551617");
    assert(bi1.ToString() == "56");

}



void AdditionTests(){
    // addition operation tests

    BigInteger bi1 = BigInteger("56");
    BigInteger bi7 = BigInteger("892");
    BigInteger bi8 = bi1 + bi7;
    //cout << "bi8: " << bi8.ToString() << endl;
    assert(bi8.ToString() == "948");

    // pointer tests
    BigInteger *bi9 = new BigInteger("77");
    BigInteger bi10 = BigInteger(*bi9);
    //cout << "bi9: " << bi9->ToString() << endl;
    //cout << "bi10: " << bi10.ToString() << endl;
    assert(bi9->ToString() == "77");
    assert(bi10.ToString() == "77");


    // increment operator test

    // WARNING!  Using ++ on bi9 won't invoke my post-increment function 
    // because bi9 is a pointer.  It instead increments the pointer (address being pointed to).
    //bi9++; 
    bi8++;
    assert(bi8.ToString() == "949");
    bi8++;
    assert(bi8.ToString() == "950");

    BigInteger bi11 = BigInteger("42949672950"); // 10x the largest unsigned 64-bit int
    bi11++;
    assert(bi11.ToString() == "42949672951");
}


void OverflowTests(){

    BigInteger bi1 = BigInteger("98");
    assert(bi1.ToString() == "98");
    bi1++;
    assert(bi1.ToString() == "99");
    bi1++;
    assert(bi1.ToString() == "100");
    bi1++;
    assert(bi1.ToString() == "101");

    unsigned long long int x = 0;
    for(BigInteger bi = BigInteger("0"); bi < BigInteger("1000"); bi++){
        assert(bi.ToString() == to_string(x));
        x++;
    }
}
