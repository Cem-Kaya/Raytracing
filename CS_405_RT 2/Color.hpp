#ifndef COLOR_HPP
#define COLOR_HPP
#include "Ray.hpp"
#include "Def.hpp"
#include "Hittable.hpp"
#include <iostream>
#include"Sphere.hpp"



void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    float r = pixel_color.x;
    float g = pixel_color.y;
    float b = pixel_color.z;

    // Divide the color by the number of samples.
    float scale = 1.0 / samples_per_pixel;
    r = sqrt(r * scale );
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>((256 * clamp(r, 0.0, 0.999))) << ' '
        << static_cast<int>((256 * clamp(g, 0.0, 0.999))) << ' '
        << static_cast<int>((256 * clamp(b, 0.0, 0.999))) << '\n';
}







float hit_sphere(const point3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}



color background_color(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5f * color(N.x + 1, N.y + 1, N.z + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5f * (unit_direction.y + 1.0);
    return (float)(1.0f - t) * color(0.2, 0.1, 0.4) + t * color(1.0, 0.6, 0.35);
}


color ray_color(const ray& r, const hittable& world , int depth , color background ) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    
    // If the ray hits nothing, return the background color.
    
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted( rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, world, depth - 1, background);
   /* hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return color(0, 0, 0);
    }
    if (world.hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
        //point3 target = rec.p + rec.normal + random_unit_vector();
        //return 0.5f * ray_color(ray(rec.p, target - rec.p ), world , depth - 1);

        //return 0.5f * (rec.normal + color(1, 1, 1));// for normal based color
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y + 1.0);
    return  (float)(1.0f - t) * color(0.2, 0.1, 0.4) + t * color(1.0, 0.6, 0.35);
    */
}



#endif