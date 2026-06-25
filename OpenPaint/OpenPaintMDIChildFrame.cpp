/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, OpenPaint
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
#include "BrushSamp.h"
#include "res/draw-airbrush.xpm"

#include "ToolManager.h"
#include "SubMainFrame.h"
#include <wx/cursor.h>
#include <wx/dcclient.h>
#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/textdlg.h>
#include <wx/dcmemory.h>
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>
#include <wx/imagbmp.h>
#include <wx/timer.h>
#include <wx/utils.h>
#include <cmath>

namespace {

wxCursor CreateSprayCanCursor()
{
    wxImage image(IDI_ICON_DRAW_AIRBRUSH_xpm);
    if (!image.IsOk())
    {
        return wxCursor(wxCURSOR_SPRAYCAN);
    }

    image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 4);
    image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 27);
    wxCursor cursor(image);
    return cursor.IsOk() ? cursor : wxCursor(wxCURSOR_SPRAYCAN);
}

const wxCursor& SprayCanCursor()
{
    static wxCursor cursor = CreateSprayCanCursor();
    return cursor;
}

} // namespace

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
    EVT_ENTER_WINDOW    (             OpenPaintMDIChildFrame::OnMouse)
    EVT_LEAVE_WINDOW    (             OpenPaintMDIChildFrame::OnMouseLeave)
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
    m_bImageUpdated = false;

    SetZoom(1.0);
    m_ScrollOrigin = wxPoint(0,0);
    m_lastPixelStatusUpdate = 0;
    m_currentCursor = wxCURSOR_NONE;
    m_bUsingSprayCanCursor = false;
    m_status = MOUSE_NOACTION;

    m_bHasSelection = false;
    m_bSelectionIsLasso = false;
    m_iSelectionOriginX = -1;
    m_iSelectionOriginY = -1;
    m_iSelectionWidth = -1;
    m_iSelectionHeight = -1;
    m_iSelectionMoveX = -1;
    m_iSelectionMoveY = -1;
    m_DragImage = NULL;

    // Per-frame tool state initialisation (replaces the old file-scope
    // globals that were shared between every MDI child).
    m_prevX = 0;
    m_prevY = 0;
    m_prevX2 = 0;
    m_prevY2 = 0;
    m_curveStage = 0;
    m_bCurvePreviewIsLine = false;
    m_drawLine.clear();

    SetImage(m_Image);

    //Listen to tab changes
    //GetMDIParentFrame()->GetClientWindow()->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( OpenPaintMDIChildFrame::OnTabChanged ), NULL, this );
}

OpenPaintMDIChildFrame::~OpenPaintMDIChildFrame()
{
    //GetMDIParentFrame()->GetClientWindow()->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( OpenPaintMDIChildFrame::OnTabChanged ), NULL, this );
}

void OpenPaintMDIChildFrame::Shutdown()
{
    this->Destroy();
}

void OpenPaintMDIChildFrame::OnTabChanged( wxAuiNotebookEvent& event )
{
    //TODO: Properly implement tab changes
    //UpdateStatusBar();
    //wxLogDebug("%d tab changed %d\n", event.GetSelection(), event.GetId());

    //event.Skip();
}

bool OpenPaintMDIChildFrame::Open(wxString strFilename)
{
    if(m_Image.LoadFile(strFilename))
    {
        // Reset the undo history so undoing after Open() can't restore a
        // different image's pixels.
        m_LastImages.clear();
        m_HistoryIndex = 0;
        m_bImageUpdated = false;

        SetImage(m_Image);
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
        wxLogDebug(wxT("File Saved."));
        return true;
    }
    return false;
}

