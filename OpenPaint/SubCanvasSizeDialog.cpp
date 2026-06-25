#include "SubCanvasSizeDialog.h"

#include "IconLoader.h"

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
        SetHeight(wxRound(m_iWidth / m_dRatio));
    }
}

void SubCanvasSizeDialog::OnHeight( wxSpinEvent& event )
{
    m_iHeight = m_spinCtrlHeight->GetValue();
    if(m_bIsLinked)
    {
        SetWidth(wxRound(m_dRatio * m_iHeight));
    }
}

void SubCanvasSizeDialog::OnLink( wxCommandEvent& event )
{
    m_bIsLinked = !m_bIsLinked;
    if(m_bIsLinked)
    {
        m_bpButtonLink->SetBitmapLabel(IconLoader::Load(wxT("linked"), IconLoader::LogicalToolbarSize()));
    }
    else
    {
        m_bpButtonLink->SetBitmapLabel(IconLoader::Load(wxT("unlinked"), IconLoader::LogicalToolbarSize()));
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
