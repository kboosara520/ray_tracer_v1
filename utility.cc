#include "utility.h"

double deg2rad(double degrees) {
    return degrees * pi / 180;
}

double random_double() {
    static uniform_real_distribution<double> distribution(0.0, 1.0);
    static mt19937 generator;
    return distribution(generator);
}

double random_double(double min, double max) {
    return min + (max - min) * random_double();
}
