#pragma once

#include <Eigen/Core>

using Eigen::Vector3f;

class Ray
{
    public:
    Vector3f origin;
    Vector3f direction;

public:
    Ray();
    Ray(Vector3f const &origin_, Vector3f const &dir_);
    Vector3f at(float t) const;
};