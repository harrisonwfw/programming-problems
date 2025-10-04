// Author: HW

#pragma once

#include <cmath>
#include <algorithm>
#include "common/point.hh"
#include "common/line_segment.hh"

namespace geometry {

/**
 * @brief Determines the orientation of three points in 2D space.
 * @param p1 First point
 * @param p2 Second point  
 * @param p3 Third point
 * @return 0 if collinear, 1 if counterclockwise, 2 if clockwise
 */
template <typename T>
int orientation(const Point<T, 2>& p1, const Point<T, 2>& p2, const Point<T, 2>& p3) {
    T val = (p2.y() - p1.y()) * (p3.x() - p2.x()) - (p2.x() - p1.x()) * (p3.y() - p2.y());
    
    if (std::abs(val) < 1e-9) return 0;  // collinear
    return (val > 0) ? 1 : 2;  // counterclockwise or clockwise
}

/**
 * @brief Checks if point q lies on line segment pr.
 * @param p First endpoint of line segment
 * @param q Point to check
 * @param r Second endpoint of line segment
 * @return true if q lies on segment pr, false otherwise
 */
template <typename T>
bool on_segment(const Point<T, 2>& p, const Point<T, 2>& q, const Point<T, 2>& r) {
    return q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
           q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y());
}

/**
 * @brief Determines if two line segments intersect in 2D space.
 * Uses the orientation-based algorithm for robust intersection detection.
 * @param seg1 First line segment
 * @param seg2 Second line segment
 * @return true if the segments intersect, false otherwise
 */
template <typename T>
bool do_intersect(const LineSegment<T, 2>& seg1, const LineSegment<T, 2>& seg2) {
    const Point<T, 2>& p1 = seg1.start();
    const Point<T, 2>& q1 = seg1.end();
    const Point<T, 2>& p2 = seg2.start();
    const Point<T, 2>& q2 = seg2.end();
    
    // Find the four orientations needed for the general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    // General case: segments intersect if orientations are different
    if (o1 != o2 && o3 != o4) {
        return true;
    }
    
    // Special cases: collinear points
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;
    
    return false;
}

/**
 * @brief Finds the intersection point of two line segments (if they intersect).
 * @param seg1 First line segment
 * @param seg2 Second line segment
 * @return The intersection point, or a default point if no intersection
 */
template <typename T>
Point<T, 2> intersection_point(const LineSegment<T, 2>& seg1, const LineSegment<T, 2>& seg2) {
    const Point<T, 2>& p1 = seg1.start();
    const Point<T, 2>& q1 = seg1.end();
    const Point<T, 2>& p2 = seg2.start();
    const Point<T, 2>& q2 = seg2.end();
    
    // Check if segments intersect first
    if (!do_intersect(seg1, seg2)) {
        return Point<T, 2>(0, 0); // Return default point if no intersection
    }
    
    // Calculate intersection using parametric equations
    T x1 = p1.x(), y1 = p1.y();
    T x2 = q1.x(), y2 = q1.y();
    T x3 = p2.x(), y3 = p2.y();
    T x4 = q2.x(), y4 = q2.y();
    
    T denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (std::abs(denom) < 1e-9) {
        // Lines are parallel or coincident
        return Point<T, 2>(0, 0);
    }
    
    T t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    
    T x = x1 + t * (x2 - x1);
    T y = y1 + t * (y2 - y1);
    
    return Point<T, 2>(x, y);
}

} // namespace geometry
