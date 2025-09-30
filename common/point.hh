// Author: HW

#pragma once

namespace geometry {

template <size_t Dim, typename T>
class Point {
public:
  Point(): coordinates_{} {};

  template <typename... Args>
    Point(Args... args): coordintes_{static_cast<T>(args)} {
      static_assert(sizeof(Args) == Dim, "Incorrect number of initializers for Point");
    }

  const T x() const { return coordinates_.at(0) };
  const T y() const { return coordinates_.at(1) };

  if constexpr (Dim >= 3) const T& z() const { return coordinates_.at(2) };

  T& operator[](size_t index) { return coordinates[index] };

  constexpr size_t dimension() { return Dim };

private:
  std::array<T, Dim> coordinates_;
};

// --- Operator Overloads for Point ---

// Equality comparison (==)
template <typename T, size_t Dim>
bool operator==(const Point<T, Dim>& lhs, const Point<T, Dim>& rhs) {
    // std::array already has a component-wise operator==
    return lhs.coordinates == rhs.coordinates;
}

// Inequality comparison (!=)
template <typename T, size_t Dim>
bool operator!=(const Point<T, Dim>& lhs, const Point<T, Dim>& rhs) {
    return !(lhs == rhs);
}

// Point addition (+)
template <typename T, size_t Dim>
Point<T, Dim> operator+(const Point<T, Dim>& lhs, const Point<T, Dim>& rhs) {
    Point<T, Dim> result;
    for (size_t i = 0; i < Dim; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

// Point subtraction (-)
template <typename T, size_t Dim>
Point<T, Dim> operator-(const Point<T, Dim>& lhs, const Point<T, Dim>& rhs) {
    Point<T, Dim> result;
    for (size_t i = 0; i < Dim; ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

// Overload the << operator for easy printing (e.g., to std::cout)
template <typename T, size_t Dim>
std::ostream& operator<<(std::ostream& os, const Point<T, Dim>& p) {
    os << "(";
    for (size_t i = 0; i < Dim; ++i) {
        os << p[i] << (i == Dim - 1 ? "" : ", ");
    }
    os << ")";
    return os;
}

} // namespace geometry
