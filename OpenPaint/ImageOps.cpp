/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, Steven Jedlicka
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "ImageOps.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stack>
#include <vector>

namespace openpaint {

namespace {

inline unsigned char ClampByte(int v)
{
    if (v < 0)   return 0;
    if (v > 255) return 255;
    return static_cast<unsigned char>(v);
}

inline bool PixelsEqual(const ImageData& img, int idx, unsigned char r,
                        unsigned char g, unsigned char b)
{
    if (idx < 0) return false;
    return img.pixels[static_cast<size_t>(idx)]     == r
        && img.pixels[static_cast<size_t>(idx) + 1] == g
        && img.pixels[static_cast<size_t>(idx) + 2] == b;
}

inline unsigned char Luma(unsigned char r, unsigned char g, unsigned char b)
{
    // BT.601 luma, matching wxImage::ConvertToGreyscale.
    return static_cast<unsigned char>((299 * r + 587 * g + 114 * b) / 1000);
}

} // namespace

void InvertColors(ImageData& img)
{
    if (!img.IsValid())
    {
        return;
    }
    for (size_t i = 0; i < img.pixels.size(); i += 3)
    {
        img.pixels[i]     = static_cast<unsigned char>(255 - img.pixels[i]);
        img.pixels[i + 1] = static_cast<unsigned char>(255 - img.pixels[i + 1]);
        img.pixels[i + 2] = static_cast<unsigned char>(255 - img.pixels[i + 2]);
    }
}

void Blur(ImageData& img, int radius)
{
    if (!img.IsValid())
    {
        return;
    }
    if (radius < 1) radius = 1;
    if (radius > 50) radius = 50;

    const int w = img.width;
    const int h = img.height;
    const int n = w * h;
    std::vector<unsigned char> out(img.pixels.size(), 0);

    // Pre-compute prefix sums per channel to make box blurs O(1) per pixel.
    // Each prefix sum array has (w+1) * (h+1) entries; indexing at (x, y) is
    // (y * (w+1) + x). We store sums of pixel values within the inclusive
    // rectangle (0, 0) to (x-1, y-1) so a 1x1 box hits exactly one pixel.
    const int stride = w + 1;
    std::vector<int> pR(static_cast<size_t>(stride) * (h + 1), 0);
    std::vector<int> pG(static_cast<size_t>(stride) * (h + 1), 0);
    std::vector<int> pB(static_cast<size_t>(stride) * (h + 1), 0);

    for (int y = 1; y <= h; ++y)
    {
        int rowSumR = 0, rowSumG = 0, rowSumB = 0;
        for (int x = 1; x <= w; ++x)
        {
            int src = ((y - 1) * w + (x - 1)) * 3;
            rowSumR += img.pixels[static_cast<size_t>(src)];
            rowSumG += img.pixels[static_cast<size_t>(src) + 1];
            rowSumB += img.pixels[static_cast<size_t>(src) + 2];
            pR[static_cast<size_t>(y) * stride + x] = pR[static_cast<size_t>(y - 1) * stride + x] + rowSumR;
            pG[static_cast<size_t>(y) * stride + x] = pG[static_cast<size_t>(y - 1) * stride + x] + rowSumG;
            pB[static_cast<size_t>(y) * stride + x] = pB[static_cast<size_t>(y - 1) * stride + x] + rowSumB;
        }
    }

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            int x0 = x - radius;     if (x0 < 0)     x0 = 0;
            int y0 = y - radius;     if (y0 < 0)     y0 = 0;
            int x1 = x + radius + 1; if (x1 > w)     x1 = w;
            int y1 = y + radius + 1; if (y1 > h)     y1 = h;
            int count = (x1 - x0) * (y1 - y0);
            auto sum = [&](const std::vector<int>& p) {
                int a = p[static_cast<size_t>(y1) * stride + x1];
                int b = p[static_cast<size_t>(y0) * stride + x1];
                int c = p[static_cast<size_t>(y1) * stride + x0];
                int d = p[static_cast<size_t>(y0) * stride + x0];
                return a - b - c + d;
            };
            int sR = sum(pR);
            int sG = sum(pG);
            int sB = sum(pB);
            int dst = (y * w + x) * 3;
            out[static_cast<size_t>(dst)]     = ClampByte(sR / count);
            out[static_cast<size_t>(dst) + 1] = ClampByte(sG / count);
            out[static_cast<size_t>(dst) + 2] = ClampByte(sB / count);
        }
    }

    img.pixels = std::move(out);
    (void)n;
}

