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


#ifndef __OpenPaintMDIChildFrame__
#define __OpenPaintMDIChildFrame__

/**
@file
Subclass of wxAuiMDIChildFrame
@todo Add your event handlers directly to this file.
*/

#include <wx/aui/aui.h>
#include <wx/bitmap.h>
#include <wx/gdicmn.h>
#include <wx/image.h>
#include <vector>
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

        void OnTabChanged( wxAuiNotebookEvent& event );
        //Image access functions
        void SetImage(wxImage image);
        void UpdateStatusBar();
        void SetThumbIcon();

        double GetZoom(){return m_dZoom;};
        void SetZoom(double dZoom);

        double m_dZoom;
        MouseStatus m_status;
        wxPoint m_ScrollOrigin;
        wxLongLong m_lastPixelStatusUpdate;
        wxStockCursor m_currentCursor;
        bool m_bUsingSprayCanCursor;

        // Per-frame tool state. These used to be file-scope globals shared by
        // every MDI child, which meant switching tabs in the middle of a
        // drawing operation could corrupt the rubber-band state of the other
        // tab. Keeping them per-frame is the fix.
        std::vector<wxPoint> m_drawLine;
        int m_prevX;
        int m_prevY;
        int m_prevX2;
        int m_prevY2;
        int m_curveStage;
        bool m_bCurvePreviewIsLine;
        wxPoint m_curveStart;
        wxPoint m_curveEnd;
        wxPoint m_curveControl1;
        wxPoint m_curvePreviewControl1;
        wxPoint m_curvePreviewControl2;
        bool m_bToolPreviewActive;
        int m_previewTool;
        wxColour m_previewColor;
        int m_previewPenWidth;
        wxPen m_customPen;
        wxBrush m_customBrush;

        //Selection Attributes
        wxBitmap m_SelectedBitmap;
        bool m_bHasSelection;
        bool m_bSelectionIsLasso;
        int m_iSelectionOriginX, m_iSelectionOriginY, m_iSelectionWidth, m_iSelectionHeight;
        int m_iSelectionMoveX, m_iSelectionMoveY;
        std::vector<wxPoint> m_selectionOutline;
        wxGenericDragImage * m_DragImage;

        // event handlers
        void OnClose(wxCloseEvent& event);
        //void OnIdle(wxIdleEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnMouse(wxMouseEvent& event);
        void OnMouseWheel(wxMouseEvent& event);
        void OnMouseLeave(wxMouseEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnScroll(wxScrollWinEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        void ApplyToolCursor(int x, int y);
        void SetCanvasCursor(wxStockCursor cursor);
        void SetSprayCanCursor();
        bool IsInsideImage(int x, int y) const;
        bool IsInsideSelection(int x, int y) const;
        void DrawSelectionOutline(wxDC& dc) const;
        void DrawToolPreview(wxDC& dc);
        void RefreshToolPreview();

        
        void PickColorTool(int x, int y, bool bIsForeground=true);
        void PencilTool(int x, int y, wxColour color, MouseStatus drawState);
        void BrushTool(int x, int y, wxColour color, MouseStatus drawState);
        // Renders a single brush "stamp" at (x, y) using the current
        // radius and tip (round / square / vertical line / horizontal line).
        void DrawBrushTip(wxDC& dc, int x, int y, int radius, int tip);
        // Stamps the brush tip at every integer pixel on the line from
        // (x0, y0) to (x1, y1). Guarantees no gaps between consecutive
        // mouse-move events regardless of the tip shape, which is
        // essential for the 1px-thick vertical/horizontal line tips.
        void StampBrushAlongLine(wxDC& dc, int x0, int y0, int x1, int y1,
                                 int radius, int tip);
        void FillTool(int x, int y, wxColour color);
        void MagnifyTool(int x, int y, int x2, int y2);
        void SprayCanTool(int x, int y, wxColour color);
        void LineTool(int x, int y, wxColour color, MouseStatus drawState);
        void CurveTool(int x, int y, wxColour color, MouseStatus drawState);
        void DrawCurvePath(wxDC& dc, const wxPoint& start, const wxPoint& control1,
                           const wxPoint& control2, const wxPoint& end);
        void DrawCurvePreview(wxDC& dc);
        void EllipseTool(int x, int y, wxColour color, MouseStatus drawState);
        void RectangleTool(int x, int y, wxColour color, MouseStatus drawState, bool bIsRounded = false);
        void PolygonTool(int x, int y, MouseStatus drawState);
        void SelectTool(int x, int y, MouseStatus drawState);
        void LassoSelectTool(int x, int y, MouseStatus drawState);
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
        wxImage GetImage(){return m_Image;};
        void RefreshToolCursor();


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
        void Rotate(double angleDegrees = 90.0);
        void Rescale(int iWidth, int iHeight);
        void Resize(int iWidth, int iHeight, int iOffsetX, int iOffsetY);

        void InvertColors();
        void Blur(int radius = 2);
        void Pixelize(int block = 10);
        void Greyscale();
        void Monochrome();
};

#endif // __OpenPaintMDIChildFrame__
