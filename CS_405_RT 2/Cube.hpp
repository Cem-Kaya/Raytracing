#ifndef cube_HPP
#define cube_HPP

#include "Ray.hpp"
#include "Def.hpp"

#include "Hittable.hpp"


class cube : public hittable {
public:        
    cube(const point3& smaller , const point3& bigger, material* m): mat_ptr(m)  { minimum = smaller; maximum = bigger; }
    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    point3 minimum;
    point3 maximum;
    material* mat_ptr;

    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec) const override;
    ~cube() {
        delete mat_ptr;
    }

};

bool  cube::hit(const ray& r, float t_min, float t_max, hit_record& rec)  const {    
    for (int a = 0; a < 3; a++) {
        float t0 = fmin((minimum[a] - r.origin()[a]) / r.direction()[a],
            (maximum[a] - r.origin()[a]) / r.direction()[a]);
        float t1 = fmax((minimum[a] - r.origin()[a]) / r.direction()[a],
            (maximum[a] - r.origin()[a]) / r.direction()[a]);
        t_min = fmax(t0, t_min);
        t_max = fmin(t1, t_max);
        if (t_max <= t_min)
            return false;
    }

    rec.t = t_min;
    rec.p = r.at(rec.t);
    bool xmin = false;
    if (rec.p.x <min().x + 0.00001f && rec.p.x > min().x - 0.00001f) {
        xmin = true;
    }
    bool ymin = false;
    if (rec.p.y <min().y + 0.0001f && rec.p.y > min().y - 0.0001f) {
        ymin = true;
    }
    bool zmin = false;
    if (rec.p.z <min().z + 0.00001f && rec.p.z > min().z - 0.00001f) {
        zmin = true;
    }


    if (xmin) {
        rec.normal = vec3(-1, 0, 0);
    }
    if (ymin) {
        rec.normal = vec3(0, -1, 0);
    }
    if (zmin) {
        rec.normal = vec3(0,0,-1);
    }
    
    bool xmax = false;
    if (rec.p.x <max().x + 0.00001f && rec.p.x > max().x - 0.00001f) {
        xmax = true;
    }
    bool ymax = false;
    if (rec.p.y <max().y + 0.00001f && rec.p.y > max().y - 0.00001f) {
        ymax = true;
    }
    bool zmax = false;
    if (rec.p.z <max().z + 0.00001f && rec.p.z > max().z - 0.00001f) {
        zmax = true;
    }


    if (xmax) {
        rec.normal = vec3(1, 0, 0);
    }
    if (ymax) {
        rec.normal = vec3(0, 1, 0);
    }
    if (zmax) {
        rec.normal = vec3(0, 0, 1);
    }
    rec.front_face = true;
    rec.mat_ptr = mat_ptr;

    return true;

}



class Trig : public hittable {
public:
    Trig(const point3& A, const point3& B, const point3& C, material* m) : a(A), b(B), c(C), mat_ptr(m){ ; }


    point3 a;
    point3 b;
    point3 c;
    material* mat_ptr;

    virtual bool hit(
        const ray& r, float t_min, float t_max, hit_record& rec) const override;
    ~Trig() {
        delete mat_ptr;
    }

};

bool  Trig::hit(const ray& r, float t_min, float t_max, hit_record& rec)  const {
    vec3 v1 = b - a;
    vec3 v2 = c - a;
    
    vec3 nor = cross(v1, v2);
    float area2 = nor.length();
    // parallel 
    if (dot(nor, r.dir) < 0.0000000001f) {
        return false;
    }
    //from www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-Trigangle/ray-Trigangle-intersection-geomeTrigc-solution
    
    float D = dot(nor, a);
    float t = (dot(nor,r.orig) + D) / dot(nor, r.dir);

    //float t = -(dot(nor, r.orig) + D) / dot(nor, r.dir);
    
    if (t < 0) {
        //cout << " less 0 " << endl;
        return false;
    }
    
    rec.t = t;
    rec.p = r.at(rec.t);

    rec.front_face = true;
    rec.mat_ptr = mat_ptr;
    //cout << " did hit " << endl;
    vec3 C; // vector perpendicular to triangle's plane 

    // edge 0
    vec3 edge0 = b - a;
    vec3 vp0 = rec.p - a;
    C = cross(edge0 , vp0);
    if (dot(nor,C) < 0) return false; // P is on the right side 

    // edge 1
    vec3 edge1 = c - b;
    vec3 vp1 = rec.p - b ;
    C = cross(edge1,vp1);
    if (dot(nor,C) < 0)  return false; // P is on the right side 

    // edge 2
    vec3 edge2 = a - c;
    vec3 vp2 = rec.p - c;
    C = cross(edge2,vp2);
    if (dot(nor,C) < 0) return false; // P is on the right side; 
    return true;







}


#endif