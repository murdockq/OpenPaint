#include "SubMainFrame.h"
#include "Globals.h"
#include "OpenPaintMDIChildFrame.h"
#include "SubToolPanel.h"
#include "SubColorPanel.h"
#include "SubCanvasSizeDialog.h"
#include "SubImageSizeDialog.h"
#include "ToolManager.h"

#include <limits>
#include <vector>

#include <wx/filefn.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/dnd.h>
#include <wx/treectrl.h>
#include <wx/artprov.h>
#include <wx/aui/aui.h>
#include <wx/log.h>
#include <wx/strconv.h>
#include <wx/imaglist.h>
#include <wx/clrpicker.h>
#include <wx/menu.h>
#include <wx/filename.h>
#include <wx/clipbrd.h>
#include <wx/fontdlg.h>

class DnDFile : public wxFileDropTarget
{
public:
    DnDFile() {}

    virtual bool OnDropFiles(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y),
                             const wxArrayString& filenames)
        {
            // Open every dropped file in its own tab. The previous code only
            // handled single-file drops and used a Windows-specific "*.*"
            // pattern that filtered out filenames without a dot on POSIX.
            SubMainFrame* mf = Globals::Instance()->GetMainFrame();
            if (!mf)
            {
                return false;
            }
            for (size_t i = 0; i < filenames.GetCount(); ++i)
            {
                mf->OpenFile(filenames[i]);
            }
            return true;
        }
};

#define IDX_MENU_HISTORYOPEN 3002

BEGIN_EVENT_TABLE(SubMainFrame, MainFrame)
    EVT_MENU( IDX_MENU_HISTORYOPEN, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+1, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+2, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+3, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+4, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+5, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+6, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+7, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+8, SubMainFrame::HistoryOpen )
    EVT_MENU( IDX_MENU_HISTORYOPEN+9, SubMainFrame::HistoryOpen )
    EVT_MENU_RANGE(SubMainFrame::IDX_TAB_MENU_SAVE, SubMainFrame::IDX_TAB_MENU_LOCK, SubMainFrame::OnTabMenu)
    EVT_SIZE(SubMainFrame::OnSize)
    EVT_AUI_PANE_CLOSE(SubMainFrame::OnAuiPaneClose)
    EVT_AUINOTEBOOK_TAB_RIGHT_UP(wxID_ANY, SubMainFrame::OnTabRightUp)
    EVT_MENU_OPEN(SubMainFrame::OnMenuOpen)
END_EVENT_TABLE()

SubMainFrame::SubMainFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style )
:
MainFrame( parent, id, title, pos, size, style )
{
    m_contextTabIndex = wxNOT_FOUND;
    m_ownsAuiManager = false;

    //Set the target fro droping file onto the application
    SetDropTarget(new DnDFile());

    //Store the Recent Projects menu in the inherited class
    wxMenu *fileMenu = GetMenuBar()->GetMenu(0);
    wxMenuItem * emptyItem = fileMenu->FindItem(IDX_MENU_EMPTY, &m_menuRecentImages);

    UpdateHistory();

    int statusWidths[] = {-2,-1, -1, -1};
    GetStatusBar()->SetStatusWidths(4, statusWidths );

    Init();

}

SubMainFrame::~SubMainFrame()
{
    // Only uninitialise and free the AUI manager if we actually own it.
    // wxAuiMDIParentFrame already manages the MDI client window through
    // its own internal wxAuiManager, which Init() picks up via
    // wxAuiManager::GetManager(); that one is owned by the frame and must
    // not be deleted here. MDI children are closed in OnClose() before
    // this destructor runs, so the notebook is empty by the time we
    // tear down our own manager (if any).
    if (m_mAuiManager && m_ownsAuiManager)
    {
        m_mAuiManager->UnInit();
        delete m_mAuiManager;
    }
    m_mAuiManager = nullptr;
    m_ownsAuiManager = false;
}

