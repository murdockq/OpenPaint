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

#include "ToolManager.h"
#include "Globals.h"
#include "SubColorPanel.h"

#include <wx/colordlg.h>


ToolManager::ToolManager()
{
    SetSelectedTool(TOOL_PENCIL);
    m_colorForeground = wxColour( 0, 0, 0 );
    m_colorBackground = wxColour( 255, 255, 255 );
    m_brushRadius = 10;
    m_brushTip = 0; // round
}

ToolManager::~ToolManager()
{

}


void ToolManager::Shutdown()
{

}

void ToolManager::SetBrushRadius(int radius)
{
    if (radius < 1) radius = 1;
    if (radius > 100) radius = 100;
    m_brushRadius = radius;
}

void ToolManager::SetBrushTip(int tip)
{
    if (tip < 0) tip = 0;
    if (tip > 3) tip = 3;
    m_brushTip = tip;
}

ToolType ToolManager::GetSelectedTool()
{
    return m_eSelectedTool;
}

void ToolManager::SetSelectedTool(ToolType selectedTool)
{
    m_eSelectedTool = selectedTool;
}

wxColour ToolManager::GetForeground()
{
    return m_colorForeground;
}

void ToolManager::SetForeground(wxColour foregroundColor)
{
    m_colorForeground = foregroundColor;
    if (SubColorPanel* p = Globals::Instance()->GetColorPanel())
    {
        p->UpdateColors();
    }
}

wxColour ToolManager::GetBackground()
{
    return m_colorBackground;
}

void ToolManager::SetBackground(wxColour backgroundColor)
{
    m_colorBackground = backgroundColor;
    if (SubColorPanel* p = Globals::Instance()->GetColorPanel())
    {
        p->UpdateColors();
    }
}


wxColour ToolManager::PickColor()
{
    // Default to the current foreground so cancelling the dialog is a no-op
    // rather than clobbering the colour with an invalid wxColour.
    wxColour returnColor = m_colorForeground;
    wxColourData data;
    data.SetChooseFull(true);
    for (int i = 0; i < 16; i++)
    {
        wxColour colour(i*16, i*16, i*16);
        data.SetCustomColour(i, colour);
    }

    wxColourDialog dialog((wxWindow *)Globals::Instance()->GetMainFrame(), &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxColourData retData = dialog.GetColourData();
        returnColor = retData.GetColour();
        wxLogDebug(returnColor.GetAsString(wxC2S_CSS_SYNTAX));
    }

    //wxColour wxGetColourFromUser(wxWindow *parent, const wxColour& colInit)
    return returnColor;
}
