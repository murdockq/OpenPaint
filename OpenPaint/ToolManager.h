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

#ifndef __ToolManager__
#define __ToolManager__

#include "Globals.h"

#include <wx/colour.h>

enum ToolType
{
    TOOL_PICK_COLOR,
    TOOL_PENCIL,
    TOOL_BRUSH,
    TOOL_FILL,
    TOOL_ERASER,
    TOOL_MAGNIFY,
    TOOL_SPRAY_CAN,
    TOOL_RECTANGLE,
    TOOL_POLYLINE,
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

    public:
        ToolManager();
        virtual ~ToolManager();
        void Shutdown();

        //Tools
        ToolType GetSelectedTool();
        void SetSelectedTool(ToolType selectedTool);

        //Colors
        wxColour GetForeground();
        void SetForeground(wxColour foregroundColor);
        wxColour GetBackground();
        void SetBackground(wxColour backgroundColor);
        wxColour PickColor();
};


#endif
