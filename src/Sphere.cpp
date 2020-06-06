#include "Sphere.hpp"

Sphere::Sphere()
{
}
Sphere::Sphere(Vector3f const &center_, float radius_, std::shared_ptr<Material> matPtr_) : center(center_), radius(radius_), matPtr(matPtr_) {

}
bool Sphere::hit(Ray const &r, float minT, float maxT, HitData &dat) const
{
    Vector3f oc = r.origin - center;
    auto a = r.direction.squaredNorm();
    auto half_b = oc.dot(r.direction);
    auto c = oc.squaredNorm() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if (temp < maxT && temp > minT) {
            dat.t = temp;
            dat.point = r.at(dat.t);
            Vector3f outward_normal = (dat.point - center) / radius;
            dat.setFaceNormal(r, outward_normal);
            dat.matPtr = matPtr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < maxT && temp > minT) {
            dat.t = temp;
            dat.point = r.at(dat.t);
            Vector3f outward_normal = (dat.point - center) / radius;
            dat.setFaceNormal(r, outward_normal);
            dat.matPtr = matPtr;
            return true;
        }
    }
    return false;
}