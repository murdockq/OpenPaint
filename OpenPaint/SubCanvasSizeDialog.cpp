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


#include "SubCanvasSizeDialog.h"

SubCanvasSizeDialog::SubCanvasSizeDialog( wxWindow* parent, int iWidth, int iHeight)
:
CanvasSizeDialog( parent )
{
    m_iCurrentWidth = iWidth;
    m_iCurrentHeight = iHeight;
    
    m_bIsLinked = true;
    m_dRatio = (double)iWidth/(double)iHeight;

    SetWidth(iWidth);
    SetHeight(iHeight);
    SetOffsetX(0);
    SetOffsetY(0);
}

int SubCanvasSizeDialog::GetWidth()
{
    return m_iWidth;
}

int SubCanvasSizeDialog::GetHeight()
{
    return m_iHeight;
}

int SubCanvasSizeDialog::GetOffsetX()
{
    return m_iOffsetX;
}

int SubCanvasSizeDialog::GetOffsetY()
{
    return m_iOffsetY;
}


void SubCanvasSizeDialog::SetWidth(int iWidth)
{
    m_iWidth = iWidth;
    m_spinCtrlWidth->SetValue(m_iWidth); 
}

void SubCanvasSizeDialog::SetHeight(int iHeight)
{
    m_iHeight = iHeight;
    m_spinCtrlHeight->SetValue(m_iHeight);
}

void SubCanvasSizeDialog::SetOffsetX(int iOffsetX)
{
    m_iOffsetX = iOffsetX;
    m_spinCtrlOffsetX->SetValue(m_iOffsetX); 
}

void SubCanvasSizeDialog::SetOffsetY(int iOffsetY)
{
    m_iOffsetY = iOffsetY;
    m_spinCtrlOffsetY->SetValue(m_iOffsetY); 
}


void SubCanvasSizeDialog::OnWidth( wxSpinEvent& event )
{
    m_iWidth = m_spinCtrlWidth->GetValue();
    if(m_bIsLinked)
    {
        SetHeight(m_iWidth / m_dRatio);
    }
}

void SubCanvasSizeDialog::OnHeight( wxSpinEvent& event )
{
    m_iHeight = m_spinCtrlHeight->GetValue();
    if(m_bIsLinked)
    {
        SetWidth(m_dRatio * m_iHeight);
    }
}

void SubCanvasSizeDialog::OnLink( wxCommandEvent& event )
{
    m_bIsLinked = !m_bIsLinked;
    if(m_bIsLinked)
    {
        m_bpButtonLink->SetBitmapLabel(wxICON( IDI_ICON_LINKED ));
    }
    else
    {
        m_bpButtonLink->SetBitmapLabel(wxICON( IDI_ICON_UNLINKED ));
    }
}

void SubCanvasSizeDialog::OnOffsetX( wxSpinEvent& event )
{
    m_iOffsetX = m_spinCtrlOffsetX->GetValue();
}

void SubCanvasSizeDialog::OnOffsetY( wxSpinEvent& event )
{
   m_iOffsetY = m_spinCtrlOffsetY->GetValue();
}

void SubCanvasSizeDialog::OnCenter( wxCommandEvent& event )
{
    SetOffsetX((m_iWidth - m_iCurrentWidth)/2);
    SetOffsetY((m_iHeight - m_iCurrentHeight)/2); 
}