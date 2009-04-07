#include "SubToolPanel.h"
#include "Globals.h"
#include "ToolManager.h"
#include <wx/statbox.h>
#include <wx/image.h>

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

void SubToolPanel::OnPickColor( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_PICK_COLOR);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Pick Color"));
    EnableTools();
    m_bpButtonPickColor->Enable(false);
}

void SubToolPanel::OnPencil( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_PENCIL);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Pencil"));
    EnableTools();
    m_bpButtonPencil->Enable(false);
}

void SubToolPanel::OnBrush( wxCommandEvent& event )
{
    Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_BRUSH);
    
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Brush"));
    m_sbSizerToolProperties->Detach(0);
    m_sbSizerToolProperties->Add(new BrushToolPanel(this));
    m_sbSizerToolProperties->Layout();

    EnableTools();
    m_bpButtonBrush->Enable(false);
}

void SubToolPanel::OnFill( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_FILL);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Fill"));
    EnableTools();
    m_bpButtonFill->Enable(false);
}

void SubToolPanel::OnEraser( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_ERASER);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Eraser"));
    EnableTools();
    m_bpButtonEraser->Enable(false);
}

void SubToolPanel::OnMagnify( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_MAGNIFY);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Magnify"));
    EnableTools();
    m_bpButtonMagnify->Enable(false);
}

void SubToolPanel::OnSprayCan( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SPRAY_CAN);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Spray Can"));
    EnableTools();
    m_bpButtonSprayCan->Enable(false);
}

void SubToolPanel::OnRectangle( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_RECTANGLE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Rectangle"));
    EnableTools();
    m_bpButtonRectangle->Enable(false);
}

void SubToolPanel::OnEllipse( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_ELLIPSE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Ellipse"));
    EnableTools();
    m_bpButtonEllipse->Enable(false);
}

void SubToolPanel::OnRectangleRounded( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_RECTANGLE_ROUNDED);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Round Rect"));
    EnableTools();
    m_bpButtonRectangleRounded->Enable(false);
}

void SubToolPanel::OnPolyline( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_POLYLINE);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Polyline"));
    EnableTools();
    m_bpButtonPolyline->Enable(false);
}

void SubToolPanel::OnSelectLasso( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SELECT_LASSO);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Lasso Select"));
    EnableTools();
    m_bpButtonSelectLasso->Enable(false);
}

void SubToolPanel::OnSelect( wxCommandEvent& event )
{
	//Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_SELECT);
 //   m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Box Select"));
 //   EnableTools();
 //   m_bpButtonSelect->Enable(false);
}

void SubToolPanel::OnText( wxCommandEvent& event )
{
	Globals::Instance()->GetToolManager()->SetSelectedTool(TOOL_TEXT);
    m_sbSizerToolProperties->GetStaticBox()->SetLabel(wxT("Text"));
    EnableTools();
    m_bpButtonText->Enable(false);
}
