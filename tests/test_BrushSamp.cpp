// Unit tests for the pure (wxDC-free) brush sampler.
//
// SampleLinePixels is the Bresenham line walker that BrushTool uses to
// stamp the brush tip at every integer pixel between two consecutive
// mouse-move events. If the walker skipped pixels the brush would
// leave unpainted gaps between stamps, which is the bug this whole
// change-set exists to fix. These tests pin the walker's contract:
// every step differs from the previous one by at most one in each
// coordinate, the segment is connected, and endpoints are emitted
// inclusively.

#include <catch2/catch_test_macros.hpp>

#include "BrushSamp.h"

#include <cstdlib>
#include <set>
#include <vector>

namespace {
inline IntPoint IP(int x, int y) { IntPoint p; p.x = x; p.y = y; return p; }
}

TEST_CASE("SampleLinePixels emits a single point for a zero-length segment",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(5, 7, 5, 7, out);
    REQUIRE(out.size() == 1);
    REQUIRE(out[0] == IP(5, 7));
}

TEST_CASE("SampleLinePixels walks a horizontal line one column at a time",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(0, 10, 5, 10, out);
    REQUIRE(out.size() == 6);
    for (size_t i = 0; i < out.size(); ++i)
    {
        CHECK(out[i] == IP(static_cast<int>(i), 10));
    }
}

TEST_CASE("SampleLinePixels walks a vertical line one row at a time",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(3, 2, 3, 7, out);
    REQUIRE(out.size() == 6);
    for (size_t i = 0; i < out.size(); ++i)
    {
        CHECK(out[i] == IP(3, static_cast<int>(i) + 2));
    }
}

TEST_CASE("SampleLinePixels emits endpoints inclusively on a diagonal",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(0, 0, 5, 3, out);
    REQUIRE(out.size() == 6);
    REQUIRE(out.front() == IP(0, 0));
    REQUIRE(out.back()  == IP(5, 3));
}

TEST_CASE("SampleLinePixels steps by at most one in each axis",
          "[brush][sampler]")
{
    // Property: between any two consecutive samples, the change in x
    // and y is at most 1 (8-connected Bresenham, so diagonal steps
    // are allowed) and at least one axis changes (no zero-length
    // duplicates). This is the property that makes the brush stamp
    // at every pixel on the line, which is what closes gaps for the
    // 1px-thick vertical / horizontal line tips.
    std::vector<IntPoint> out;
    SampleLinePixels(2, 4, 17, 9, out);
    REQUIRE(out.size() == 16);
    for (size_t i = 1; i < out.size(); ++i)
    {
        int dx = std::abs(out[i].x - out[i - 1].x);
        int dy = std::abs(out[i].y - out[i - 1].y);
        CHECK(dx <= 1);
        CHECK(dy <= 1);
        CHECK(dx + dy >= 1);
        CHECK(dx + dy <= 2);
    }
}

TEST_CASE("SampleLinePixels handles a backwards segment",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(5, 0, 0, 0, out);
    REQUIRE(out.size() == 6);
    std::set<int> xs;
    for (size_t i = 0; i < out.size(); ++i)
    {
        CHECK(out[i].y == 0);
        xs.insert(out[i].x);
    }
    // Every integer x in [0, 5] must appear exactly once regardless
    // of which direction the walker stepped.
    REQUIRE(xs.size() == 6);
    for (int x = 0; x <= 5; ++x)
    {
        REQUIRE(xs.count(x) == 1);
    }
}

TEST_CASE("SampleLinePixels covers every integer on a long horizontal",
          "[brush][sampler]")
{
    std::vector<IntPoint> out;
    SampleLinePixels(0, 0, 1000, 0, out);
    REQUIRE(out.size() == 1001);
    REQUIRE(out.front() == IP(0, 0));
    REQUIRE(out.back()  == IP(1000, 0));
    // Each x in [0, 1000] appears exactly once at y == 0.
    std::set<int> xs;
    for (size_t i = 0; i < out.size(); ++i)
    {
        CHECK(out[i].y == 0);
        xs.insert(out[i].x);
    }
    REQUIRE(xs.size() == 1001);
}

TEST_CASE("SampleLinePixels visits every integer pixel on a Bresenham diagonal",
          "[brush][sampler]")
{
    // (0,0) -> (10,6): the classic Bresenham test. The walker should
    // step in the x direction on every iteration and additionally
    // step in y on a subset. Length must be 11 (the larger axis).
    std::vector<IntPoint> out;
    SampleLinePixels(0, 0, 10, 6, out);
    REQUIRE(out.size() == 11);
    int xStepsWithY = 0;
    for (size_t i = 1; i < out.size(); ++i)
    {
        int dx = out[i].x - out[i - 1].x;
        int dy = out[i].y - out[i - 1].y;
        CHECK(dx == 1);
        CHECK((dy == 0 || dy == 1));
        if (dy == 1) ++xStepsWithY;
    }
    CHECK(xStepsWithY == 6);
}
