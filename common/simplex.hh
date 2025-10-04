// Author: HW

#pragma once

#include <numeric>

#include "common/point.hh"

namespace geometry {


/**
 * @brief Represents a (K-1)-simplex in K-dimensional space, defined by K vertices.
 * For K=3, this is a triangle. For K=4, this is a tetrahedron.
 */
template <typename T, size_t K>
class Simplex {
public:
    std::array<Point<T, K>, K> vertices;

    Simplex() = default;

    // Construct a simplex from K points
    Simplex(const std::array<Point<T, K>, K>& verts) : vertices(verts) {}

    /**
     * @brief Calculates the centroid (geometric center) of the simplex.
     * @return A new Point representing the centroid.
     */
    Point<T, K> centroid() const {
        Point<T, K> sum; // Starts at (0,0,...)
        for (const auto& v : vertices) {
            for (size_t i = 0; i < K; ++i) {
                sum[i] += v[i];
            }
        }
        
        Point<T, K> centroid_point;
        for (size_t i = 0; i < K; ++i) {
            centroid_point[i] = sum[i] / K;
        }
        return centroid_point;
    }
};

// Helper function to calculate the cross product for 3D points
template <typename T>
Point<T, 3> cross_product(const Point<T, 3>& a, const Point<T, 3>& b) {
    return Point<T, 3>(
        a.y() * b.z() - a.z() * b.y(),
        a.z() * b.x() - a.x() * b.z(),
        a.x() * b.y() - a.y() * b.x()
    );
}

} // namespace geometry
