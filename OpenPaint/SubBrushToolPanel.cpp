#include "SubBrushToolPanel.h"
#include "Globals.h"
#include "SizePicker.h"
#include "ToolManager.h"

SubBrushToolPanel::SubBrushToolPanel( wxWindow* parent )
    : BrushToolPanel( parent )
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_sizePicker->SetValue(tm->GetBrushRadius());
    SelectTip(tm->GetBrushTip());
}

void SubBrushToolPanel::OnWidth( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetBrushRadius(m_sizePicker->GetValue());
}

void SubBrushToolPanel::OnTip( wxCommandEvent& event )
{
    int tip = 0;
    switch (event.GetId())
    {
    case IDX_BRUSH_TIP_ROUND:  tip = 0; break;
    case IDX_BRUSH_TIP_SQUARE: tip = 1; break;
    case IDX_BRUSH_TIP_VLINE:  tip = 2; break;
    case IDX_BRUSH_TIP_HLINE:  tip = 3; break;
    default: return;
    }
    Globals::Instance()->GetToolManager()->SetBrushTip(tip);
    SelectTip(tip);
}

