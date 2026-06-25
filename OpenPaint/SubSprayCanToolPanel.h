#ifndef __SubSprayCanToolPanel__
#define __SubSprayCanToolPanel__

#include "OpenPaintGUI.h"

class SubSprayCanToolPanel : public SprayCanToolPanel
{
protected:
    virtual void OnSize( wxSpinEvent& event );
public:
    SubSprayCanToolPanel( wxWindow* parent );
};

#endif // __SubSprayCanToolPanel__

