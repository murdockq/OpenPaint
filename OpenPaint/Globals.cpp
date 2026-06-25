#include "Globals.h"
#include "ConfigFile.h"
#include "ToolManager.h"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

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
    : m_pMainFrame(nullptr)
    , m_pToolPanel(nullptr)
    , m_pColorPanel(nullptr)
    , m_pToolManager(nullptr)
{
    // Store the config in the per-user data directory (e.g.
    // %APPDATA%\OpenPaint on Windows, ~/Library/Application Support/OpenPaint
    // on macOS, ~/.local/share/OpenPaint on Linux) instead of the current
    // working directory. The working directory may be read-only, transient, or
    // different on every launch, which caused settings to be lost or writes to
    // fail.
    const wxString userDataDir = wxStandardPaths::Get().GetUserDataDir();
    if (!wxFileName::DirExists(userDataDir))
    {
        wxFileName::Mkdir(userDataDir, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    }

    const wxString configPath = wxFileName(userDataDir, wxT("config.xml")).GetFullPath();
    m_pConfig = new ConfigFile(configPath.ToStdString(), "OpenPaintData");
    m_pToolManager = new ToolManager();

    m_strCurrentDir = wxGetCwd();
}

Globals::~Globals()
{
    m_pConfig->Save();
    delete m_pConfig;

    m_pToolManager->Shutdown();
    delete m_pToolManager;
    m_pToolManager = nullptr;

    // Reset the singleton pointer so any code that touches Globals after
    // Shutdown() (e.g. during static destruction) does not read a dangling
    // pointer. The next Instance() call will lazily recreate the object.
    m_pInstance = nullptr;
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