void Pixelize(ImageData& img, int block)
{
    if (!img.IsValid())
    {
        return;
    }
    if (block < 1) block = 1;
    if (block > 256) block = 256;

    const int w = img.width;
    const int h = img.height;
    for (int by = 0; by < h; by += block)
    {
        for (int bx = 0; bx < w; bx += block)
        {
            int xMax = std::min(bx + block, w);
            int yMax = std::min(by + block, h);
            long r = 0, g = 0, b = 0;
            int count = 0;
            for (int y = by; y < yMax; ++y)
            {
                for (int x = bx; x < xMax; ++x)
                {
                    int src = (y * w + x) * 3;
                    r += img.pixels[static_cast<size_t>(src)];
                    g += img.pixels[static_cast<size_t>(src) + 1];
                    b += img.pixels[static_cast<size_t>(src) + 2];
                    ++count;
                }
            }
            unsigned char rr = static_cast<unsigned char>(r / count);
            unsigned char gg = static_cast<unsigned char>(g / count);
            unsigned char bb = static_cast<unsigned char>(b / count);
            for (int y = by; y < yMax; ++y)
            {
                for (int x = bx; x < xMax; ++x)
                {
                    int dst = (y * w + x) * 3;
                    img.pixels[static_cast<size_t>(dst)]     = rr;
                    img.pixels[static_cast<size_t>(dst) + 1] = gg;
                    img.pixels[static_cast<size_t>(dst) + 2] = bb;
                }
            }
        }
    }
}

void Greyscale(ImageData& img)
{
    if (!img.IsValid())
    {
        return;
    }
    for (size_t i = 0; i < img.pixels.size(); i += 3)
    {
        unsigned char l = Luma(img.pixels[i], img.pixels[i + 1], img.pixels[i + 2]);
        img.pixels[i]     = l;
        img.pixels[i + 1] = l;
        img.pixels[i + 2] = l;
    }
}

void Monochrome(ImageData& img)
{
    if (!img.IsValid())
    {
        return;
    }
    for (size_t i = 0; i < img.pixels.size(); i += 3)
    {
        unsigned char l = Luma(img.pixels[i], img.pixels[i + 1], img.pixels[i + 2]);
        unsigned char v = (l > 128) ? 255 : 0;
        img.pixels[i]     = v;
        img.pixels[i + 1] = v;
        img.pixels[i + 2] = v;
    }
}

void FloodFill(ImageData& img, int startX, int startY,
               unsigned char newR, unsigned char newG, unsigned char newB)
{
    if (!img.IsValid())
    {
        return;
    }
    if (startX < 0 || startY < 0 || startX >= img.width || startY >= img.height)
    {
        return;
    }
    int startIdx = img.Index(startX, startY);
    if (startIdx < 0)
    {
        return;
    }
    unsigned char oldR = img.pixels[static_cast<size_t>(startIdx)];
    unsigned char oldG = img.pixels[static_cast<size_t>(startIdx) + 1];
    unsigned char oldB = img.pixels[static_cast<size_t>(startIdx) + 2];
    if (oldR == newR && oldG == newG && oldB == newB)
    {
        return;
    }

    // Iterative 4-connected flood fill using an explicit stack of pixels.
    // The previous recursive implementation was both broken (only one
    // direction recursed) and unsafe (deep recursion could blow the OS
    // stack on large connected regions).
    std::vector<std::pair<int, int>> stack;
    stack.reserve(img.pixels.size() / 3);
    stack.emplace_back(startX, startY);
    while (!stack.empty())
    {
        auto [x, y] = stack.back();
        stack.pop_back();
        if (x < 0 || y < 0 || x >= img.width || y >= img.height)
        {
            continue;
        }
        int idx = img.Index(x, y);
        if (!PixelsEqual(img, idx, oldR, oldG, oldB))
        {
            continue;
        }
        img.pixels[static_cast<size_t>(idx)]     = newR;
        img.pixels[static_cast<size_t>(idx) + 1] = newG;
        img.pixels[static_cast<size_t>(idx) + 2] = newB;
        stack.emplace_back(x + 1, y);
        stack.emplace_back(x - 1, y);
        stack.emplace_back(x, y + 1);
        stack.emplace_back(x, y - 1);
    }
}

