#include "SubPencilToolPanel.h"
#include "Globals.h"
#include "SizePicker.h"
#include "ToolManager.h"

SubPencilToolPanel::SubPencilToolPanel( wxWindow* parent )
    : PencilToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_sizePicker->SetValue(tm->GetPencilSize());
}

void SubPencilToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetPencilSize(m_sizePicker->GetValue());
}

