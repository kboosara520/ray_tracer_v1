#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <random>

using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double deg2rad(double degrees);
double random_double();
double random_double(double min, double max);


#endif