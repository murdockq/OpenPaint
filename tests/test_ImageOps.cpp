// Unit tests for the openpaint::ImageOps image operations.

#include <catch2/catch_test_macros.hpp>

#include "ImageOps.h"

#include <cmath>
#include <vector>

using openpaint::ImageData;
using openpaint::InvertColors;
using openpaint::Blur;
using openpaint::Pixelize;
using openpaint::Greyscale;
using openpaint::Monochrome;
using openpaint::FloodFill;
using openpaint::SprayCan;
using openpaint::FlipHorizontal;
using openpaint::FlipVertical;
using openpaint::Rotate90;
using openpaint::RotateDeg;
using openpaint::Rescale;
using openpaint::Resize;

namespace {

// Build a 4x4 image where every pixel is the same colour.
ImageData SolidImage(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    ImageData img(w, h);
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            img.SetPixel(x, y, r, g, b);
        }
    }
    return img;
}

bool AllPixelsEqual(const ImageData& img, unsigned char r, unsigned char g, unsigned char b)
{
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            unsigned char pr, pg, pb;
            img.GetPixel(x, y, pr, pg, pb);
            if (pr != r || pg != g || pb != b)
            {
                return false;
            }
        }
    }
    return true;
}

} // namespace

TEST_CASE("InvertColors flips every RGB channel", "[ImageOps]")
{
    auto img = SolidImage(2, 2, 10, 20, 30);
    InvertColors(img);
    REQUIRE(AllPixelsEqual(img, 245, 235, 225));
}

TEST_CASE("InvertColors on a white image produces black", "[ImageOps]")
{
    auto img = SolidImage(2, 2, 255, 255, 255);
    InvertColors(img);
    REQUIRE(AllPixelsEqual(img, 0, 0, 0));
}

TEST_CASE("Blur with radius 1 averages each pixel with its 3x3 neighbourhood", "[ImageOps]")
{
    // 3x3 image, centre pixel is white, surrounds are black.
    // After Blur(1) the centre should drop to (255 / 9) ~= 28 on every channel.
    ImageData img(3, 3);
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            img.SetPixel(x, y, 0, 0, 0);
        }
    }
    img.SetPixel(1, 1, 255, 255, 255);
    Blur(img, 1);
    unsigned char r, g, b;
    img.GetPixel(1, 1, r, g, b);
    REQUIRE(static_cast<int>(r) == 255 / 9);
    REQUIRE(static_cast<int>(g) == 255 / 9);
    REQUIRE(static_cast<int>(b) == 255 / 9);
}

TEST_CASE("Blur with radius 0 is clamped to radius 1", "[ImageOps]")
{
    auto img = SolidImage(2, 2, 100, 50, 25);
    Blur(img, 0);
    // With radius clamped to 1 every pixel sees the whole 2x2 image, so the
    // average colour is the input colour.
    REQUIRE(AllPixelsEqual(img, 100, 50, 25));
}

TEST_CASE("Pixelize with block size N replaces each NxN block with the average", "[ImageOps]")
{
    ImageData img(4, 4);
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            img.SetPixel(x, y, 0, 0, 0);
        }
    }
    // Set the top-left 2x2 block to red.
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 2; ++x)
        {
            img.SetPixel(x, y, 200, 100, 50);
        }
    }
    Pixelize(img, 2);
    // Top-left block is now 200,100,50; rest is 0,0,0.
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 200);
    REQUIRE(g == 100);
    REQUIRE(b == 50);
    img.GetPixel(3, 3, r, g, b);
    REQUIRE(r == 0);
    REQUIRE(g == 0);
    REQUIRE(b == 0);
}

TEST_CASE("Greyscale converts RGB to luminance using BT.601 weights", "[ImageOps]")
{
    ImageData img(1, 1);
    img.SetPixel(0, 0, 255, 0, 0);
    Greyscale(img);
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    // (299 * 255 + 0 + 0) / 1000 = 76 (rounded down).
    REQUIRE(r == g);
    REQUIRE(g == b);
    REQUIRE(r == 76);
}

TEST_CASE("Monochrome thresholds luminance at 128", "[ImageOps]")
{
    ImageData img(2, 1);
    img.SetPixel(0, 0, 200, 200, 200);
    img.SetPixel(1, 0, 50, 50, 50);
    Monochrome(img);
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 255);
    img.GetPixel(1, 0, r, g, b);
    REQUIRE(r == 0);
}

TEST_CASE("FloodFill replaces the connected region but not other colours", "[ImageOps]")
{
    ImageData img(4, 4);
    // A 3x3 red region in the middle, surrounded by black.
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            img.SetPixel(x, y, 0, 0, 0);
        }
    }
    for (int y = 1; y < 4; ++y)
    {
        for (int x = 1; x < 4; ++x)
        {
            img.SetPixel(x, y, 255, 0, 0);
        }
    }
    FloodFill(img, 1, 1, 0, 255, 0);

    // The red region is now green; the surrounding black is untouched.
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 0); REQUIRE(g == 0); REQUIRE(b == 0);
    img.GetPixel(2, 2, r, g, b);
    REQUIRE(r == 0); REQUIRE(g == 255); REQUIRE(b == 0);
}

TEST_CASE("FloodFill on a no-op colour returns without modification", "[ImageOps]")
{
    auto img = SolidImage(3, 3, 50, 50, 50);
    FloodFill(img, 1, 1, 50, 50, 50);
    REQUIRE(AllPixelsEqual(img, 50, 50, 50));
}

