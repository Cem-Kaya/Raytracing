#ifndef HITTABLE_H
#define HITTABLE_H
#include <vector>
#include"Color.hpp"
#include "Ray.hpp"
#include "Def.hpp"

using namespace std;
class material;

struct hit_record {
    material* mat_ptr;
    point3 p;
    vec3 normal;
    float t;    

    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
    /*
    ~hit_record(){
        delete mat_ptr;  this pointer will be cleaned up by the object aka cube or sphere 
    }
    */
};

class hittable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};





class hittable_list : public hittable {
public:
    hittable_list() {}
    hittable_list(hittable* object) { add(object); }

    void clear() { objects.clear(); }
    void add(hittable* object) { objects.push_back(object); }
    ~hittable_list();
    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec) const override ;

public:
    vector<hittable*> objects;
};

inline hittable_list::~hittable_list()
{
    for (int i = 0; i < objects.size(); i++) {
        delete objects.at(i);
    }
}

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}








class material {
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
    virtual color emitted( const point3& p) const {
        return color(0, 0, 0);
    }
};





class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        // Catch degenerate scatter direction
        if (near_zero(scatter_direction)) {
            scatter_direction = rec.normal;
        }
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};


class metal : public material {
public:
    metal(const color& a , float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_unit_vector());
        
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
    float fuzz;
};





class dielectric : public material {

public:
    float ir; // Index of Refraction
    color t;
    dielectric(float index_of_refraction , color tint ) : ir(index_of_refraction),t(tint) { }
    
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        
        float refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
        attenuation = t;

        vec3 unit_direction = unit_vector(r_in.direction());
        float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
        float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
        vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = ray(rec.p, direction);
        return true;
    }


private:
    static float reflectance(float cosine, float ref_idx) {
        // Use Schlick's approximation for reflectance.
        float r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1.0f-r0) * pow((1 - cosine), 5);
    }
};



class diffuse_light : public material {
public:
    
    diffuse_light(const color & c) : emit( c) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        return false;
    }

    virtual color emitted( const point3& p) const override {
        return emit;
    }

public:
    color emit;
};





#endif