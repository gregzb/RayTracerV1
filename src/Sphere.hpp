# pragma once

# include <Eigen/Core>
# include "Hitable.hpp"
# include "Material.hpp"
# include <memory>

using Eigen::Vector3f;

class Sphere : public Hitable{
    Vector3f center;
    float radius;
    std::shared_ptr<Material> matPtr;

    public:
    Sphere();
    Sphere(Vector3f const & center_, float radius_, std::shared_ptr<Material> matPtr_);
    virtual bool hit(Ray const & r, float minT, float maxT, HitData& dat) const;
};