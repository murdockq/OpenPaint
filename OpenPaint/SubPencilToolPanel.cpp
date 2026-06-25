#include "SubPencilToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

SubPencilToolPanel::SubPencilToolPanel( wxWindow* parent )
    : PencilToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_spinCtrlSize->SetValue(tm->GetPencilSize());
}

void SubPencilToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetPencilSize(m_spinCtrlSize->GetValue());
}

