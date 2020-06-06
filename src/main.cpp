#include <iostream>
#include <string>

#include <Eigen/Core>

#include "Image.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dielectric.hpp"

Vector3f ray_color(Ray const &r, Hitable const &hitables, int remainingBounces)
{
    // if (flag) {
    //     std::cout << remainingBounces << ": " << std::endl;
    //     std::cout << r.origin << std::endl;
    //     std::cout << r.direction << std::endl;
    //     std::cout << "~~~~" << std::endl;
    // }
    if (remainingBounces < 0) {
        return {0, 0, 0};
    }
    HitData dat;
    if (hitables.hit(r, 0.001, std::numeric_limits<float>::infinity(), dat))
    {
        Ray scattered;
        Vector3f attenuation;
        if (dat.matPtr->scatter(r, dat, attenuation, scattered))
            return attenuation.cwiseProduct(ray_color(scattered, hitables, remainingBounces-1));
        return Vector3f(0,0,0);
    }
    Vector3f unit_direction = r.direction.normalized();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
}

int main()
{
    Image img(960, 540, 4);
    //float aspectRatio = img.getAspectRatio();

    // auto viewport_height = 2.0;
    // auto viewport_width = aspectRatio * viewport_height;
    // float focal_length = 1.0;

    // auto origin = Vector3f(0, 0, 0);
    // auto horizontal = Vector3f(viewport_width, 0, 0);
    // auto vertical = Vector3f(0, viewport_height, 0);
    // auto focal = Vector3f(0, 0, focal_length);
    // auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - focal;

    const int samples_per_pixel = 120;
    const int bounces = 8;

    Camera cam(80, img.getAspectRatio());

    Scene scene;
    scene.addSurface(make_shared<Sphere>(Vector3f(0, 0, -1), 0.5, make_shared<Lambertian>(Vector3f(0.1, 0.2, 0.5)) ));
    scene.addSurface(make_shared<Sphere>(Vector3f(0, -100.5, -1), 100, make_shared<Lambertian>(Vector3f(0.8, 0.8, 0.0)) ));

    scene.addSurface(make_shared<Sphere>(Vector3f(1,0,-1), 0.5, make_shared<Metal>(Vector3f(.8,.6,.2), 0.5)));
    scene.addSurface(make_shared<Sphere>(Vector3f(-1,0,-1), 0.5, make_shared<Dielectric>(1.5) ));

    // for (int j = 0; j < img.getHeight(); j++)
    // {
    //     std::cout << "\rScanlines remaining: " << img.getHeight() - j << std::endl;
    //     for (int i = 0; i < img.getWidth(); ++i)
    //     {
    //         auto u = (i + Utils::random()) / (img.getWidth() - 1);
    //         auto v = (j + Utils::random()) / (img.getHeight() - 1);
    //         Ray r = cam.getRay(u, v);
    //         Vector3f result = ray_color(r, scene);
    //         Color c = Utils::toColor3(result);
    //         img.setPixel(i, j, c);
    //     }
    // }

    float gamma = 2.2;

    for (int j = 0; j < img.getHeight(); j++)
    {
        std::cout << "\rScanlines remaining: " << img.getHeight() - j << std::endl;
        for (int i = 0; i < img.getWidth(); ++i)
        {
            Vector3f currColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                // flag = false;
                // if (j == 257 && i == 114 && s == 0) {
                //     std::cout << "flagged" << std::endl;
                //     flag = true;
                // }
                auto u = (i + 0.5 + Utils::random() - 0.5) / (img.getWidth()-1);
                auto v = (j + 0.5 + Utils::random() - 0.5) / (img.getHeight()-1);
                Ray r = cam.getRay(u, v);
                Vector3f rayC = ray_color(r, scene, bounces);
                currColor += rayC;
                // if (rayC.x() != rayC.x()) {
                //     std::cout << j << " " << i << " " << s << std::endl;
                //     std::cout << rayC << std::endl;
                // }
            }
            // Vector3f backup = currColor;
            currColor /= samples_per_pixel;
            currColor[0] = std::pow(currColor[0], 1/gamma);
            currColor[1] = std::pow(currColor[1], 1/gamma);
            currColor[2] = std::pow(currColor[2], 1/gamma);
            Color c = Utils::toColor3(currColor);
            // if (c.r == 0 && c.g == 0 && c.b == 0) {
            //     std::cout << j << " " << i << std::endl;
            //     std::cout << samples_per_pixel << std::endl;
            //     std::cout << currColor << std::endl;
            //     std::cout << backup << std::endl;
            // }
            img.setPixel(i, j, c);
        }
    }

    img.toFile("output3.png", true);

    return 0;
}