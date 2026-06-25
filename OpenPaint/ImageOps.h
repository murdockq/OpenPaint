#ifndef OPENPAINT_IMAGEOPS_H
#define OPENPAINT_IMAGEOPS_H

#include <cstdint>
#include <vector>

namespace openpaint {

// Minimal, dependency-free image descriptor used for testing image operations
// in isolation. The GUI layer bridges between this and wxImage. The buffer
// is laid out as 3 bytes per pixel (R, G, B) in row-major order, which is
// the format returned by wxImage::GetData() and consumed by wxImage::SetData().
struct ImageData
{
    int width  = 0;
    int height = 0;
    std::vector<unsigned char> pixels; // size = width * height * 3

    ImageData() = default;
    ImageData(int w, int h) : width(w), height(h), pixels(static_cast<size_t>(w) * h * 3, 0) {}

    bool IsValid() const
    {
        return width > 0 && height > 0
               && pixels.size() == static_cast<size_t>(width) * height * 3u;
    }

    // Return the index of pixel (x, y) in pixels[]. Returns -1 if out of
    // bounds; the GUI layer should bounds-check before calling.
    int Index(int x, int y) const
    {
        if (x < 0 || y < 0 || x >= width || y >= height)
        {
            return -1;
        }
        return (y * width + x) * 3;
    }

    void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    {
        int idx = Index(x, y);
        if (idx < 0)
        {
            return;
        }
        pixels[idx]     = r;
        pixels[idx + 1] = g;
        pixels[idx + 2] = b;
    }

    void GetPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b) const
    {
        int idx = Index(x, y);
        if (idx < 0)
        {
            r = g = b = 0;
            return;
        }
        r = pixels[idx];
        g = pixels[idx + 1];
        b = pixels[idx + 2];
    }
};

// Invert RGB channels of every pixel. Alpha (if any) is not affected.
void InvertColors(ImageData& img);

// Box-blur radius N. Radius is clamped to [1, 50].
void Blur(ImageData& img, int radius);

// Pixelize: each block×block region is replaced by the average colour of
// the pixels it contains. Block size is clamped to [1, 256].
void Pixelize(ImageData& img, int block);

// Convert each pixel to luminance using the standard ITU-R BT.601 weights.
void Greyscale(ImageData& img);

// Convert to a 1-bit black/white image by thresholding luminance at 128.
void Monochrome(ImageData& img);

// Stack-based 4-connected flood fill. Replaces every pixel of the same
// colour as (startX, startY) with the new colour. Uses an explicit
// std::vector as the work stack so we don't blow the OS stack on large
// regions. Bounds-checked.
void FloodFill(ImageData& img, int startX, int startY,
               unsigned char newR, unsigned char newG, unsigned char newB);

// Spray paint: scatter `count` droplets of `r, g, b` inside a `radius`-pixel
// square centred at (cx, cy). Coordinates are clamped to the image buffer.
void SprayCan(ImageData& img, int cx, int cy, int radius, int count,
              unsigned char r, unsigned char g, unsigned char b);

// Mirror horizontally (left <-> right). In place.
void FlipHorizontal(ImageData& img);

// Mirror vertically (top <-> bottom). In place.
void FlipVertical(ImageData& img);

// Rotate 90 degrees clockwise `n` times (n in 0..3). Returns a new image
// (the original is left untouched). For arbitrary angles use RotateDeg.
ImageData Rotate90(const ImageData& img, int n = 1);

// Rotate by an arbitrary angle in degrees around the image centre.
// Returns a new image of the same size; pixels outside the source bounds
// are filled with `fillR, fillG, fillB` (default: black).
ImageData RotateDeg(const ImageData& img, double angleDegrees,
                    unsigned char fillR = 0, unsigned char fillG = 0,
                    unsigned char fillB = 0);

// Nearest-neighbour scale to (newWidth, newHeight).
void Rescale(ImageData& img, int newWidth, int newHeight);

// Create a new image with the given size, copying the source into the
// rectangle (offsetX, offsetY)..(offsetX+srcW, offsetY+srcH). Pixels
// outside the source are filled with `fillR, fillG, fillB`.
ImageData Resize(const ImageData& src, int newWidth, int newHeight,
                 int offsetX, int offsetY,
                 unsigned char fillR = 255, unsigned char fillG = 255,
                 unsigned char fillB = 255);

} // namespace openpaint

#endif // OPENPAINT_IMAGEOPS_H

