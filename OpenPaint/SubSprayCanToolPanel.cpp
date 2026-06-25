#include "SubSprayCanToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

SubSprayCanToolPanel::SubSprayCanToolPanel( wxWindow* parent )
    : SprayCanToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_spinCtrlSize->SetValue(tm->GetSprayCanSize());
}

void SubSprayCanToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSprayCanSize(m_spinCtrlSize->GetValue());
}