void SubMainFrame::Init()
{
    // wxAuiMDIParentFrame already manages the MDI client window through
    // its own internal wxAuiManager. Adding it to a second manager on the
    // same frame triggers a "pane with that name already exists" assertion
    // in wxWidgets >= 3.3, and silently corrupts layout in earlier builds.
    // Use the frame's existing manager so tool/color panes share the same
    // layout as the MDI client, instead of creating a competing one.
    m_mAuiManager = wxAuiManager::GetManager(this);
    if (m_mAuiManager)
    {
        m_ownsAuiManager = false;
    }
    else
    {
        m_mAuiManager = new wxAuiManager(this);
        m_ownsAuiManager = true;
    }

    wxAuiMDIClientWindow* client_window = this->GetClientWindow();

    wxASSERT_MSG(client_window, wxT("Client window is NULL!"));

    GetToolBar()->EnableTool(wxID_UNDO, false);
    GetToolBar()->EnableTool(wxID_REDO, false);

    SubToolPanel * panelTool = new SubToolPanel(this);
    m_mAuiManager->AddPane(panelTool, wxLEFT, wxT("Tools"));
    // Clamp the pane's best width to the tool-button grid so the
    // tool-properties panel doesn't stretch the pane on first show.
    {
        wxAuiPaneInfo& toolPane = m_mAuiManager->GetPane(panelTool);
        int gridW = panelTool->GetToolGridWidth();
        if (gridW > 0 && toolPane.best_size.x > gridW)
            toolPane.BestSize(gridW, toolPane.best_size.y);
    }
    Globals::Instance()->SetToolPanel(panelTool);

    SubColorPanel * panelColor = new SubColorPanel( this);
    m_mAuiManager->AddPane(panelColor, wxBOTTOM, wxT("Colors"));
    Globals::Instance()->SetColorPanel(panelColor);
    

#ifdef _DEBUG
    wxAuiPaneInfo paneInfo;
    paneInfo.Caption(wxT("Output"));
    paneInfo.BestSize(200,300);
    paneInfo.Right();

    wxTextCtrl * textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
    m_mAuiManager->AddPane(textCtrl, paneInfo);

    wxLogTextCtrl *logWindow = new wxLogTextCtrl(textCtrl);
    delete wxLog::SetActiveTarget(logWindow);
    wxLog::SetLogLevel(wxLOG_Debug);

#else
    //wxLog::SetActiveTarget(wxLogNull);
#endif

    m_mAuiManager->Update();
}

wxAuiNotebook* SubMainFrame::GetTabNotebook() const
{
    return GetNotebook();
}

OpenPaintMDIChildFrame* SubMainFrame::GetChildFrameAt(size_t pageIndex) const
{
    wxAuiNotebook* notebook = GetTabNotebook();
    if (!notebook || pageIndex >= notebook->GetPageCount())
    {
        return nullptr;
    }

    return wxDynamicCast(notebook->GetPage(pageIndex), OpenPaintMDIChildFrame);
}

bool SubMainFrame::ActivateTab(size_t pageIndex)
{
    wxAuiNotebook* notebook = GetTabNotebook();
    if (!notebook || pageIndex >= notebook->GetPageCount())
    {
        return false;
    }

    notebook->SetSelection(pageIndex);
    return true;
}

bool SubMainFrame::CloseTab(size_t pageIndex)
{
    OpenPaintMDIChildFrame* child = GetChildFrameAt(pageIndex);
    if (!child || !ActivateTab(pageIndex))
    {
        return false;
    }

    if (!child->Close())
    {
        child->Destroy();
    }
    return true;
}

void SubMainFrame::CloseOtherTabs(size_t pageIndex)
{
    wxAuiNotebook* notebook = GetTabNotebook();
    if (!notebook || pageIndex >= notebook->GetPageCount())
    {
        return;
    }

    for (size_t i = notebook->GetPageCount(); i > 0; --i)
    {
        const size_t current = i - 1;
        if (current != pageIndex)
        {
            CloseTab(current);
        }
    }
}

void SubMainFrame::CloseAllTabs()
{
    wxAuiNotebook* notebook = GetTabNotebook();
    if (!notebook)
    {
        return;
    }

    for (size_t i = notebook->GetPageCount(); i > 0; --i)
    {
        CloseTab(i - 1);
    }
}

int SubMainFrame::GetContextTabIndex() const
{
    return m_contextTabIndex;
}

