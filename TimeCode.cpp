
#include "TimeCode.h"
#include "TimeCode_Tests.h"
#include <stdexcept> // for the exceptions
#include <climits>

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
	t = TimeCode::ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc){
	t = tc.GetTimeCodeAsSeconds();
}


void TimeCode::SetHours(unsigned int hours){
	// An entire timecode may be negative
	// e.g., tc1 = -4:23:64
	
	// But calling tc1.setHours(h) with h = a negative
	// number is none-sense and therefore not supported
	if(hours < 0){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(hours));
	}
	
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	hr = hours;
	long long unsigned int newT = TimeCode::ComponentsToSeconds(hr, min, sec);
	t = newT;

}

void TimeCode::SetMinutes(unsigned int mins){
	// An entire timecode may be negative
	// e.g., tc1 = -4:23:64
	
	// But calling tc1.setHours(h) with h = a negative
	// number is none-sense and therefore not supported

	if(mins > 60){
		throw std::invalid_argument("Invalid minutes: " + std::to_string(mins));
	}
	
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	min = mins;
	long long unsigned newT = TimeCode::ComponentsToSeconds(hr, min, sec);
	t = newT;

}

void TimeCode::SetSeconds(unsigned int secs){
	// An entire timecode may be negative
	// e.g., tc1 = -4:23:64

	if(secs > 60){
		throw std::invalid_argument("Invalid seconds: " + std::to_string(secs));
	}
	
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	sec = secs;
	long long unsigned newT = TimeCode::ComponentsToSeconds(hr, min, sec);
	t = newT;

}


void TimeCode::reset(){
	t = 0;
}


unsigned int TimeCode::GetHours() const {
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	return hr;
}

unsigned int TimeCode::GetMinutes() const {
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	return min;
}

unsigned int TimeCode::GetSeconds() const {
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);
	return sec;
}



void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
	
	//cout << "t: " << t << endl;
	hr = this->t/3600;
	unsigned long long int tmpHr = hr;
	long long unsigned int tmpT = this->t - (tmpHr * 3600);
	//cout << "hr: " << hr << endl;
	//cout << "tmpT: "<< tmpT << endl;
	
	min = tmpT/60;
	unsigned long long int tmpMin = min;
	tmpT = tmpT - (tmpMin * 60);
	
	sec = tmpT;
	//cout << "t: " << t << endl;
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
	//cout << "hr: " << hr << "  min: " << min << "  sec: " << sec << endl;

	// because the parameters are unsigned int, it is IMPOSSIBLE to detect a negative value here.
	// any negative value passed in will immediately rollover to a positive value
	
	long long unsigned int HRSeconds = 3600 * static_cast<long long unsigned int>(hr);
	long long unsigned int MINSeconds = 60 * static_cast<long long unsigned int>(min);
	long long unsigned int totalSeconds =  HRSeconds + MINSeconds + sec;
	//cout << "total seconds: " << totalSeconds << endl;

	return totalSeconds;
	
}  


std::string TimeCode::ToString() const {
	
	unsigned int hr;
	unsigned int min;
	unsigned int sec;
	
	TimeCode::GetComponents(hr, min, sec);

	std::string str = std::to_string(hr) + ":" + std::to_string(min) + ":" + std::to_string(sec);
	return str;
}


TimeCode TimeCode::operator+(const TimeCode& other) const {
	unsigned long long int newT = this->t + other.GetTimeCodeAsSeconds();
	TimeCode ans = TimeCode(0, 0, newT);
	return ans;
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
	if(t < other.GetTimeCodeAsSeconds()){
		throw std::invalid_argument("Negative TimeCode Exception");
	}
	long long unsigned int newT = t - other.GetTimeCodeAsSeconds();
	TimeCode ans = TimeCode(0, 0, newT);
	return ans;
}

TimeCode TimeCode::operator*(double a) const {
	if(a < 0){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(a));
	}
	long long unsigned int newT = static_cast<long long unsigned int>(t * a);
	TimeCode ans = TimeCode(0, 0, newT);
	return ans;
}

TimeCode TimeCode::operator/(double a) const {
	if(a < 0){
		throw std::invalid_argument("Negative arguments not allowed: " + std::to_string(a));
	}
	long long unsigned int newT = static_cast<long long unsigned int>(t / a);
	TimeCode ans = TimeCode(0, 0, newT);
	return ans;
}



bool TimeCode::operator == (const TimeCode& other) const {
	return t == other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator != (const TimeCode& other) const {
	return (!(t == other.GetTimeCodeAsSeconds()));
}

bool TimeCode::operator < (const TimeCode& other) const {
	return t < other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator <= (const TimeCode& other) const {
	return t <= other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator > (const TimeCode& other) const {
	return t > other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator >= (const TimeCode& other) const {
	return t >= other.GetTimeCodeAsSeconds();
}
