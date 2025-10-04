#include <iostream>
#include "line_segment_plane_intersection.hh"

int main() {
    using namespace geometry;
    
    // Test case 1: Line segment that crosses the plane
    Point<double, 3> p1(0, 0, -1);  // Below XY plane
    Point<double, 3> p2(0, 0, 1);   // Above XY plane
    LineSegment<double, 3> segment1(p1, p2);
    
    // Create XY plane (z = 0)
    Point<double, 3> plane_point(0, 0, 0);
    Point<double, 3> normal(0, 0, 1);  // Normal pointing in +Z direction
    Plane<double> xy_plane(plane_point, normal);
    
    std::cout << "Test 1 - Line segment crossing plane:" << std::endl;
    std::cout << "Segment: " << segment1 << std::endl;
    std::cout << "Plane: " << xy_plane << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(segment1, xy_plane) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection type: " << intersection_type(segment1, xy_plane) << std::endl;
    
    if (do_intersect(segment1, xy_plane)) {
        Point<double, 3> intersection = intersection_point(segment1, xy_plane);
        std::cout << "Intersection point: " << intersection << std::endl;
    }
    std::cout << std::endl;
    
    // Test case 2: Line segment parallel to plane (no intersection)
    Point<double, 3> p3(1, 0, 1);   // Above XY plane
    Point<double, 3> p4(2, 0, 1);   // Above XY plane
    LineSegment<double, 3> segment2(p3, p4);
    
    std::cout << "Test 2 - Line segment parallel to plane:" << std::endl;
    std::cout << "Segment: " << segment2 << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(segment2, xy_plane) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection type: " << intersection_type(segment2, xy_plane) << std::endl;
    std::cout << std::endl;
    
    // Test case 3: Line segment lying on the plane
    Point<double, 3> p5(1, 1, 0);  // On XY plane
    Point<double, 3> p6(2, 2, 0);  // On XY plane
    LineSegment<double, 3> segment3(p5, p6);
    
    std::cout << "Test 3 - Line segment on plane:" << std::endl;
    std::cout << "Segment: " << segment3 << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(segment3, xy_plane) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection type: " << intersection_type(segment3, xy_plane) << std::endl;
    std::cout << std::endl;
    
    // Test case 4: Line segment with one endpoint on plane
    Point<double, 3> p7(0, 0, 0);   // On XY plane
    Point<double, 3> p8(1, 1, 1);  // Above XY plane
    LineSegment<double, 3> segment4(p7, p8);
    
    std::cout << "Test 4 - Line segment with endpoint on plane:" << std::endl;
    std::cout << "Segment: " << segment4 << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(segment4, xy_plane) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection type: " << intersection_type(segment4, xy_plane) << std::endl;
    
    if (do_intersect(segment4, xy_plane)) {
        Point<double, 3> intersection = intersection_point(segment4, xy_plane);
        std::cout << "Intersection point: " << intersection << std::endl;
    }
    std::cout << std::endl;
    
    // Test case 5: Line segment crossing at an angle
    Point<double, 3> p9(0, 0, -2);  // Below XY plane
    Point<double, 3> p10(1, 1, 2);  // Above XY plane
    LineSegment<double, 3> segment5(p9, p10);
    
    std::cout << "Test 5 - Line segment crossing at angle:" << std::endl;
    std::cout << "Segment: " << segment5 << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(segment5, xy_plane) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection type: " << intersection_type(segment5, xy_plane) << std::endl;
    
    if (do_intersect(segment5, xy_plane)) {
        Point<double, 3> intersection = intersection_point(segment5, xy_plane);
        std::cout << "Intersection point: " << intersection << std::endl;
    }
    
    return 0;
}
