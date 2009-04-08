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

#include "Globals.h"
#include "OpenPaintMDIChildFrame.h"

#include "ToolManager.h"
#include "SubMainFrame.h"
#include <wx/dcclient.h>
#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/textdlg.h>
#include <wx/dcmemory.h>
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>

BEGIN_EVENT_TABLE(OpenPaintMDIChildFrame, wxAuiMDIChildFrame)
    EVT_CLOSE           (             OpenPaintMDIChildFrame::OnClose)
    //EVT_IDLE            (             OpenPaintMDIChildFrame::OnIdle)
    EVT_PAINT           (             OpenPaintMDIChildFrame::OnPaint)
    EVT_SCROLLWIN       (             OpenPaintMDIChildFrame::OnScroll)
    EVT_SIZE            (             OpenPaintMDIChildFrame::OnSize)
    EVT_MOTION          (             OpenPaintMDIChildFrame::OnMouse)
    EVT_LEFT_DOWN       (             OpenPaintMDIChildFrame::OnMouse)
    EVT_LEFT_UP         (             OpenPaintMDIChildFrame::OnMouse)
    EVT_LEFT_DCLICK     (             OpenPaintMDIChildFrame::OnMouse)
    EVT_RIGHT_DOWN      (             OpenPaintMDIChildFrame::OnMouse)
    EVT_RIGHT_UP        (             OpenPaintMDIChildFrame::OnMouse)
    EVT_RIGHT_DCLICK    (             OpenPaintMDIChildFrame::OnMouse) 
    EVT_MOUSEWHEEL      (             OpenPaintMDIChildFrame::OnMouseWheel)
    EVT_ERASE_BACKGROUND(             OpenPaintMDIChildFrame::OnEraseBackground)
END_EVENT_TABLE()

OpenPaintMDIChildFrame::OpenPaintMDIChildFrame( wxAuiMDIParentFrame* parent, int id, wxString title, int iWidth, int iHeight)
:
wxAuiMDIChildFrame( parent, id, title)
{
    m_Image = wxImage(iWidth, iHeight);
    m_Image.SetRGB(wxRect(0,0,iWidth,iHeight), 255,255,255);
    m_Bitmap = wxBitmap(m_Image);
    SetThumbIcon();
    m_HistoryIndex = 0;

    SetZoom(1.0);
    m_ScrollOrigin = wxPoint(0,0);
    m_status = MOUSE_NOACTION;

    m_bHasSelection = false;
    m_iSelectionOriginX = -1;
    m_iSelectionOriginY = -1;
    m_iSelectionWidth = -1;
    m_iSelectionHeight = -1;
    m_iSelectionMoveX = -1;
    m_iSelectionMoveY = -1;
    m_DragImage = NULL;


}

OpenPaintMDIChildFrame::~OpenPaintMDIChildFrame()
{

}

void OpenPaintMDIChildFrame::Shutdown()
{
    this->Destroy();
}

bool OpenPaintMDIChildFrame::Open(wxString strFilename)
{
    if(m_Image.LoadFile(strFilename))
    {
        m_strFilename = strFilename;
        this->SetTitle(wxFileNameFromPath(strFilename));
        SetThumbIcon();
        m_Bitmap = wxBitmap(m_Image);
        SetZoom(1.0);
        Refresh(false);
        return true;
    }
    return false;
}

bool OpenPaintMDIChildFrame::Save()
{
    if(m_Image.SaveFile(m_strFilename))
    {
        wxLogDebug("File Saved.");
        return true;
    }
    return false;
}

bool OpenPaintMDIChildFrame::SaveAs(wxString strFilename)
{
    if(m_Image.SaveFile(strFilename))
    {
        m_strFilename = strFilename;
        wxLogDebug("File Saved As.");
        this->SetTitle(wxFileNameFromPath(strFilename));
        return true;
    }
    return false;
}

wxString OpenPaintMDIChildFrame::GetFilename()
{
    return m_strFilename;
}

void OpenPaintMDIChildFrame::SetImage(wxImage image)
{
    //Update undo menu
    SubMainFrame * pMainFrame = Globals::Instance()->GetMainFrame();
    wxMenu *editMenu = pMainFrame->GetMenuBar()->GetMenu(1);
    wxMenuItem * undoItem = editMenu->FindItem(wxID_UNDO, NULL);
    undoItem->Enable(true);
    pMainFrame->GetToolBar()->EnableTool(wxID_UNDO, true);
    
    if(m_HistoryIndex != 0)
    {
        wxMenuItem * redoItem = editMenu->FindItem(wxID_REDO, NULL);
        redoItem->Enable(false);
        pMainFrame->GetToolBar()->EnableTool(wxID_REDO, false);

        while( m_HistoryIndex != 0)
        {
            m_LastImages.pop_back();
            m_HistoryIndex--;
        }
    }

    while(m_LastImages.size() > 3)
    {
        m_LastImages.erase(m_LastImages.begin());
    }

    m_LastImages.push_back(m_Image);

    m_Image = image;
    
    m_bImageUpdated = true;

    SetThumbIcon();
}