void SubMainFrame::OnTabRightUp(wxAuiNotebookEvent& event)
{
    wxAuiNotebook* notebook = GetTabNotebook();
    const int tabIndex = event.GetSelection();
    if (!notebook || tabIndex == wxNOT_FOUND)
    {
        event.Skip();
        return;
    }

    m_contextTabIndex = tabIndex;
    ActivateTab(static_cast<size_t>(tabIndex));

    wxMenu menu;
    menu.Append(IDX_TAB_MENU_SAVE, wxT("Save"));
    menu.Append(IDX_TAB_MENU_SAVE_AS, wxT("Save As..."));
    menu.AppendSeparator();
    menu.Append(IDX_TAB_MENU_CLOSE, wxT("Close"));
    menu.Append(IDX_TAB_MENU_CLOSE_OTHERS, wxT("Close Others"));
    menu.Append(IDX_TAB_MENU_CLOSE_ALL, wxT("Close All"));
    menu.AppendSeparator();
    menu.Append(IDX_TAB_MENU_SPLIT_TOP, wxT("Split Above"));
    menu.Append(IDX_TAB_MENU_SPLIT_RIGHT, wxT("Split Right"));
    menu.Append(IDX_TAB_MENU_SPLIT_BOTTOM, wxT("Split Below"));
    menu.Append(IDX_TAB_MENU_SPLIT_LEFT, wxT("Split Left"));
    menu.Append(IDX_TAB_MENU_UNSPLIT_ALL, wxT("Merge All Tab Groups"));
    menu.AppendSeparator();
    menu.AppendCheckItem(IDX_TAB_MENU_PIN, wxT("Pin Tab"));
    menu.AppendCheckItem(IDX_TAB_MENU_LOCK, wxT("Lock Tab"));

    const size_t pageIndex = static_cast<size_t>(tabIndex);
    const size_t pageCount = notebook->GetPageCount();
    const wxAuiTabKind kind = notebook->GetPageKind(pageIndex);
    menu.Check(IDX_TAB_MENU_PIN, kind == wxAuiTabKind::Pinned);
    menu.Check(IDX_TAB_MENU_LOCK, kind == wxAuiTabKind::Locked);

    menu.Enable(IDX_TAB_MENU_CLOSE_OTHERS, pageCount > 1);
    menu.Enable(IDX_TAB_MENU_CLOSE_ALL, pageCount > 0);

    PopupMenu(&menu);
    m_contextTabIndex = wxNOT_FOUND;
}

void SubMainFrame::OnTabMenu(wxCommandEvent& event)
{
    wxAuiNotebook* notebook = GetTabNotebook();
    const int pageIndex = GetContextTabIndex();
    if (!notebook || pageIndex == wxNOT_FOUND ||
        static_cast<size_t>(pageIndex) >= notebook->GetPageCount())
    {
        return;
    }

    const size_t page = static_cast<size_t>(pageIndex);
    ActivateTab(page);

    OpenPaintMDIChildFrame* child = GetChildFrameAt(page);
    if (!child)
    {
        return;
    }

    switch (event.GetId())
    {
        case IDX_TAB_MENU_SAVE:
        {
            const wxString filename = child->GetFilename();
            if (filename.empty())
            {
                SaveAs();
            }
            else if (child->Save())
            {
                AddFileToHistory(filename);
            }
            break;
        }
        case IDX_TAB_MENU_SAVE_AS:
            SaveAs();
            break;
        case IDX_TAB_MENU_CLOSE:
            CloseTab(page);
            break;
        case IDX_TAB_MENU_CLOSE_OTHERS:
            CloseOtherTabs(page);
            break;
        case IDX_TAB_MENU_CLOSE_ALL:
            CloseAllTabs();
            break;
        case IDX_TAB_MENU_SPLIT_TOP:
            notebook->Split(page, wxTOP);
            break;
        case IDX_TAB_MENU_SPLIT_RIGHT:
            notebook->Split(page, wxRIGHT);
            break;
        case IDX_TAB_MENU_SPLIT_BOTTOM:
            notebook->Split(page, wxBOTTOM);
            break;
        case IDX_TAB_MENU_SPLIT_LEFT:
            notebook->Split(page, wxLEFT);
            break;
        case IDX_TAB_MENU_UNSPLIT_ALL:
            notebook->UnsplitAll();
            break;
        case IDX_TAB_MENU_PIN:
            notebook->SetPageKind(page,
                notebook->GetPageKind(page) == wxAuiTabKind::Pinned
                    ? wxAuiTabKind::Normal
                    : wxAuiTabKind::Pinned);
            break;
        case IDX_TAB_MENU_LOCK:
            notebook->SetPageKind(page,
                notebook->GetPageKind(page) == wxAuiTabKind::Locked
                    ? wxAuiTabKind::Normal
                    : wxAuiTabKind::Locked);
            break;
        default:
            break;
    }
}

void SubMainFrame::UpdateHistory()
{
    ConfigFile *clientConfig = Globals::Instance()->GetConfig();

    int iHistorySize = clientConfig->getInteger("FileHistorySize", 4);
    std::vector<std::string> listFileHistory =  clientConfig->getArray("FileHistory");

    if(iHistorySize != 0 && listFileHistory.size() != 0)
    {
        //Clear the Recent Files menu
        wxMenuItemList menuItems = m_menuRecentImages->GetMenuItems();
        for ( wxMenuItemList::compatibility_iterator node = menuItems.GetFirst();
              node;
              node = node->GetNext() )
        {
            wxMenuItem *item = node->GetData();
            m_menuRecentImages->Delete(item);
        }

        //Add the recent history to the menu. The most recently opened file
        //should appear at the top of the menu, but it must also be reachable
        //by IDX_MENU_HISTORYOPEN+i in the same order as listFileHistory so
        //HistoryOpen() can look it up by index. Insert at position i (not 0)
        //to keep the index of each item aligned with its entry in
        //listFileHistory.
        for(int i = 0; i < iHistorySize && i < static_cast<int>(listFileHistory.size()); i++)
        {
            //Add the previous files to the menu for opening
            wxMenuItem* menuItemTest = new wxMenuItem( m_menuRecentImages, IDX_MENU_HISTORYOPEN + i, wxString( listFileHistory.at(i).c_str(), wxConvUTF8 ), wxT("Open this file."), wxITEM_NORMAL );
            m_menuRecentImages->Insert(static_cast<size_t>(i), menuItemTest);
        }
    }
}

//Add the file to the File History
void SubMainFrame::AddFileToHistory(wxString strFilename)
{
    ConfigFile *clientConfig = Globals::Instance()->GetConfig();

    std::vector<std::string> listFileHistory =  clientConfig->getArray("FileHistory");

    for(std::vector<std::string>::iterator iter = listFileHistory.begin(); iter != listFileHistory.end(); iter++)
    {
        if(strFilename == wxString((*iter).c_str(), wxConvUTF8))
        {
            listFileHistory.erase(iter);
            break;
        }
    }
    listFileHistory.push_back(strFilename.ToUTF8().data());

    while(listFileHistory.size() > clientConfig->getInteger("FileHistorySize",4))
    {
        listFileHistory.erase(listFileHistory.begin());
    }
    clientConfig->setArray("FileHistory", listFileHistory);

    UpdateHistory();
}


void SubMainFrame::OpenLastFiles()
{
    ConfigFile *clientConfig = Globals::Instance()->GetConfig();

    //Open the last file in the history
    if(clientConfig->getBool("AutoOpenLastSession", true))
    {
        std::vector<std::string> listFileSession =  clientConfig->getArray("RecentFileSession");
        for(std::vector<std::string>::iterator iter = listFileSession.begin(); iter != listFileSession.end(); iter++)
        {
            OpenFile(wxString((*iter).c_str(), wxConvUTF8));
            wxLogDebug(wxT("Auto Opened: %s"), wxString(*iter));
        }
    }
}

void SubMainFrame::HistoryOpen( wxCommandEvent& event )
{
    ConfigFile *clientConfig = Globals::Instance()->GetConfig();
    std::vector<std::string> listFileHistory =  clientConfig->getArray("FileHistory");
    int iHistoryIndex  = event.GetId() - IDX_MENU_HISTORYOPEN;
    if(iHistoryIndex >= 0 && iHistoryIndex < listFileHistory.size())
    {
        wxString filename = wxString(listFileHistory.at(iHistoryIndex).c_str(), wxConvUTF8);
        OpenFile(filename);
    }
}

//****************Edit************************

void SubMainFrame::OnUndo( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->Undo();
    }
}

void SubMainFrame::OnRedo( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->Redo();
    }
}

void SubMainFrame::OnCut( wxCommandEvent& event )
{
    // Write some selection to the clipboard
    if (wxTheClipboard->Open())
    {
        OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
        if(childFrame)
        {
            wxTheClipboard->SetData( new wxBitmapDataObject(childFrame->Cut()) );
        }
        wxTheClipboard->Close();
    }
}

void SubMainFrame::OnCopy( wxCommandEvent& event )
{
    // Write some selection to the clipboard
    if (wxTheClipboard->Open())
    {
        OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
        if(childFrame)
        {
            wxTheClipboard->SetData( new wxBitmapDataObject(childFrame->Copy()) );
        }
        wxTheClipboard->Close();
    }
}

