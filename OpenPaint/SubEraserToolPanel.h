#ifndef __SubEraserToolPanel__
#define __SubEraserToolPanel__

#include "OpenPaintGUI.h"

class SubEraserToolPanel : public EraserToolPanel
{
protected:
    virtual void OnSize( wxSpinEvent& event );
public:
    SubEraserToolPanel( wxWindow* parent );
};

#endif // __SubEraserToolPanel__

