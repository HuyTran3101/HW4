

#include <iostream>
#include <stdexcept> // for the exceptions

// author: Programmer Intern Jordan


#include "BigInteger.h"


using namespace std;


BigInteger::BigInteger(const BigInteger &bi){
	// Right!
	this->digits->clear();
	for(size_t i = 0; i < bi.digits->size(); i++){
		this->digits->push_back(bi.digits->at(i));
	}

	this->is_negative = bi.is_negative;
}

/*
BigInteger::BigInteger(const BigInteger &bi){
	// Wrong!
	this->digits = bi.digits;
	this->is_negative = bi.is_negative;
}
*/


BigInteger::BigInteger(int x){
	digits->clear();
	if(x == 0){
		digits->push_back(0);
		return;
	}

	if(x < 0){
		this->is_negative = true;
		x = -x;
	}

	while(x > 0){
		unsigned short int digit = x % 10;
		digits->push_back(digit);
		x = x / 10;
	}
}


BigInteger::BigInteger(string str){

	int l = str.length();

	for(int i = 0; i < l; i++){
		digits->clear();
		//cout << "digits: " << vec_to_string(*digits) << endl;


		size_t idx = 0;
		if(str.at(0) == '-'){
			this->is_negative = true;
			idx++;
		}

		for(;idx < str.size(); idx++){
			int dig = ((int)str.at(idx)) - '0';
			this->digits->push_back(dig);
		}
	}
}

string BigInteger::ToString() const {
	string str = "";

	if(is_negative){
		str = str + "-";
	}

	for(size_t i = 0; i < digits->size(); i++){
		str = str + to_string(digits->at(i));
	}
	
	return str;
}

void BigInteger::MakeNegative() {
	this->is_negative = true;
}
    
void BigInteger::SetDigit(size_t pos, unsigned short int new_digit){
	if(new_digit > 9)
	{
		throw invalid_argument("Two digits not allowed: " + to_string(new_digit));
	}

	this->digits->at(pos) = new_digit;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
	//cout << this->ToString() << " + " << other.ToString() << endl;


	// find RHS
	int i = this->digits->size()-1;
	int j = other.digits->size()-1;



	string result = "";
	unsigned short int carry = 0;
	unsigned short int arg1_digit;
	unsigned short int arg2_digit;

	bool addition_is_necessary = true;
	while(addition_is_necessary){
		//cout << "i:" << i << "  j:" << j << endl;

		if(i >= 0){
			arg1_digit = this->digits->at(i);
		} else{
			arg1_digit = 0;
		}

		if(j >= 0){
			arg2_digit = other.digits->at(j);
		} else {
			arg2_digit = 0;
		}


		unsigned short int sum = arg1_digit + arg2_digit + carry;
		unsigned short int new_digit = sum % 10;
		carry = sum / 10;

		i--;
		j--;

		// Would be more efficient probably to put the digits straight into the vector of a BiInteger object
		result = to_string(new_digit) + result;

		if(i < 0 && j < 0 && carry == 0){
			addition_is_necessary = false;
		}
	}

	//cout << "string so far:" << result << endl;

	BigInteger ans = BigInteger(result);
	return ans;

}

BigInteger BigInteger::operator++(int ignored) {
	// 'ignored' is a dummy variable to distinguish pre- and post-increment! ++x and x++
	// this function has the int variable, so it is the implementation of post-increment
	BigInteger temp = *this;
	BigInteger one = BigInteger("1");
	*this = *this + one;

	return temp;
}

bool BigInteger::operator<(const BigInteger& other) const {

	// check sign and length of number first for possible quick exit
	if (!this->is_negative && other.is_negative) {
		return false;
	}

	if (this->digits->size() > other.digits->size()) {
		return false;
	}

	if(this->digits->size() < other.digits->size()) {
		return true;
	}



	// If sizes are equal, compare digit by digit
	for (size_t i = 0; i < this->digits->size(); i++) {
		if (this->digits->at(i) < other.digits->at(i)) {
			return true;
		} else if (this->digits->at(i) > other.digits->at(i)) {
			return false;
		}
	}

	return false; // They are exactly equal
}


//bool BigInteger::operator*(const BigInteger& other) const {
//	// TODO: implement this
//}
    