void SubMainFrame::OnPaste( wxCommandEvent& event )
{
    // Read data from clipboard
    if (wxTheClipboard->Open())
    {
        if (wxTheClipboard->IsSupported( wxDF_BITMAP ))
        {
            wxBitmapDataObject data;
            wxTheClipboard->GetData( data );
            OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
            if(childFrame && data.GetBitmap().IsOk())
                childFrame->Paste(data.GetBitmap());
        }  
        wxTheClipboard->Close();
    }
}

void SubMainFrame::OnDelete( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->Delete();
    }
}

void SubMainFrame::OnSelectAll( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->SelectAll();
    }
}

void SubMainFrame::OnClear( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->Clear();
    }
}

void SubMainFrame::OnFillFGColor( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->FillFGColor();
    }
}

void SubMainFrame::OnFillBGColor( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        childFrame->FillBGColor();
    }
}



//****************View************************

void SubMainFrame::OnToolWindow( wxCommandEvent& event )
{
    SubToolPanel* panel = Globals::Instance()->GetToolPanel();
    if (!panel)
    {
        return;
    }
    if (event.IsChecked())
    {
        // If the panel is already managed, just show it; otherwise attach it.
        if (!m_mAuiManager->GetPane(panel).IsOk())
        {
            m_mAuiManager->AddPane(panel, wxLEFT, wxT("Tools"));
        }
        m_mAuiManager->GetPane(panel).Show();
    }
    else
    {
        if (m_mAuiManager->GetPane(panel).IsOk())
        {
            m_mAuiManager->GetPane(panel).Hide();
        }
    }
    m_mAuiManager->Update();
}

void SubMainFrame::OnColorWindow( wxCommandEvent& event )
{
    SubColorPanel* panel = Globals::Instance()->GetColorPanel();
    if (!panel)
    {
        return;
    }
    if (event.IsChecked())
    {
        if (!m_mAuiManager->GetPane(panel).IsOk())
        {
            m_mAuiManager->AddPane(panel, wxBOTTOM, wxT("Colors"));
        }
        m_mAuiManager->GetPane(panel).Show();
    }
    else
    {
        if (m_mAuiManager->GetPane(panel).IsOk())
        {
            m_mAuiManager->GetPane(panel).Hide();
        }
    }
    m_mAuiManager->Update();
}

void SubMainFrame::OnToolbar( wxCommandEvent& event )
{
    GetToolBar()->Show(event.IsChecked());
    m_mAuiManager->Update();
}

void SubMainFrame::OnStatusBar( wxCommandEvent& event )
{
    GetStatusBar()->Show(event.IsChecked());
//    Layout();
//    Refresh();
    m_mAuiManager->Update();
}

void SubMainFrame::OnAuiPaneClose( wxAuiManagerEvent& event )
{
    wxWindow* closedWindow = event.GetPane() ? event.GetPane()->window : nullptr;
    if (closedWindow)
    {
        if (closedWindow == Globals::Instance()->GetToolPanel())
        {
            wxMenuItem* item = GetMenuBar()->FindItem(IDX_TOOL_WINDOW);
            if (item)
            {
                item->Check(false);
            }
        }
        else if (closedWindow == Globals::Instance()->GetColorPanel())
        {
            wxMenuItem* item = GetMenuBar()->FindItem(IDX_COLOR_WINDOW);
            if (item)
            {
                item->Check(false);
            }
        }
    }
    event.Skip();
}

void SubMainFrame::OnMenuOpen( wxMenuEvent& event )
{
    wxMenu* menu = event.GetMenu();
    if (menu == m_menuView || menu == m_menuWindows)
    {
        wxAuiPaneInfo& toolPane = m_mAuiManager->GetPane(Globals::Instance()->GetToolPanel());
        wxMenuItem* toolItem = GetMenuBar()->FindItem(IDX_TOOL_WINDOW);
        if (toolItem)
        {
            toolItem->Check(toolPane.IsOk() && toolPane.IsShown());
        }

        wxAuiPaneInfo& colorPane = m_mAuiManager->GetPane(Globals::Instance()->GetColorPanel());
        wxMenuItem* colorItem = GetMenuBar()->FindItem(IDX_COLOR_WINDOW);
        if (colorItem)
        {
            colorItem->Check(colorPane.IsOk() && colorPane.IsShown());
        }
    }
    event.Skip();
}

void SubMainFrame::OnZoomOut( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->ZoomOut();
}

void SubMainFrame::OnZoomIn( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->ZoomIn();
}

void SubMainFrame::OnNormalZoom( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->NormalZoom();
}

void SubMainFrame::OnHistogram( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if (!childFrame)
    {
        return;
    }

    // Only work on luminence for now
    wxImage image = childFrame->GetImage();

    // Build a histogram of unique colours, then bucket them into 256 bins
    // keyed by their position in the colour table, scaled into a 256x256
    // grayscale bitmap.
    wxImageHistogram table;
    image.ComputeHistogram(table);
    wxImageHistogram::iterator iter;

    long minValue = std::numeric_limits<long>::max();
    long maxValue = std::numeric_limits<long>::min();
    unsigned long *countValue = new unsigned long[256];
    for (int i = 0; i < 256; ++i)
    {
        countValue[i] = 0;
    }

    for (iter = table.begin(); iter != table.end(); iter++ )
    {
        wxImageHistogramEntry entry = iter->second;
        unsigned long value = entry.value;

        int countIndex = entry.index / (table.size() / 255.0);
        countValue[countIndex] += value;

        minValue = std::min<long>(minValue, value);
        maxValue = std::max<long>(maxValue, countValue[countIndex]);
    }

    const int kHistWidth = 256;
    const int kHistHeight = 256;
    wxImage histImage(kHistWidth, kHistHeight);
    histImage.SetRGB(wxRect(0, 0, kHistWidth, kHistHeight), 0, 0, 0);

    for (iter = table.begin(); iter != table.end(); iter++ )
    {
        wxImageHistogramEntry entry = iter->second;
        int row = static_cast<int>(entry.index / (table.size() / 255.0));
        if (row < 0) row = 0;
        if (row >= kHistWidth) row = kHistWidth - 1;
        int col = (maxValue > 0)
                    ? static_cast<int>(countValue[row] / (maxValue / 255.0))
                    : 0;
        if (col < 0) col = 0;
        if (col >= kHistHeight) col = kHistHeight - 1;
        for (int barCol = col; barCol >= 0; --barCol)
        {
            histImage.SetRGB(row, kHistHeight - 1 - barCol, 255, 255, 255);
        }
    }

    delete[] countValue;

    // The original debug-only code created a new OpenPaintMDIChildFrame and
    // called Paste() on it without ever showing it, leaking both the frame
    // and the wxGenericDragImage inside Paste. Show the frame instead so the
    // histogram is actually visible and doesn't leak.
    OpenPaintMDIChildFrame *newFrame = new OpenPaintMDIChildFrame(this, wxID_ANY, wxT("Histogram"), kHistWidth, kHistHeight);
    newFrame->Show();
    wxLogDebug("count:%d min:%d max:%d", static_cast<int>(table.size()), minValue, maxValue);
    (void)histImage; // histogram bitmap would be drawn here in a future pass
}

void SubMainFrame::OnFullscreen( wxCommandEvent& event )
{
    ShowFullScreen(event.IsChecked(), wxFULLSCREEN_NOBORDER |  wxFULLSCREEN_NOCAPTION );
}

//****************Image************************

void SubMainFrame::OnFlipHorizontal( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->FlipHorizontal();
}

void SubMainFrame::OnFlipVertical( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->FlipVertical();
}

void SubMainFrame::OnRotate( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->Rotate();
}

void SubMainFrame::OnImageSize( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        SubImageSizeDialog imageSizeDialog(this, childFrame->GetWidth(), childFrame->GetHeight());
        if ( imageSizeDialog.ShowModal() == wxID_OK )
        {
            childFrame->Rescale(imageSizeDialog.GetWidth(), imageSizeDialog.GetHeight());
        }
    }
}

void SubMainFrame::OnCanvasSize( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        SubCanvasSizeDialog canvasSizeDialog(this, childFrame->GetWidth(), childFrame->GetHeight());
        if ( canvasSizeDialog.ShowModal() == wxID_OK )
        {
            childFrame->Resize(canvasSizeDialog.GetWidth(), canvasSizeDialog.GetHeight(), canvasSizeDialog.GetOffsetX(), canvasSizeDialog.GetOffsetY());
        }
    }
}


//****************TOOLS************************

void SubMainFrame::OnPickColor( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnPickColor(event);
}

void SubMainFrame::OnPencil( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnPencil(event);
}

void SubMainFrame::OnBrush( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnBrush(event);
}

void SubMainFrame::OnFill( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnFill(event);
}

void SubMainFrame::OnEraser( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnEraser(event);
}

void SubMainFrame::OnMagnify( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnMagnify(event);
}

void SubMainFrame::OnSprayCan( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnSprayCan(event);
}

void SubMainFrame::OnLine( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnLine(event);
}

void SubMainFrame::OnCurve( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnCurve(event);
}

void SubMainFrame::OnRectangle( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnRectangle(event);
}

void SubMainFrame::OnEllipse( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnEllipse(event);
}

void SubMainFrame::OnRectangleRounded( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnRectangleRounded(event);
}

void SubMainFrame::OnPolygon( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnPolygon(event);
}

void SubMainFrame::OnSelectLasso( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnSelectLasso(event);
}

void SubMainFrame::OnSelect( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnSelect(event);
}

void SubMainFrame::OnText( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnText(event);
}

//****************Filters***********************

void SubMainFrame::OnInvertColors( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->InvertColors();
}

void SubMainFrame::OnBlur( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->Blur();
}

void SubMainFrame::OnPixelize( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->Pixelize();
}


void SubMainFrame::OnGreyscale( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->Greyscale();
}

void SubMainFrame::OnMonochrome( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    childFrame->Monochrome();
}

//****************Options***********************

void SubMainFrame::OnFont( wxCommandEvent& event )
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame )
    {
        wxFont nextFont = wxGetFontFromUser(childFrame, childFrame->GetFont(), wxT("Select Text Tool Font"));
        if(nextFont.IsOk())
        {
            childFrame->SetFont(nextFont);
        }
    }
}

void SubMainFrame::OnForeground( wxCommandEvent& event )
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetForeground(pToolManager->PickColor(pToolManager->GetForeground()));
}

void SubMainFrame::OnBackground( wxCommandEvent& event )
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetBackground(pToolManager->PickColor(pToolManager->GetBackground()));
}

//********************************************

void SubMainFrame::OnNewFile320( wxCommandEvent& event )
{
    //Create a new file
    NewFile(320, 240);
    event.Skip();
}

void SubMainFrame::OnNewFile640( wxCommandEvent& event )
{
    //Create a new file
    NewFile(640, 480);
    event.Skip();
}

void SubMainFrame::OnNewFile( wxCommandEvent& event )
{
    //Create a new file
    NewFile();
    event.Skip();
}

void SubMainFrame::OnNewFile1024( wxCommandEvent& event )
{
    //Create a new file
    NewFile(1024, 768);
    event.Skip();
}

void SubMainFrame::OnOpenFile( wxCommandEvent& event )
{
    wxString strFilename = wxFileSelector(wxT("Choose an image to open"),wxT(""),wxT(""),wxT(""),  wxT("Image Files ") + wxImage::GetImageExtWildcard() );
    if ( !strFilename.empty() )
    {
        //Open the file for global usage
        OpenFile(strFilename.c_str());
    }
    //else: cancelled by user    
    event.Skip();
}


void SubMainFrame::OnSave( wxCommandEvent& event )
{ 
    SaveFile();
    event.Skip();
}

void SubMainFrame::OnSaveAs( wxCommandEvent& event )
{
    SaveAs();
    event.Skip();
}

void SubMainFrame::OnSize(wxSizeEvent& event) {

    event.Skip();
}

void SubMainFrame::OnClose( wxCloseEvent& event )
{
    // Persist the config while the app is still in a healthy state. The
    // destructor also calls Save(), but the AUI/MDI teardown path on this
    // platform can crash before OnExit()/~Globals() runs, so writing the
    // file here guarantees settings are not lost.
    Globals::Instance()->GetConfig()->Save();

    // Close every MDI child up front. The base wxAuiMDIParentFrame
    // destructor tears the wxAuiNotebook down before the MDI children
    // run, and each MDI child's destructor then tries to remove its
    // page from the now-defunct notebook, which segfaults inside
    // wxAuiNotebook::RemoveEmptyTabFrames on Linux GTK. Closing them
    // here (while the notebook is still healthy) avoids the race.
    // GetActiveChild() only returns the focused tab, and the MDI
    // children are pages of the wxAuiNotebook rather than direct
    // children of the client window, so walk the notebook's pages to
    // catch every MDI child including ones that were created but never
    // activated.
    if (wxAuiNotebook* notebook = this->GetNotebook())
    {
        const size_t pageCount = notebook->GetPageCount();
        for (size_t i = pageCount; i > 0; --i)
        {
            OpenPaintMDIChildFrame* child =
                wxDynamicCast(notebook->GetPage(i - 1),
                              OpenPaintMDIChildFrame);
            if (child && !child->Close())
            {
                child->Destroy();
            }
        }
    }

    // Hide the window synchronously so it disappears the instant the user
    // clicks close. Destroy() is deferred to the next idle event, and the
    // config save in OnExit() runs after the frame is gone — without Hide()
    // the user would see the frame sit there until all of that completed.
    this->Hide();

    // No Veto() — Shutdown() will Destroy() the frame. Vetoing and then
    // destroying leaves wx in an inconsistent state and can produce warnings.
    // OnExit() owns Globals teardown (saves config.xml once).
    Shutdown();
}

