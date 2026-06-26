#include "SubEraserToolPanel.h"
#include "Globals.h"
#include "SizePicker.h"
#include "ToolManager.h"

SubEraserToolPanel::SubEraserToolPanel( wxWindow* parent )
    : EraserToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_sizePicker->SetValue(tm->GetEraserSize());
}

void SubEraserToolPanel::OnSize( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetEraserSize(m_sizePicker->GetValue());
}

