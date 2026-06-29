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
#include <wx/region.h>
#include <wx/timer.h>
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

        double m_dZoom = 1.0;
        MouseStatus m_status;
        wxPoint m_ScrollOrigin;
        wxLongLong m_lastPixelStatusUpdate;
        wxStockCursor m_currentCursor;
        bool m_bUsingSprayCanCursor;

        // Per-frame tool state. These used to be file-scope globals shared by
        // every MDI child, which meant switching tabs in the middle of a
        // drawing operation could corrupt the rubber-band state of the other
        // tab. Keeping them per-frame is the fix.
        // Same caveat as the selection members above: default-initialise so
        // an early paint event during construction can't read garbage.
        std::vector<wxPoint> m_drawLine;
        int m_prevX = 0;
        int m_prevY = 0;
        int m_prevX2 = 0;
        int m_prevY2 = 0;
        int m_curveStage = 0;
        bool m_bCurvePreviewIsLine = false;
        wxPoint m_curveStart;
        wxPoint m_curveEnd;
        wxPoint m_curveControl1;
        wxPoint m_curvePreviewControl1;
        wxPoint m_curvePreviewControl2;
        bool m_bToolPreviewActive = false;
        int m_previewTool = 0;
        wxColour m_previewColor;
        int m_previewPenWidth = 1;
        wxPen m_customPen;
        wxBrush m_customBrush;

        //Selection Attributes
        // Members that are read by OnPaint / DrawSelectionOutline / DrawToolPreview
        // must be default-initialised here, NOT in the constructor body. The
        // base wxAuiMDIChildFrame constructor plus our own SetZoom(1.0) call
        // can post a paint event that the message loop dispatches before the
        // rest of the derived constructor body has run; if these members are
        // uninitialised at that point, DrawSelectionOutline's guard falls
        // through and the for loop iterates up to INT_MAX times, hanging the
        // UI thread inside std::vector::push_back.
        wxBitmap m_SelectedBitmap;
        bool m_bHasSelection = false;
        bool m_bSelectionIsLasso = false;
        bool m_bSelectionFloating = false;
        int m_iSelectionOriginX = -1;
        int m_iSelectionOriginY = -1;
        int m_iSelectionWidth = -1;
        int m_iSelectionHeight = -1;
        int m_iSelectionMoveX = -1;
        int m_iSelectionMoveY = -1;
        std::vector<wxPoint> m_selectionOutline;
        wxRegion m_selectionRegion;
        wxGenericDragImage * m_DragImage = nullptr;
        wxTimer m_selectionTimer;
        int m_selectionDashOffset = 0;

        // event handlers
        void OnClose(wxCloseEvent& event);
        //void OnIdle(wxIdleEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnMouse(wxMouseEvent& event);
        void OnMouseWheel(wxMouseEvent& event);
        void OnMouseLeave(wxMouseEvent& event);
        void OnSize(wxSizeEvent& event);
        void UpdateScrollbars(int w, int h);
        void OnScroll(wxScrollWinEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        void OnSelectionTimer(wxTimerEvent& event);
        void ApplyToolCursor(int x, int y);
        void SetCanvasCursor(wxStockCursor cursor);
        void SetSprayCanCursor();
        bool IsInsideImage(int x, int y) const;
        bool IsInsideSelection(int x, int y) const;
        void DrawSelectionOutline(wxDC& dc) const;
        void ClearSelection();
        void CommitSelection();
        void StartSelectionAnimation();
        void StopSelectionAnimation();
        bool IsSelectionPixel(int localX, int localY) const;
        void BuildSelectionBitmapFromRegion();
        void FillSelectionRegion(const wxColour& color);
        void DrawToolPreview(wxDC& dc);
        void RefreshToolPreview();

        
        void PickColorTool(int x, int y, bool bIsForeground=true, bool bIsAlternate=false);
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
        void EllipseTool(int x, int y, wxColour color, MouseStatus drawState, wxColour fillColor = wxColour());
        void RectangleTool(int x, int y, wxColour color, MouseStatus drawState, bool bIsRounded = false, wxColour fillColor = wxColour());
        void PolygonTool(int x, int y, MouseStatus drawState, wxColour color = wxColour(), wxColour fillColor = wxColour());
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

