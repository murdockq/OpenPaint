/*
 * OpenPaint
 * www.sourceforge.net/projects/OpenPaint
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

#include "Globals.h"
#include "ConfigFile.h"
#include "ToolManager.h"
#include <wx/msgdlg.h>

Globals* Globals::m_pInstance = 0;// initialize pointer

Globals* Globals::Instance () 
{
    if (m_pInstance == 0)  // is it the first call?
    {  
        m_pInstance = new Globals; // create sole instance
    }
    
    return m_pInstance; // address of sole instance
}

Globals::Globals()
{
    m_pConfig = new ConfigFile("config.xml", "OpenPaintData");
    m_pToolManager = new ToolManager();

    m_strCurrentDir = wxGetCwd();
}

Globals::~Globals()
{
    m_pConfig->Save();
    delete m_pConfig;

    m_pToolManager->Shutdown();
    delete m_pToolManager;
}


ConfigFile * Globals::GetConfig()
{
    return m_pConfig;
}


SubMainFrame * Globals::GetMainFrame()
{
    return m_pMainFrame;
}

void Globals::SetMainFrame(SubMainFrame * pMainFrame)
{
    m_pMainFrame = pMainFrame;
}

SubToolPanel * Globals::GetToolPanel()
{
    return m_pToolPanel;
}

void Globals::SetToolPanel(SubToolPanel* pToolPanel)
{
    m_pToolPanel = pToolPanel;
}

SubColorPanel * Globals::GetColorPanel()
{
    return m_pColorPanel;
}

void Globals::SetColorPanel(SubColorPanel* pColorPanel)
{
    m_pColorPanel = pColorPanel;
}

ToolManager * Globals::GetToolManager()
{
    return m_pToolManager;
}

void Globals::SetToolManager(ToolManager * pToolManager)
{
    m_pToolManager = pToolManager;
}

wxString Globals::GetCurrentDir()
{
    return m_strCurrentDir;
}

void Globals::SetCurrentDir(wxString strCurrentDir)
{
    m_strCurrentDir = strCurrentDir;
}
