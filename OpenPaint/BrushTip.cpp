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

