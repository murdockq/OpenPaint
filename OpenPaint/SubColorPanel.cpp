#include "SubColorPanel.h"
#include "Globals.h"
#include "ToolManager.h"
#include <wx/clrpicker.h>

SubColorPanel::SubColorPanel( wxWindow* parent )
:
ColorPanel( parent )
{

}

void SubColorPanel::OnForegroundSet( wxColourPickerEvent& event )
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetForeground(event.GetColour());
}

void SubColorPanel::OnBackgroundSet( wxColourPickerEvent& event )
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetBackground(event.GetColour());
}

void SubColorPanel::UpdateColors()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    m_colourPickerForeground->SetColour(pToolManager->GetForeground());
    m_colourPickerBackground->SetColour(pToolManager->GetBackground());
}
