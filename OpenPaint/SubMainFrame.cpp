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

#include "SubMainFrame.h"
#include "Globals.h"
#include "OpenPaintMDIChildFrame.h"
#include "SubToolPanel.h"
#include "SubColorPanel.h"
#include "SubCanvasSizeDialog.h"
#include "SubImageSizeDialog.h"
#include "ToolManager.h"

#include <limits>

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
            if(filenames.GetCount() == 1)
            {
                if(wxMatchWild(wxT("*.*"), filenames.Last()))
                {
                    Globals::Instance()->GetMainFrame()->OpenFile(filenames.Last());
                }
                else
                {
                    wxLogError(wxT("Invalid File."));
                }
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
    EVT_SIZE(SubMainFrame::OnSize)
END_EVENT_TABLE()

SubMainFrame::SubMainFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style )
:
MainFrame( parent, id, title, pos, size, style )
{

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
    
}

void SubMainFrame::Init()
{
    m_mAuiManager = new wxAuiManager(this);

    wxAuiMDIClientWindow* client_window = this->GetClientWindow();

    wxASSERT_MSG(client_window, wxT("Client window is NULL!"));

    m_mAuiManager->AddPane(client_window,
                wxAuiPaneInfo().Name(wxT("client_mdiclient")).
                CenterPane().PaneBorder(false));

    //client_window->AddPage(sourcePanel, wxT("Pane Caption"));

    GetToolBar()->EnableTool(wxID_UNDO, false);
    GetToolBar()->EnableTool(wxID_REDO, false);

    SubToolPanel * panelTool = new SubToolPanel(this);
    m_mAuiManager->AddPane(panelTool, wxLEFT, wxT("Tools"));
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
        
        //Add the recent history to the menu
        for(int i = 0; i < iHistorySize && i < listFileHistory.size(); i++)
        {
            //Add the previous files to the menu for opening
            wxMenuItem* menuItemTest = new wxMenuItem( m_menuRecentImages, IDX_MENU_HISTORYOPEN + i, wxString( listFileHistory.at(i).c_str(), wxConvLocal ), wxT("Open this file."), wxITEM_NORMAL );
            m_menuRecentImages->Insert(0,menuItemTest);
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
        if(strFilename == wxString((*iter).c_str(), wxConvLocal))
        {
            listFileHistory.erase(iter);
            break;
        }
    }
    listFileHistory.push_back(strFilename.ToStdString());

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
            OpenFile(wxString((*iter).c_str(), wxConvLocal));
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
        wxString filename = wxString(listFileHistory.at(iHistoryIndex).c_str(), wxConvLocal);
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
    Globals::Instance()->GetToolPanel()->Show(event.IsChecked());
    if(event.IsChecked())
    {
        m_mAuiManager->AddPane(Globals::Instance()->GetToolPanel(),wxLEFT, wxT("Tools"));
    }
    else
    {
        m_mAuiManager->DetachPane(Globals::Instance()->GetToolPanel());
    }
    m_mAuiManager->Update();
}

