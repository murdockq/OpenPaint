// Per-tip continuity tests for the brush tool.
//
// The bug being fixed: BrushTool used to stamp the brush tip only at
// each individual mouse-move event and never drew a line between
// consecutive events. For the round / square tips (2r-thick stamps)
// the gap was usually hidden, but for the vertical-line and
// horizontal-line tips (1px-thick along the cursor's direction of
// travel) any inter-event motion of more than 1 pixel left an
// unpainted corridor between the two stamps.
//
// These tests build a small white wxBitmap, paint a segment with
// StampBrushAlongLine (the helper BrushTool now uses), and read the
// pixels back. For each Bresenham step that the brush made, the
// centre pixel must be painted. This is a direct, mechanical test
// of the gap-closing property the fix is supposed to guarantee.
//
// The bitmaps are not part of the openpaint_core target (no GUI
// dependency), so this file is compiled into a separate wx-linked
// test binary.

#include <catch2/catch_test_macros.hpp>

#include "BrushSamp.h"

#include <wx/bitmap.h>
#include <wx/colour.h>
#include <wx/dcmemory.h>
#include <wx/image.h>

#include <cstddef>
#include <vector>

namespace {

// Pixel data laid out row-major as 24-bit RGB.
struct PaintedBitmap
{
    int width = 0;
    int height = 0;
    std::vector<unsigned char> rgb; // width * height * 3
};

PaintedBitmap PaintSegmentWithTip(int x0, int y0, int x1, int y1,
                                  int radius, int tip)
{
    const int W = 64;
    const int H = 64;
    PaintedBitmap out;
    out.width = W;
    out.height = H;

    // Use the system default depth (matches what BrushTool will use
    // on the user's display). ConvertToImage gives us a portable
    // RGB byte buffer regardless of the source depth.
    wxBitmap bmp(W, H);
    {
        wxMemoryDC dc(bmp);
        dc.SetBackground(wxBrush(wxColour(255, 255, 255), wxSOLID));
        dc.Clear();
        dc.SetBrush(wxBrush(wxColour(0, 0, 0), wxSOLID));
        StampBrushAlongLine(dc, x0, y0, x1, y1, radius, tip);
    }
    wxImage img = bmp.ConvertToImage();
    REQUIRE(img.IsOk());
    REQUIRE(img.GetWidth() == W);
    REQUIRE(img.GetHeight() == H);
    const std::size_t bytes = static_cast<std::size_t>(W) * H * 3;
    const unsigned char* data = img.GetData();
    out.rgb.assign(data, data + bytes);
    return out;
}

bool PixelIsBlack(const PaintedBitmap& bmp, int x, int y)
{
    if (x < 0 || y < 0 || x >= bmp.width || y >= bmp.height) return false;
    const std::size_t idx = (static_cast<std::size_t>(y) * bmp.width + x) * 3;
    // Threshold well clear of anti-alias noise so the test only
    // fails when the brush genuinely did not paint the centre
    // pixel of a stamp.
    return bmp.rgb[idx]     < 64 &&
           bmp.rgb[idx + 1] < 64 &&
           bmp.rgb[idx + 2] < 64;
}

} // namespace

TEST_CASE("Brush with any tip paints the centre pixel of every Bresenham step",
          "[brush][tip]")
{
    // Diagonal segment chosen so that consecutive Bresenham steps
    // differ in both x and y. The 1px-thick vertical/horizontal
    // line tips are exactly the case where a stamp-only-at-endpoint
    // implementation would miss every intermediate step.
    const int x0 = 8, y0 = 8, x1 = 56, y1 = 24, radius = 3;

    std::vector<IntPoint> steps;
    SampleLinePixels(x0, y0, x1, y1, steps);
    REQUIRE_FALSE(steps.empty());

    for (int tip = 0; tip < 4; ++tip)
    {
        PaintedBitmap bmp = PaintSegmentWithTip(x0, y0, x1, y1, radius, tip);
        for (const IntPoint& p : steps)
        {
            INFO("tip=" << tip << " step=(" << p.x << "," << p.y << ")");
            CHECK(PixelIsBlack(bmp, p.x, p.y));
        }
    }
}