//Set title thumbnail icon
void OpenPaintMDIChildFrame::SetThumbIcon()
{
    wxIcon iconThumb; 
    iconThumb.CopyFromBitmap(wxBitmap(m_Image.Scale(22, 22,wxIMAGE_QUALITY_HIGH)));
    SetIcon(iconThumb);
}

void OpenPaintMDIChildFrame::SetZoom(double dZoom)
{
    m_dZoom = dZoom;

    // Send Size Event
    wxSizeEvent sizeEvent( GetSize(), GetId() );
    GetEventHandler()->ProcessEvent( sizeEvent );
    Refresh();
}

void OpenPaintMDIChildFrame::OnClose(wxCloseEvent& event)
{
    event.Veto();
    wxLogDebug("OnClose");
    this->Shutdown();
}

void OpenPaintMDIChildFrame::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    //wxLogDebug("Painting");
    wxPaintDC dc(this);
   
    int width = m_Bitmap.GetWidth();
    int height = m_Bitmap.GetHeight();

    double zoom = m_dZoom;
    int w, h;
    GetClientSize(&w, &h);


    dc.SetUserScale(zoom,zoom);
    dc.DrawBitmap(m_Bitmap, m_ScrollOrigin.x/zoom, m_ScrollOrigin.y/zoom);
#ifndef  __WXGTK__
    //wxBitmap(m_Image.Scale(width*zoom, height*zoom))
    dc.SetPen(*wxGREY_PEN);
    dc.SetBrush(*wxGREY_BRUSH);
    //dc.DrawRectangle(width*zoom, 0, w-(width*zoom), height*zoom);
    //dc.DrawRectangle(0, height*zoom, w ,h-(height*zoom));
    dc.DrawRectangle(width, 0, (w/zoom)-width, height);
    dc.DrawRectangle(0, height, w/zoom ,(h/zoom));
#endif

#if 0
    //Creates anti-aliased view of image
    wxGraphicsContext *gc = wxGraphicsContext::Create(this);
    gc->DrawBitmap(m_Bitmap, m_ScrollOrigin.x, m_ScrollOrigin.y, width*zoom,height*zoom);
    gc->SetPen(*wxGREY_PEN);
    gc->SetBrush(*wxGREY_BRUSH);
    gc->DrawRectangle(width*zoom, 0, w-(width*zoom), height*zoom);
    gc->DrawRectangle(0, height*zoom, w ,h-(height*zoom));
#endif

}


//void OpenPaintMDIChildFrame::OnIdle(wxIdleEvent& event)
//{
    //ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    //if(pToolManager->GetSelectedTool()== TOOL_SPRAY_CAN)
    //{
    //    
    //}
//}

