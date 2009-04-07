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
}

ToolManager::~ToolManager()
{

}


void ToolManager::Shutdown()
{

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
    Globals::Instance()->GetColorPanel()->UpdateColors();
}

wxColour ToolManager::GetBackground()
{
    return m_colorBackground;
}

void ToolManager::SetBackground(wxColour backgroundColor)
{
    m_colorBackground = backgroundColor;
    Globals::Instance()->GetColorPanel()->UpdateColors();
}


wxColour ToolManager::PickColor()
{
    wxColour returnColor;
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