bool OpenPaintMDIChildFrame::SaveAs(wxString strFilename)
{
    if(m_Image.SaveFile(strFilename))
    {
        m_strFilename = strFilename;
        wxLogDebug(wxT("File Saved As."));
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

    UpdateStatusBar();

    SetThumbIcon();
}

void OpenPaintMDIChildFrame::UpdateStatusBar()
{
    wxAuiMDIParentFrame* parent = GetMDIParentFrame();
    if (!parent)
    {
        return;
    }
    wxStatusBar * pStatusBar = parent->GetStatusBar();
    if (!pStatusBar)
    {
        return;
    }
    pStatusBar->SetStatusText(wxString::Format(wxT("Image Size: %dx%d "), GetWidth() , GetHeight() ), 2);

    pStatusBar->SetStatusText(wxString::Format(wxT("Zoom: %d%%"),(int)(GetZoom()*100) ), 3);

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

    UpdateStatusBar();

    // Send Size Event
    wxSizeEvent sizeEvent( GetSize(), GetId() );
    GetEventHandler()->ProcessEvent( sizeEvent );
    Refresh();
}

void OpenPaintMDIChildFrame::OnClose(wxCloseEvent& event)
{
    // No Veto() — let the default close handler Destroy() the frame. Calling
    // Destroy() ourselves while the MDI notebook is already tearing down the
    // child can double-free the window.
    wxLogDebug(wxT("OnClose"));
    event.Skip();
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
    // Draw the grey "canvas surround" outside the image on every platform.
    // The original code wrapped this in #ifndef __WXGTK__ which made the
    // canvas area look broken on Linux; just draw it unconditionally.
    dc.SetPen(*wxGREY_PEN);
    dc.SetBrush(*wxGREY_BRUSH);
    dc.DrawRectangle(width, 0, (w/zoom)-width, height);
    dc.DrawRectangle(0, height, w/zoom ,(h/zoom));

    DrawSelectionOutline(dc);

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

void OpenPaintMDIChildFrame::DrawSelectionOutline(wxDC& dc) const
{
    if (!m_bHasSelection || m_iSelectionWidth <= 0 || m_iSelectionHeight <= 0)
    {
        return;
    }

    wxPen dottedPen(*wxBLACK, 1, wxPENSTYLE_DOT);
    dc.SetPen(dottedPen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    if (m_bSelectionIsLasso && m_selectionOutline.size() >= 2)
    {
        for (size_t i = 0; i < m_selectionOutline.size(); ++i)
        {
            const wxPoint& from = m_selectionOutline[i];
            const wxPoint& to = m_selectionOutline[(i + 1) % m_selectionOutline.size()];
            dc.DrawLine(m_iSelectionOriginX + from.x, m_iSelectionOriginY + from.y,
                        m_iSelectionOriginX + to.x, m_iSelectionOriginY + to.y);
        }
        return;
    }

    dc.DrawRectangle(m_iSelectionOriginX, m_iSelectionOriginY,
                     m_iSelectionWidth, m_iSelectionHeight);
}


//void OpenPaintMDIChildFrame::OnIdle(wxIdleEvent& event)
//{
    //ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    //if(pToolManager->GetSelectedTool()== TOOL_SPRAY_CAN)
    //{
    //    
    //}
//}

bool OpenPaintMDIChildFrame::IsInsideImage(int x, int y) const
{
    return x >= 0 && y >= 0 && x < m_Image.GetWidth() && y < m_Image.GetHeight();
}

bool OpenPaintMDIChildFrame::IsInsideSelection(int x, int y) const
{
    return m_bHasSelection &&
           x >= m_iSelectionOriginX &&
           x < m_iSelectionOriginX + m_iSelectionWidth &&
           y >= m_iSelectionOriginY &&
           y < m_iSelectionOriginY + m_iSelectionHeight;
}

void OpenPaintMDIChildFrame::SetCanvasCursor(wxStockCursor cursor)
{
    if (!m_bUsingSprayCanCursor && m_currentCursor == cursor)
    {
        return;
    }

    SetCursor(wxCursor(cursor));
    m_currentCursor = cursor;
    m_bUsingSprayCanCursor = false;
}

void OpenPaintMDIChildFrame::SetSprayCanCursor()
{
    if (m_bUsingSprayCanCursor)
    {
        return;
    }

    SetCursor(SprayCanCursor());
    m_currentCursor = wxCURSOR_NONE;
    m_bUsingSprayCanCursor = true;
}

void OpenPaintMDIChildFrame::ApplyToolCursor(int x, int y)
{
    if (!IsInsideImage(x, y))
    {
        SetCanvasCursor(wxCURSOR_ARROW);
        return;
    }

    if (IsInsideSelection(x, y))
    {
        SetCanvasCursor(wxCURSOR_SIZING);
        return;
    }

    ToolManager* toolManager = Globals::Instance()->GetToolManager();
    if (!toolManager)
    {
        SetCanvasCursor(wxCURSOR_ARROW);
        return;
    }

    if (toolManager->GetSelectedTool() == TOOL_SPRAY_CAN)
    {
        SetSprayCanCursor();
        return;
    }

    SetCanvasCursor(toolManager->GetSelectedToolCursor());
}

void OpenPaintMDIChildFrame::RefreshToolCursor()
{
    wxPoint cursorPos = ScreenToClient(wxGetMousePosition());
    wxInt32 x = (cursorPos.x - m_ScrollOrigin.x) / m_dZoom;
    wxInt32 y = (cursorPos.y - m_ScrollOrigin.y) / m_dZoom;
    ApplyToolCursor(x, y);
}

void OpenPaintMDIChildFrame::OnMouse(wxMouseEvent& event)
{
    wxInt32 i = (event.GetX()-m_ScrollOrigin.x)/m_dZoom;
    wxInt32 j = (event.GetY()-m_ScrollOrigin.y)/m_dZoom;

    if (wxStatusBar* pStatusBar = GetMDIParentFrame() ? GetMDIParentFrame()->GetStatusBar() : nullptr)
    {
        // Throttle status-bar updates so the pixel coordinate text doesn't
        // flicker as the cursor moves across individual pixels. 20 Hz is
        // more than enough for a status-bar read-out.
        const long cStatusUpdateIntervalMs = 50;
        wxLongLong now = wxGetLocalTimeMillis();
        if ((now - m_lastPixelStatusUpdate) >= cStatusUpdateIntervalMs)
        {
            m_lastPixelStatusUpdate = now;
            pStatusBar->SetStatusText(wxString::Format(wxT("Pixel: (%d, %d) "), i , j ), 1);
        }
    }

    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    ApplyToolCursor(i, j);

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
                // Free any prior drag image before allocating a new one,
                // otherwise repeated drags leak one wxGenericDragImage each.
                if (m_DragImage)
                {
                    m_DragImage->EndDrag();
                    delete m_DragImage;
                }
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
                m_bSelectionIsLasso = false;
                m_selectionOutline.clear();

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
            Refresh();
            return;
        }

        //wxLogDebug("hasselection %d, %d" , i ,j);
        return;
    }


    UpdateStatusBar();

    if(this != wxWindow::FindFocus())
    {
        //Get focus on mouse enter for mouse wheel events
        this->SetFocus();
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
                // Old behaviour: single click toggled 1x/4x. To get a
                // region zoom, the user now uses Ctrl+LeftClick; that case
                // is handled separately by handling EVT_MOUSEWHEEL and the
                // (still wired) LeftDClick path.
                MagnifyTool(0, 0, 0, 0);
                break;
            case TOOL_SPRAY_CAN:
                SprayCanTool(i,j, fColor);
                break;
            case TOOL_LINE:
                LineTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_CURVE:
                CurveTool(i,j, fColor, MOUSE_BEGIN_DRAWING);
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
            case TOOL_POLYGON:
                PolygonTool(i,j, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_SELECT_LASSO:
                LassoSelectTool(i,j, MOUSE_BEGIN_DRAWING);
                break;
            case TOOL_TEXT:
                TextTool(i,j, fColor);
                break;

        }
    }
    else if (event.LeftDClick())
    {
        // Double-click finishes a polygon / lasso so the user can place
        // many points with single clicks and commit the shape with a
        // double-click anywhere in the canvas.
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_POLYGON:
                PolygonTool(i, j, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_SELECT_LASSO:
                LassoSelectTool(i, j, MOUSE_FINISHED_DRAWING);
                break;
            default:
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
            case TOOL_LINE:
                LineTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_CURVE:
                CurveTool(i,j, fColor, MOUSE_CONTINUE_DRAWING);
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
            case TOOL_POLYGON:
                PolygonTool(i,j, MOUSE_CONTINUE_DRAWING);
                break;
            case TOOL_SELECT_LASSO:
                LassoSelectTool(i,j, MOUSE_CONTINUE_DRAWING);
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
            case TOOL_LINE:
                LineTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
                break;
            case TOOL_CURVE:
                CurveTool(i,j, fColor, MOUSE_FINISHED_DRAWING);
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
    else if(event.Moving())
    {
        switch(pToolManager->GetSelectedTool())
        {
            case TOOL_POLYGON:
                PolygonTool(i,j, MOUSE_CONTINUE_DRAWING);
                break;
            default:
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
                MagnifyTool(0, 0, 0, 0);
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
                SetZoom(GetZoom() * 1.5);
            }
        }
        else
        {
             if(GetZoom() > 0.2)
            {
                SetZoom(GetZoom() / 1.5);
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

void OpenPaintMDIChildFrame::OnMouseLeave(wxMouseEvent& event)
{
    SetCanvasCursor(wxCURSOR_ARROW);

    if (wxAuiMDIParentFrame* parent = GetMDIParentFrame())
    {
        if (wxStatusBar* pStatusBar = parent->GetStatusBar())
        {
            pStatusBar->SetStatusText(wxT(""), 1);
        }
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
    SubMainFrame * pMainFrame = Globals::Instance()->GetMainFrame();
    wxMenu *editMenu = pMainFrame->GetMenuBar()->GetMenu(1);
    wxMenuItem * redoItem = editMenu->FindItem(wxID_REDO, NULL);
    redoItem->Enable(true);
    pMainFrame->GetToolBar()->EnableTool(wxID_REDO, true);

    // If the user makes a change after the last undo, capture it so that
    // subsequent undos can step back to it.
    if(m_HistoryIndex == 0 && m_bImageUpdated)
    {
        m_bImageUpdated = false;
        m_LastImages.push_back(m_Image);
    }

    // Bounds check BEFORE indexing the history vector. The old code
    // incremented m_HistoryIndex and then indexed m_LastImages at the new
    // value, which threw std::out_of_range when the user kept clicking
    // Undo past the deepest recorded state.
    if (m_HistoryIndex >= static_cast<int>(m_LastImages.size()) - 1)
    {
        wxMenuItem * undoItem = editMenu->FindItem(wxID_UNDO, NULL);
        undoItem->Enable(false);
        pMainFrame->GetToolBar()->EnableTool(wxID_UNDO, false);
        return;
    }

    m_HistoryIndex++;
    int idx = static_cast<int>(m_LastImages.size()) - m_HistoryIndex - 1;
    if (idx < 0 || idx >= static_cast<int>(m_LastImages.size()))
    {
        // Should not happen after the guard above, but be defensive.
        return;
    }
    m_Image = m_LastImages.at(static_cast<size_t>(idx));
    SetThumbIcon();
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::Redo()
{
    SubMainFrame * pMainFrame = Globals::Instance()->GetMainFrame();
    wxMenu *editMenu = pMainFrame->GetMenuBar()->GetMenu(1);
    wxMenuItem * undoItem = editMenu->FindItem(wxID_UNDO, NULL);
    undoItem->Enable(true);
    pMainFrame->GetToolBar()->EnableTool(wxID_UNDO, true);

    // Bounds check BEFORE indexing; the old code decremented past zero and
    // then read at a negative offset, which both produced out-of-range
    // exceptions and silently read garbage.
    if (m_HistoryIndex <= 0)
    {
        wxMenuItem * redoItem = editMenu->FindItem(wxID_REDO, NULL);
        redoItem->Enable(false);
        pMainFrame->GetToolBar()->EnableTool(wxID_REDO, false);
        return;
    }

    m_HistoryIndex--;
    int idx = static_cast<int>(m_LastImages.size()) - m_HistoryIndex - 1;
    if (idx < 0 || idx >= static_cast<int>(m_LastImages.size()))
    {
        return;
    }
    m_Image = m_LastImages.at(static_cast<size_t>(idx));
    SetThumbIcon();
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(wxPoint, wxArrayPoints);
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayPoints);
// Note: the four file-scope globals (drawLine, prevX, prevY, customPen,
// customBrush) and the int prevX2/prevY2 that used to live here have been
// moved to OpenPaintMDIChildFrame members. See the header for the new
// m_drawLine/m_prevX/m_prevY/m_prevX2/m_prevY2/m_customPen/m_customBrush
// fields. This keeps tool state per-tab so switching tabs mid-stroke
// doesn't corrupt the other tab's rubber-band.
wxBitmap OpenPaintMDIChildFrame::Cut()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    m_customPen = wxPen(bColor, 1, wxPENSTYLE_SOLID);
    m_customBrush = wxBrush(bColor, wxBRUSHSTYLE_SOLID);

    wxMemoryDC memDC;
    memDC.SelectObject(m_Bitmap);
    memDC.SetPen(m_customPen);
    memDC.SetBrush(m_customBrush);
    memDC.DrawRectangle(m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight);
    SetImage(m_Bitmap.ConvertToImage());
    Refresh();

    wxBitmap m_TempBitmap = m_SelectedBitmap;
    //Clear the selection
    m_SelectedBitmap = wxBitmap();
    m_bHasSelection = false;
    m_bSelectionIsLasso = false;
    m_selectionOutline.clear();

    return m_TempBitmap;
}

wxBitmap OpenPaintMDIChildFrame::Copy()
{
    return m_SelectedBitmap;
}

void OpenPaintMDIChildFrame::Paste(wxBitmap bitmap)
{
    m_SelectedBitmap = bitmap;
    // Delete any prior drag image so repeated pastes don't leak one each.
    if (m_DragImage)
    {
        m_DragImage->EndDrag();
        delete m_DragImage;
    }
    m_DragImage = new wxGenericDragImage(m_SelectedBitmap);
    m_DragImage->BeginDrag(wxPoint(0, 0), this);
    m_DragImage->Move(wxPoint(0,0));
    m_DragImage->Show();
    m_bHasSelection = true;
    m_bSelectionIsLasso = false;
    m_selectionOutline.clear();

    //SetImage(m_Bitmap.ConvertToImage());
    //m_Image.ConvertAlphaToMask();
    //m_Bitmap =  wxBitmap(m_Image);
    //Refresh();
}

void OpenPaintMDIChildFrame::Delete()
{
    ToolManager * pToolManager = Globals::Instance()->GetToolManager();
    wxColour bColor = pToolManager->GetBackground();

    m_customPen = wxPen(bColor, 1, wxPENSTYLE_SOLID);
    m_customBrush = wxBrush(bColor, wxBRUSHSTYLE_SOLID);

    wxMemoryDC memDC;
    memDC.SelectObject(m_Bitmap);
    memDC.SetPen(m_customPen);
    memDC.SetBrush(m_customBrush);
    memDC.DrawRectangle(m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight);
    SetImage(m_Bitmap.ConvertToImage());
    m_SelectedBitmap = wxBitmap();
    m_bHasSelection = false;
    m_bSelectionIsLasso = false;
    m_selectionOutline.clear();
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

void OpenPaintMDIChildFrame::Rotate(double angleDegrees)
{
    if (angleDegrees == 0.0)
    {
        return;
    }
    // wxImage::Rotate expects radians and an interpolation flag. A value very
    // close to a 90-degree multiple is mapped to the integer multiples via
    // Rotate90() to keep the fast, lossless path.
    double mod = std::fmod(std::fabs(angleDegrees), 90.0);
    if (mod < 0.5 || mod > 89.5)
    {
        int n = static_cast<int>(std::round(angleDegrees / 90.0));
        n = ((n % 4) + 4) % 4; // reduce to 0..3
        if (n == 0) return;
        wxImage img = m_Image;
        for (int i = 0; i < n; ++i)
        {
            img = img.Rotate90();
        }
        SetImage(img);
    }
    else
    {
        double radians = angleDegrees * M_PI / 180.0;
        // Rotate around the image centre; wxImage's Rotate uses the same
        // convention as the rest of wx (origin at the centre of the image).
        SetImage(m_Image.Rotate(radians, wxPoint(m_Image.GetWidth() / 2,
                                                 m_Image.GetHeight() / 2),
                                true));
    }
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

void OpenPaintMDIChildFrame::Blur(int radius)
{
    // Clamp radius to a sane range; wxImage::Blur treats very small values as
    // "use default" and very large values as slow but harmless.
    if (radius < 1) radius = 1;
    if (radius > 50) radius = 50;
    SetImage(m_Image.Blur(radius));
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::Pixelize(int block)
{
    if (block < 1) block = 1;
    if (block > 256) block = 256;
    int pixelWidth = block;
    int pixelHeight = block;

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
        m_drawLine.clear();
        m_prevX = x;
        m_prevY = y;
    }
    // The eraser reuses PencilTool with the background colour. Read the
    // matching size from the ToolManager so the size spinner in the
    // tool-properties panel actually affects what the user sees.
    ToolManager* tm = Globals::Instance()->GetToolManager();
    int width = (tm->GetSelectedTool() == TOOL_ERASER)
                    ? tm->GetEraserSize()
                    : tm->GetPencilSize();
    if (width < 1) width = 1;
    m_customPen = wxPen(color, width, wxPENSTYLE_SOLID);

    dc.SetPen(m_customPen);
    dc.DrawPoint(x,y);
    dc.DrawLine(x,y,m_prevX,m_prevY);

    m_drawLine.push_back(wxPoint(x,y));
    m_prevX = x;
    m_prevY = y;

    mydc.Blit(m_ScrollOrigin.x/GetZoom(), m_ScrollOrigin.y/GetZoom(), m_Bitmap.GetWidth(), m_Bitmap.GetHeight(), &dc, 0, 0);

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC(m_Bitmap);
        memDC.SetPen(m_customPen);

        memDC.DrawPoint(x,y);

        for(size_t i = 0; i + 1 < m_drawLine.size(); i++)
        {
            memDC.DrawLine(m_drawLine[i].x, m_drawLine[i].y, m_drawLine[i+1].x, m_drawLine[i+1].y);
        }

        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::FillTool(int x, int y, wxColour color)
{
    //FillTool(x,y,color,wxColour());
    // Defensive bounds check: FloodFill on out-of-bounds coords is undefined
    // behaviour in wxWidgets.
    if (x < 0 || y < 0 || x >= m_Image.GetWidth() || y >= m_Image.GetHeight())
    {
        return;
    }

    wxColour colorOld(m_Image.GetRed(x, y),m_Image.GetGreen(x, y),m_Image.GetBlue(x, y));
    m_customBrush = wxBrush(color, wxBRUSHSTYLE_SOLID);
    //can use
    //wxCROSSDIAG_HATCH
    //wxBDIAGONAL_HATCH

    wxMemoryDC mdc(m_Bitmap);
    mdc.SetBrush(m_customBrush);
    mdc.FloodFill(x,y, colorOld);

    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}

// Note: the old recursive FillTool(int, int, wxColour, wxColour) used to
// live here. It was broken (only one of four directional recursions was
// enabled), never called from anywhere, and would have stack-overflowed on
// any non-trivial region. Removed. The active flood fill is performed by
// wxMemoryDC::FloodFill inside the single-arg FillTool() overload.

void OpenPaintMDIChildFrame::PickColorTool(int x, int y, bool bIsForeground)
{
    // The user may click outside the canvas (margin, scrollbar area, etc.).
    // Clamp to the image bounds so we don't read past the buffer.
    if (x < 0 || y < 0 || x >= m_Image.GetWidth() || y >= m_Image.GetHeight())
    {
        return;
    }

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

void OpenPaintMDIChildFrame::MagnifyTool(int x, int y, int x2, int y2)
{
    if (x2 <= x || y2 <= y)
    {
        // No valid selection region (e.g. user just clicked). Fall back to
        // the old "toggle 1x/4x" behaviour so a single click still does
        // something useful.
        if (GetZoom() == 1.0)
        {
            SetZoom(4.0);
        }
        else
        {
            SetZoom(1.0);
        }
        return;
    }

    // Zoom to the bounding box selected by the user. Compute the zoom that
    // fits the region into the current client size, clamp to the existing
    // min/max (0.2 to 8.0) and recenter the view on the selected area.
    int clientW = 0, clientH = 0;
    GetClientSize(&clientW, &clientH);
    if (clientW <= 0 || clientH <= 0)
    {
        return;
    }
    int regionW = x2 - x;
    int regionH = y2 - y;
    if (regionW <= 0 || regionH <= 0)
    {
        return;
    }
    double zoomX = static_cast<double>(clientW) / regionW;
    double zoomY = static_cast<double>(clientH) / regionH;
    double newZoom = (zoomX < zoomY) ? zoomX : zoomY;
    if (newZoom < 0.2) newZoom = 0.2;
    if (newZoom > 8.0) newZoom = 8.0;
    SetZoom(newZoom);
}

void OpenPaintMDIChildFrame::DrawBrushTip(wxDC& dc, int x, int y, int radius, int tip)
{
    // Thin wrapper around the free-function StampBrushTip so the same
    // per-tip stamping logic is reachable from the test binary without
    // instantiating a full MDI child frame.
    StampBrushTip(dc, x, y, radius, tip);
}

void OpenPaintMDIChildFrame::StampBrushAlongLine(wxDC& dc, int x0, int y0,
                                                 int x1, int y1,
                                                 int radius, int tip)
{
    // Thin wrapper around the free-function StampBrushAlongLine so the
    // same gap-closing logic is reachable from the test binary without
    // instantiating a full MDI child frame.
    ::StampBrushAlongLine(dc, x0, y0, x1, y1, radius, tip);
}

void OpenPaintMDIChildFrame::BrushTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC mydc(this);
    mydc.SetUserScale(m_dZoom,m_dZoom);

    wxMemoryDC dc;
    dc.SelectObjectAsSource(m_Bitmap);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        m_drawLine.clear();
        m_prevX = x;
        m_prevY = y;
    }
    // Read the brush settings from the ToolManager (driven by the
    // BrushToolPanel) so the radius spinner and tip combo both affect
    // the rendered result.
    ToolManager* tm = Globals::Instance()->GetToolManager();
    int brushRadius = tm->GetBrushRadius();
    if (brushRadius < 1) brushRadius = 1;
    int brushTip = tm->GetBrushTip();

    // Paint the tip along the segment from the previous mouse position
    // to the current one. Stamping at every integer pixel between the
    // two endpoints (rather than only at (x, y)) is what closes the gap
    // that otherwise appears between consecutive mouse-move events,
    // especially for the 1px-thick vertical/horizontal line tips.
    // Using filled shapes (per the tip) is what makes "square"/"vertical"/
    // "horizontal" brushes render as the user picked them; the
    // pre-stamp-only implementation always rendered a 1-pixel-thick
    // line regardless of the tip selection.
    dc.SetBrush(wxBrush(color, wxBRUSHSTYLE_SOLID));
    StampBrushAlongLine(dc, m_prevX, m_prevY, x, y, brushRadius, brushTip);

    m_drawLine.push_back(wxPoint(x,y));
    m_prevX = x;
    m_prevY = y;

    mydc.Blit(m_ScrollOrigin.x/GetZoom(), m_ScrollOrigin.y/GetZoom(), m_Bitmap.GetWidth(), m_Bitmap.GetHeight(), &dc, 0, 0);

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        // Replay the stroke onto the committed bitmap using the same
        // pixel-by-pixel stamping the live preview used, so the saved
        // image is bit-for-bit identical to what the user saw on screen.
        wxMemoryDC memDC(m_Bitmap);
        memDC.SetBrush(wxBrush(color, wxBRUSHSTYLE_SOLID));
        for (size_t i = 0; i + 1 < m_drawLine.size(); i++)
        {
            StampBrushAlongLine(memDC,
                                m_drawLine[i].x, m_drawLine[i].y,
                                m_drawLine[i+1].x, m_drawLine[i+1].y,
                                brushRadius, brushTip);
        }
        // The loop above connects every recorded point to the next but
        // does not stamp the last point itself (no "next" to walk to).
        // Stamp it explicitly so the stroke ends at the cursor.
        if (!m_drawLine.empty())
        {
            const wxPoint& tail = m_drawLine.back();
            DrawBrushTip(memDC, tail.x, tail.y, brushRadius, brushTip);
        }

        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::SprayCanTool(int x, int y, wxColour color)
{
    srand((unsigned)time(0)+x+y);

    // Read the spray-can size from the ToolManager so the size spinner in
    // the Spray Can properties panel affects how wide the spray pattern is.
    ToolManager* tm = Globals::Instance()->GetToolManager();
    int spraySize = tm->GetSprayCanSize();
    if (spraySize < 1) spraySize = 1;

    //SQUARE SPRAY
    int random_integer1,random_integer2;
    int lowest=-spraySize, highest=spraySize;
    int range=(highest-lowest)+1;
    const int w = m_Image.GetWidth();
    const int h = m_Image.GetHeight();
    for(int index=0; index<20; index++){
        random_integer1 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        random_integer2 = lowest+int(range*rand()/(RAND_MAX + 1.0));

        // Use inclusive bounds so pixels at the very edge of the canvas are
        // reachable, and reject anything outside the image buffer.
        if( x+random_integer1 >= 0 &&
            x+random_integer1 <  w &&
            y+random_integer2 >= 0 &&
            y+random_integer2 <  h)
        {
            m_Image.SetRGB(x+random_integer1, y+random_integer2, color.Red(), color.Green(), color.Blue());
        }

    }

    //ROUND SPRAY
    //double random_angle,random_radius;
    //int random_integerX,random_integerY; 
    //int lowest=0, highest= M_PI; 
    //int range_angle = (highest-lowest); 
    //lowest=-10, highest = 10;
    //int range_radius = (highest-lowest);

    //for(int index=0; index < 30; index++){ 
    //    random_angle = double(range_angle*rand()/(RAND_MAX + 1.0));
    //    random_radius = lowest+double(range_radius*rand()/(RAND_MAX + 1.0));

    //    random_integerX = cos(random_angle)*random_radius;
    //    random_integerY = sin(random_angle)*random_radius;

    //    if( x+random_integerX > 0 &&
    //        x+random_integerX < m_Image.GetWidth() &&
    //        y+random_integerY > 0 &&
    //        y+random_integerY < m_Image.GetHeight())
    //    {
    //        m_Image.SetRGB(x+random_integerX, y+random_integerY, color.Red(), color.Green(), color.Blue());
    //    }

    //} 
    
    m_Bitmap = wxBitmap(m_Image);
    Refresh();
}

void OpenPaintMDIChildFrame::LineTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom, m_dZoom);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        m_prevX = x;
        m_prevY = y;
        m_prevX2 = x;
        m_prevY2 = y;
    }

    ToolManager* tm = Globals::Instance()->GetToolManager();
    int penWidth = tm->GetShapeLineWidth();
    if (penWidth < 1) penWidth = 1;
    m_customPen = wxPen(color, penWidth, wxPENSTYLE_SOLID);

    dc.SetPen(m_customPen);
    dc.SetLogicalFunction(wxINVERT);
    dc.DrawLine(m_prevX, m_prevY, m_prevX2, m_prevY2);
    dc.DrawLine(m_prevX, m_prevY, x, y);
    m_prevX2 = x;
    m_prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC(m_Bitmap);
        memDC.SetPen(m_customPen);
        memDC.DrawLine(m_prevX, m_prevY, x, y);
        SetImage(m_Bitmap.ConvertToImage());
        Refresh();
    }
}

void OpenPaintMDIChildFrame::DrawCurvePath(wxDC& dc, const wxPoint& start,
                                           const wxPoint& control1,
                                           const wxPoint& control2,
                                           const wxPoint& end)
{
    wxPoint prev = start;
    const int steps = 64;
    for (int i = 1; i <= steps; ++i)
    {
        double t = static_cast<double>(i) / steps;
        double u = 1.0 - t;
        double x = (u * u * u * start.x) +
                   (3.0 * u * u * t * control1.x) +
                   (3.0 * u * t * t * control2.x) +
                   (t * t * t * end.x);
        double y = (u * u * u * start.y) +
                   (3.0 * u * u * t * control1.y) +
                   (3.0 * u * t * t * control2.y) +
                   (t * t * t * end.y);
        wxPoint next(static_cast<int>(std::lround(x)), static_cast<int>(std::lround(y)));
        dc.DrawLine(prev.x, prev.y, next.x, next.y);
        prev = next;
    }
}

void OpenPaintMDIChildFrame::CurveTool(int x, int y, wxColour color, MouseStatus drawState)
{
    ToolManager* tm = Globals::Instance()->GetToolManager();
    int penWidth = tm->GetShapeLineWidth();
    if (penWidth < 1) penWidth = 1;
    m_customPen = wxPen(color, penWidth, wxPENSTYLE_SOLID);

    if (drawState == MOUSE_BEGIN_DRAWING)
    {
        if (m_curveStage == 0)
        {
            m_curveStart = wxPoint(x, y);
            m_curveEnd = wxPoint(x, y);
            m_curvePreviewControl1 = m_curveStart;
            m_curvePreviewControl2 = m_curveEnd;
            m_bCurvePreviewIsLine = true;
        }
        return;
    }

    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom, m_dZoom);
    dc.SetPen(m_customPen);
    dc.SetLogicalFunction(wxINVERT);

    if (drawState == MOUSE_CONTINUE_DRAWING)
    {
        if (m_curveStage == 0)
        {
            dc.DrawLine(m_curveStart.x, m_curveStart.y, m_curveEnd.x, m_curveEnd.y);
            m_curveEnd = wxPoint(x, y);
            dc.DrawLine(m_curveStart.x, m_curveStart.y, m_curveEnd.x, m_curveEnd.y);
            m_bCurvePreviewIsLine = true;
        }
        else if (m_curveStage == 1)
        {
            if (m_bCurvePreviewIsLine)
            {
                dc.DrawLine(m_curveStart.x, m_curveStart.y, m_curveEnd.x, m_curveEnd.y);
            }
            else
            {
                DrawCurvePath(dc, m_curveStart, m_curvePreviewControl1,
                              m_curvePreviewControl2, m_curveEnd);
            }
            m_curvePreviewControl1 = wxPoint(x, y);
            m_curvePreviewControl2 = wxPoint(x, y);
            DrawCurvePath(dc, m_curveStart, m_curvePreviewControl1,
                          m_curvePreviewControl2, m_curveEnd);
            m_bCurvePreviewIsLine = false;
        }
        else if (m_curveStage == 2)
        {
            if (m_bCurvePreviewIsLine)
            {
                dc.DrawLine(m_curveStart.x, m_curveStart.y, m_curveEnd.x, m_curveEnd.y);
            }
            else
            {
                DrawCurvePath(dc, m_curveStart, m_curvePreviewControl1,
                              m_curvePreviewControl2, m_curveEnd);
            }
            m_curvePreviewControl2 = wxPoint(x, y);
            DrawCurvePath(dc, m_curveStart, m_curvePreviewControl1,
                          m_curvePreviewControl2, m_curveEnd);
            m_bCurvePreviewIsLine = false;
        }
        return;
    }

    if (drawState == MOUSE_FINISHED_DRAWING)
    {
        if (m_curveStage == 0)
        {
            m_curveEnd = wxPoint(x, y);
            m_curveStage = 1;
            m_bCurvePreviewIsLine = true;
        }
        else if (m_curveStage == 1)
        {
            m_curveControl1 = wxPoint(x, y);
            m_curvePreviewControl1 = m_curveControl1;
            m_curvePreviewControl2 = m_curveControl1;
            m_curveStage = 2;
        }
        else
        {
            if (m_bCurvePreviewIsLine)
            {
                dc.DrawLine(m_curveStart.x, m_curveStart.y, m_curveEnd.x, m_curveEnd.y);
            }
            else
            {
                DrawCurvePath(dc, m_curveStart, m_curvePreviewControl1,
                              m_curvePreviewControl2, m_curveEnd);
            }

            wxMemoryDC memDC(m_Bitmap);
            memDC.SetPen(m_customPen);
            DrawCurvePath(memDC, m_curveStart, m_curveControl1, wxPoint(x, y), m_curveEnd);
            SetImage(m_Bitmap.ConvertToImage());
            m_curveStage = 0;
            m_bCurvePreviewIsLine = false;
            Refresh();
        }
    }
}

void OpenPaintMDIChildFrame::EllipseTool(int x, int y, wxColour color, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom,m_dZoom);

    if(drawState == MOUSE_BEGIN_DRAWING)
    {
        m_prevX = x;
        m_prevY = y;
        m_prevX2 = x;
        m_prevY2 = y;
    }

    ToolManager* tm = Globals::Instance()->GetToolManager();
    int penWidth = tm->GetShapeLineWidth();
    if (penWidth < 1) penWidth = 1;
    m_customPen = wxPen(color, penWidth, wxPENSTYLE_SOLID);
    dc.SetPen(m_customPen);

    // If the user has filled shapes enabled, fill with the current background
    // colour; otherwise leave the interior transparent so only the outline
    // shows.
    if (tm->GetShapesFilled())
    {
        dc.SetBrush(wxBrush(tm->GetBackground(), wxBRUSHSTYLE_SOLID));
    }
    else
    {
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
    }

    dc.SetLogicalFunction(wxINVERT);

    //Remove last draw Rectangle
    dc.DrawEllipse(m_prevX, m_prevY, -(m_prevX-m_prevX2), -(m_prevY-m_prevY2));

    //Add current rectangle
    dc.DrawEllipse(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y));

    //Update previous rectangle second point
    m_prevX2 = x;
    m_prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC;
        memDC.SelectObject(m_Bitmap);
        memDC.SetPen(m_customPen);
        if (tm->GetShapesFilled())
        {
            memDC.SetBrush(wxBrush(tm->GetBackground(), wxBRUSHSTYLE_SOLID));
        }
        else
        {
            memDC.SetBrush(*wxTRANSPARENT_BRUSH);
        }

        memDC.DrawEllipse(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y));

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
        m_prevX = x;
        m_prevY = y;
        m_prevX2 = x;
        m_prevY2 = y;
    }

    ToolManager* tm = Globals::Instance()->GetToolManager();
    int penWidth = tm->GetShapeLineWidth();
    if (penWidth < 1) penWidth = 1;
    m_customPen = wxPen(color, penWidth, wxPENSTYLE_SOLID);
    dc.SetPen(m_customPen);

    if (tm->GetShapesFilled())
    {
        dc.SetBrush(wxBrush(tm->GetBackground(), wxBRUSHSTYLE_SOLID));
    }
    else
    {
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
    }

    dc.SetLogicalFunction(wxINVERT);

    if(bIsRounded)
    {
        //Remove last draw Rectangle
        dc.DrawRoundedRectangle(m_prevX, m_prevY, -(m_prevX-m_prevX2), -(m_prevY-m_prevY2), 10);

        //Add current rectangle
        dc.DrawRoundedRectangle(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y), 10);
    }
    else
    {
        //Remove last draw Rectangle
        dc.DrawRectangle(m_prevX, m_prevY, -(m_prevX-m_prevX2), -(m_prevY-m_prevY2));

        //Add current rectangle
        dc.DrawRectangle(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y));
    }

    //Update previous rectangle second point
    m_prevX2 = x;
    m_prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        wxMemoryDC memDC;
        memDC.SelectObject(m_Bitmap);
        memDC.SetPen(m_customPen);
        if (tm->GetShapesFilled())
        {
            memDC.SetBrush(wxBrush(tm->GetBackground(), wxBRUSHSTYLE_SOLID));
        }
        else
        {
            memDC.SetBrush(*wxTRANSPARENT_BRUSH);
        }

        if(bIsRounded)
        {
            memDC.DrawRoundedRectangle(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y), 10);
        }
        else
        {
            memDC.DrawRectangle(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y));
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
        m_prevX = x;
        m_prevY = y;
        m_prevX2 = x;
        m_prevY2 = y;
    }

    wxPen dottedPen(*wxBLACK, 1, wxPENSTYLE_DOT);
    dc.SetPen(dottedPen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetLogicalFunction(wxINVERT);

    //Remove last draw Rectangle
    dc.DrawRectangle(m_prevX, m_prevY, -(m_prevX-m_prevX2), -(m_prevY-m_prevY2));

    //Add current rectangle
    dc.DrawRectangle(m_prevX, m_prevY, -(m_prevX-x), -(m_prevY-y));

    //Update previous rectangle second point
    m_prevX2 = x;
    m_prevY2 = y;

    if(drawState == MOUSE_FINISHED_DRAWING)
    {
        if(m_prevX != x && m_prevY != y)//Make sure at least one pixel is selected
        {
            m_iSelectionOriginX = std::min(m_prevX,x);
            m_iSelectionOriginY = std::min(m_prevY,y);
            m_iSelectionWidth = abs(m_prevX-x);
            m_iSelectionHeight = abs(m_prevY-y);
            m_SelectedBitmap = m_Bitmap.GetSubBitmap(wxRect(m_iSelectionOriginX, m_iSelectionOriginY , m_iSelectionWidth, m_iSelectionHeight)) ;

            m_iSelectionMoveX = m_iSelectionOriginX;
            m_iSelectionMoveY = m_iSelectionOriginY;

            m_bHasSelection = true;
            m_bSelectionIsLasso = false;
            m_selectionOutline.clear();
            Refresh();
        }
    }
}

