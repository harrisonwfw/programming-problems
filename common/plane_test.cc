#include <iostream>
#include "plane.hh"

int main() {
    using namespace geometry;
    
    // Test case 1: Create plane from point and normal
    Point<double, 3> point(0, 0, 0);
    Point<double, 3> normal(0, 0, 1);  // Normal pointing in +Z direction
    Plane<double> plane1(point, normal);
    
    std::cout << "Test 1 - Plane from point and normal:" << std::endl;
    std::cout << "Plane: " << plane1 << std::endl;
    std::cout << "Point on plane: " << plane1.point() << std::endl;
    std::cout << "Normal vector: " << plane1.normal() << std::endl;
    std::cout << std::endl;
    
    // Test case 2: Create plane from three points
    Point<double, 3> p1(1, 0, 0);
    Point<double, 3> p2(0, 1, 0);
    Point<double, 3> p3(0, 0, 1);
    Plane<double> plane2(p1, p2, p3);
    
    std::cout << "Test 2 - Plane from three points:" << std::endl;
    std::cout << "Plane: " << plane2 << std::endl;
    std::cout << std::endl;
    
    // Test case 3: Distance calculations
    Point<double, 3> test_point(0, 0, 5);
    double distance = plane1.distance_to_point(test_point);
    std::cout << "Test 3 - Distance calculation:" << std::endl;
    std::cout << "Distance from point " << test_point << " to plane: " << distance << std::endl;
    std::cout << "Point on plane? " << (plane1.contains_point(test_point) ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
    
    // Test case 4: Point on plane
    Point<double, 3> point_on_plane(2, 3, 0);
    std::cout << "Test 4 - Point on plane:" << std::endl;
    std::cout << "Point " << point_on_plane << " on plane? " 
              << (plane1.contains_point(point_on_plane) ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
    
    // Test case 5: Parallel planes
    Point<double, 3> point2(0, 0, 1);
    Plane<double> plane3(point2, normal);
    std::cout << "Test 5 - Parallel planes:" << std::endl;
    std::cout << "Plane 1: " << plane1 << std::endl;
    std::cout << "Plane 3: " << plane3 << std::endl;
    std::cout << "Are they parallel? " << (plane1.is_parallel_to(plane3) ? "Yes" : "No") << std::endl;
    std::cout << "Are they the same? " << (plane1.is_same_as(plane3) ? "Yes" : "No") << std::endl;
    
    return 0;
}
