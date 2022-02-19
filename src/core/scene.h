#pragma once
#include <memory>
#include <vector>
#include "hittable.h"
class Scene
{
public:
    Scene() : m_hittables()
    {
    }

    void add(std::shared_ptr<Hittable> object)
    {
        m_hittables.push_back(object);
    }

    bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;
        for (const auto &object : m_hittables)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

protected:
    std::vector<std::shared_ptr<Hittable>> m_hittables;
};
