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
 */

#include "IconLoader.h"
#include "IconPaths.h"

#include <wx/bmpbndl.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/log.h>

namespace {

wxBitmap LoadSvg(const wxString& path, const wxSize& size)
{
#if wxUSE_SVG
    if (!wxFileName::FileExists(path))
    {
        return wxBitmap();
    }
    wxBitmapBundle bundle = wxBitmapBundle::FromSVGFile(path, size);
    if (!bundle.IsOk())
    {
        return wxBitmap();
    }
    wxBitmap bmp = bundle.GetBitmap(size);
    if (!bmp.IsOk())
    {
        bmp = bundle.GetBitmap(wxDefaultSize);
    }
    return bmp;
#else
    (void)path;
    (void)size;
    return wxBitmap();
#endif
}

wxBitmap LoadXpm(const wxString& path)
{
    if (!wxFileName::FileExists(path))
    {
        return wxBitmap();
    }
    wxImage image;
    if (!image.LoadFile(path, wxBITMAP_TYPE_XPM))
    {
        return wxBitmap();
    }
    return wxBitmap(image);
}

} // namespace

wxBitmap IconLoader::Load(const wxString& name, const wxSize& size)
{
    if (name.IsEmpty())
    {
        return wxBitmap();
    }

    const wxString svgPath = wxString::FromUTF8(OPENPAINT_SVG_DIR) +
                             wxFILE_SEP_PATH + name + wxT(".svg");
    wxBitmap svg = LoadSvg(svgPath, size);
    if (svg.IsOk())
    {
        return svg;
    }

    const wxString xpmPath = wxString::FromUTF8(OPENPAINT_XPM_DIR) +
                             wxFILE_SEP_PATH + name + wxT(".xpm");
    wxBitmap xpm = LoadXpm(xpmPath);
    if (xpm.IsOk())
    {
        return xpm;
    }

    wxLogWarning(wxT("IconLoader: no source for icon '%s'"), name);
    return wxBitmap();
}

wxSize IconLoader::LogicalToolbarSize()
{
    return wxSize(24, 24);
}
