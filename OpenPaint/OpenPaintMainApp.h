#ifndef __OpenPaintMainApp__
#define __OpenPaintMainApp__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif //WX_PRECOMP

#include "OpenPaintGUI.h"
#include <wx/arrstr.h>


///////////////////////////////////////////////////////////////////////////
// Define a new application type, each program should derive a class from wxApp
class OpenPaintMainApp : public wxApp
{
    private:
        bool m_bSilentMode;
        wxArrayString m_asFilenames;
    public:
        virtual bool OnInit();
        virtual int OnExit();
        virtual void OnInitCmdLine(wxCmdLineParser& parser);
        virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
};

#endif

