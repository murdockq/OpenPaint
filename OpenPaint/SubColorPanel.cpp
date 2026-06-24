#include "SubColorPanel.h"
#include "Globals.h"
#include "ToolManager.h"
#include "PaletteCtrl.h"

SubColorPanel::SubColorPanel( wxWindow* parent )
:
ColorPanel( parent )
{

}

void SubColorPanel::UpdateColors()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    m_colourPickerForeground->SetBackgroundColour(pToolManager->GetForeground());
    m_colourPickerForeground->Refresh();
    m_colourPickerBackground->SetBackgroundColour(pToolManager->GetBackground());
    m_colourPickerBackground->Refresh();
}
