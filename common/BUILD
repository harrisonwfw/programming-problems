# Author: HW

package(default_visibility=["//visibility:public"])


cc_library(
    name="point",
    hdrs=["point.hh"],
)

cc_library(
    name="line_segment",
    hdrs=["line_segment.hh"],
    deps=[":point"],
)

cc_library(
    name="simplex",
    hdrs=["simplex.hh"],
    deps=[":point"],
)

cc_library(
    name="surface",
    hdrs=["surface.hh"],
    deps=[":simplex"],
)

cc_library(
    name="line_segment_intersection",
    hdrs=["line_segment_intersection.hh"],
    deps=[":point", ":line_segment"],
)

cc_test(
    name="line_segment_intersection_test",
    srcs=["line_segment_intersection_test.cc"],
    deps=[":line_segment_intersection"],
)
