#ifndef CAMERA_H
#define CAMERA_H

#include "Def.hpp"
#include "Ray.hpp"
using namespace std;
class camera {
public:
    camera(point3 lookfrom,
        vec3 lookat,
        vec3   vup  ,
        float vfov,  float aspect_ratio 
        ) {
        float theta = degrees_to_radians(vfov);
        float h = tan(theta / 2.0f);
        float viewport_height = 2.0f * h;
        float  viewport_width = aspect_ratio * viewport_height;

        vec3 w = unit_vector(lookfrom - lookat);
        vec3 u= unit_vector(cross(vup, w));
        vec3 v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - w;
    }
    /*
    ray get_ray(float u, float v) const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }*/
    ray get_ray(float s, float t) const {
        return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif