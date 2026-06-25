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

