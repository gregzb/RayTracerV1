# pragma once

# include <Eigen/Core>
# include "Hitable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene : public Hitable{
    std::vector<shared_ptr<Hitable>> surfaces;

    public:
    Scene();
    void clear();
    void addSurface(shared_ptr<Hitable> h);
    
    virtual bool hit(Ray const & r, float minT, float maxT, HitData & dat) const;
};