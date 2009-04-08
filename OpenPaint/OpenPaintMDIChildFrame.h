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


#ifndef __OpenPaintMDIChildFrame__
#define __OpenPaintMDIChildFrame__

/**
@file
Subclass of wxAuiMDIChildFrame
@todo Add your event handlers directly to this file.
*/

#include <wx/aui/aui.h>
#include <wx/bitmap.h>
#include <wx/image.h>
class wxGraphicsContext;
class wxGenericDragImage;


/** Implementing wxAuiMDIChildFrame */
class OpenPaintMDIChildFrame : public wxAuiMDIChildFrame
{
    private:
        DECLARE_EVENT_TABLE()
   
        enum MouseStatus
        {
            MOUSE_NOACTION,
            MOUSE_BEGIN_DRAWING,
            MOUSE_CONTINUE_DRAWING,
            MOUSE_FINISHED_DRAWING
        };
    protected:
        wxBitmap m_Bitmap;
        wxImage m_Image;

        std::vector<wxImage> m_LastImages;
        bool m_bImageUpdated;
        int m_HistoryIndex;
        wxString m_strFilename;

        //Image access functions
        void SetImage(wxImage image);
        void SetThumbIcon();

        double GetZoom(){return m_dZoom;};
        void SetZoom(double dZoom);

        double m_dZoom;
        MouseStatus m_status;
        wxPoint m_ScrollOrigin;

        //Selection Attributes
        wxBitmap m_SelectedBitmap;
        bool m_bHasSelection;
        int m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight;
        int m_iSelectionMoveX, m_iSelectionMoveY;
        wxGenericDragImage * m_DragImage;

        // event handlers
        void OnClose(wxCloseEvent& event);
        //void OnIdle(wxIdleEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnMouseWheel(wxMouseEvent& event);
        void OnMouse(wxMouseEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnScroll(wxScrollWinEvent& event);
        void OnEraseBackground(wxEraseEvent& event);

        
        void PickColorTool(int x, int y, bool bIsForeground=true);
        void PencilTool(int x, int y, wxColour color, MouseStatus drawState);
        void BrushTool(int x, int y, wxColour color, MouseStatus drawState);
        void FillTool(int x, int y, wxColour color);
        void FillTool(int x, int y, wxColour color, wxColour colorOld);
        void MagnifyTool();
        void SprayCanTool(int x, int y, wxColour color);
        void EllipseTool(int x, int y, wxColour color, MouseStatus drawState);
        void RectangleTool(int x, int y, wxColour color, MouseStatus drawState, bool bIsRounded = false);
        void SelectTool(int x, int y, MouseStatus drawState);
        void TextTool(int x, int y, wxColour color);

    public:
	    /** Constructor */
	    OpenPaintMDIChildFrame( wxAuiMDIParentFrame* parent, int id = wxID_ANY, wxString title = wxT("New"), int iWidth = 800, int iHeight = 600);
        virtual ~OpenPaintMDIChildFrame();
        virtual void Shutdown();
        bool Open(wxString strFilename);
        bool Save();
        bool SaveAs(wxString strFilename);
        wxString GetFilename();
        int GetWidth();
        int GetHeight();

        void Undo();
        void Redo();
        wxBitmap Cut();
        wxBitmap Copy();
        void Paste(wxBitmap bitmap);
        void Delete();
        void SelectAll();
        void Clear();
        void FillFGColor();
        void FillBGColor();

        void ZoomOut();
        void ZoomIn();
        void NormalZoom();

        void FlipHorizontal();
        void FlipVertical();
        void Rotate();
        void Rescale(int iWidth, int iHeight);
        void Resize(int iWidth, int iHeight, int iOffsetX, int iOffsetY);

        void InvertColors();
        void Blur();
        void Pixelize();
        void Greyscale();
        void Monochrome();
};

#endif // __OpenPaintMDIChildFrame__
