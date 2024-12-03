#include <iostream>
#include <fstream>
#include<vector>
#include <sstream>
#include "include/glm/glm/vec3.hpp"
#include "include/glm/glm/geometric.hpp"
#include "Ray.hpp"
#include "Def.hpp"
#include"Color.hpp"
#include "Cube.hpp"
#include "Cam.hpp"
//#include "Trig.hpp"
using namespace std;
const bool RAND_AA= true ;
const int GRID_AA_n = 15; // n^2 sampels due to 2D grid 
const int samples_per_pixel = 10;
const int DEPTH = 5 ;

const color BACK(0.01, 0.03, 0.05);
int main() {
    // file
    fstream file;
    file.open("test.ppm", std::ios::out);
    // image 
    const float aspect_ratio = 21.0f / 9.0f;
    const int image_width = 2560, image_height = image_width / aspect_ratio;

    // WORLD
    hittable_list world;
    
    //auto material_center = new diffuse_light(color(0, 0.1, 0));
    //auto material_left = new dielectric(1.11, color(0.1, 0.9, 1));
    //auto material_center = new metal(color(0.7, 0.7, 1), 0.01);
    //auto material_right = new metal(color(0.8, 0.6, 0.2), 0.80);
    /*
    auto m1 = new lambertian( color(1, 1, 1));
    auto m2 = new dielectric(1.16, color(1, 1, 1));
    auto m3 = new metal( color(0.7, 0.9, 1),0.2);
    auto m4 = new dielectric(1, color(1, 0, 0.1));
    auto m5 = new dielectric(0.2, color(3, 0.1, 0.1));
    auto m6 = new dielectric(0.5, color(0.9, 0.7, 0.9));
    auto m8 = new dielectric(0.4, color(0.3, 0.9, 0.5));
    auto m7 = new dielectric(0.8, color(0.3, 0.9, 0.5));
    auto m9 = new dielectric(0.7, color(0.7, 0.5, 0.5));
    auto m10 = new lambertian( color(0.6,1 , 0.7) );
    world.add(new sphere(point3(0.0, -100.5, -1.0), 100.0, m10));
    auto m11 = new diffuse_light(color(3, 3, 3));
    
    auto m12 = new diffuse_light(color(0, 5, 0));
    auto m13 = new diffuse_light(color(4,0, 0));
    world.add(new cube(point3(-2, 1, -3),point3(-1.7, 2.3, -3.4) , m12));
    world.add(new cube(point3(2, 1, -3), point3(2.3, 2.3, -3.4), m13));
    


    world.add(new sphere(point3(0, 0.56, -3), 0.3, m11));
    world.add(new sphere(point3(0, 0, -2), 0.5, m2)  );
    world.add(new sphere(point3(-1, 0, -2), 0.5, m1) );
    world.add(new sphere(point3(1, 0, -2), 0.5, m11)  );

    


    world.add(new sphere(point3(-1, 1, -1), 0.5, m1));
    world.add(new sphere(point3(0, 1, -1), 0.5, m2));
    world.add(new sphere(point3(1, 1, -1), 0.5, m3));
    world.add(new sphere(point3(-1, 1, -2), 0.5, m4));
    world.add(new sphere(point3(0, 1, -2), 0.5, m5));
    world.add(new sphere(point3(1, 1, -2), 0.5, m6));
    world.add(new sphere(point3(-1, 1, -3), 0.5, m7));
    world.add(new sphere(point3(0, 1, -3), 0.5, m8));
    world.add(new sphere(point3(1, 1, -3), 0.5, m9));
   
    
    world.add(new cube(point3(2, 2, -5), point3(3, 3, -4), material_left));

    world.add(new sphere(point3(0, -100.5, -1), 100));
    world.add(new sphere(point3(0, 0, -1), 0.5));

    //world.add( new sphere(point3(0, 0, -1), 0.5));

    //world.add(new sphere(point3(120, 0, -1), 100));


    world.add(new sphere(point3(5, 2, -3), 0.1));
    world.add(new sphere(point3(9, 6, -7), 0.2));
    */

    auto m1 = new lambertian(color(0.6, 0.8, 0.4));

    auto dino1 = new metal(color(0.7,0.7, 0.7),0.1);
    auto dino2 = new lambertian(color(0.4, 0.1, 0.7));
    auto dino3 = new diffuse_light(color(0, 0.6, 0.6));
    auto dino4 = new metal(color(0.1, 0.1, 0.2),1);
    auto metall = new metal(color(0.8, 0.8, 1),  0.05);
    auto metdark = new metal(color(0.2, 0.2, 0.1), 0.1);

    auto sar = new diffuse_light(color(3,0.5, 0.1));

    auto re = new diffuse_light(color(0.5, 0.5, 0.5));

    world.add(new sphere(point3(220.847168, -650.31552887, 98.47318268), 525, m1));
    world.add(new cube(point3(160, -250, 150.47318268), point3(170, 200.31552887, 200.47318268), metall));
    world.add(new cube(point3(150 , -250, 150.47318268), point3(100, -100 , 40 ), metdark));
    world.add(new sphere(point3(350.847168, -90.31552887, 70.47318268),20, re));

    world.add(new sphere(point3(420.847168, 40.31552887, 70.47318268), 10, sar));
    world.add(new sphere(point3(225.847168, -10.31552887, 70.47318268), 10, sar));
    world.add(new sphere(point3(420.847168, 0.31552887, 70.47318268), 10, sar));
    world.add(new sphere(point3(420.847168, 20.31552887, 70.47318268), 10, sar));
    world.add(new sphere(point3(420.847168, 0.31552887, 140.47318268), 10, sar));
    world.add(new sphere(point3(420.847168, 40.31552887, 0.47318268), 10, sar));
    world.add(new sphere(point3(450.847168, 37.31552887, 0.47318268), 15, sar));
    world.add(new sphere(point3(450.847168, 12.31552887, 50.47318268), 7, sar));
    world.add(new sphere(point3(525.847168, 22.31552887, -10.47318268), 20, sar));
    world.add(new sphere(point3(319, 0.31552887, 0.47318268), 10, sar));

    auto rer = new diffuse_light(color(6 , 0, 0));

    world.add(new sphere(point3(0, 0, -550), 450, rer ));

    


    auto ufoblue = new diffuse_light(color(0.2, 0.4, 4));
    auto ufoW = new diffuse_light(color(40, 40, 40));

    world.add(new sphere(point3(122 , -50 , 250 ),20, metdark));
    world.add(new cube(point3(95 , -49 , 227 ),point3(145 , -53 , 270 ), ufoblue));
    world.add(new sphere(point3(122, -71, 250), 2, ufoW));

    auto ufff  = new dielectric(1.20,color(0.3, 0.5, 1));

    world.add(new sphere(point3(500.847168, -650.31552887, 150.47318268), 525, ufff));

    for (int i = 0; i < 2000; i++) {
       // world.add(new sphere(point3(1000 + random_float() * 100, -100 + random_float() * 400, 120 + random_float() * 10000), 0.2f + random_float() * 1.7, ufoW));
    }

    for (int i = 0; i < 2000; i++) {
        //world.add(new sphere(point3(1000 + random_float() * 100, -100+ random_float() * 400 ,120+ random_float() * 10000), 0.2f + random_float() * 1.5 , ufoblue));
    }
    //    camera cam ( point3(0 ,0 ,0), point3(180.847168 ,- 75.31552887, 98.47318268), vec3(0, 1, 0),62.0f, aspect_ratio);

    


    // mesh import system
    ifstream input("model2.obj", std::ifstream::in);;
    string line = "";
    vector<point3> vvec;
    vector<hittable*> fvec;
    while (getline(input, line)) {
        istringstream istr(line);
        string temp;
        istr >> temp;
        if (temp == "v") {
            string temp1;
            string temp2;
            string temp3;
            istr >> temp1;
            istr >> temp2;
            istr >> temp3;
            vvec.push_back(point3(stof(temp1) , stof(temp2), stof(temp3)) );
        }
        else if (temp == "f") {
            string temp1;
            string temp2;
            string temp3;
            istr >> temp1;
            istr >> temp2;
            istr >> temp3;
            int ta = stoi(temp1)-1;
            int tb = stoi(temp2)-1;
            int tc = stoi(temp3)-1;
            material * dino;
            if ((int)ta % 4 == 0) {
                 dino = dino1;
            }else if ((int)ta % 4 == 1) {
                 dino = dino1;
            }
            else if ((int)ta % 4 == 2) {
                 dino = dino3;
            }
            else  //(int)ta % 4 == 3) 
            {
                dino = dino4;
            }
            
            fvec.push_back(new cube(vvec.at(ta), vvec.at(tb), dino));
            fvec.push_back(new cube(vvec.at(ta), vvec.at(tc), dino));

            //fvec.push_back(new Trig(vvec.at(ta), vvec.at(tb), vvec.at(tc), dino));
        }
    }
    for (int i = 0; i < fvec.size(); i++) {
        world.add( fvec.at(i));
    }
    //end of mesh import system

    




















    // Camera
    // for trex 
    camera cam ( point3(0 ,0 ,0), point3(180.847168 ,- 75.31552887, 98.47318268), vec3(0, 1, 0.5),62.0f, aspect_ratio);
    //camera cam(point3(0,0, 0), point3(0, 0,-1), vec3(0, 1, 0), 60.0f, aspect_ratio);




    // Render

    file << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    if (RAND_AA) {
        for (int j = image_height - 1; j >= 0; --j) {      
            cout << "\rScanlines remaining: " << j  << "   " << flush;

            for (int i = 0; i < image_width; ++i) {
                //cout << "\rScanlines remaining: " << j << " column:   " << i << "   " << flush;

                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    float u = (i + random_float()) / (image_width - 1);
                    float v = (j + random_float()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, world, DEPTH, BACK);
                    //pixel_color +=  background_color(r);
                }
                write_color(file, pixel_color, samples_per_pixel);
            }

        }
    }
    else {
        for (int j = image_height - 1; j >= 0; --j) {
            cout << "\rScanlines remaining: " << j << ' ' << flush;
            for (int i = 0; i < image_width; ++i) {
                //cout << "\rScanlines remaining: " << j << " column:   " << i << "   " << flush;

                color pixel_color(0, 0, 0);
                for (int aa = 0; aa < GRID_AA_n; ++aa) {
                    for (int bb = 0; bb < GRID_AA_n; ++bb) {
                        float u = (i + ((float)aa / GRID_AA_n)) / (image_width - 1);
                        float v = (j + ((float)bb / GRID_AA_n)) / (image_height - 1);
                        ray r = cam.get_ray(u, v);
                        pixel_color += ray_color(r, world, DEPTH, BACK);
                    }
                }
                write_color(file, pixel_color, GRID_AA_n * GRID_AA_n);

            }

        }
    }

    cout << "\nDone.\n";

    //file close
    file << fflush;
    file.close();
}