void OpenPaintMDIChildFrame::OnMouse(wxMouseEvent& event)
{
    wxInt32 i = (event.GetX()-m_ScrollOrigin.x)/m_dZoom;
    wxInt32 j = (event.GetY()-m_ScrollOrigin.y)/m_dZoom;

    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour fColor = pToolManager->GetForeground();
    wxColour bColor = pToolManager->GetBackground();

    if(m_bHasSelection)
    {
        //Check if selection is clicked
        if(i >= m_iSelectionOriginX  && i < m_iSelectionOriginX+ m_iSelectionWidth 
            && j >= m_iSelectionOriginY && j < m_iSelectionOriginY+ m_iSelectionHeight)
        {
            if(event.LeftDown())//&& !m_DragImage)
            {
                m_iSelectionMoveX = i - m_iSelectionOriginX;
                m_iSelectionMoveY = j - m_iSelectionOriginY;
                m_DragImage = new wxGenericDragImage(wxBitmap(m_SelectedBitmap.ConvertToImage().Scale(m_iSelectionWidth*m_dZoom, m_iSelectionHeight*m_dZoom)));
                m_DragImage->BeginDrag(wxPoint(m_iSelectionMoveX*m_dZoom, m_iSelectionMoveY*m_dZoom), this);
                m_DragImage->Move(wxPoint(i,j));
                m_DragImage->Show();
                return;
            }
        }
        else //outside of selection
        {
            if(event.LeftDown() && m_DragImage)
            {
                m_DragImage->EndDrag();
                delete m_DragImage;
                m_DragImage = NULL;

                //Clear Selection Tool
                SelectTool(i,j, MOUSE_BEGIN_DRAWING);
                SelectTool(i,j, MOUSE_FINISHED_DRAWING);

                m_bHasSelection = false;

                wxMemoryDC memDC;
                memDC.SelectObject(m_Bitmap);
                memDC.DrawBitmap(m_SelectedBitmap, m_iSelectionOriginX, m_iSelectionOriginY);
                SetImage(m_Bitmap.ConvertToImage());
                Refresh();
                return;
            }
            
        }

        //Dragging selection
        if(event.LeftIsDown() && m_DragImage)
        {
            m_DragImage->Move(wxPoint(i*m_dZoom,j*m_dZoom));
            return;
        }

        if(event.LeftUp())
        {
            m_iSelectionOriginX = i - m_iSelectionMoveX;
            m_iSelectionOriginY = j - m_iSelectionMoveY;
            return;
        }

        wxLogDebug("hasselection %d, %d" , i ,j);
        return;
    }


    
    if(this != wxWindow::FindFocus())
    {
        //Get focus on mouse enter for mouse wheel events
        this->SetFocus();

        if(pToolManager->GetSelectedTool() == TOOL_SELECT)
        {
            this->SetCursor(*wxCROSS_CURSOR);
        }
        else
        {
            this->SetCursor(*wxSTANDARD_CURSOR);
        }

    }

    // was it pressed just now?
    if (event.LeftDown())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_SELECT:
                SelectTool(i,j, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_PICK_COLOR:
                PickColorTool(i,j, true);
                break;
            case TOOL_PENCIL:
                PencilTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
                break;                
            case TOOL_FILL:
                FillTool(i,j, fColor);
                break;
            case TOOL_ERASER:
                PencilTool(i,j, bColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_MAGNIFY:
                MagnifyTool();
                break;
            case TOOL_SPRAY_CAN:
                SprayCanTool(i,j, fColor);
                break;
            case TOOL_ELLIPSE:
                EllipseTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_RECTANGLE:
                RectangleTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_RECTANGLE_ROUNDED:
                RectangleTool(i,j, fColor, MOUSE_BEGIN_DRAWING, true);
                break;
            case TOOL_TEXT:
                TextTool(i,j, fColor);
                break;
                
        }
    }
    // is the button down?
    else if (event.LeftIsDown())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_SELECT:
                SelectTool(i,j, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_PENCIL:
                PencilTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
                break; 
            case TOOL_ERASER:
                PencilTool(i,j, bColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_SPRAY_CAN:
                SprayCanTool(i,j, fColor);
                break;
            case TOOL_ELLIPSE:
                EllipseTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_RECTANGLE:
                RectangleTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_RECTANGLE_ROUNDED:
                RectangleTool(i,j, fColor, MOUSE_CONTINUE_DRAWING, true);
                break;
        }
    }
    else if(event.LeftUp())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_PENCIL:
                PencilTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_SELECT:
                SelectTool(i,j, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_ELLIPSE:
                EllipseTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_RECTANGLE:
                RectangleTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_RECTANGLE_ROUNDED:
                RectangleTool(i,j, fColor, MOUSE_FINISHED_DRAWING, true);
                break;
        }
    }
    // was it pressed just now?
    else if (event.RightDown())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_PICK_COLOR:
                PickColorTool(i,j, false);
                break;
            case TOOL_PENCIL:
                PencilTool(i,j, bColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, bColor, MOUSE_BEGIN_DRAWING);
                break; 
            case TOOL_FILL:
                FillTool(i,j, bColor);
                break;
            case TOOL_MAGNIFY:
                MagnifyTool();
                break;
            case TOOL_SPRAY_CAN:
                SprayCanTool(i,j, bColor);
                break;
        }
    
    }
    // is the button down?
    else if (event.RightIsDown())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_PENCIL:
                PencilTool(i,j, bColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, bColor, MOUSE_CONTINUE_DRAWING);
                break; 
            case TOOL_SPRAY_CAN:
                SprayCanTool(i,j, bColor);
                break;
        }
    }
    else if(event.RightUp())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_PENCIL:
                PencilTool(i,j, bColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_BRUSH:
                BrushTool(i,j, bColor, MOUSE_FINISHED_DRAWING);
                break; 
        }
    }
    
}

void OpenPaintMDIChildFrame::OnMouseWheel(wxMouseEvent& event)
{
    if(event.GetEventType() == wxEVT_MOUSEWHEEL)
    {
        if(event.GetWheelRotation() > 0)
        {
            if(GetZoom() < 8.0)
            {
                SetZoom(GetZoom() * 2.0);
            }
        }
        else
        {
             if(GetZoom() > 0.2)
            {
                SetZoom(GetZoom() / 2.0);
            }
        }
        //#ifdef __WXGTK__
        //m_Bitmap = wxBitmap(m_Image.Scale(width*zoom, height*zoom);

        // Send Size Event
        wxSizeEvent sizeEvent( GetSize(), GetId() );
        GetEventHandler()->ProcessEvent( sizeEvent );
        Refresh();
    }
    event.Skip();
}

