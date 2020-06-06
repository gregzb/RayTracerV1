#pragma once

#include <Eigen/Core>
#include "Ray.hpp"

using Eigen::Vector3f;

class Camera
{
    Vector3f origin;
    Vector3f lowerLeft;
    Vector3f horizontal;
    Vector3f vertical;

public:
Camera(float vFov, float aspectRatio);
Ray getRay(float u, float v);
};