void SprayCan(ImageData& img, int cx, int cy, int radius, int count,
              unsigned char r, unsigned char g, unsigned char b)
{
    if (!img.IsValid() || count <= 0)
    {
        return;
    }
    if (radius < 0) radius = 0;
    const int w = img.width;
    const int h = img.height;
    for (int i = 0; i < count; ++i)
    {
        // Use a simple deterministic hash of i so the result is reproducible
        // and doesn't depend on the global rand() state.
        unsigned int h1 = static_cast<unsigned int>(i) * 2654435761u;
        int dx = static_cast<int>(h1 % (2u * static_cast<unsigned int>(radius) + 1u))
                 - radius;
        unsigned int h2 = (h1 ^ (h1 >> 13)) * 1597334677u;
        int dy = static_cast<int>(h2 % (2u * static_cast<unsigned int>(radius) + 1u))
                 - radius;
        int x = cx + dx;
        int y = cy + dy;
        if (x < 0 || y < 0 || x >= w || y >= h)
        {
            continue;
        }
        int idx = img.Index(x, y);
        img.pixels[static_cast<size_t>(idx)]     = r;
        img.pixels[static_cast<size_t>(idx) + 1] = g;
        img.pixels[static_cast<size_t>(idx) + 2] = b;
    }
}

void FlipHorizontal(ImageData& img)
{
    if (!img.IsValid())
    {
        return;
    }
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width / 2; ++x)
        {
            int xi = (y * img.width + x) * 3;
            int xj = (y * img.width + (img.width - 1 - x)) * 3;
            for (int c = 0; c < 3; ++c)
            {
                std::swap(img.pixels[static_cast<size_t>(xi) + c],
                          img.pixels[static_cast<size_t>(xj) + c]);
            }
        }
    }
}

void FlipVertical(ImageData& img)
{
    if (!img.IsValid())
    {
        return;
    }
    const int rowBytes = img.width * 3;
    std::vector<unsigned char> tmp(static_cast<size_t>(rowBytes));
    for (int y = 0; y < img.height / 2; ++y)
    {
        unsigned char* top = img.pixels.data() + static_cast<size_t>(y) * rowBytes;
        unsigned char* bot = img.pixels.data()
                           + static_cast<size_t>(img.height - 1 - y) * rowBytes;
        std::copy(top, top + rowBytes, tmp.begin());
        std::copy(bot, bot + rowBytes, top);
        std::copy(tmp.begin(), tmp.end(), bot);
    }
}

ImageData Rotate90(const ImageData& img, int n)
{
    ImageData out;
    if (!img.IsValid())
    {
        return out;
    }
    int steps = ((n % 4) + 4) % 4;
    if (steps == 0)
    {
        return img;
    }
    const int w = img.width;
    const int h = img.height;
    int curW = w, curH = h;
    const ImageData* cur = &img;
    ImageData tmp;
    for (int s = 0; s < steps; ++s)
    {
        tmp = ImageData(curH, curW);
        for (int y = 0; y < curH; ++y)
        {
            for (int x = 0; x < curW; ++x)
            {
                int src = (y * curW + x) * 3;
                int dst = (x * curH + (curH - 1 - y)) * 3;
                tmp.pixels[static_cast<size_t>(dst)]     = cur->pixels[static_cast<size_t>(src)];
                tmp.pixels[static_cast<size_t>(dst) + 1] = cur->pixels[static_cast<size_t>(src) + 1];
                tmp.pixels[static_cast<size_t>(dst) + 2] = cur->pixels[static_cast<size_t>(src) + 2];
            }
        }
        std::swap(curW, curH);
        cur = &tmp;
        if (s + 1 < steps)
        {
            tmp = ImageData(curH, curW);
        }
    }
    return tmp;
}

