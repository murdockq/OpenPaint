#include "ColorPairCtrl.h"
#include "Globals.h"
#include "ToolManager.h"
#include <wx/wx.h>

ColorPairCtrl::ColorPairCtrl( wxWindow* parent, int id, const wxPoint& pos, const wxSize& size )
    : wxPanel( parent, id, pos, size, 0 )
    , m_foreground( 0, 0, 0 )
    , m_background( 255, 255, 255 )
    , m_buttonSize( 22 )
    , m_offset( 10 )
{
    SetMinSize( wxSize( m_buttonSize + m_offset, m_buttonSize + m_offset ) );

    Connect( wxEVT_PAINT, wxPaintEventHandler( ColorPairCtrl::OnPaint ) );
    Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorPairCtrl::OnLeftDown ) );
    Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ColorPairCtrl::OnRightDown ) );
}

ColorPairCtrl::~ColorPairCtrl()
{
    Disconnect( wxEVT_PAINT, wxPaintEventHandler( ColorPairCtrl::OnPaint ) );
    Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorPairCtrl::OnLeftDown ) );
    Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ColorPairCtrl::OnRightDown ) );
}

void ColorPairCtrl::SetFGColour( const wxColour& color )
{
    m_foreground = color;
    Refresh();
}

void ColorPairCtrl::SetBGColour( const wxColour& color )
{
    m_background = color;
    Refresh();
}

void ColorPairCtrl::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc( this );

    // Draw the background swatch first (fill + outline) so everything is behind the foreground.
    dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
    dc.SetBrush( wxBrush( m_background, wxSOLID ) );
    dc.DrawRectangle( m_offset, m_offset, m_buttonSize, m_buttonSize );

    // Draw the foreground swatch on top (fill + outline).
    dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
    dc.SetBrush( wxBrush( m_foreground, wxSOLID ) );
    dc.DrawRectangle( 0, 0, m_buttonSize, m_buttonSize );
}

void ColorPairCtrl::OnLeftDown( wxMouseEvent& event )
{
    ToolManager* pToolManager = Globals::Instance()->GetToolManager();
    wxPoint pos = event.GetPosition();
    bool inForeground = pos.x >= 0 && pos.x < m_buttonSize && pos.y >= 0 && pos.y < m_buttonSize;
    bool inBackground = pos.x >= m_offset && pos.x < m_offset + m_buttonSize && pos.y >= m_offset && pos.y < m_offset + m_buttonSize;

    if( inForeground )
    {
        pToolManager->SetForeground( pToolManager->PickColor( pToolManager->GetForeground() ) );
    }
    else if( inBackground )
    {
        pToolManager->SetBackground( pToolManager->PickColor( pToolManager->GetBackground() ) );
    }
}

void ColorPairCtrl::OnRightDown( wxMouseEvent& event )
{
    ToolManager* pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetBackground( pToolManager->PickColor( pToolManager->GetBackground() ) );
}
