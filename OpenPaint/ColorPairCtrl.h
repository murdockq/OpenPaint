#ifndef __ColorPairCtrl__
#define __ColorPairCtrl__

#include <wx/panel.h>
#include <wx/colour.h>

class ColorPairCtrl : public wxPanel
{
protected:
    wxColour m_foreground;
    wxColour m_background;
    wxColour m_alternate;
    int m_buttonSize;
    int m_offset;
    int m_padding;

    void OnPaint( wxPaintEvent& event );
    void OnLeftDown( wxMouseEvent& event );
    void OnRightDown( wxMouseEvent& event );

public:
    ColorPairCtrl( wxWindow* parent, int id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
    ~ColorPairCtrl();

    void SetFGColour( const wxColour& color );
    void SetBGColour( const wxColour& color );
    void SetAltColour( const wxColour& color );
    wxColour GetFGColour() const { return m_foreground; }
    wxColour GetBGColour() const { return m_background; }
    wxColour GetAltColour() const { return m_alternate; }
};

#endif // __ColorPairCtrl__
