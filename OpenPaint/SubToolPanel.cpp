#include "SubToolPanel.h"
#include "SubBrushToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"
#include <wx/statbox.h>
#include <wx/image.h>
#include <wx/aui/aui.h>

SubToolPanel::SubToolPanel( wxWindow* parent )
:
ToolPanel( parent )
{
    //wxBitmap m_SmallBitmap = wxICON( IDI_ICON_COLOR_FILL );
    //if ( m_SmallBitmap.Ok() )
    //{
    //    wxImage m_SmallImage = m_SmallBitmap.ConvertToImage();
    //    m_SmallImage = m_SmallImage.Scale( 22, 22);
    //    m_bpButtonFill->SetBitmapLabel(wxBitmap(m_SmallImage));
    //}
}

void SubToolPanel::EnableTools()
{
    //Hack: Use the disable state as a toggle for the bitmap button untill a wxBitmapToggleButton is added
    m_bpButtonSelectLasso->Enable(true);
    m_bpButtonSelect->Enable(true);
    m_bpButtonEraser->Enable(true);
    m_bpButtonFill->Enable(true);
    m_bpButtonPickColor->Enable(true);
    m_bpButtonMagnify->Enable(true);
    m_bpButtonPencil->Enable(true);
    m_bpButtonBrush->Enable(true);
    m_bpButtonSprayCan->Enable(true);
    m_bpButtonText->Enable(true);
    m_bpButtonRectangle->Enable(true);
    m_bpButtonPolyline->Enable(true);
    m_bpButtonEllipse->Enable(true);
    m_bpButtonRectangleRounded->Enable(true);
}

void SubToolPanel::ClearToolProperties()
{
    // Detach and destroy any window currently held in the properties
    // sizer so that switching tools doesn't leave a stale panel (e.g.
    // the BrushToolPanel) visible under the new tool's label.
    while (m_sbSizerToolProperties->GetItemCount() > 0)
    {
        wxSizerItem* item = m_sbSizerToolProperties->GetItem(static_cast<size_t>(0));
        if (!item) break;
        wxWindow* w = item->GetWindow();
        m_sbSizerToolProperties->Remove(0);
        if (w)
        {
            w->Destroy();
        }
    }
}

void SubToolPanel::UpdateToolPropertiesLayout()
{
    m_sbSizerToolProperties->Layout();
    Layout();
    // Tell the AUI manager that owns this pane to re-fit it; otherwise
    // changes only become visible after the pane is toggled via the
    // View > Tool Window menu.
    wxAuiManager* aui = wxAuiManager::GetManager(this);
    if (aui)
    {
        wxAuiPaneInfo& pane = aui->GetPane(this);
        pane.best_size = GetBestSize();
        aui->Update();
    }
}

void SubToolPanel::OnPickColor( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_PICK_COLOR);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Pick Color"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonPickColor->Enable(false);
}

void SubToolPanel::OnPencil( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_PENCIL);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Pencil"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonPencil->Enable(false);
}

void SubToolPanel::OnBrush( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_BRUSH);

    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Brush"));
    ClearToolProperties();
    SubBrushToolPanel* brushPanel = new SubBrushToolPanel(this);
    // BrushToolPanel hides itself in its constructor; reveal it so the
    // radius/tip controls are actually visible inside the tool-properties box.
    brushPanel->Show();
    m_sbSizerToolProperties->Add(brushPanel);
    UpdateToolPropertiesLayout();

    EnableTools();
    m_bpButtonBrush->Enable(false);
}

void SubToolPanel::OnFill( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_FILL);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Fill"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonFill->Enable(false);
}

void SubToolPanel::OnEraser( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_ERASER);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Eraser"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonEraser->Enable(false);
}

void SubToolPanel::OnMagnify( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_MAGNIFY);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Magnify"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonMagnify->Enable(false);
}

void SubToolPanel::OnSprayCan( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SPRAY_CAN);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Spray Can"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonSprayCan->Enable(false);
}

void SubToolPanel::OnRectangle( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_RECTANGLE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Rectangle"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonRectangle->Enable(false);
}

void SubToolPanel::OnEllipse( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_ELLIPSE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Ellipse"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonEllipse->Enable(false);
}

void SubToolPanel::OnRectangleRounded( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_RECTANGLE_ROUNDED);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Round Rect"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonRectangleRounded->Enable(false);
}

void SubToolPanel::OnPolyline( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_POLYLINE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Polyline"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonPolyline->Enable(false);
}

void SubToolPanel::OnSelectLasso( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SELECT_LASSO);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Lasso Select"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonSelectLasso->Enable(false);
}

void SubToolPanel::OnSelect( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SELECT);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Box Select"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonSelect->Enable(false);
}

void SubToolPanel::OnText( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_TEXT);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Text"));
    ClearToolProperties();
    UpdateToolPropertiesLayout();
    EnableTools();
    m_bpButtonText->Enable(false);
}
