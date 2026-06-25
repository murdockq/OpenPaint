#include "ColorPairCtrl.h"
#include "Globals.h"
#include "ToolManager.h"
#include <wx/wx.h>

ColorPairCtrl::ColorPairCtrl( wxWindow* parent, int id, const wxPoint& pos, const wxSize& size )
    : wxPanel( parent, id, pos, size, 0 )
    , m_foreground( 0, 0, 0 )
    , m_background( 255, 255, 255 )
    , m_alternate()
    , m_buttonSize( 22 )
    , m_offset( 10 )
    , m_padding( 5 )
{
    SetMinSize( wxSize( m_buttonSize + m_offset + m_padding * 2, m_buttonSize + m_offset + m_padding * 2 ) );

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

void ColorPairCtrl::SetAltColour( const wxColour& color )
{
    m_alternate = color;
    Refresh();
}

void ColorPairCtrl::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc( this );
    int altSize = m_buttonSize + m_offset + m_padding * 2;

    if( m_alternate.IsOk() )
    {
        dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
        dc.SetBrush( wxBrush( m_alternate, wxBRUSHSTYLE_SOLID ) );
        dc.DrawRectangle( 0, 0, altSize, altSize );
    }
    else
    {
        dc.SetPen( *wxTRANSPARENT_PEN );
        int checkSize = 2;
        for( int y = 0; y < altSize; y += checkSize )
        {
            for( int x = 0; x < altSize; x += checkSize )
            {
                bool light = ((x / checkSize) + (y / checkSize)) % 2 == 0;
                dc.SetBrush( wxBrush( light ? wxColour( 255, 255, 255 ) : wxColour( 192, 192, 192 ), wxBRUSHSTYLE_SOLID ) );
                dc.DrawRectangle( x, y, checkSize, checkSize );
            }
        }
        dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        dc.DrawRectangle( 0, 0, altSize, altSize );
    }

    // Draw the background swatch first (fill + outline) so everything is behind the foreground.
    dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
    dc.SetBrush( wxBrush( m_background, wxBRUSHSTYLE_SOLID ) );
    dc.DrawRectangle( m_padding + m_offset, m_padding + m_offset, m_buttonSize, m_buttonSize );

    // Draw the foreground swatch on top (fill + outline).
    dc.SetPen( wxPen( wxColour( 128, 128, 128 ), 1 ) );
    dc.SetBrush( wxBrush( m_foreground, wxBRUSHSTYLE_SOLID ) );
    dc.DrawRectangle( m_padding, m_padding, m_buttonSize, m_buttonSize );
}

void ColorPairCtrl::OnLeftDown( wxMouseEvent& event )
{
    ToolManager* pToolManager = Globals::Instance()->GetToolManager();
    wxPoint pos = event.GetPosition();
    int altSize = m_buttonSize + m_offset + m_padding * 2;
    bool inForeground = pos.x >= m_padding && pos.x < m_padding + m_buttonSize && pos.y >= m_padding && pos.y < m_padding + m_buttonSize;
    bool inBackground = pos.x >= m_padding + m_offset && pos.x < m_padding + m_offset + m_buttonSize && pos.y >= m_padding + m_offset && pos.y < m_padding + m_offset + m_buttonSize;
    bool inAlternate = pos.x >= 0 && pos.x < altSize && pos.y >= 0 && pos.y < altSize && !inForeground && !inBackground;

    if( event.ControlDown() || inAlternate )
    {
        pToolManager->SetAlternate( pToolManager->PickColor( pToolManager->GetAlternate(), true ) );
    }
    else if( inForeground )
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
    wxPoint pos = event.GetPosition();
    int altSize = m_buttonSize + m_offset + m_padding * 2;
    bool inForeground = pos.x >= m_padding && pos.x < m_padding + m_buttonSize && pos.y >= m_padding && pos.y < m_padding + m_buttonSize;
    bool inBackground = pos.x >= m_padding + m_offset && pos.x < m_padding + m_offset + m_buttonSize && pos.y >= m_padding + m_offset && pos.y < m_padding + m_offset + m_buttonSize;
    bool inAlternate = pos.x >= 0 && pos.x < altSize && pos.y >= 0 && pos.y < altSize && !inForeground && !inBackground;

    if( event.ControlDown() || inAlternate )
    {
        pToolManager->SetAlternate( pToolManager->PickColor( pToolManager->GetAlternate(), true ) );
    }
    else
    {
        pToolManager->SetBackground( pToolManager->PickColor( pToolManager->GetBackground() ) );
    }
}
