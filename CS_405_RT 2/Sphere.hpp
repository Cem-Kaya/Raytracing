#ifndef Sphere_HPP
#define Sphere_HPP

#include "Ray.hpp"
#include "Def.hpp"

#include "Hittable.hpp"


class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, float r , material* m) : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, float t_min, float t_max, hit_record& rec) const override;

    public:        
        material* mat_ptr;
        point3 center;
        float radius;
        ~sphere() {
            delete mat_ptr;
        };
};

 bool  sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec)  const  {
    vec3 oc = r.origin() - center;
    float a = length_squared(r.direction());
    float half_b = dot(oc, r.direction());
    float c = length_squared(oc) - radius * radius;

    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    rec.mat_ptr = mat_ptr;

    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}






#endif