void OpenPaintMDIChildFrame::PolygonTool(int x, int y, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom, m_dZoom);
    ToolManager* tm = Globals::Instance()->GetToolManager();
    wxColour color = tm->GetForeground();
    int penWidth = tm->GetShapeLineWidth();
    if (penWidth < 1) penWidth = 1;
    m_customPen = wxPen(color, penWidth, wxPENSTYLE_SOLID);
    dc.SetPen(m_customPen);
    dc.SetLogicalFunction(wxINVERT);

    if (drawState == MOUSE_BEGIN_DRAWING)
    {
        if (m_drawLine.empty())
        {
            m_drawLine.push_back(wxPoint(x, y));
        }
        else
        {
            wxPoint prev = m_drawLine.back();
            dc.DrawLine(prev.x, prev.y, m_prevX2, m_prevY2);
            dc.DrawLine(prev.x, prev.y, x, y);
            m_drawLine.push_back(wxPoint(x, y));
        }
        m_prevX2 = x;
        m_prevY2 = y;
        return;
    }

    if (drawState == MOUSE_CONTINUE_DRAWING)
    {
        if (!m_drawLine.empty())
        {
            wxPoint prev = m_drawLine.back();
            dc.DrawLine(prev.x, prev.y, m_prevX2, m_prevY2);
            dc.DrawLine(prev.x, prev.y, x, y);
            m_prevX2 = x;
            m_prevY2 = y;
        }
        return;
    }

    if (drawState == MOUSE_FINISHED_DRAWING)
    {
        if (!m_drawLine.empty())
        {
            wxPoint prev = m_drawLine.back();
            dc.DrawLine(prev.x, prev.y, m_prevX2, m_prevY2);
            if (prev != wxPoint(x, y))
            {
                m_drawLine.push_back(wxPoint(x, y));
            }
        }

        if (m_drawLine.size() < 2)
        {
            m_drawLine.clear();
            return;
        }

        wxMemoryDC memDC(m_Bitmap);
        memDC.SetPen(m_customPen);
        if (tm->GetShapesFilled() && m_drawLine.size() >= 3)
        {
            memDC.SetBrush(wxBrush(tm->GetBackground(), wxBRUSHSTYLE_SOLID));
            memDC.DrawPolygon(static_cast<int>(m_drawLine.size()), &m_drawLine[0]);
        }
        else
        {
            for (size_t i = 0; i + 1 < m_drawLine.size(); ++i)
            {
                memDC.DrawLine(m_drawLine[i].x, m_drawLine[i].y,
                               m_drawLine[i + 1].x, m_drawLine[i + 1].y);
            }
            if (m_drawLine.size() >= 3)
            {
                const wxPoint& first = m_drawLine.front();
                const wxPoint& last = m_drawLine.back();
                memDC.DrawLine(last.x, last.y, first.x, first.y);
            }
        }

        SetImage(m_Bitmap.ConvertToImage());
        m_drawLine.clear();
        Refresh();
    }
}

