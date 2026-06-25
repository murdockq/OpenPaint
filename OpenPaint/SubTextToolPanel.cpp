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

