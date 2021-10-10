#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// @brief A Ray class to portray a linear interpolation of a ray line from source 'orig' in direction 'dir'.
class ray {
 public:
  ray() {}
  ray(const point3 &origin, const vec3 &direction)
      : orig(origin), dir(direction) {}
  // @return Origin of the ray
  point3 origin() const { return orig; }
  // Return direction of the ray
  vec3 direction() const { return dir; }

  // Return P(t) = A+tb
  point3 at(double t) const { return orig + t * dir; }

 public:
  point3 orig;
  vec3 dir;
};
#endif