void OpenPaintMDIChildFrame::OnSize(wxSizeEvent& event)
{
    wxCoord w = event.GetSize().GetX();
    wxCoord h = event.GetSize().GetY();

    int scrollWidth = m_Image.GetWidth()*m_dZoom;
    int scrollHeight = m_Image.GetHeight()*m_dZoom;

    SetSize(scrollWidth,scrollHeight);
    //GetParent()->Fit();
    
    //TODO:HasScrollbar not returning true
    //if(HasScrollbar(wxVERTICAL))
    {
        scrollWidth += wxSystemSettings::GetMetric(wxSYS_VSCROLL_ARROW_X);
    }
    //if(HasScrollbar(wxHORIZONTAL))
    {
        scrollHeight += wxSystemSettings::GetMetric(wxSYS_HSCROLL_ARROW_Y);
    }
    SetScrollbar(wxHORIZONTAL, GetScrollPos(wxHORIZONTAL), w, scrollWidth);
    SetScrollbar(wxVERTICAL, GetScrollPos(wxVERTICAL), h, scrollHeight);

    if(w > m_Image.GetWidth()+scrollWidth)
    {
        m_ScrollOrigin.x = 0;
    }
    else
    {
        m_ScrollOrigin.x = -GetScrollPos(wxHORIZONTAL);
    }

    if(h > m_Image.GetHeight()+scrollHeight)
    {
        m_ScrollOrigin.y = 0;
    }
    else
    {
        m_ScrollOrigin.y = -GetScrollPos(wxVERTICAL);
    }

}

void OpenPaintMDIChildFrame::OnScroll(wxScrollWinEvent& event)
{
    WXTYPE type = (WXTYPE)event.GetEventType();
    int pos     = event.GetPosition();
    int orient  = event.GetOrientation();

    // calculate scroll increment
    /*int scrollinc = 0;
    if (type == wxEVT_SCROLLWIN_TOP)
    {
        if (orient == wxHORIZONTAL)
            scrollinc = -m_viewportW;
        else
            scrollinc = -m_viewportH;
    }
    else
    if (type == wxEVT_SCROLLWIN_BOTTOM)
    {
        if (orient == wxHORIZONTAL)
            scrollinc = m_viewportW;
        else
            scrollinc = m_viewportH;
    }
    else
    if (type == wxEVT_SCROLLWIN_LINEUP)
    {
        scrollinc = -1;
    }
    else
    if (type == wxEVT_SCROLLWIN_LINEDOWN)
    {
        scrollinc = +1;
    }
    else
    if (type == wxEVT_SCROLLWIN_PAGEUP)
    {
        scrollinc = -10;
    }
    else
    if (type == wxEVT_SCROLLWIN_PAGEDOWN)
    {
        scrollinc = +10;
    }
    else
    if (type == wxEVT_SCROLLWIN_THUMBTRACK)
    {
        if (orient == wxHORIZONTAL)
        {
            scrollinc = pos - m_thumbX;
            m_thumbX = pos;
        }
        else
        {
            scrollinc = pos - m_thumbY;
            m_thumbY = pos;
        }
    }
    else
    if (type == wxEVT_SCROLLWIN_THUMBRELEASE)
    {
        m_thumbX = m_viewportW;
        m_thumbY = m_viewportH;
    }


    if (scrollinc == 0) return;

    // scroll the window and adjust the viewport
    if (orient == wxHORIZONTAL)
    {
        m_viewportX -= scrollinc;
        ScrollWindow( -m_cellsize * scrollinc, 0, (const wxRect *) NULL);
    }
    else
    {
        m_viewportY -= scrollinc;
        ScrollWindow( 0, -m_cellsize * scrollinc, (const wxRect *) NULL);
    }
*/
    if (orient == wxHORIZONTAL)
    {
        m_ScrollOrigin.x = -pos;
        //ScrollWindow( 5, 0, (const wxRect *) NULL);
        SetScrollPos(wxHORIZONTAL, abs(m_ScrollOrigin.x) );
    }
    else
    {
        m_ScrollOrigin.y = -pos;
        //ScrollWindow( 0, 5, (const wxRect *) NULL);
        SetScrollPos(wxVERTICAL, abs(m_ScrollOrigin.y) );
    }
    Refresh(false);
    
}

void OpenPaintMDIChildFrame::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
    //Do not erase the background
}

int OpenPaintMDIChildFrame::GetWidth()
{
    return m_Image.GetWidth();
}

int OpenPaintMDIChildFrame::GetHeight()
{
    return m_Image.GetHeight();
}

void OpenPaintMDIChildFrame::Undo()
{
    //Update redo menu
    SubMainFrame * pMainFrame = Globals::Instance()->GetMainFrame();
    wxMenu *editMenu = pMainFrame->GetMenuBar()->GetMenu(1);
    wxMenuItem * redoItem = editMenu->FindItem(wxID_REDO, NULL);
    redoItem->Enable(true);
    pMainFrame->GetToolBar()->EnableTool(wxID_REDO, true);

    if(m_HistoryIndex == 0 && m_bImageUpdated)
    {
        m_bImageUpdated = false;
        m_LastImages.push_back(m_Image);
    }

    m_HistoryIndex++;

    m_Image = m_LastImages.at(m_LastImages.size()-m_HistoryIndex-1);
    SetThumbIcon();
    m_Bitmap =  wxBitmap(m_Image);
    Refresh();

    if(m_HistoryIndex >= m_LastImages.size()-1)
    {
        wxMenuItem * undoItem = editMenu->FindItem(wxID_UNDO, NULL);
        undoItem->Enable(false);
        pMainFrame->GetToolBar()->EnableTool(wxID_UNDO, false);
        return;
    }
    
}

