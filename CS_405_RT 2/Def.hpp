#ifndef DEF_H
#define DEF_H

#include "include/glm/glm/vec3.hpp"
#include "include/glm/glm/geometric.hpp"

#include <cstdlib>
typedef  glm::vec3 point3;
typedef  glm::vec3 vec3;
typedef  glm::vec3 color;

using namespace std;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592;

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}





 float random_float() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

float random_float(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_float();
}
float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}



vec3 random_vec() {
    return vec3(random_float(), random_float(), random_float());
}

vec3 random_vec(float min, float max) {
    return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}


bool near_zero(vec3 e )  {
    // Return true if the vector is close to zero in all dimensions.
    const float s = 0.000000001f;
    return (fabs(e.x) < s) && (fabs(e.y) < s) && (fabs(e.z) < s);
}


vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

   






#endif