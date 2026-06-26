#include "SubSprayCanToolPanel.h"
#include "Globals.h"
#include "SizePicker.h"
#include "ToolManager.h"

SubSprayCanToolPanel::SubSprayCanToolPanel( wxWindow* parent )
    : SprayCanToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_sizePicker->SetValue(tm->GetSprayCanSize());
}

void SubSprayCanToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSprayCanSize(m_sizePicker->GetValue());
}