TEST_CASE("Brush with vertical-line tip covers every column on a horizontal sweep",
          "[brush][tip]")
{
    // A purely horizontal segment drawn with the vertical-line tip
    // (1px wide, 2r tall). With Bresenham walking, every column
    // from x0 to x1 must contain a painted pixel at y0 (the centre
    // of the stamp). The pre-fix "stamp at endpoints only" path
    // would leave columns 9..27 entirely white.
    const int x0 = 4, x1 = 60, y0 = 16, radius = 3;
    PaintedBitmap bmp = PaintSegmentWithTip(x0, y0, x1, y0, radius, 2);
    for (int x = x0; x <= x1; ++x)
    {
        CHECK(PixelIsBlack(bmp, x, y0));
    }
}

TEST_CASE("Brush with horizontal-line tip covers every row on a vertical sweep",
          "[brush][tip]")
{
    const int x0 = 16, y0 = 4, y1 = 60, radius = 3;
    PaintedBitmap bmp = PaintSegmentWithTip(x0, y0, x0, y1, radius, 3);
    for (int y = y0; y <= y1; ++y)
    {
        CHECK(PixelIsBlack(bmp, x0, y));
    }
}

TEST_CASE("Brush with round tip covers every step on a steep diagonal",
          "[brush][tip]")
{
    // A 45-degree-ish diagonal: the round brush is the most forgiving
    // tip but it must still cover every Bresenham step.
    const int x0 = 10, y0 = 10, x1 = 50, y1 = 40, radius = 4;
    std::vector<IntPoint> steps;
    SampleLinePixels(x0, y0, x1, y1, steps);
    PaintedBitmap bmp = PaintSegmentWithTip(x0, y0, x1, y1, radius, 0);
    for (const IntPoint& p : steps)
    {
        CHECK(PixelIsBlack(bmp, p.x, p.y));
    }
}

TEST_CASE("Brush with square tip covers every step on a steep diagonal",
          "[brush][tip]")
{
    const int x0 = 10, y0 = 10, x1 = 50, y1 = 40, radius = 4;
    std::vector<IntPoint> steps;
    SampleLinePixels(x0, y0, x1, y1, steps);
    PaintedBitmap bmp = PaintSegmentWithTip(x0, y0, x1, y1, radius, 1);
    for (const IntPoint& p : steps)
    {
        CHECK(PixelIsBlack(bmp, p.x, p.y));
    }
}

TEST_CASE("Brush segments that share an endpoint join without a gap",
          "[brush][tip]")
{
    // Two segments back-to-back through a sharp corner. The shared
    // endpoint must be painted, and every step on each segment must
    // be painted. This catches the failure mode where the "re-stamp
    // at endpoints" pass leaves the joint unpainted.
    const int radius = 3;
    const int W = 48, H = 48;
    wxBitmap bmp(W, H);
    {
        wxMemoryDC dc(bmp);
        dc.SetBackground(wxBrush(wxColour(255, 255, 255), wxSOLID));
        dc.Clear();
        dc.SetBrush(wxBrush(wxColour(0, 0, 0), wxSOLID));
        StampBrushAlongLine(dc, 4, 4,  30, 4,   radius, 2); // horizontal
        StampBrushAlongLine(dc, 30, 4, 30, 40, radius, 3); // vertical
    }
    wxImage img = bmp.ConvertToImage();
    std::vector<unsigned char> rgb(img.GetData(),
                                    img.GetData() + W * H * 3);

    auto isBlack = [&](int x, int y) {
        if (x < 0 || y < 0 || x >= W || y >= H) return false;
        const std::size_t idx = (static_cast<std::size_t>(y) * W + x) * 3;
        return rgb[idx] < 64 && rgb[idx + 1] < 64 && rgb[idx + 2] < 64;
    };

    // The horizontal arm: every column from x=4..30 must be painted
    // at y=4.
    for (int x = 4; x <= 30; ++x)
    {
        CHECK(isBlack(x, 4));
    }
    // The vertical arm: every row from y=4..40 must be painted
    // at x=30.
    for (int y = 4; y <= 40; ++y)
    {
        CHECK(isBlack(30, y));
    }
}