void OpenPaintMDIChildFrame::LassoSelectTool(int x, int y, MouseStatus drawState)
{
    wxClientDC dc(this);
    dc.SetUserScale(m_dZoom, m_dZoom);

    if (drawState == MOUSE_BEGIN_DRAWING)
    {
        m_drawLine.clear();
        m_drawLine.push_back(wxPoint(x, y));
        m_prevX2 = x;
        m_prevY2 = y;
        return;
    }

    if (drawState == MOUSE_FINISHED_DRAWING)
    {
        if (!m_drawLine.empty() && m_drawLine.back() != wxPoint(x, y))
        {
            m_drawLine.push_back(wxPoint(x, y));
        }
        if (m_drawLine.size() < 3)
        {
            m_drawLine.clear();
            return;
        }
        // Build the lasso selection: bounding box around the polygon, then
        // capture the rectangular sub-bitmap and the polygon path so future
        // operations (Cut, Copy, Paste, drag-move) can use it.
        int minX = m_drawLine[0].x, minY = m_drawLine[0].y;
        int maxX = minX, maxY = minY;
        for (const wxPoint& p : m_drawLine)
        {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }
        // Clamp to image bounds.
        if (minX < 0) minX = 0;
        if (minY < 0) minY = 0;
        if (maxX > m_Image.GetWidth())  maxX = m_Image.GetWidth();
        if (maxY > m_Image.GetHeight()) maxY = m_Image.GetHeight();
        m_iSelectionOriginX = minX;
        m_iSelectionOriginY = minY;
        m_iSelectionWidth  = maxX - minX;
        m_iSelectionHeight = maxY - minY;
        if (m_iSelectionWidth > 0 && m_iSelectionHeight > 0)
        {
            m_SelectedBitmap = m_Bitmap.GetSubBitmap(
                wxRect(m_iSelectionOriginX, m_iSelectionOriginY,
                       m_iSelectionWidth, m_iSelectionHeight));
            m_iSelectionMoveX = m_iSelectionOriginX;
            m_iSelectionMoveY = m_iSelectionOriginY;
            m_selectionOutline.clear();
            m_selectionOutline.reserve(m_drawLine.size());
            for (const wxPoint& p : m_drawLine)
            {
                m_selectionOutline.push_back(
                    wxPoint(p.x - m_iSelectionOriginX, p.y - m_iSelectionOriginY));
            }
            m_bHasSelection = true;
            m_bSelectionIsLasso = true;
            Refresh();
        }
        m_drawLine.clear();
        return;
    }

    // CONTINUE_DRAWING: extend the lasso and rubber-band the new segment.
    if (m_drawLine.empty())
    {
        m_drawLine.push_back(wxPoint(x, y));
    }
    else
    {
        wxPen dottedPen(*wxBLACK, 1, wxPENSTYLE_DOT);
        dc.SetPen(dottedPen);
        dc.SetLogicalFunction(wxINVERT);
        dc.DrawLine(m_prevX2, m_prevY2, x, y);
        m_drawLine.push_back(wxPoint(x, y));
    }
    m_prevX2 = x;
    m_prevY2 = y;
}

