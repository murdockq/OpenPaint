#ifndef __SubBrushToolPanel__
#define __SubBrushToolPanel__

#include "OpenPaintGUI.h"

class SubBrushToolPanel : public BrushToolPanel
{
protected:
    virtual void OnWidth( wxSpinEvent& event );
    virtual void OnTip( wxCommandEvent& event );
public:
    SubBrushToolPanel( wxWindow* parent );
};

#endif // __SubBrushToolPanel__

