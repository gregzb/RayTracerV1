#include "Camera.hpp"
#include "Utils.hpp"

Camera::Camera(float vFov, float aspectRatio)
{
    auto theta = Utils::degToRad(vFov);
    auto h = tan(theta / 2);
    auto aspect_ratio = aspectRatio;
    auto viewport_height = 2 * h;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin = Vector3f(0, 0, 0);
    horizontal = Vector3f(viewport_width, 0.0, 0.0);
    vertical = Vector3f(0.0, viewport_height, 0.0);
    auto focal = Vector3f(0, 0, focal_length);
    lowerLeft = origin - horizontal / 2 - vertical / 2 - focal;
}
Ray Camera::getRay(float u, float v)
{
    return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
}