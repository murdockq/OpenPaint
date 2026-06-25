#ifndef __SubShapeToolPanel__
#define __SubShapeToolPanel__

#include "OpenPaintGUI.h"

class SubShapeToolPanel : public ShapeToolPanel
{
protected:
    virtual void OnWidth( wxSpinEvent& event );
    virtual void OnFilled( wxCommandEvent& event );
public:
    SubShapeToolPanel( wxWindow* parent );
};

#endif // __SubShapeToolPanel__

