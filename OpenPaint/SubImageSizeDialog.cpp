#include "SubImageSizeDialog.h"

#include "IconLoader.h"

SubImageSizeDialog::SubImageSizeDialog( wxWindow* parent, int iWidth, int iHeight)
:
ImageSizeDialog( parent )
{
    m_iCurrentWidth = iWidth;
    m_iCurrentHeight = iHeight;
    
    m_bIsLinked = true;
    m_dRatio = (double)iWidth/(double)iHeight;

    SetWidth(iWidth);
    SetHeight(iHeight);
}

int SubImageSizeDialog::GetWidth()
{
    return m_iWidth;
}

int SubImageSizeDialog::GetHeight()
{
    return m_iHeight;
}


void SubImageSizeDialog::SetWidth(int iWidth)
{
    m_iWidth = iWidth;
    m_spinCtrlWidth->SetValue(m_iWidth); 
}

void SubImageSizeDialog::SetHeight(int iHeight)
{
    m_iHeight = iHeight;
    m_spinCtrlHeight->SetValue(m_iHeight);
}


void SubImageSizeDialog::OnWidth( wxSpinEvent& event )
{
    m_iWidth = m_spinCtrlWidth->GetValue();
    if(m_bIsLinked)
    {
        SetHeight(wxRound(m_iWidth / m_dRatio));
    }
}

void SubImageSizeDialog::OnHeight( wxSpinEvent& event )
{
    m_iHeight = m_spinCtrlHeight->GetValue();
    if(m_bIsLinked)
    {
        SetWidth(wxRound(m_dRatio * m_iHeight));
    }
}

void SubImageSizeDialog::OnLink( wxCommandEvent& event )
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

