#pragma once

#include <Eigen/Core>
#include <iostream>
#include <cmath>
#include <random>

#include "Ray.hpp"

using Eigen::Vector3f;
using Eigen::Vector4f;

typedef unsigned char u_char;

struct Color
{
    u_char r, g, b, a;
};

// inline bool flag = false;

namespace Utils
{
    inline int sign(float x)
    {
        return (x > 0) - (x < 0);
    }

    inline float inverseLerp(float a, float b, float val)
    {
        return (val - a) / (b - a);
    }

    inline float lerp(float a, float b, float t)
    {
        return (1 - t) * a + t * b;
    }

    inline float map(float value, float low1, float high1, float low2, float high2)
    {
        return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
    }

    inline float clamp(float value, float min, float max)
    {
        return std::min(std::max(value, min), max);
    }

    inline float saturate(float value)
    {
        return Utils::clamp(value, 0.0, 1.0);
    }

    inline int clamp(int value, int min, int max)
    {
        return std::min(std::max(value, min), max);
    }

    inline Color toColor3(Vector3f const &vec)
    {
        Color temp;
        temp.r = Utils::saturate(vec.x()) * 255.9999;
        temp.g = Utils::saturate(vec.y()) * 255.9999;
        temp.b = Utils::saturate(vec.z()) * 255.9999;
        temp.a = 255;
        return temp;
    }

    inline Color toColor4(Vector4f const &vec)
    {
        Color temp = Utils::toColor3({vec.x(), vec.y(), vec.z()});
        temp.a = Utils::saturate(vec.w()) * 255.9999;
        return temp;
    }

    inline float degToRad(float degrees)
    {
        return degrees * M_PI / 180;
    }

    inline float random()
    {
        static std::uniform_real_distribution<float> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline float random(float min, float max)
    {
        // Returns a random real in [min,max).
        return min + (max - min) * Utils::random();
    }

    inline Vector3f randomUnitVec()
    {
        auto a = random(0, 2 * M_PI);
        auto z = random(-1, 1);
        auto r = std::sqrt(1 - z * z);
        return Vector3f(r * cos(a), r * sin(a), z);
    }
    inline Vector3f reflect(const Vector3f &v, const Vector3f &n)
    {
        return v - 2 * v.dot(n) * n;
    }
    inline Vector3f refract(Vector3f const &uv, Vector3f const &n, float etai_over_etat)
    {
        // if (flag) std::cout << "ref: " << etai_over_etat << " " << uv << " - " << n << std::endl;
        auto cos_theta = (-uv).dot(n);
        Vector3f r_out_parallel = etai_over_etat * (uv + cos_theta * n);
        Vector3f r_out_perp = -sqrt(1.0 - r_out_parallel.squaredNorm()) * n;
        return r_out_parallel + r_out_perp;
    }
    inline float schlick(float cosine, double ref_idx)
    {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
}; // namespace Utils