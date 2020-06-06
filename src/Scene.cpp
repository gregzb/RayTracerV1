#include "Scene.hpp"

Scene::Scene()
{
}
void Scene::clear() {
    surfaces.clear();
}
void Scene::addSurface(shared_ptr<Hitable> h) {
    surfaces.push_back(h);
}

bool Scene::hit(Ray const &r, float minT, float maxT, HitData &dat) const { 
    HitData tempDat;
    bool hit_anything = false;
    auto closest_so_far = maxT+1;

    for (const auto& object : surfaces) {
        if (object->hit(r, minT, closest_so_far, tempDat)) {
            hit_anything = true;
            closest_so_far = tempDat.t;
            dat = tempDat;
        }
    }

    return hit_anything;
}