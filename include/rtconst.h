#ifndef RTCONST_H
#define RTCONST_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Using
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double epsilon = std::numeric_limits<double>::epsilon();
const double pi = 3.1415926535897932385;

// Utility Functions
//@brief degree to rad.
inline double deg_to_rad(double degrees) { return degrees * pi / 180.0; }

// Returns a random real in [0,1)
inline double random_double() { return rand() / (RAND_MAX + 1.0); }

// Returns a random [min, max)
inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif