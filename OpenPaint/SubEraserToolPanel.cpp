#include "SubEraserToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

SubEraserToolPanel::SubEraserToolPanel( wxWindow* parent )
    : EraserToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_spinCtrlSize->SetValue(tm->GetEraserSize());
}

void SubEraserToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetEraserSize(m_spinCtrlSize->GetValue());
}

