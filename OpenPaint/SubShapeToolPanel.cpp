#include "SubShapeToolPanel.h"
#include "Globals.h"
#include "SizePicker.h"
#include "ToolManager.h"

SubShapeToolPanel::SubShapeToolPanel( wxWindow* parent )
    : ShapeToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_sizePicker->SetValue(tm->GetShapeLineWidth());
    m_checkBoxFilled->SetValue(tm->GetShapesFilled());
}

void SubShapeToolPanel::OnWidth( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetShapeLineWidth(m_sizePicker->GetValue());
}

void SubShapeToolPanel::OnFilled( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetShapesFilled(m_checkBoxFilled->GetValue());
}

