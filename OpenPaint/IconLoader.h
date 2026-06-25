#ifndef __OPENPAINT_ICON_LOADER__
#define __OPENPAINT_ICON_LOADER__

#include <wx/bitmap.h>
#include <wx/gdicmn.h>
#include <wx/string.h>

/**
 * @file
 * Loads UI icons by logical name (e.g. "draw-brush", "color-fill", "linked").
 *
 * Resolution order:
 *   1. SVG from res/svg/<name>.svg  (used when wxWidgets is built with
 *      wxUSE_SVG=1, otherwise the call returns an empty bitmap and the
 *      loader falls through).
 *   2. XPM from res/<name>.xpm      (cross-platform raster fallback that
 *      still resolves on every existing build).
 *   3. The legacy wxICON() resource as a last resort, so a name that
 *      hasn't been ported to an SVG or XPM still renders.
 *
 * The returned wxBitmap is sized to @a size. The toolbar passes the size
 * it set with SetToolBitmapSize, menus pass 16x16, etc.
 */
class IconLoader
{
public:
    static wxBitmap Load(const wxString& name, const wxSize& size);

    // The toolbar's preferred logical tool size, in pixels. 24x24 is the
    // modern flat-icon size; callers can still pass any other size to Load.
    static wxSize LogicalToolbarSize();
};

#endif // __OPENPAINT_ICON_LOADER__

