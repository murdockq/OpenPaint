/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, OpenPaint
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

#ifndef __OpenPaintBrushSamp__
#define __OpenPaintBrushSamp__

#include <utility>
#include <vector>

class wxDC;

// A single integer pixel on the brush's stamping path. Uses std::pair
// instead of wxPoint so this header is wxWidgets-free: the pure
// sampler is compiled into the openpaint_core library which has no
// wx dependency. The wx-side stamping code in BrushTip.cpp converts
// between IntPoint and wxPoint at the boundary.
struct IntPoint
{
    int x;
    int y;
};

inline bool operator==(const IntPoint& a, const IntPoint& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const IntPoint& a, const IntPoint& b)
{
    return !(a == b);
}

// Fills `out` with every integer pixel on the Bresenham line from
// (x0, y0) to (x1, y1), inclusive of both endpoints. A zero-length
// segment emits the single point (x1, y1). Used by BrushTool to ensure
// the brush tip is stamped at every integer pixel between consecutive
// mouse-move events so the resulting line has no gaps regardless of
// which brush tip shape is selected. The function is pure (no wxDC
// dependency) so it can be unit-tested without a real DC.
void SampleLinePixels(int x0, int y0, int x1, int y1,
                      std::vector<IntPoint>& out);

// Renders a single brush stamp at (x, y) using the chosen tip shape:
//   0 = round:           filled circle of diameter 2*radius
//   1 = square:          filled square of side  2*radius
//   2 = vertical line:   1px-wide vertical line of height 2*radius
//   3 = horizontal line: 1px-wide horizontal line of width  2*radius
// The caller is responsible for setting the pen/brush colour on `dc`
// and for clamping `radius` to a sane non-negative value. Lives in a
// free function (not a method) so the per-tip stamping can be unit
// tested against a wxMemoryDC without instantiating a full MDI frame.
void StampBrushTip(wxDC& dc, int x, int y, int radius, int tip);

// Stamps the brush tip at every integer pixel on the line from
// (x0, y0) to (x1, y1). Used by BrushTool to close the gap between
// consecutive mouse-move events for every tip shape, including the
// 1px-thick vertical/horizontal line tips which would otherwise leave
// an unpainted corridor between two events that are more than 1 pixel
// apart in the perpendicular direction.
void StampBrushAlongLine(wxDC& dc, int x0, int y0, int x1, int y1,
                         int radius, int tip);

#endif // __OpenPaintBrushSamp__