void SubMainFrame::OnColorWindow( wxCommandEvent& event )
{
    Globals::Instance()->GetColorPanel()->Show(event.IsChecked());
    if(event.IsChecked())
    {
        m_mAuiManager->AddPane(Globals::Instance()->GetColorPanel(),wxBOTTOM, wxT("Colors"));
    }
    else
    {
        m_mAuiManager->DetachPane(Globals::Instance()->GetColorPanel());
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

#ifdef _DEBUG //Testing histgram image creation
    OpenPaintMDIChildFrame *childFrame = (OpenPaintMDIChildFrame *)this->GetActiveChild();
    if(childFrame)
    {
        //Only work on luminence for now
        wxImage image = childFrame->GetImage();//.ConvertToGreyscale();
        
        //This table is how the table mapped.
        //Key as color "unsigned long RGB" ???
        //Entry.index as index with range 0 to size-1 (is it linear?)
        //Entry.value as count of pixels with that color

        wxImageHistogram table;
        image.ComputeHistogram(table);
        wxImageHistogram::iterator iter;

        long minValue= std::numeric_limits<long>::max();
        long maxValue = std::numeric_limits<long>::min();
        unsigned long *countValue = new unsigned long[256];//col counts
        for (int i = 0; i < 256; ++i)
            countValue[i] = 0;

        char *test_bits = new char[8192];//8192
        for (int i = 0; i < 8192; ++i)
            test_bits[i] = 0x00;

        char test = 0x01;
        test = (test << 4);
        for( iter = table.begin(); iter != table.end(); iter++ )
        {
            unsigned long key = iter->first;
            wxImageHistogramEntry entry = iter->second;
            unsigned long value = entry.value;

            int countIndex = entry.index / (table.size() / 255.0);
            countValue[countIndex] += value;

            //int index = key;
            minValue = std::min<long>(minValue, value);
            maxValue = std::max<long>(maxValue, countValue[countIndex]);
            //int value = value.value % 256;
            //wxLogDebug("key:%d index:%d value:%d", key, value.index, value.value);
        }
    
        //int index = 0;
        //for(int row = 0; row < 3; row++)
        //{
        //    for(int col = 0; col < 3; col++)
        //    {
        //        index = col + (row*3);
        //    }
        //}

        for( iter = table.begin(); iter != table.end(); iter++ )
        {
            wxImageHistogramEntry entry = iter->second;

            double row = entry.index / (table.size() / 255.0);
            //double col = entry.value / ( (maxValue)/ 255.0);
            double col = countValue[(int)row] / ( (maxValue)/ 255.0);

            for(int barCol = col; barCol >= 0; barCol--)
            {
                //barCol = barCol;
                int index = ((255-barCol) * 256) + row;
                int realIndex = index/8;
                //test_bits[realIndex] |= 0x80 >> (index % 8);
                test_bits[realIndex] |= 0x01 << (index % 8);
                //test_bits[index] ^= 0xff;
                    //entry.value;
            }
        }

        //test_bits[33] |= 0x80 ;//>> (index % 8);
    
        //invert
        //b ^= 0xFF

        wxBitmap bitmapHistogram(test_bits,256,256);
        OpenPaintMDIChildFrame *newFrame = new OpenPaintMDIChildFrame(this, wxID_ANY, wxT("Histogram"), 256, 256);
        newFrame->Paste(bitmapHistogram);
        delete [] countValue;
        delete [] test_bits;
        wxLogDebug("count:%d min:%d max:%d", table.size(), minValue, maxValue);
    }
#endif
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

void SubMainFrame::OnPolyline( wxCommandEvent& event )
{
    Globals::Instance()->GetToolPanel()->OnPolyline(event);
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
    pToolManager->SetForeground(pToolManager->PickColor());
}

void SubMainFrame::OnBackground( wxCommandEvent& event )
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    pToolManager->SetBackground(pToolManager->PickColor());
}

//********************************************

void SubMainFrame::OnNewFile320( wxCommandEvent& event )
{
    //Create a new file
    NewFile(320,240);
    event.Skip();
}

void SubMainFrame::OnNewFile640( wxCommandEvent& event )
{
    //Create a new file
    NewFile(640,480);
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
    NewFile(1024,768);
    event.Skip();
}

void SubMainFrame::OnOpenFile( wxCommandEvent& event )
{
    wxString strFilename = wxFileSelector(wxT("Choose an image to open"),"","","",  wxT("Image Files ") + wxImage::GetImageExtWildcard() );
    if ( !strFilename.empty() )
    {
        //Open the file for global usage
        OpenFile(strFilename);
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
    event.Veto();
    Shutdown();
}

void SubMainFrame::OnExit( wxCommandEvent& event )
{
    event.Skip();
    Shutdown();
}

#include <wx/aboutdlg.h>
#include <wx/generic/aboutdlgg.h>
void SubMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;

    info.SetName(wxT("OpenPaint"));
    info.SetVersion(wxT("1.1 Beta"));
    info.SetDescription(wxT("The open alternative to propriatry painting."));
    info.SetCopyright(wxT("(C) 2009 Steven Jedlicka"));
    info.AddDeveloper(wxT("Steven Jedlicka"));
    info.SetWebSite(wxT("http://www.openpaint.org"));
    info.SetLicense(wxString::FromAscii(
         "OpenPaint\n"
         "www.sourceforge.net/projects/openpaint\n"
         "\n"
         "Copyright (C) 2009, Steven Jedlicka\n"
         "\n"
         "This program is free software; you can redistribute it and/or\n"
         "modify it under the terms of the GNU General Public License\n"
         "as published by the Free Software Foundation; either version 2\n"
         "of the License, or (at your option) any later version.\n"
         "\n"
         "This program is distributed in the hope that it will be useful,\n"
         "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
         "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
         "GNU General Public License for more details.\n"
         "\n"
         "You should have received a copy of the GNU General Public License\n"
         "along with this program; if not, write to the Free Software\n"
         "Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n"
        ));

    wxAboutBox(info);
}

void SubMainFrame::NewFile(int height, int width)
{
    OpenPaintMDIChildFrame *childFrame = new OpenPaintMDIChildFrame(this, wxID_ANY, wxT("New"), height, width);
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

    wxString strFilename = childFrame->GetFilename();

    if(strFilename.empty())
    {
        SaveAs();
    }
    else if(childFrame && childFrame->Save())
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
        wxString strFilename = wxFileSelector(wxT("Choose a file to Save As"),"","", fileName.GetExt(), wxT("Image Files ") + wxImage::GetImageExtWildcard() , wxFD_SAVE);
        wxLogDebug(strFilename);
        
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
    delete Globals::Instance();
    this->Destroy();
}
