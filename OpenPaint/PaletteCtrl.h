#ifndef __PaletteCtrl__
#define __PaletteCtrl__

#include <wx/colour.h>
#include <wx/panel.h>
#include <wx/clrpicker.h>

class PaletteCtrl : public wxPanel
{
protected:
    bool m_bPickerMode;
    bool m_bIsForeground;

	// Handlers for ColorPanel events.
	virtual void OnPalette( wxMouseEvent& event );
	virtual void OnForeground( wxMouseEvent& event );
	virtual void OnBackground( wxMouseEvent& event );

public:
	/** Constructor */
    PaletteCtrl( wxWindow* parent, int id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, int style = wxTAB_TRAVERSAL );
    /** Destructor */
    ~PaletteCtrl();

    void SetPickerMode( bool foreground );

};

#endif

