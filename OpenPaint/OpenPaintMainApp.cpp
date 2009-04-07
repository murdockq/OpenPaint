/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, Steven Jedlicka
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */	


#include "OpenPaintMainApp.h"
#include "Globals.h"
#include "SubMainFrame.h"
#include "OpenPaintMDIChildFrame.h"
#include <wx/cmdline.h>

IMPLEMENT_APP(OpenPaintMainApp)      // This declares wxApp::OpenPaintMainApp as "the" Application


bool OpenPaintMainApp::OnInit(void)  // Does everything needed for a program start
{
    // call default behaviour (mandatory)
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    // Create the main frame window
    Globals::Instance()->SetMainFrame(new SubMainFrame((wxFrame *) NULL));
    SubMainFrame * frame = Globals::Instance()->GetMainFrame();
    frame->SetIcon(wxICON(IDI_ICON_APP));    // lowest name and first entry in RC File

    if(m_asFilenames.GetCount() > 0)
    {
        for(unsigned int i = 0; i < m_asFilenames.GetCount(); i++)
        {
            if(wxMatchWild(wxT("*.*"), m_asFilenames[i]))
            {
                frame->OpenFile(m_asFilenames[i]);
            }
        }
    }
    else
    {
        frame->NewFile();
    }

    wxLogDebug(wxT("Ready to paint."));
    
    frame->Show(true);                            // Show the frame
    SetTopWindow(frame);                          // At this point the frame can be seen

    return true;
}

static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
    { wxCMD_LINE_SWITCH, wxT("h"), wxT("help"), wxT("displays help on the command line parameters"),
            wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
    { wxCMD_LINE_PARAM,  NULL, NULL, "Input Filename", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL|wxCMD_LINE_PARAM_MULTIPLE },
    { wxCMD_LINE_NONE }
};

void OpenPaintMainApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}
 
bool OpenPaintMainApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    for(unsigned int i = 0; i < parser.GetParamCount(); i++)
    {
        m_asFilenames.Add(parser.GetParam(i));
    }

    return true;
}