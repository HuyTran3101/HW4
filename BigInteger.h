// BigInteger.h

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <vector>

// author: PennDOT Programmer Intern Jordan


class BigInteger {
	public:
		BigInteger(int init_val);
		BigInteger(std::string init_val);
		std::string ToString() const;

		void MakeNegative();
		void SetDigit(size_t pos, unsigned short int new_digit);
		BigInteger(const BigInteger &bi);
		BigInteger operator+(const BigInteger& other) const; // addition
		BigInteger operator++(int); // post-increment
		bool operator<(const BigInteger& other) const;


		
	private:
		std::vector<unsigned short int> *digits = new std::vector<unsigned short int>;
		bool is_negative = false;
};


#endif
