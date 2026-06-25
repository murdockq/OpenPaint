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

#ifndef __ToolManager__
#define __ToolManager__

#include "Globals.h"

#include <wx/colour.h>
#include <wx/gdicmn.h>

enum ToolType
{
    TOOL_PICK_COLOR,
    TOOL_PENCIL,
    TOOL_BRUSH,
    TOOL_FILL,
    TOOL_ERASER,
    TOOL_MAGNIFY,
    TOOL_SPRAY_CAN,
    TOOL_LINE,
    TOOL_CURVE,
    TOOL_RECTANGLE,
    TOOL_POLYLINE,
    TOOL_POLYGON,
    TOOL_ELLIPSE,
    TOOL_RECTANGLE_ROUNDED,
    TOOL_SELECT_LASSO,
    TOOL_SELECT,
    TOOL_TEXT
};

class ToolManager
{
    private:

    protected:
        ToolType m_eSelectedTool;
        wxColour m_colorForeground;
        wxColour m_colorBackground;

        // Brush settings driven by the BrushToolPanel UI; BrushTool reads the
        // radius at draw time so the spinner/tip combobox actually affect
        // rendering.
        int m_brushRadius;
        int m_brushTip; // 0 = round, 1 = square, 2 = vertical line, 3 = horizontal line

        // Per-tool sizes / settings that the corresponding *ToolPanel UI
        // controls drive. Each tool reads its own field at draw time so
        // the spinner/checkbox values actually affect rendering.
        int m_pencilSize;
        int m_eraserSize;
        int m_sprayCanSize;
        int m_shapeLineWidth;
        bool m_bShapesFilled;

        // Text-tool font settings: face name, point size, style flags and an
        // underline toggle. The TextTool panel populates these and
        // TextTool() applies them when drawing the entered text.
        wxString m_textFontFace;
        int m_textFontSize;
        bool m_textFontBold;
        bool m_textFontItalic;
        bool m_textFontUnderline;

    public:
        ToolManager();
        virtual ~ToolManager();
        void Shutdown();

        //Tools
        ToolType GetSelectedTool();
        void SetSelectedTool(ToolType selectedTool);
        wxStockCursor GetSelectedToolCursor() const;
        static wxStockCursor GetToolCursor(ToolType tool);

        //Colors
        wxColour GetForeground();
        void SetForeground(wxColour foregroundColor);
        wxColour GetBackground();
        void SetBackground(wxColour backgroundColor);
        wxColour PickColor(const wxColour& initialColor = wxColour());

        // Brush settings
        int GetBrushRadius() const { return m_brushRadius; }
        void SetBrushRadius(int radius);
        int GetBrushTip() const { return m_brushTip; }
        void SetBrushTip(int tip);

        // Per-tool size / settings
        int GetPencilSize() const { return m_pencilSize; }
        void SetPencilSize(int size);
        int GetEraserSize() const { return m_eraserSize; }
        void SetEraserSize(int size);
        int GetSprayCanSize() const { return m_sprayCanSize; }
        void SetSprayCanSize(int size);
        int GetShapeLineWidth() const { return m_shapeLineWidth; }
        void SetShapeLineWidth(int width);
        bool GetShapesFilled() const { return m_bShapesFilled; }
        void SetShapesFilled(bool filled) { m_bShapesFilled = filled; }

        // Text-tool font settings
        wxString GetTextFontFace() const { return m_textFontFace; }
        void SetTextFontFace(const wxString& face) { m_textFontFace = face; }
        int GetTextFontSize() const { return m_textFontSize; }
        void SetTextFontSize(int size);
        bool GetTextFontBold() const { return m_textFontBold; }
        void SetTextFontBold(bool bold) { m_textFontBold = bold; }
        bool GetTextFontItalic() const { return m_textFontItalic; }
        void SetTextFontItalic(bool italic) { m_textFontItalic = italic; }
        bool GetTextFontUnderline() const { return m_textFontUnderline; }
        void SetTextFontUnderline(bool ul) { m_textFontUnderline = ul; }
};


#endif
