#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <math.h>

point3 angle_to_position(double distance, double theta)
{
    double x = distance * cos(theta);
    double y = distance * sin(theta);
    return point3(x, y, -1);
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <output_file.ppm>" << std::endl;
        return 1;
    }

    std::ofstream output_file(argv[1]);

    hittable_list world;

    // Get User input to build the scene

    std::cout << "Do you want to use the default scene? (y/n): ";
    char use_default_scene;
    std::cin >> use_default_scene;
    std::cin.ignore();
    if (use_default_scene == 'y' || use_default_scene == 'Y')
    {
        std::cout << "Using default scene." << std::endl;

        auto material_space = make_shared<metal>(color(0.0, 0.0, 0.0), 0.001);
        auto material_star = make_shared<lambertian>(color(1.0, 1.0, 1.0));

        auto material_earth = make_shared<lambertian>(color(0.1, 0.2, 0.5));

        auto material_mars = make_shared<metal>(color(0.8, 0.4, 0.1), 0.6);

        auto material_moon = make_shared<lambertian>(color(0.5, 0.5, 0.5));

        auto material_sun = make_shared<metal>(color(1.0, 1.0, 0.0), 0.9);

        auto material_jupiter = make_shared<lambertian>(color(0.8, 0.5, 0.2));

        auto material_saturn = make_shared<metal>(color(0.9, 0.8, 0.5), 0.8);

        auto material_venus = make_shared<lambertian>(color(0.9, 0.7, 0.5));

        auto material_mercury = make_shared<lambertian>(color(0.7, 0.7, 0.7));

        auto material_neptune = make_shared<dielectric>(0.5);
        auto material_neptune_inside = make_shared<lambertian>(color(0.5, 0.5, 0.5));

        auto material_uranus = make_shared<lambertian>(color(0.5, 0.8, 0.9));

        auto material_atmosphere = make_shared<dielectric>(1.0 / 1.5);

        // generate random stars in the sky
        for (int i = 0; i < 100; i++)
        {
            auto x = random_double(-1.7, 1.7);
            auto y = random_double(-1.7, 1.7);
            auto z = -1.25;
            auto radius = 0.005;
            world.add(make_shared<sphere>(point3(x, y, z), radius, material_star));
        }

        world.add(make_shared<sphere>(point3(0, 0, -9), 7.5, material_space));

        world.add(make_shared<sphere>(point3(0, 0, -1), 0.15, material_sun));

        world.add(make_shared<sphere>(angle_to_position(0.175, 1.1 * pi), 0.015, material_mercury));

        world.add(make_shared<sphere>(angle_to_position(0.225, 1.7 * pi), 0.025, material_venus));
        point3 earth_pos = angle_to_position(0.315, 0.45 * pi);
        world.add(make_shared<sphere>(earth_pos, 0.04, material_earth));
        world.add(make_shared<sphere>(earth_pos, 0.041, material_atmosphere));

        world.add(make_shared<sphere>(point3(earth_pos.x(), earth_pos.y() + 0.05, earth_pos.z()), 0.01, material_moon));
        world.add(make_shared<sphere>(angle_to_position(0.40, 0.1 * pi), 0.03, material_mars));
        world.add(make_shared<sphere>(angle_to_position(0.55, 0.8 * pi), 0.075, material_jupiter));
        world.add(make_shared<sphere>(angle_to_position(0.68, 1.68 * pi), 0.065, material_saturn));
        world.add(make_shared<sphere>(angle_to_position(0.9, 1.1 * pi), 0.045, material_uranus));

        point3 neptune_pos = angle_to_position(0.9, 0.2 * pi);

        world.add(make_shared<sphere>(neptune_pos, 0.05, material_neptune));
        world.add(make_shared<sphere>(neptune_pos, 0.05, material_neptune_inside));
    }
    else
    {
        // Ask the use to input parameters for each sphere in the scene.
        std::cout << std::endl;
        std::cout << "----------------------------------------------- " << std::endl;
        std::cout
            << "Please input the parameters for each sphere in the scene." << std::endl;
        std::cout << std::endl;
        std::cout << "The different material types are: lambertian, metal, dielectric." << std::endl;
        std::cout << "Lambertian: l r[0-1] g[0-1] b[0-1]. ex: l 0.1 0.2 0.5" << std::endl;
        std::cout << "Metal: m r[0-1] g[0-1] b[0-1] fuzz[0-1]. ex: m 0.8 0.8 0.8 0.5" << std::endl;
        std::cout << "Dielectric: d refraction_index.  ex: d 1.5 " << std::endl;
        std::cout << std::endl;
        std::cout << "The camera is at 0,0,0 and looks towards -z" << std::endl;
        std::cout << std::endl;
        std::cout << "Make spheres using [x y z radius material_type material_parameters] one sphere per line. ex: 0 0 -1 0.5 l 0.1 0.2 0.5" << std::endl;
        std::cout << std::endl;
        std::cout << "When you are finished making all spheres, type 'done'." << std::endl;

        std::string input = " ";
        std::getline(std::cin, input);

        while (input != "done")
        {
            std::istringstream iss(input);
            double x, y, z, radius;
            std::string material_type;
            iss >> x >> y >> z >> radius >> material_type;

            shared_ptr<material> mat;

            if (material_type == "l")
            {
                double r, g, b;
                iss >> r >> g >> b;
                mat = make_shared<lambertian>(color(r, g, b));
            }
            else if (material_type == "m")
            {
                double r, g, b, fuzz;
                iss >> r >> g >> b >> fuzz;
                mat = make_shared<metal>(color(r, g, b), fuzz);
            }
            else if (material_type == "d")
            {
                double refraction_index;
                iss >> refraction_index;
                mat = make_shared<dielectric>(refraction_index);
            }
            else
            {
                std::cout << "Unknown material type: " << material_type << std::endl;
            }

            world.add(make_shared<sphere>(point3(x, y, z), radius, mat));

            std::getline(std::cin, input);
        }
    }
    std::cout << "Set the samples per pixel (default 100). Higher is smoother, but takes longer to render: ";
    int samples_per_pixel;
    std::cin >> samples_per_pixel;

    std::cout << "Set the image width for the 16:9 image. (default 400):";
    int image_width;
    std::cin >> image_width;

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = image_width;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth = 50;

    cam.vfov = 70;
    cam.lookfrom = point3(0, 0, 0);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 1;
    cam.focus_dist = 1;

    cam.render(world, output_file);
}