void OpenPaintMDIChildFrame::Redo()
{
    //Update redo menu
    SubMainFrame * pMainFrame = Globals::Instance()->GetMainFrame();
    wxMenu *editMenu = pMainFrame->GetMenuBar()->GetMenu(1);
    wxMenuItem * undoItem = editMenu->FindItem(wxID_UNDO, NULL);
    undoItem->Enable(true);
    pMainFrame->GetToolBar()->EnableTool(wxID_UNDO, true);

    m_HistoryIndex--;

    m_Image = m_LastImages.at(m_LastImages.size()-m_HistoryIndex-1);
    SetThumbIcon();
    m_Bitmap =  wxBitmap(m_Image);
    Refresh();

    if(m_HistoryIndex <= 0)
    {
        wxMenuItem * redoItem = editMenu->FindItem(wxID_REDO, NULL);
        redoItem->Enable(false);
        pMainFrame->GetToolBar()->EnableTool(wxID_REDO, false);
        return;
    }
}

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(wxPoint, wxArrayPoints);
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayPoints);
wxArrayPoints drawLine;
int prevX = 0;
int prevY = 0;
wxPen customPen;
wxBrush customBrush;
wxBitmap OpenPaintMDIChildFrame::Cut()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    customPen = wxPen(bColor, 1, wxSOLID);
    customBrush = wxBrush(bColor, wxSOLID);
    
    wxMemoryDC memDC;
    memDC.SelectObject(m_Bitmap);
    memDC.SetPen(customPen);
    memDC.SetBrush(customBrush);
    memDC.DrawRectangle(m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight);
    SetImage(m_Bitmap.ConvertToImage());
    Refresh();

    wxBitmap m_TempBitmap = m_SelectedBitmap;
    //Clear the selection
    m_SelectedBitmap = wxBitmap();

    return m_TempBitmap;
}

wxBitmap OpenPaintMDIChildFrame::Copy()
{
    return m_SelectedBitmap;
}

void OpenPaintMDIChildFrame::Paste(wxBitmap bitmap)
{
    m_SelectedBitmap = bitmap;
    m_DragImage = new wxGenericDragImage(m_SelectedBitmap);
    m_DragImage->BeginDrag(wxPoint(0, 0), this);
    m_DragImage->Move(wxPoint(0,0));
    m_DragImage->Show();
    m_bHasSelection = true;
    
    //SetImage(m_Bitmap.ConvertToImage());
    //m_Image.ConvertAlphaToMask();
    //m_Bitmap =  wxBitmap(m_Image);
    //Refresh();
}

void OpenPaintMDIChildFrame::Delete()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    customPen = wxPen(bColor, 1, wxSOLID);
    customBrush = wxBrush(bColor, wxSOLID);
    
    wxMemoryDC memDC;
    memDC.SelectObject(m_Bitmap);
    memDC.SetPen(customPen);
    memDC.SetBrush(customBrush);
    memDC.DrawRectangle(m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight);
    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}

void OpenPaintMDIChildFrame::SelectAll()
{
    SelectTool(0,0, MOUSE_BEGIN_DRAWING);
    SelectTool(m_Image.GetWidth(),m_Image.GetHeight(), MOUSE_FINISHED_DRAWING);
}

