#include "SubBrushToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"

SubBrushToolPanel::SubBrushToolPanel( wxWindow* parent )
    : BrushToolPanel( parent )
{
    // Seed the controls with the current ToolManager state so the UI
    // reflects the same brush settings that BrushTool will read.
    ToolManager* tm = Globals::Instance()->GetToolManager();
    m_spinCtrlRadius->SetValue(tm->GetBrushRadius());
    m_comboBoxTip->SetSelection(tm->GetBrushTip());
}

void SubBrushToolPanel::OnWidth( wxSpinEvent& event )
{
    Globals::Instance()->GetToolManager()->SetBrushRadius(m_spinCtrlRadius->GetValue());
}

void SubBrushToolPanel::OnTip( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetBrushTip(m_comboBoxTip->GetSelection());
}

