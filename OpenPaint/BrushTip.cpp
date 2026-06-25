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

#include "BrushSamp.h"

#include <wx/dc.h>
#include <wx/gdicmn.h>

void StampBrushTip(wxDC& dc, int x, int y, int radius, int tip)
{
    dc.SetPen(*wxTRANSPARENT_PEN);
    switch (tip)
    {
    case 1:
        dc.DrawRectangle(x - radius, y - radius, radius * 2, radius * 2);
        break;
    case 2:
        dc.DrawRectangle(x, y - radius, 1, radius * 2);
        break;
    case 3:
        dc.DrawRectangle(x - radius, y, radius * 2, 1);
        break;
    case 0:
    default:
        dc.DrawCircle(x, y, radius);
        break;
    }
}

void StampBrushAlongLine(wxDC& dc, int x0, int y0, int x1, int y1,
                         int radius, int tip)
{
    std::vector<IntPoint> samples;
    SampleLinePixels(x0, y0, x1, y1, samples);
    for (size_t i = 0; i < samples.size(); ++i)
    {
        StampBrushTip(dc, samples[i].x, samples[i].y, radius, tip);
    }
}