void OpenPaintMDIChildFrame::Clear()
{
    wxImage clearImage = m_Image;
    clearImage.SetRGB(wxRect(0,0,m_Image.GetWidth(),m_Image.GetHeight()), 255,255,255);
    SetImage(clearImage);
    m_Bitmap =  wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::FillFGColor()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour fColor = pToolManager->GetForeground();
    wxImage clearImage = m_Image;
    clearImage.SetRGB(wxRect(0,0,m_Image.GetWidth(),m_Image.GetHeight()), fColor.Red(),fColor.Green(),fColor.Blue());
    SetImage(clearImage);
    m_Bitmap =  wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::FillBGColor()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();
    wxImage clearImage = m_Image;
    clearImage.SetRGB(wxRect(0,0,m_Image.GetWidth(),m_Image.GetHeight()), bColor.Red(),bColor.Green(),bColor.Blue());
    SetImage(clearImage);
    m_Bitmap =  wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::ZoomOut()
{
    if(GetZoom() > 0.2)
    {
        SetZoom(GetZoom()/2.0);
    }
}

void OpenPaintMDIChildFrame::ZoomIn()
{
    if(GetZoom() < 8.0)
    {
        SetZoom(GetZoom() * 2.0);
    }
}

void OpenPaintMDIChildFrame::NormalZoom()
{
    SetZoom(1.0);
}


void OpenPaintMDIChildFrame::FlipHorizontal()
{
    SetImage(m_Image.Mirror(true));
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::FlipVertical()
{
    SetImage(m_Image.Mirror(false));
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::Rotate()
{
    SetImage(m_Image.Rotate90());
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}


void OpenPaintMDIChildFrame::Rescale(int iWidth, int iHeight)
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    SetImage(m_Image.Rescale(iWidth,iHeight));
    m_Bitmap = wxBitmap(m_Image);

    // Send Size Event
    m_ScrollOrigin.x = 0;
    m_ScrollOrigin.y = 0;
    SetScrollPos(wxVERTICAL,0);
    SetScrollPos(wxHORIZONTAL,0);
    wxSizeEvent sizeEvent( GetSize(), GetId() );
    GetEventHandler()->ProcessEvent( sizeEvent );

    Refresh();
}

void OpenPaintMDIChildFrame::Resize(int iWidth, int iHeight, int iOffsetX, int iOffsetY)
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    SetImage(m_Image.Resize(wxSize( iWidth,iHeight), wxPoint(iOffsetX, iOffsetY), bColor.Red(), bColor.Green(), bColor.Blue()));
    m_Bitmap = wxBitmap(m_Image);

    // Send Size Event
    m_ScrollOrigin.x = 0;
    m_ScrollOrigin.y = 0;
    SetScrollPos(wxVERTICAL,0);
    SetScrollPos(wxHORIZONTAL,0);
    wxSizeEvent sizeEvent( GetSize(), GetId() );
    GetEventHandler()->ProcessEvent( sizeEvent );

    Refresh();
}

//void OpenPaintMDIChildFrame::InvertColors()
//{
//    m_Image.RotateHue(0.5);
//    m_Bitmap = wxBitmap(m_Image);
//    Refresh();
//}

void OpenPaintMDIChildFrame::InvertColors()
{
    wxMemoryDC mdc(m_Bitmap);
    mdc.SetLogicalFunction(wxINVERT);
    mdc.DrawRectangle(0,0, m_Image.GetWidth(), m_Image.GetHeight());

    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}

void OpenPaintMDIChildFrame::Blur()
{
    SetImage(m_Image.Blur(2));
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::Pixelize()
{
    int pixelWidth = 10;
    int pixelHeight = 10;

    //Another alternate way (moves pixels down and right though)
    //wxImage pixelImage = m_Image.Scale(m_Image.GetWidth()/pixelWidth, m_Image.GetHeight()/pixelHeight,wxIMAGE_QUALITY_HIGH);
    //SetImage(pixelImage.Scale(m_Image.GetWidth(), m_Image.GetHeight()));
    //m_Bitmap = wxBitmap(m_Image);
    //Refresh();

    wxImage pixelImage = m_Image;
    for(int x=0; x < m_Image.GetWidth(); x+=pixelWidth)
    {
        for(int y=0; y < m_Image.GetHeight(); y+=pixelHeight)
        {
            char red,green,blue;
            //This uses the center most pixel only
            //int center = (pixelWidth/2);
            //red = m_Image.GetRed(x+center,y+center);
            //green = m_Image.GetGreen(x+center,y+center);
            //blue = m_Image.GetBlue(x+center,y+center);

            //This computes avg color to be applied for pixel
            int avgCount = 0, redTotal = 0, greenTotal = 0, blueTotal = 0;
            for(int px=0; px < pixelWidth && x+px < m_Image.GetWidth(); px++)
            {
                for(int py=0; py < pixelHeight && y+py < m_Image.GetHeight(); py++)
                {
                    redTotal += m_Image.GetRed(x+px,y+py);
                    greenTotal += m_Image.GetGreen(x+px,y+py);
                    blueTotal += m_Image.GetBlue(x+px,y+py);
                    avgCount++;
                }
            }
            red = redTotal/avgCount;
            green = greenTotal/avgCount;
            blue = blueTotal/avgCount;


            pixelImage.SetRGB(wxRect(x, y, pixelWidth, pixelHeight ), red,green,blue);


        }
    }

    SetImage(pixelImage);
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

//void OpenPaintMDIChildFrame::Noise()
//{
//    wxImage noiseImage = m_Image;
//    for(int x=0; x < m_Image.GetWidth(); x++)
//    {
//        for(int y=0; y < m_Image.GetHeight(); y++)
//        {
//            char red,green,blue;
//            red = m_Image.GetRed(x,y);
//            green = m_Image.GetGreen(x,y);
//            blue = m_Image.GetBlue(x,y);
//
//
//            noiseImage.SetRGB(x, y, blue ,red, green);
//
//
//        }
//    }
//
//    SetImage(noiseImage);
//    m_Bitmap = wxBitmap(m_Image);
//    Refresh();
//}

void OpenPaintMDIChildFrame::Greyscale()
{
    SetImage(m_Image.ConvertToGreyscale());
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::Monochrome()
{
    wxImage monoImage = m_Image.ConvertToGreyscale();
    for(int x=0; x < m_Image.GetWidth(); x++)
    {
        for(int y=0; y < m_Image.GetHeight(); y++)
        {
            if(monoImage.GetRed(x,y) > 128)
            {
                monoImage.SetRGB(x, y, 255,255,255);
            }
        }
    }

    SetImage(monoImage.ConvertToMono(255,255,255));
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::PencilTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC mydc(this);
    mydc.SetUserScale(m_dZoom,m_dZoom);

    wxMemoryDC dc;
    dc.SelectObjectAsSource(m_Bitmap);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        drawLine.Clear();
        prevX = x;
        prevY = y;
    }
    customPen = wxPen(color, 1, wxSOLID);

    dc.SetPen(customPen);
    dc.DrawPoint(x,y);
    dc.DrawLine(x,y,prevX,prevY);

    drawLine.Add(wxPoint(x,y));
    prevX = x;
    prevY = y;

    mydc.Blit(m_ScrollOrigin.x/GetZoom(), m_ScrollOrigin.y/GetZoom(), m_Bitmap.GetWidth(), m_Bitmap.GetHeight(), &dc, 0, 0);

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC(m_Bitmap);
        memDC.SetPen(customPen);

        memDC.DrawPoint(x,y);

        for(int i = 0; i < drawLine.GetCount()-1; i++)
        {
            memDC.DrawLine(drawLine[i].x, drawLine[i].y, drawLine[i+1].x, drawLine[i+1].y);
        }

        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::FillTool(int x, int y, wxColour color)
{
    //FillTool(x,y,color,wxColour());
    wxColour colorOld(m_Image.GetRed(x, y),m_Image.GetGreen(x, y),m_Image.GetBlue(x, y));
    customBrush = wxBrush(color, wxSOLID);
    //can use
    //wxCROSSDIAG_HATCH
    //wxBDIAGONAL_HATCH

    wxMemoryDC mdc(m_Bitmap);
    mdc.SetBrush(customBrush);
    mdc.FloodFill(x,y, colorOld);

    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}

//Recursive fill function
void OpenPaintMDIChildFrame::FillTool(int x, int y, wxColour colorNew, wxColour colorOld)
{
    //Bounds check
    if(x < 0 || y < 0 || x >= m_Image.GetWidth() || y >= m_Image.GetHeight())
    {
        return;
    }

    //Get old color to replace
    if(!colorOld.IsOk())
    {
        colorOld.Set(m_Image.GetRed(x, y),m_Image.GetGreen(x, y),m_Image.GetBlue(x, y));
    }

    unsigned char red = m_Image.GetRed(x, y);
    unsigned char green = m_Image.GetGreen(x, y);
    unsigned char blue = m_Image.GetBlue(x, y);

    if(colorOld.Red() == red && colorOld.Green() == green && colorOld.Blue() == blue)
    {
        m_Image.SetRGB( x, y, colorNew.Red(), colorNew.Green(), colorNew.Blue());
        FillTool(x+1,y,colorNew,colorOld);
        //FillTool(x,y+1,colorNew,colorOld);
        //FillTool(x-1,y,colorNew,colorOld);
        //FillTool(x,y-1,colorNew,colorOld);
    }
}

void OpenPaintMDIChildFrame::PickColorTool(int x, int y, bool bIsForeground)
{
    wxColour colorPicked(m_Image.GetRed(x, y),m_Image.GetGreen(x, y),m_Image.GetBlue(x, y));
    
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    
    if(bIsForeground)
    {
        pToolManager->SetForeground(colorPicked);
    }
    else
    {
        pToolManager->SetBackground(colorPicked);
    }
}

void OpenPaintMDIChildFrame::MagnifyTool()
{
    if(GetZoom() == 1.0)
    {
        SetZoom(4.0);
    }
    else
    {
        SetZoom(1.0);
    }
}

int radius = 10;
void OpenPaintMDIChildFrame::BrushTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC mydc(this);
    mydc.SetUserScale(m_dZoom,m_dZoom);

    wxMemoryDC dc;
    dc.SelectObjectAsSource(m_Bitmap);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        drawLine.Clear();
        prevX = x;
        prevY = y;
    }
    customPen = wxPen(color, radius, wxSOLID);

    dc.SetPen(customPen);
    dc.DrawLine(x,y,prevX,prevY);

    drawLine.Add(wxPoint(x,y));
    prevX = x;
    prevY = y;

    mydc.Blit(m_ScrollOrigin.x/GetZoom(), m_ScrollOrigin.y/GetZoom(), m_Bitmap.GetWidth(), m_Bitmap.GetHeight(), &dc, 0, 0);

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC(m_Bitmap);
        memDC.SetPen(customPen);

        for(int i = 0; i < drawLine.GetCount()-1; i++)
        {
            memDC.DrawLine(drawLine[i].x, drawLine[i].y, drawLine[i+1].x, drawLine[i+1].y);
        }

        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::SprayCanTool(int x, int y, wxColour color)
{
    srand((unsigned)time(0)+x+y); 
    int random_integer1,random_integer2; 
    int lowest=-10, highest=10; 
    int range=(highest-lowest)+1; 
    for(int index=0; index<20; index++){ 
        random_integer1 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        random_integer2 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        m_Image.SetRGB(x+random_integer1, y+random_integer2, color.Red(), color.Green(), color.Blue());

    } 
    
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

int prevX2 = 0;
int prevY2 =0;
void OpenPaintMDIChildFrame::EllipseTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom,m_dZoom);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        prevX = x;
        prevY = y;
        prevX2 = x;
        prevY2 = y;
    }

    customPen = wxPen(color, 1, wxSOLID);
    dc.SetPen(customPen);

    //TODO:if solid box use background color
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    dc.SetLogicalFunction(wxINVERT);

    //Remove last draw Rectangle
    dc.DrawEllipse(prevX, prevY, -(prevX-prevX2), -(prevY-prevY2));

    //Add current rectangle
    dc.DrawEllipse(prevX, prevY, -(prevX-x), -(prevY-y));
    
    //Update previous rectangle second point
    prevX2 = x;
    prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC;
        memDC.SelectObject(m_Bitmap);
        memDC.SetPen(customPen);
        memDC.SetBrush(*wxTRANSPARENT_BRUSH);

        memDC.DrawEllipse(prevX, prevY, -(prevX-x), -(prevY-y));
        
        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::RectangleTool(int x, int y, wxColour color, MouseStatus drawState, bool bIsRounded)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom,m_dZoom);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        prevX = x;
        prevY = y;
        prevX2 = x;
        prevY2 = y;
    }

    customPen = wxPen(color, 1, wxSOLID);
    dc.SetPen(customPen);

    //TODO:if solid box use background color
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    dc.SetLogicalFunction(wxINVERT);

    if(bIsRounded)
    {
        //Remove last draw Rectangle
        dc.DrawRoundedRectangle(prevX, prevY, -(prevX-prevX2), -(prevY-prevY2), 10);

        //Add current rectangle
        dc.DrawRoundedRectangle(prevX, prevY, -(prevX-x), -(prevY-y), 10);
    }
    else
    {
        //Remove last draw Rectangle
        dc.DrawRectangle(prevX, prevY, -(prevX-prevX2), -(prevY-prevY2));

        //Add current rectangle
        dc.DrawRectangle(prevX, prevY, -(prevX-x), -(prevY-y));
    }
    
    //Update previous rectangle second point
    prevX2 = x;
    prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC;
        memDC.SelectObject(m_Bitmap);
        memDC.SetPen(customPen);
        memDC.SetBrush(*wxTRANSPARENT_BRUSH);

        if(bIsRounded)
        {
            memDC.DrawRoundedRectangle(prevX, prevY, -(prevX-x), -(prevY-y), 10);
        }
        else
        {
            memDC.DrawRectangle(prevX, prevY, -(prevX-x), -(prevY-y));
        }
        
        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::SelectTool(int x, int y, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom,m_dZoom);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        prevX = x;
        prevY = y;
        prevX2 = x;
        prevY2 = y;
    }

    dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetLogicalFunction(wxINVERT);

    //Remove last draw Rectangle
    dc.DrawRectangle(prevX, prevY, -(prevX-prevX2), -(prevY-prevY2));

    //Add current rectangle
    dc.DrawRectangle(prevX, prevY, -(prevX-x), -(prevY-y));
    
    //Update previous rectangle second point
    prevX2 = x;
    prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        if(prevX != x && prevY != y)//Make sure at least one pixel is selected
        {
            m_iSelectionOriginX = std::min(prevX,x);
            m_iSelectionOriginY = std::min(prevY,y);
            m_iSelectionWidth = abs(prevX-x);
            m_iSelectionHeight = abs(prevY-y);
            m_SelectedBitmap = m_Bitmap.GetSubBitmap(wxRect(m_iSelectionOriginX, m_iSelectionOriginY , m_iSelectionWidth, m_iSelectionHeight)) ;

            m_iSelectionMoveX = m_iSelectionOriginX;
            m_iSelectionMoveY = m_iSelectionOriginY;

            m_bHasSelection = true;
        }
    }
}

void OpenPaintMDIChildFrame::TextTool(int x, int y, wxColour color)
{
    wxString strText = wxGetTextFromUser(wxT("Write text."));

    wxMemoryDC mdc(m_Bitmap);
    wxGraphicsContext* gc = wxGraphicsContext::Create(mdc);
    //wxFont wxGetFontFromUser(wxWindow *parent, const wxFont& fontInit)
    //gc->SetBackgroundMode(wxSOLID); //sets the background color draw mode
    gc->SetFont(wxSystemSettings::GetFont(wxSYS_SYSTEM_FONT), color);
    gc->DrawText(strText,x,y);
    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}
