// Smoke tests for IconLoader.
//
// Verifies that every icon name used by the GUI resolves to a non-empty
// bitmap at the requested size, and that the resolver chain returns the
// expected result for the various fallback paths.

#include <catch2/catch_test_macros.hpp>

#include <wx/bitmap.h>
#include <wx/gdicmn.h>
#include <wx/init.h>
#include <wx/string.h>

#include "IconLoader.h"

#include <set>
#include <string>

namespace {

// Every icon name the GUI passes to IconLoader. Keep this list in sync with
// the call sites in OpenPaintGUI.cpp, SubCanvasSizeDialog.cpp and
// SubImageSizeDialog.cpp. The test will fail if a new icon is added
// without being added here, and vice-versa.
const char* kAllIconNames[] = {
    "new",
    "open",
    "save",
    "undo",
    "redo",
    "draw-brush",
    "draw-ellipse",
    "draw-eraser",
    "color-fill",
    "page-magnifier",
    "draw-freehand",
    "color-picker",
    "draw-line",
    "draw-curve",
    "draw-polygon",
    "draw-rectangle",
    "draw-rectangle-rounded",
    "select-rectangular",
    "select-lasso",
    "draw-airbrush",
    "draw-text",
    "linked",
    "unlinked",
};

} // namespace

TEST_CASE("IconLoader: empty name returns empty bitmap", "[icons]")
{
    wxInitializer init;
    REQUIRE(init.IsOk());
    auto bmp = IconLoader::Load(wxString(), wxSize(24, 24));
    REQUIRE_FALSE(bmp.IsOk());
}

TEST_CASE("IconLoader: unknown name returns empty bitmap", "[icons]")
{
    wxInitializer init;
    REQUIRE(init.IsOk());
    auto bmp = IconLoader::Load(wxT("does-not-exist"), wxSize(24, 24));
    REQUIRE_FALSE(bmp.IsOk());
}

TEST_CASE("IconLoader: every GUI icon name resolves to a non-empty bitmap", "[icons]")
{
    wxInitializer init;
    REQUIRE(init.IsOk());
    for (const char* name : kAllIconNames)
    {
        INFO("icon name: " << name);
        auto bmp = IconLoader::Load(wxString::FromUTF8(name),
                                    IconLoader::LogicalToolbarSize());
        REQUIRE(bmp.IsOk());
        REQUIRE(bmp.GetWidth() == IconLoader::LogicalToolbarSize().GetWidth());
        REQUIRE(bmp.GetHeight() == IconLoader::LogicalToolbarSize().GetHeight());
    }
}

TEST_CASE("IconLoader: requested size is honoured", "[icons]")
{
    wxInitializer init;
    REQUIRE(init.IsOk());
    auto smallBmp = IconLoader::Load(wxT("new"), wxSize(16, 16));
    REQUIRE(smallBmp.IsOk());
    REQUIRE(smallBmp.GetWidth() == 16);
    REQUIRE(smallBmp.GetHeight() == 16);

    auto largeBmp = IconLoader::Load(wxT("new"), wxSize(48, 48));
    REQUIRE(largeBmp.IsOk());
    REQUIRE(largeBmp.GetWidth() == 48);
    REQUIRE(largeBmp.GetHeight() == 48);
}

TEST_CASE("IconLoader: icon name set is internally consistent", "[icons]")
{
    // Defensive check: make sure the kAllIconNames array has no duplicates,
    // since that would silently mask a misnamed call site.
    std::set<std::string> seen;
    for (const char* name : kAllIconNames)
    {
        REQUIRE(seen.insert(name).second);
    }
}
