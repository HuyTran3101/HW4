#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream> // use for the throw "Negative Condition" lines

class TimeCode {
	public:
		TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0);
		TimeCode(const TimeCode& tc);
		~TimeCode(){};
		
		void SetHours(unsigned int hours);
		void SetMinutes(unsigned int minutes);
		void SetSeconds(unsigned int seconds);
		void WasteTimeAndBeSlow() const;
		
		void reset();
		
		unsigned int GetHours() const;
		unsigned int GetMinutes() const;
		unsigned int GetSeconds() const;

		long long unsigned int GetTimeCodeAsSeconds() const { return t; };		
		void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const;
		static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec);
		
		std::string ToString() const;
		
		TimeCode operator+(const TimeCode& other) const;
		TimeCode operator-(const TimeCode& other) const;
		TimeCode operator*(double a) const; 
		TimeCode operator/(double a) const;
		
		bool operator == (const TimeCode& other) const;
		bool operator != (const TimeCode& other) const;
		
		bool operator < (const TimeCode& other) const;
		bool operator <= (const TimeCode& other) const;
		
		bool operator > (const TimeCode& other) const;
		bool operator >= (const TimeCode& other) const;
		
	private:
		long long unsigned int t = 0;
};

#endif