TEST_CASE("FloodFill on out-of-bounds seed is a no-op", "[ImageOps]")
{
    auto img = SolidImage(3, 3, 50, 50, 50);
    FloodFill(img, -1, 0, 200, 200, 200);
    REQUIRE(AllPixelsEqual(img, 50, 50, 50));
}

TEST_CASE("SprayCan paints only pixels inside the requested radius", "[ImageOps]")
{
    ImageData img(10, 10); // starts black
    SprayCan(img, 5, 5, 2, 20, 255, 255, 255);
    int painted = 0;
    int outsideBox = 0;
    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            unsigned char r, g, b;
            img.GetPixel(x, y, r, g, b);
            if (r == 255)
            {
                ++painted;
                // (x, y) must be in the 5x5 box centred at (5, 5).
                if (x < 3 || x > 7 || y < 3 || y > 7)
                {
                    ++outsideBox;
                }
            }
        }
    }
    REQUIRE(painted > 0);
    REQUIRE(outsideBox == 0);
}

TEST_CASE("FlipHorizontal mirrors columns", "[ImageOps]")
{
    ImageData img(2, 1);
    img.SetPixel(0, 0, 10, 0, 0);
    img.SetPixel(1, 0, 20, 0, 0);
    FlipHorizontal(img);
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 20);
    img.GetPixel(1, 0, r, g, b);
    REQUIRE(r == 10);
}

TEST_CASE("FlipVertical mirrors rows", "[ImageOps]")
{
    ImageData img(1, 2);
    img.SetPixel(0, 0, 10, 0, 0);
    img.SetPixel(0, 1, 20, 0, 0);
    FlipVertical(img);
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 20);
    img.GetPixel(0, 1, r, g, b);
    REQUIRE(r == 10);
}

TEST_CASE("Rotate90 swaps width and height", "[ImageOps]")
{
    // 2x3 source: pixel values are 1..6 reading row-major.
    ImageData img(2, 3);
    img.SetPixel(0, 0, 1, 0, 0);
    img.SetPixel(1, 0, 2, 0, 0);
    img.SetPixel(0, 1, 3, 0, 0);
    img.SetPixel(1, 1, 4, 0, 0);
    img.SetPixel(0, 2, 5, 0, 0);
    img.SetPixel(1, 2, 6, 0, 0);
    auto out = Rotate90(img, 1);
    REQUIRE(out.width == 3);
    REQUIRE(out.height == 2);
    unsigned char r, g, b;
    // After one clockwise 90-degree turn, source (x, y) ends up at
    // (height - 1 - y, x). The source pixel with value 1 was at (0, 0) in a
    // 2x3 image, so it lands at (2, 0) in the 3x2 destination.
    out.GetPixel(2, 0, r, g, b);
    REQUIRE(r == 1);
    // The source pixel with value 6 was at (1, 2) in the 2x3 image, so it
    // lands at (0, 1) in the 3x2 destination.
    out.GetPixel(0, 1, r, g, b);
    REQUIRE(r == 6);
}

TEST_CASE("Rotate90 four times is a no-op (modulo the copy)", "[ImageOps]")
{
    ImageData img(2, 2);
    img.SetPixel(0, 0, 1, 2, 3);
    img.SetPixel(1, 0, 4, 5, 6);
    img.SetPixel(0, 1, 7, 8, 9);
    img.SetPixel(1, 1, 10, 11, 12);
    auto out = Rotate90(img, 4);
    REQUIRE(out.width == img.width);
    REQUIRE(out.height == img.height);
    unsigned char r, g, b;
    img.GetPixel(0, 0, r, g, b);
    unsigned char r2, g2, b2;
    out.GetPixel(0, 0, r2, g2, b2);
    REQUIRE(r == r2);
    REQUIRE(g == g2);
    REQUIRE(b == b2);
}

TEST_CASE("RotateDeg with 0 degrees returns a copy of the input", "[ImageOps]")
{
    auto img = SolidImage(3, 3, 100, 100, 100);
    auto out = RotateDeg(img, 0.0);
    REQUIRE(out.width == img.width);
    REQUIRE(out.height == img.height);
    REQUIRE(AllPixelsEqual(out, 100, 100, 100));
}

TEST_CASE("Rescale resizes the image", "[ImageOps]")
{
    ImageData img(2, 2);
    img.SetPixel(0, 0, 200, 0, 0);
    auto out = Resize(img, 4, 4, 0, 0, 0, 0, 0);
    REQUIRE(out.width == 4);
    REQUIRE(out.height == 4);
    unsigned char r, g, b;
    out.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 200);
}

TEST_CASE("Rescale with the inline mutator changes the size", "[ImageOps]")
{
    ImageData img(4, 4);
    Rescale(img, 2, 2);
    REQUIRE(img.width == 2);
    REQUIRE(img.height == 2);
}

TEST_CASE("Resize fills the new area with the requested fill colour", "[ImageOps]")
{
    ImageData img(2, 2);
    img.SetPixel(0, 0, 200, 0, 0);
    img.SetPixel(1, 0, 200, 0, 0);
    img.SetPixel(0, 1, 200, 0, 0);
    img.SetPixel(1, 1, 200, 0, 0);
    auto out = Resize(img, 4, 4, 0, 0, 50, 50, 50);
    REQUIRE(out.width == 4);
    REQUIRE(out.height == 4);
    unsigned char r, g, b;
    out.GetPixel(3, 3, r, g, b);
    REQUIRE(r == 50);
    REQUIRE(g == 50);
    REQUIRE(b == 50);
    out.GetPixel(0, 0, r, g, b);
    REQUIRE(r == 200);
}
