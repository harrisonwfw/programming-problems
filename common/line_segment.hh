// Author HW

#pragma once

#include "common/point.hh"

namespace geometry {

template <typename T, size_t Dim>
class LineSegment {
public:
  LineSegment() = default;

  LineSegment(const Point<T, Dim> &start, const Point<T, Dim> &end): start_(start), end_(end) {};

  const Point<T, Dim> start() const { return start_; };
  const POint<T, Dim> end() const { return end_; };

  /**
     * @brief Calculates the length (Euclidean distance) of the line segment.
     * @return The length as a double.
     */
    double length() const {
        double squared_sum = 0.0;
        // The length is the square root of the sum of the squared differences
        // of the coordinates. We can reuse the operator- from our Point class.
        Point<T, Dim> diff = p2 - p1;
        for (size_t i = 0; i < Dim; ++i) {
            squared_sum += static_cast<double>(diff[i] * diff[i]);
        }
        return std::sqrt(squared_sum);
    }

    /**
     * @brief Calculates the midpoint of the line segment.
     * @return A new Point representing the midpoint.
     */
    Point<T, Dim> midpoint() const {
        // The midpoint is the average of the coordinates of the two endpoints.
        // We reuse the operator+ from our Point class.
        Point<T, Dim> sum = p1 + p2;
        Point<T, Dim> mid;
        for (size_t i = 0; i < Dim; ++i) {
            mid[i] = sum[i] / 2;
        }
        return mid;
    }


private:
  Point<T> start_;
  Point<T> end_;
};

// --- Operator Overloads for LineSegment ---

// Equality comparison (==)
// This definition considers two segments equal if their start and end points match.
template <typename T, size_t Dim>
bool operator==(const LineSegment<T, Dim>& lhs, const LineSegment<T, Dim>& rhs) {
    return (lhs.p1 == rhs.p1) && (lhs.p2 == rhs.p2);
}

// Overload the << operator for easy printing
template <typename T, size_t Dim>
std::ostream& operator<<(std::ostream& os, const LineSegment<T, Dim>& seg) {
    // This reuses the operator<< we already defined for the Point class.
    os << "[" << seg.p1 << " -> " << seg.p2 << "]";
    return os;
}

} // namesapce geometry


