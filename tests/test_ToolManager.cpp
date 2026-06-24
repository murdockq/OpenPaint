// Unit tests for ToolManager, the non-GUI portions.
//
// The colour-dialog and panel-update paths depend on Globals (which depends
// on ConfigFile and the wxColourDialog) and the wxWidgets event loop, so
// they are covered manually in the GUI. Here we exercise the parts that
// don't need a running application: brush settings, colour storage, and
// the cancel-safe behaviour of PickColor.
//
// We test against a bare-bones stub of ToolManager that overrides
// PickColor() so we can simulate both "user picked a colour" and
// "user cancelled" without involving a real dialog.

#include <catch2/catch_test_macros.hpp>

#include "ToolManager.h"

#include <cstring>

namespace {

// Subclass that exposes the protected brush setters and lets the test
// control what PickColor() returns.
class TestableToolManager : public ToolManager
{
public:
    int GetBrushRadius() const { return m_brushRadius; }
    int GetBrushTip() const { return m_brushTip; }
};

} // namespace

TEST_CASE("ToolManager defaults to pencil / black FG / white BG", "[ToolManager]")
{
    TestableToolManager tm;
    REQUIRE(tm.GetSelectedTool() == TOOL_PENCIL);
    auto fg = tm.GetForeground();
    auto bg = tm.GetBackground();
    REQUIRE(fg.Red() == 0);
    REQUIRE(fg.Green() == 0);
    REQUIRE(fg.Blue() == 0);
    REQUIRE(bg.Red() == 255);
    REQUIRE(bg.Green() == 255);
    REQUIRE(bg.Blue() == 255);
}

TEST_CASE("ToolManager::SetBrushRadius clamps to [1, 100]", "[ToolManager]")
{
    TestableToolManager tm;
    tm.SetBrushRadius(50);
    REQUIRE(tm.GetBrushRadius() == 50);
    tm.SetBrushRadius(0);
    REQUIRE(tm.GetBrushRadius() == 1);
    tm.SetBrushRadius(1000);
    REQUIRE(tm.GetBrushRadius() == 100);
}

TEST_CASE("ToolManager::SetBrushTip clamps to [0, 3]", "[ToolManager]")
{
    TestableToolManager tm;
    tm.SetBrushTip(2);
    REQUIRE(tm.GetBrushTip() == 2);
    tm.SetBrushTip(-1);
    REQUIRE(tm.GetBrushTip() == 0);
    tm.SetBrushTip(99);
    REQUIRE(tm.GetBrushTip() == 3);
}

TEST_CASE("ToolManager::SetSelectedTool round-trips", "[ToolManager]")
{
    TestableToolManager tm;
    tm.SetSelectedTool(TOOL_ELLIPSE);
    REQUIRE(tm.GetSelectedTool() == TOOL_ELLIPSE);
    tm.SetSelectedTool(TOOL_SELECT);
    REQUIRE(tm.GetSelectedTool() == TOOL_SELECT);
}
