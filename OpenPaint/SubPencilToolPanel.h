#ifndef __SubPencilToolPanel__
#define __SubPencilToolPanel__

#include "OpenPaintGUI.h"

class SubPencilToolPanel : public PencilToolPanel
{
protected:
    virtual void OnSize( wxSpinEvent& event );
public:
    SubPencilToolPanel( wxWindow* parent );
};

#endif // __SubPencilToolPanel__