ImageData RotateDeg(const ImageData& img, double angleDegrees,
                    unsigned char fillR, unsigned char fillG, unsigned char fillB)
{
    ImageData out;
    if (!img.IsValid())
    {
        return out;
    }
    out = ImageData(img.width, img.height);
    std::fill(out.pixels.begin(), out.pixels.end(), 0);
    // Fill with the requested colour.
    for (int y = 0; y < out.height; ++y)
    {
        for (int x = 0; x < out.width; ++x)
        {
            out.SetPixel(x, y, fillR, fillG, fillB);
        }
    }
    if (angleDegrees == 0.0)
    {
        return img;
    }
    double rad = angleDegrees * 3.14159265358979323846 / 180.0;
    double cs = std::cos(rad);
    double sn = std::sin(rad);
    double cx0 = (img.width  - 1) / 2.0;
    double cy0 = (img.height - 1) / 2.0;
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            double dx = x - cx0;
            double dy = y - cy0;
            double sx =  cs * dx + sn * dy + cx0;
            double sy = -sn * dx + cs * dy + cy0;
            int sxi = static_cast<int>(std::lround(sx));
            int syi = static_cast<int>(std::lround(sy));
            if (sxi < 0 || syi < 0 || sxi >= img.width || syi >= img.height)
            {
                continue;
            }
            int src = (syi * img.width + sxi) * 3;
            int dst = (y * img.width + x) * 3;
            out.pixels[static_cast<size_t>(dst)]     = img.pixels[static_cast<size_t>(src)];
            out.pixels[static_cast<size_t>(dst) + 1] = img.pixels[static_cast<size_t>(src) + 1];
            out.pixels[static_cast<size_t>(dst) + 2] = img.pixels[static_cast<size_t>(src) + 2];
        }
    }
    return out;
}

void Rescale(ImageData& img, int newWidth, int newHeight)
{
    if (!img.IsValid() || newWidth <= 0 || newHeight <= 0)
    {
        return;
    }
    ImageData out(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y)
    {
        int srcY = (y * img.height) / newHeight;
        for (int x = 0; x < newWidth; ++x)
        {
            int srcX = (x * img.width) / newWidth;
            int src = (srcY * img.width + srcX) * 3;
            int dst = (y * newWidth + x) * 3;
            out.pixels[static_cast<size_t>(dst)]     = img.pixels[static_cast<size_t>(src)];
            out.pixels[static_cast<size_t>(dst) + 1] = img.pixels[static_cast<size_t>(src) + 1];
            out.pixels[static_cast<size_t>(dst) + 2] = img.pixels[static_cast<size_t>(src) + 2];
        }
    }
    img = std::move(out);
}

ImageData Resize(const ImageData& src, int newWidth, int newHeight,
                 int offsetX, int offsetY,
                 unsigned char fillR, unsigned char fillG, unsigned char fillB)
{
    ImageData out(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y)
    {
        for (int x = 0; x < newWidth; ++x)
        {
            out.SetPixel(x, y, fillR, fillG, fillB);
        }
    }
    if (!src.IsValid())
    {
        return out;
    }
    for (int y = 0; y < src.height; ++y)
    {
        int dy = y + offsetY;
        if (dy < 0 || dy >= newHeight)
        {
            continue;
        }
        for (int x = 0; x < src.width; ++x)
        {
            int dx = x + offsetX;
            if (dx < 0 || dx >= newWidth)
            {
                continue;
            }
            int s = (y * src.width + x) * 3;
            int d = (dy * newWidth + dx) * 3;
            out.pixels[static_cast<size_t>(d)]     = src.pixels[static_cast<size_t>(s)];
            out.pixels[static_cast<size_t>(d) + 1] = src.pixels[static_cast<size_t>(s) + 1];
            out.pixels[static_cast<size_t>(d) + 2] = src.pixels[static_cast<size_t>(s) + 2];
        }
    }
    return out;
}

} // namespace openpaint
