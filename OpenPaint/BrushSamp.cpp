#include "BrushSamp.h"

#include <cstdlib>

void SampleLinePixels(int x0, int y0, int x1, int y1,
                      std::vector<IntPoint>& out)
{
    // Bresenham's line algorithm. Walks the integer pixels of the line
    // from (x0, y0) to (x1, y1) inclusive. Used by BrushTool to stamp
    // the brush tip at every pixel between consecutive mouse-move
    // events so a vertical-line or horizontal-line tip (which is only
    // 1px thick along the cursor's direction of travel) cannot leave
    // unpainted corridors between events. This function is the only
    // piece of brush-stamping logic that is wxDC-free, which lets it
    // be unit-tested without instantiating a real DC.
    int dx = std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;

    while (true)
    {
        IntPoint p;
        p.x = x0;
        p.y = y0;
        out.push_back(p);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy)
        {
            if (x0 == x1) break;
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            if (y0 == y1) break;
            err += dx;
            y0 += sy;
        }
    }
}

