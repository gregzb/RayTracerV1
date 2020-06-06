# pragma once

# include "Utils.hpp"
# include "Hitable.hpp"

class Material {
    public:
    virtual bool scatter(Ray const & r, HitData const &dat, Vector3f &attenuation, Ray &scattered) const = 0;
};