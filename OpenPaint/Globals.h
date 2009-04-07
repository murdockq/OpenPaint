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

#ifndef __Globals__
#define __Globals__

#include "ConfigFile.h"
#include <wx/log.h>
class SubMainFrame;
class SubToolPanel;
class SubColorPanel;
class ToolManager;


class Globals
{
    public:
        static Globals* Instance();
        virtual ~Globals();

        ConfigFile * GetConfig();

        SubMainFrame * GetMainFrame();
        void SetMainFrame(SubMainFrame * pMainFrame);

        SubToolPanel * GetToolPanel();
        void SetToolPanel(SubToolPanel* pToolPanel);

        SubColorPanel * GetColorPanel();
        void SetColorPanel(SubColorPanel* pColorPanel);

        ToolManager * GetToolManager();
        void SetToolManager(ToolManager* pToolManager);

        wxString GetCurrentDir();
        void SetCurrentDir(wxString strCurrentDir);
    protected:
        Globals();
        SubMainFrame * m_pMainFrame;
        SubToolPanel * m_pToolPanel;
        SubColorPanel * m_pColorPanel;
        ToolManager * m_pToolManager;
    private:
        //Singleton instance of class
        static Globals* m_pInstance;

        ConfigFile * m_pConfig;

        wxString m_strCurrentDir;

};

#endif