void OpenPaintMDIChildFrame::TextTool(int x, int y, wxColour color)
{
    wxString strText = wxGetTextFromUser(wxT("Write text."));

    // Apply the text-tool font settings from the ToolManager: face name,
    // point size, bold/italic/underline. If the face is empty, fall back
    // to whatever font the child frame currently has (so the old
    // wxGetFontFromUser dialog still works for picking faces).
    ToolManager* tm = Globals::Instance()->GetToolManager();
    wxFont font = GetFont();
    wxString face = tm->GetTextFontFace();
    if (!face.IsEmpty())
    {
        font.SetFaceName(face);
    }
    font.SetPointSize(tm->GetTextFontSize());
    font.SetStyle(tm->GetTextFontItalic() ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
    font.SetUnderlined(tm->GetTextFontUnderline());
    font.SetWeight(tm->GetTextFontBold() ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);

    // Drawing via wxMemoryDC + wxFont (the previous approach used
    // wxGraphicsContext but never deleted the context, leaking every
    // invocation; the graphics backend also has no easy way to honour the
    // font that the user picked in the Set Font dialog).
    wxMemoryDC mdc(m_Bitmap);
    mdc.SetFont(font);
    mdc.SetTextForeground(color);
    mdc.DrawText(strText, x, y);

    SetImage(m_Bitmap.ConvertToImage());
    Refresh();
}
