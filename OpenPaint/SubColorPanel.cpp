#include "SubColorPanel.h"
#include "Globals.h"
#include "ToolManager.h"
#include "ColorPairCtrl.h"

SubColorPanel::SubColorPanel( wxWindow* parent )
:
ColorPanel( parent )
{

}

void SubColorPanel::UpdateColors()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    m_colourPickerPair->SetFGColour(pToolManager->GetForeground());
    m_colourPickerPair->SetBGColour(pToolManager->GetBackground());
    m_colourPickerPair->SetAltColour(pToolManager->GetAlternate());
}
