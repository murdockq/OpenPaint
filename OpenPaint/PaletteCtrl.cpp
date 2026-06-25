#include "PaletteCtrl.h"
#include "Globals.h"
#include "ToolManager.h"

PaletteCtrl::PaletteCtrl( wxWindow* parent, int id , wxPoint pos , wxSize size, int style )
    : wxPanel( parent, id, pos, size, style )
    , m_bPickerMode( false )
    , m_bIsForeground( true )
{
    this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PaletteCtrl::OnForeground ) );
    this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( PaletteCtrl::OnBackground ) );

}

void PaletteCtrl::SetPickerMode( bool foreground )
{
    m_bPickerMode = true;
    m_bIsForeground = foreground;
}

PaletteCtrl::~PaletteCtrl()
{
    // Disconnect the four mouse handlers we bound in the constructor so that
    // destroying a palette swatch (one of ~20 on the colour panel) does not
    // leave dangling event entries in the global wx event table.
    this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PaletteCtrl::OnForeground ) );
    this->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( PaletteCtrl::OnPalette ) );
    this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( PaletteCtrl::OnBackground ) );
}

void PaletteCtrl::OnPalette( wxMouseEvent& event )
{
    wxWindow * eventWindow = wxDynamicCast(event.GetEventObject(), wxWindow);
    if (!eventWindow)
    {
        event.Skip();
        return;
    }
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();

    if(event.ControlDown())
    {
        pToolManager->SetAlternate(eventWindow->GetBackgroundColour());
        Refresh();
        return;
    }

    if(event.GetEventType() == wxEVT_LEFT_DCLICK)
    {
        pToolManager->SetForeground(pToolManager->PickColor(pToolManager->GetForeground()));
        this->SetBackgroundColour(pToolManager->GetForeground());
    }
    else if(event.GetEventType() == wxEVT_RIGHT_DCLICK)
    {
        pToolManager->SetBackground(pToolManager->PickColor(pToolManager->GetBackground()));
        this->SetBackgroundColour(pToolManager->GetBackground());
    }
    Refresh();
}

void PaletteCtrl::OnForeground( wxMouseEvent& event )
{
   	wxWindow * eventWindow = wxDynamicCast(event.GetEventObject(), wxWindow);
    if (!eventWindow)
    {
        event.Skip();
        return;
    }
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();

    if( event.ControlDown() )
    {
        pToolManager->SetAlternate(eventWindow->GetBackgroundColour());
        return;
    }

    if( m_bPickerMode )
    {
        if( m_bIsForeground )
        {
            pToolManager->SetForeground( pToolManager->PickColor( pToolManager->GetForeground() ) );
        }
        else
        {
            pToolManager->SetBackground( pToolManager->PickColor( pToolManager->GetBackground() ) );
        }
        SetBackgroundColour( m_bIsForeground ? pToolManager->GetForeground() : pToolManager->GetBackground() );
        Refresh();
        return;
    }

    pToolManager->SetForeground(eventWindow->GetBackgroundColour());
}

void PaletteCtrl::OnBackground( wxMouseEvent& event )
{
   	wxWindow * eventWindow = wxDynamicCast(event.GetEventObject(), wxWindow);
    if (!eventWindow)
    {
        event.Skip();
        return;
    }
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    if( event.ControlDown() )
    {
        pToolManager->SetAlternate(eventWindow->GetBackgroundColour());
        return;
    }
    pToolManager->SetBackground(eventWindow->GetBackgroundColour());
}

