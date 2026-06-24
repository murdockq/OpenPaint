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

#include "SubTextToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

SubTextToolPanel::SubTextToolPanel( wxWindow* parent )
    : TextToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_textCtrlFont->SetValue(tm->GetTextFontFace());
    m_spinCtrlSize->SetValue(tm->GetTextFontSize());
    m_checkBoxBold->SetValue(tm->GetTextFontBold());
    m_checkBoxItalic->SetValue(tm->GetTextFontItalic());
    m_checkBoxUnderline->SetValue(tm->GetTextFontUnderline());
}

void SubTextToolPanel::OnFont( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetTextFontFace(m_textCtrlFont->GetValue());
}

void SubTextToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetTextFontSize(m_spinCtrlSize->GetValue());
}

void SubTextToolPanel::OnBold( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetTextFontBold(m_checkBoxBold->GetValue());
}

void SubTextToolPanel::OnItalic( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetTextFontItalic(m_checkBoxItalic->GetValue());
}

void SubTextToolPanel::OnUnderline( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetTextFontUnderline(m_checkBoxUnderline->GetValue());
}
