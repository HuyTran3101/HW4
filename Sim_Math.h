// Sim_Math.

// Author: Programmer Intern Jordan

#ifndef SIM_MATH_H
#define SIM_MATH_H

#include <unordered_map>
#include <string>

#include "TimeCode.h"


const double e = 2.718281828459045;

double power(double, int);
int poisson(int);
int binomial(int, double);
int percentage(int, int);
int day_of_week_code(TimeCode);
std::string day_of_week_name(int);
std::unordered_map<std::string, double> build_crash_prob_map();
bool crash_occurs(double);


#endif

