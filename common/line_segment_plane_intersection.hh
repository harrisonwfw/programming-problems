// Author: HW

#pragma once

#include <cmath>
#include "common/point.hh"
#include "common/line_segment.hh"
#include "common/plane.hh"

namespace geometry {

/**
 * @brief Determines if a line segment intersects a plane in 3D space.
 * @param segment The line segment to test
 * @param plane The plane to test intersection with
 * @param tolerance The tolerance for considering points on the plane
 * @return true if the segment intersects the plane, false otherwise
 */
template <typename T>
bool do_intersect(const LineSegment<T, 3>& segment, const Plane<T>& plane, T tolerance = 1e-9) {
    const Point<T, 3>& p1 = segment.start();
    const Point<T, 3>& p2 = segment.end();
    
    // Calculate distances from both endpoints to the plane
    T dist1 = plane.distance_to_point(p1);
    T dist2 = plane.distance_to_point(p2);
    
    // If both points are on the same side of the plane (both positive or both negative)
    // and neither is on the plane, then the segment doesn't intersect
    if (std::abs(dist1) > tolerance && std::abs(dist2) > tolerance) {
        if ((dist1 > 0 && dist2 > 0) || (dist1 < 0 && dist2 < 0)) {
            return false;
        }
    }
    
    // If we reach here, either:
    // 1. One point is on the plane (distance ≈ 0)
    // 2. Points are on opposite sides of the plane
    // 3. Both points are on the plane
    return true;
}

/**
 * @brief Finds the intersection point of a line segment and a plane.
 * @param segment The line segment
 * @param plane The plane
 * @param tolerance The tolerance for considering points on the plane
 * @return The intersection point, or a default point if no intersection
 */
template <typename T>
Point<T, 3> intersection_point(const LineSegment<T, 3>& segment, const Plane<T>& plane, T tolerance = 1e-9) {
    const Point<T, 3>& p1 = segment.start();
    const Point<T, 3>& p2 = segment.end();
    
    // Check if segment intersects the plane first
    if (!do_intersect(segment, plane, tolerance)) {
        return Point<T, 3>(0, 0, 0); // Return default point if no intersection
    }
    
    // Calculate distances from both endpoints to the plane
    T dist1 = plane.distance_to_point(p1);
    T dist2 = plane.distance_to_point(p2);
    
    // If both points are on the plane, return the first point
    if (std::abs(dist1) < tolerance && std::abs(dist2) < tolerance) {
        return p1;
    }
    
    // If one point is on the plane, return that point
    if (std::abs(dist1) < tolerance) {
        return p1;
    }
    if (std::abs(dist2) < tolerance) {
        return p2;
    }
    
    // Calculate the intersection point using parametric line equation
    // The line segment can be parameterized as: P = p1 + t * (p2 - p1)
    // We need to find t such that the point lies on the plane
    // Using the plane equation: normal · (point - plane_point) = 0
    
    Point<T, 3> direction = p2 - p1;
    T denominator = dot_product(plane.normal(), direction);
    
    // If the line is parallel to the plane, there's no unique intersection
    if (std::abs(denominator) < tolerance) {
        return Point<T, 3>(0, 0, 0);
    }
    
    // Calculate the parameter t
    T t = -dist1 / denominator;
    
    // Calculate the intersection point
    Point<T, 3> scaled_direction(direction.x() * t, direction.y() * t, direction.z() * t);
    Point<T, 3> intersection = p1 + scaled_direction;
    
    return intersection;
}

/**
 * @brief Determines the type of intersection between a line segment and a plane.
 * @param segment The line segment
 * @param plane The plane
 * @param tolerance The tolerance for considering points on the plane
 * @return A string describing the intersection type
 */
template <typename T>
std::string intersection_type(const LineSegment<T, 3>& segment, const Plane<T>& plane, T tolerance = 1e-9) {
    const Point<T, 3>& p1 = segment.start();
    const Point<T, 3>& p2 = segment.end();
    
    T dist1 = plane.distance_to_point(p1);
    T dist2 = plane.distance_to_point(p2);
    
    // Check if both points are on the plane
    if (std::abs(dist1) < tolerance && std::abs(dist2) < tolerance) {
        return "segment_lies_on_plane";
    }
    
    // Check if one endpoint is on the plane
    if (std::abs(dist1) < tolerance || std::abs(dist2) < tolerance) {
        return "endpoint_on_plane";
    }
    
    // Check if points are on opposite sides
    if ((dist1 > 0 && dist2 < 0) || (dist1 < 0 && dist2 > 0)) {
        return "segment_crosses_plane";
    }
    
    // Points are on the same side
    return "no_intersection";
}

/**
 * @brief Calculates the dot product of two 3D vectors.
 * @param a First vector
 * @param b Second vector
 * @return The dot product
 */
template <typename T>
T dot_product(const Point<T, 3>& a, const Point<T, 3>& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

/**
 * @brief Calculates the cross product of two 3D vectors.
 * @param a First vector
 * @param b Second vector
 * @return The cross product vector
 */
template <typename T>
Point<T, 3> cross_product(const Point<T, 3>& a, const Point<T, 3>& b) {
    return Point<T, 3>(
        a.y() * b.z() - a.z() * b.y(),
        a.z() * b.x() - a.x() * b.z(),
        a.x() * b.y() - a.y() * b.x()
    );
}

} // namespace geometry
