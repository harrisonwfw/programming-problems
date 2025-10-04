// Author: HW

#pragma once

#include "common/simplex.hh"

namespace geometry {

/**
 * @brief Represents a (K-1)-dimensional manifold in K-dimensional space,
 * composed of a set of (K-1)-simplices (facets).
 */
template <typename T, size_t K>
class Surface {
public:
    std::vector<Simplex<T, K>> facets;

    Surface() = default;

    // Construct a surface from an initializer list of simplices
    Surface(std::initializer_list<Simplex<T, K>> facet_list) : facets(facet_list) {}

    void add_facet(const Simplex<T, K>& facet) {
        facets.push_back(facet);
    }
    
    size_t num_facets() const {
        return facets.size();
    }

    /**
     * @brief Calculates the centroid of the entire surface mesh.
     * @return A Point representing the centroid.
     */
    Point<T, K> centroid() const {
        if (facets.empty()) return Point<T, K>();
        
        Point<T, K> sum;
        size_t total_vertices = 0;

        for (const auto& facet : facets) {
            for (const auto& vertex : facet.vertices) {
                for (size_t i = 0; i < K; ++i) {
                    sum[i] += vertex[i];
                }
                total_vertices++;
            }
        }

        Point<T, K> centroid_point;
        if (total_vertices > 0) {
            for (size_t i = 0; i < K; ++i) {
                centroid_point[i] = sum[i] / total_vertices;
            }
        }
        return centroid_point;
    }

    /**
     * @brief Calculates the total surface area (for a 2D surface in 3D space).
     * This is a specialization for K=3.
     * @return The total area as a double.
     */
    double area() const {
        // This static_assert ensures this function is only callable for 3D surfaces.
        static_assert(K == 3, "area() is only implemented for 3D space (K=3).");
        
        double total_area = 0.0;
        for (const auto& triangle : facets) {
            // The area of a triangle in 3D is 0.5 * |AB x AC|
            Point<T, 3> ab = triangle.vertices[1] - triangle.vertices[0];
            Point<T, 3> ac = triangle.vertices[2] - triangle.vertices[0];
            
            Point<T, 3> cp = cross_product(ab, ac);
            
            double magnitude_sq = 0.0;
            for(size_t i = 0; i < 3; ++i) {
                magnitude_sq += static_cast<double>(cp[i] * cp[i]);
            }
            
            total_area += 0.5 * std::sqrt(magnitude_sq);
        }
        return total_area;
    }
};

// Overload the << operator for easy printing
template <typename T, size_t K>
std::ostream& operator<<(std::ostream& os, const Surface<T, K>& surface) {
    os << "Surface with " << surface.num_facets() << " facets";
    return os;
}

} // namespace geometry
