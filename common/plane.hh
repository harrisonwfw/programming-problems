// Author: HW

#pragma once

#include <cmath>
#include <tuple>
#include <stdexcept>
#include "common/point.hh"

namespace geometry {

/**
 * @brief Represents a plane in 3D space.
 * A plane is defined by a point on the plane and a normal vector.
 * The plane equation is: normal · (point - plane_point) = 0
 */
template <typename T>
class Plane {
public:
    Plane() = default;

    /**
     * @brief Construct a plane from a point on the plane and a normal vector.
     * @param point_on_plane A point that lies on the plane
     * @param normal_vector The normal vector to the plane (will be normalized)
     */
    Plane(const Point<T, 3>& point_on_plane, const Point<T, 3>& normal_vector) 
        : point_(point_on_plane), normal_(normalize(normal_vector)) {}

    /**
     * @brief Construct a plane from three non-collinear points.
     * @param p1 First point on the plane
     * @param p2 Second point on the plane  
     * @param p3 Third point on the plane
     */
    Plane(const Point<T, 3>& p1, const Point<T, 3>& p2, const Point<T, 3>& p3) {
        point_ = p1;
        // Calculate normal using cross product of two vectors on the plane
        Point<T, 3> v1 = p2 - p1;
        Point<T, 3> v2 = p3 - p1;
        normal_ = normalize(cross_product(v1, v2));
    }

    /**
     * @brief Get a point on the plane.
     * @return A point that lies on the plane
     */
    const Point<T, 3>& point() const { return point_; }

    /**
     * @brief Get the normal vector of the plane.
     * @return The normalized normal vector
     */
    const Point<T, 3>& normal() const { return normal_; }

    /**
     * @brief Calculate the distance from a point to the plane.
     * @param p The point to measure distance from
     * @return The signed distance (positive if point is on normal side)
     */
    T distance_to_point(const Point<T, 3>& p) const {
        Point<T, 3> diff = p - point_;
        return dot_product(normal_, diff);
    }

    /**
     * @brief Check if a point lies on the plane (within tolerance).
     * @param p The point to check
     * @param tolerance The tolerance for considering points on the plane
     * @return true if the point is on the plane
     */
    bool contains_point(const Point<T, 3>& p, T tolerance = 1e-9) const {
        return std::abs(distance_to_point(p)) < tolerance;
    }

    /**
     * @brief Get the plane equation coefficients (ax + by + cz + d = 0).
     * @return A tuple of (a, b, c, d) where the plane equation is ax + by + cz + d = 0
     */
    std::tuple<T, T, T, T> equation() const {
        T a = normal_.x();
        T b = normal_.y();
        T c = normal_.z();
        T d = -dot_product(normal_, point_);
        return std::make_tuple(a, b, c, d);
    }

    /**
     * @brief Check if two planes are parallel.
     * @param other The other plane to compare with
     * @param tolerance The tolerance for considering vectors parallel
     * @return true if the planes are parallel
     */
    bool is_parallel_to(const Plane<T>& other, T tolerance = 1e-9) const {
        T dot = std::abs(dot_product(normal_, other.normal_));
        return std::abs(dot - 1.0) < tolerance;
    }

    /**
     * @brief Check if two planes are the same (same normal and point).
     * @param other The other plane to compare with
     * @param tolerance The tolerance for considering planes equal
     * @return true if the planes are the same
     */
    bool is_same_as(const Plane<T>& other, T tolerance = 1e-9) const {
        return is_parallel_to(other, tolerance) && 
               contains_point(other.point_, tolerance);
    }

private:
    Point<T, 3> point_;    // A point on the plane
    Point<T, 3> normal_;   // Normalized normal vector

    /**
     * @brief Normalize a vector.
     * @param v The vector to normalize
     * @return The normalized vector
     */
    static Point<T, 3> normalize(const Point<T, 3>& v) {
        T magnitude = std::sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
        if (magnitude < 1e-9) {
            throw std::invalid_argument("Cannot normalize zero vector");
        }
        return Point<T, 3>(v.x() / magnitude, v.y() / magnitude, v.z() / magnitude);
    }

    /**
     * @brief Calculate the dot product of two 3D vectors.
     * @param a First vector
     * @param b Second vector
     * @return The dot product
     */
    static T dot_product(const Point<T, 3>& a, const Point<T, 3>& b) {
        return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
    }

    /**
     * @brief Calculate the cross product of two 3D vectors.
     * @param a First vector
     * @param b Second vector
     * @return The cross product vector
     */
    static Point<T, 3> cross_product(const Point<T, 3>& a, const Point<T, 3>& b) {
        return Point<T, 3>(
            a.y() * b.z() - a.z() * b.y(),
            a.z() * b.x() - a.x() * b.z(),
            a.x() * b.y() - a.y() * b.x()
        );
    }
};

// --- Operator Overloads for Plane ---

/**
 * @brief Equality comparison for planes.
 * @param lhs First plane
 * @param rhs Second plane
 * @return true if the planes are the same
 */
template <typename T>
bool operator==(const Plane<T>& lhs, const Plane<T>& rhs) {
    return lhs.is_same_as(rhs);
}

/**
 * @brief Inequality comparison for planes.
 * @param lhs First plane
 * @param rhs Second plane
 * @return true if the planes are different
 */
template <typename T>
bool operator!=(const Plane<T>& lhs, const Plane<T>& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Stream output operator for planes.
 * @param os Output stream
 * @param plane The plane to output
 * @return The output stream
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Plane<T>& plane) {
    auto [a, b, c, d] = plane.equation();
    os << "Plane: " << a << "x + " << b << "y + " << c << "z + " << d << " = 0";
    return os;
}

} // namespace geometry
