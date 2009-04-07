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

#include "PaletteCtrl.h"
#include "Globals.h"
#include "ToolManager.h"

PaletteCtrl::PaletteCtrl( wxWindow* parent, int id , wxPoint pos , wxSize size, int style )
    : wxPanel( parent, id, pos, size, style )
{
    this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PaletteCtrl::OnForeground ) );
    this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( PaletteCtrl::OnBackground ) );

}

void PaletteCtrl::OnPalette( wxMouseEvent& event )
{
    wxWindow * eventWindow = (wxWindow *)event.GetEventObject();
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();

    if(event.GetEventType() == wxEVT_LEFT_DCLICK)
    {
        pToolManager->SetForeground(pToolManager->PickColor());
        this->SetBackgroundColour(pToolManager->GetForeground());
    }
    else if(event.GetEventType() == wxEVT_RIGHT_DCLICK)
    {
        pToolManager->SetBackground(pToolManager->PickColor());
        this->SetBackgroundColour(pToolManager->GetBackground());
    }
    Refresh();
}

void PaletteCtrl::OnForeground( wxMouseEvent& event )
{
   	wxWindow * eventWindow = (wxWindow *)event.GetEventObject();
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetForeground(eventWindow->GetBackgroundColour());
}

void PaletteCtrl::OnBackground( wxMouseEvent& event )
{
   	wxWindow * eventWindow = (wxWindow *)event.GetEventObject();
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetBackground(eventWindow->GetBackgroundColour());
}
