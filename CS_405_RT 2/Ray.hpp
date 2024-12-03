#ifndef RAY_H
#define RAY_H

#include "Def.hpp"

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(float t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};


float length_squared(vec3 v) {
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 unit_vector(vec3 v) {
   return v / sqrt(length_squared(v));
}





vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = random_vec(-1, 1);
        if (length_squared(p) >= 1) continue;
        return p;
    }
}


vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}


// snalls law the eta and ligth bending due to speed delta 
vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) {
    float  cos_theta = fmin(dot(-uv, n), 1.0f );
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0f - length_squared(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}





#endif