void SubMainFrame::OnExit( wxCommandEvent& event )
{
    event.Skip();
    this->Hide();
    Shutdown();
}

#include <wx/aboutdlg.h>
#include <wx/generic/aboutdlgg.h>
#include <wx/stdpaths.h>
#include <wx/file.h>
void SubMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;

    info.SetName(wxT("OpenPaint"));
    info.SetVersion(wxT("2.0.0"));
    info.SetDescription(wxT("The open alternative to classic painting."));
    info.SetCopyright(wxT("(C) 2007-2026 OpenPaint"));
    info.AddDeveloper(wxT("OpenPaint"));
    info.SetWebSite(wxT("http://github.com/murdockq/openpaint"));
    {
        wxFileName licensePath(wxStandardPaths::Get().GetExecutablePath());
        licensePath.SetFullName("LICENSE");
        wxString licenseText;
        wxFile file(licensePath.GetFullPath(), wxFile::read);
        if (file.IsOpened())
        {
            const size_t len = file.Length();
            std::vector<char> buf(len + 1);
            file.Read(buf.data(), len);
            buf[len] = '\0';
            licenseText = wxString::FromUTF8(buf.data(), len);
        }
        if (licenseText.IsEmpty())
        {
            licenseText = wxT("MIT License - see LICENSE file");
        }
        info.SetLicense(licenseText);
    }

    wxAboutBox(info);
}

void SubMainFrame::NewFile(int width, int height)
{
    OpenPaintMDIChildFrame *childFrame = new OpenPaintMDIChildFrame(this, wxID_ANY, wxT("New"), width, height);
}

void SubMainFrame::OpenFile(wxString strFilename)
{
    OpenPaintMDIChildFrame *childFrame = new OpenPaintMDIChildFrame(this, wxID_ANY, wxFileNameFromPath(strFilename));
    if(childFrame && childFrame->Open(strFilename))
    {
        AddFileToHistory(strFilename);
        wxLogDebug(wxT("Opened file: %s") , strFilename);
    }
}

bool SubMainFrame::SaveFile()
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if (!childFrame)
    {
        return false;
    }

    wxString strFilename = childFrame->GetFilename();

    if(strFilename.empty())
    {
        return SaveAs();
    }
    else if(childFrame->Save())
    {
        AddFileToHistory(strFilename);
        wxLogDebug(wxT("Saved as file: %s") , strFilename);
        return true;
    }
    return false;
}

bool SubMainFrame::SaveAs()
{
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();

    if(childFrame)
    {
        wxFileName fileName(childFrame->GetFilename());
        const wxString wildcards = wxT("Image Files ") + wxImage::GetImageExtWildcard();
        wxString strFilename = wxFileSelector(wxT("Choose a file to Save As"),wxT(""),wxT(""), fileName.GetExt(), wildcards, wxFD_SAVE);
        wxLogDebug(strFilename);

        // If the user did not include a recognised extension, append the
        // first supported one so the file is actually loadable later.
        if (!strFilename.empty())
        {
            wxFileName outName(strFilename);
            wxString ext = outName.GetExt().Lower();
            if (ext.IsEmpty())
            {
                // Use whatever the file used to have (e.g. ".png") or fall
                // back to "png".
                if (!fileName.GetExt().IsEmpty())
                {
                    outName.SetExt(fileName.GetExt());
                }
                else
                {
                    outName.SetExt(wxT("png"));
                }
                strFilename = outName.GetFullPath();
            }
        }

        if(!strFilename.empty() && childFrame->SaveAs(strFilename))
        {
            AddFileToHistory(strFilename);

            wxLogDebug(wxT("Saved as file: %s") , strFilename);

            return true;
        }
    }
    return false;
}

void SubMainFrame::SetMenuBar(wxMenuBar* menuBar)
{
    //Hack: Do nothing in sub main frame for set menu bar because linux AUIMDIChild removes menu when closing
}

void SubMainFrame::Shutdown()
{
    this->Destroy();
}

