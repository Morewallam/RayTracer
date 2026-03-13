#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.5);
    auto material_dia = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.001);

    world.add(make_shared<sphere>(point3(-1.5, 1, -3), 0.5, material_left));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_dia));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(+1.5, 0, -1), 0.5, material_right));
    world.add(make_shared<sphere>(point3(0, -5, -5), 0.5, material_left));
    world.add(make_shared<sphere>(point3(0, -105.5, -1), 100, material_ground));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 70;
    cam.lookfrom = point3(0, 0, 0);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 1;
    cam.focus_dist = 1;

    cam.render(world);
}