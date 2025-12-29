#pragma once

#include <cmath>

namespace sd {
    // Basic 2 points on warehouse floor
    struct Vec2 {
        double x = 0.0;
        double y = 0.0;
    };

    // Equality comparator used for test and simple check slater
    inline bool operator==(Vec2 a, Vec2 b) {
        return a.x == b.x && a.y == b.y;
    }

    // Euclidean Distance between two points
    inline double distance (Vec2 a, Vec2 b) {
        const double dx = a.x - b.x;
        const double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    
}