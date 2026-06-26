#include "SubTextToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

#include <wx/fontdlg.h>

SubTextToolPanel::SubTextToolPanel( wxWindow* parent )
    : TextToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    wxString face = tm->GetTextFontFace();
    if (face.IsEmpty())
        m_textCtrlFont->SetLabel(_("Font..."));
    else
        m_textCtrlFont->SetLabel(face);
    m_spinCtrlSize->SetValue(tm->GetTextFontSize());
    m_checkBoxBold->SetValue(tm->GetTextFontBold());
    m_checkBoxItalic->SetValue(tm->GetTextFontItalic());
    m_checkBoxUnderline->SetValue(tm->GetTextFontUnderline());
}

void SubTextToolPanel::OnFont( wxCommandEvent& event )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();

    wxFont current;
    wxString face = tm->GetTextFontFace();
    if (!face.IsEmpty())
        current.SetFaceName(face);
    current.SetPointSize(tm->GetTextFontSize());
    current.SetWeight(tm->GetTextFontBold() ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    current.SetStyle(tm->GetTextFontItalic() ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
    current.SetUnderlined(tm->GetTextFontUnderline());

    wxFont chosen = wxGetFontFromUser(this, current, _("Select Font"));
    if (!chosen.IsOk())
        return;

    tm->SetTextFontFace(chosen.GetFaceName());
    tm->SetTextFontSize(chosen.GetPointSize());
    tm->SetTextFontBold(chosen.GetWeight() == wxFONTWEIGHT_BOLD);
    tm->SetTextFontItalic(chosen.GetStyle() == wxFONTSTYLE_ITALIC);
    tm->SetTextFontUnderline(chosen.GetUnderlined());

    m_textCtrlFont->SetLabel(chosen.GetFaceName());
    m_spinCtrlSize->SetValue(chosen.GetPointSize());
    m_checkBoxBold->SetValue(chosen.GetWeight() == wxFONTWEIGHT_BOLD);
    m_checkBoxItalic->SetValue(chosen.GetStyle() == wxFONTSTYLE_ITALIC);
    m_checkBoxUnderline->SetValue(chosen.GetUnderlined());
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

