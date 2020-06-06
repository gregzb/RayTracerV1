#include "Ray.hpp"

Ray::Ray() {

}
Ray::Ray(Vector3f const &origin_, Vector3f const &dir_) : origin(origin_), direction(dir_) {

}
Vector3f Ray::at(float t) const{
    return origin + direction * t;
}