# pragma once

# include <Eigen/Core>
# include "Ray.hpp"
# include <memory>

using Eigen::Vector3f;

class Material;

struct HitData {
    Vector3f point;
    Vector3f normal;
    float t;

    std::shared_ptr<Material> matPtr;

    bool frontFace;

    inline void setFaceNormal(const Ray& r, const Vector3f& outward_normal) {
        frontFace = r.direction.dot(outward_normal) < 0;
        normal = frontFace ? outward_normal :-outward_normal;
    }
};

class Hitable {
    public:
    virtual bool hit(Ray const & r, float minT, float maxT, HitData& dat) const = 0;
};