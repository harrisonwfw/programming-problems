workspace(name = "programming-problems")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
    strip_prefix = "eigen-3.4.0",
    sha256 = "b4dba9ff03549d1dcf64f148d464c5c1a0d1941c82d92a3c8bd227c8a29a474b",
    build_file = "//third_party:eigen.BUILD",
)

