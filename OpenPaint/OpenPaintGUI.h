///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __OpenPaintGUI__
#define __OpenPaintGUI__

#include <wx/intl.h>

class PaletteCtrl;
class wxAuiMDIParentFrame;

#include "wx/aui/aui.h"
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

#include "resource.h"

///////////////////////////////////////////////////////////////////////////

#define IDX_NEW_FILE_320 1000
#define IDX_NEW_FILE_640 1001
#define IDX_NEW_FILE_1024 1002
#define IDX_MENU_EMPTY 1003
#define IDX_SELECT_ALL 1004
#define IDX_FILL_FG_COLOR 1005
#define IDX_FILL_BG_COLOR 1006
#define IDX_TOOL_WINDOW 1007
#define IDX_COLOR_WINDOW 1008
#define IDX_TOOLBAR 1009
#define IDX_STATUS_BAR 1010
#define IDX_ZOOM_OUT 1011
#define IDX_ZOOM_IN 1012
#define IDX_NORMAL_ZOOM 1013
#define IDX_HISTOGRAM 1014
#define IDX_FULLSCREEN 1015
#define IDX_FLIP_HORIZONTAL 1016
#define IDX_FLIP_VERTICAL 1017
#define IDX_ROTATE 1018
#define IDX_IMAGE_SIZE 1019
#define IDX_CANVAS_SIZE 1020
#define IDX_TOOL_BRUSH 1021
#define IDX_TOOL_ELLIPSE 1022
#define IDX_TOOL_ERASER 1023
#define IDX_TOOL_FILL 1024
#define IDX_TOOL_MAGNIFY 1025
#define IDX_TOOL_PENCIL 1026
#define IDX_TOOL_PICK_COLOR 1027
#define IDX_TOOL_POLYLINE 1028
#define IDX_TOOL_RECTANGLE 1029
#define IDX_TOOL_RECTANGLE_ROUNDED 1030
#define IDX_TOOL_SELECT 1031
#define IDX_TOOL_SELECT_LASSO 1032
#define IDX_TOOL_SPRAY_CAN 1033
#define IDX_TOOL_TEXT 1034
#define IDX_BLUR 1035
#define IDX_PIXELIZE 1036
#define IDX_GREYSCALE 1037
#define IDX_MONOCHROME 1038
#define IDX_FOREGROUND 1039
#define IDX_BACKGROUND 1040
#define IDX_PALETTE 1041
#define IDX_WIDTH 1042
#define IDX_HEIGHT 1043
#define IDX_LINK_PROPORTION 1044
#define IDX_OFFSET_X 1045
#define IDX_OFFSET_Y 1046

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxAuiMDIParentFrame
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menuFile;
		wxMenu* m_menuNew;
		wxMenu* m_menuRecentImages;
		wxMenu* m_menuEdit;
		wxMenu* m_menuView;
		wxMenu* m_menuWindows;
		wxMenu* m_menuImage;
		wxMenu* m_menuTools;
		wxMenu* m_menuFilters;
		wxMenu* m_menuOptions;
		wxMenu* m_menuColors;
		wxMenu* m_menuHelp;
		wxToolBar* m_toolBar1;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnNewFile320( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNewFile640( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNewFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNewFile1024( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOpenFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveAs( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnUndo( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRedo( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCut( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCopy( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPaste( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClear( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFillFGColor( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFillBGColor( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnToolWindow( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnColorWindow( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnToolbar( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnStatusBar( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnZoomOut( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnZoomIn( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNormalZoom( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnHistogram( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFullscreen( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFlipHorizontal( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFlipVertical( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRotate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnImageSize( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCanvasSize( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBrush( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEllipse( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEraser( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFill( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMagnify( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPencil( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPickColor( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPolyline( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRectangle( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRectangleRounded( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectLasso( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSprayCan( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnInvertColors( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBlur( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPixelize( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGreyscale( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMonochrome( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFont( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnForeground( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBackground( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRunProcess( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("OpenPaint"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ColorPanel
///////////////////////////////////////////////////////////////////////////////
class ColorPanel : public wxPanel 
{
	private:
	
	protected:
		wxColourPickerCtrl* m_colourPickerForeground;
		
		
		wxColourPickerCtrl* m_colourPickerBackground;
		PaletteCtrl* m_panelPalette0;
		PaletteCtrl* m_panelPalette1;
		PaletteCtrl* m_panelPalette2;
		PaletteCtrl* m_panelPalette3;
		PaletteCtrl* m_panelPalette4;
		PaletteCtrl* m_panelPalette5;
		PaletteCtrl* m_panelPalette6;
		PaletteCtrl* m_panelPalette7;
		PaletteCtrl* m_panelPalette8;
		PaletteCtrl* m_panelPalette9;
		PaletteCtrl* m_panelPalette10;
		PaletteCtrl* m_panelPalette11;
		PaletteCtrl* m_panelPalette12;
		PaletteCtrl* m_panelPalette13;
		PaletteCtrl* m_panelPalette14;
		PaletteCtrl* m_panelPalette15;
		PaletteCtrl* m_panelPalette16;
		PaletteCtrl* m_panelPalette17;
		PaletteCtrl* m_panelPalette18;
		PaletteCtrl* m_panelPalette19;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnForegroundSet( wxColourPickerEvent& event ){ event.Skip(); }
		virtual void OnBackgroundSet( wxColourPickerEvent& event ){ event.Skip(); }
		
	
	public:
		
		ColorPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~ColorPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ToolPanel
///////////////////////////////////////////////////////////////////////////////
class ToolPanel : public wxPanel 
{
	private:
	
	protected:
		wxBitmapButton* m_bpButtonSelect;
		wxBitmapButton* m_bpButtonEraser;
		wxBitmapButton* m_bpButtonFill;
		wxBitmapButton* m_bpButtonPickColor;
		wxBitmapButton* m_bpButtonMagnify;
		wxBitmapButton* m_bpButtonPencil;
		wxBitmapButton* m_bpButtonBrush;
		wxBitmapButton* m_bpButtonSprayCan;
		wxBitmapButton* m_bpButtonText;
		wxBitmapButton* m_bpButtonRectangle;
		wxBitmapButton* m_bpButtonEllipse;
		wxBitmapButton* m_bpButtonRectangleRounded;
		wxBitmapButton* m_bpButtonPolyline;
		wxBitmapButton* m_bpButtonSelectLasso;
		wxStaticBoxSizer* m_sbSizerToolProperties;
		wxPanel* m_panelTestTool;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSelect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEraser( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFill( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPickColor( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMagnify( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPencil( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBrush( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSprayCan( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRectangle( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEllipse( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRectangleRounded( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPolyline( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectLasso( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		
		ToolPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~ToolPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class BrushToolPanel
///////////////////////////////////////////////////////////////////////////////
class BrushToolPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxSpinCtrl* m_spinCtrlRadius;
		wxStaticText* m_staticText2;
		wxComboBox* m_comboBoxTip;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWidth( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnTip( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		
		BrushToolPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 147,300 ), long style = wxTAB_TRAVERSAL );
		~BrushToolPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CanvasSizeDialog
///////////////////////////////////////////////////////////////////////////////
class CanvasSizeDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText3;
		wxSpinCtrl* m_spinCtrlWidth;
		wxStaticText* m_staticText4;
		wxSpinCtrl* m_spinCtrlHeight;
		wxStaticText* m_staticText9;
		wxBitmapButton* m_bpButtonLink;
		wxStaticText* m_staticText10;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText7;
		wxSpinCtrl* m_spinCtrlOffsetX;
		wxStaticText* m_staticText8;
		wxSpinCtrl* m_spinCtrlOffsetY;
		wxButton* m_buttonCenter;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWidth( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnHeight( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnLink( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOffsetX( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnOffsetY( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnCenter( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		
		CanvasSizeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set Canvas Size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~CanvasSizeDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ImageSizeDialog
///////////////////////////////////////////////////////////////////////////////
class ImageSizeDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText3;
		wxSpinCtrl* m_spinCtrlWidth;
		wxStaticText* m_staticText4;
		wxSpinCtrl* m_spinCtrlHeight;
		wxStaticText* m_staticText9;
		wxBitmapButton* m_bpButtonLink;
		wxStaticText* m_staticText10;
		wxStaticLine* m_staticline1;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWidth( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnHeight( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnLink( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		
		ImageSizeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set Image Size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~ImageSizeDialog();
	
};

#endif //__OpenPaintGUI__
