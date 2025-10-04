#include <iostream>
#include "line_segment_intersection.hh"

int main() {
    using namespace geometry;
    
    // Test case 1: Intersecting segments
    Point<double, 2> p1(0, 0);
    Point<double, 2> q1(2, 2);
    Point<double, 2> p2(0, 2);
    Point<double, 2> q2(2, 0);
    
    LineSegment<double, 2> seg1(p1, q1);
    LineSegment<double, 2> seg2(p2, q2);
    
    std::cout << "Test 1 - Intersecting segments:" << std::endl;
    std::cout << "Segment 1: " << seg1 << std::endl;
    std::cout << "Segment 2: " << seg2 << std::endl;
    std::cout << "Do they intersect? " << (do_intersect(seg1, seg2) ? "Yes" : "No") << std::endl;
    
    if (do_intersect(seg1, seg2)) {
        Point<double, 2> intersection = intersection_point(seg1, seg2);
        std::cout << "Intersection point: " << intersection << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}