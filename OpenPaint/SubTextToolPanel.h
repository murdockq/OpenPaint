#ifndef __SubTextToolPanel__
#define __SubTextToolPanel__

#include "OpenPaintGUI.h"

class SubTextToolPanel : public TextToolPanel
{
protected:
    virtual void OnFont( wxCommandEvent& event );
    virtual void OnSize( wxSpinEvent& event );
    virtual void OnBold( wxCommandEvent& event );
    virtual void OnItalic( wxCommandEvent& event );
    virtual void OnUnderline( wxCommandEvent& event );
public:
    SubTextToolPanel( wxWindow* parent );
};

#endif // __SubTextToolPanel__

