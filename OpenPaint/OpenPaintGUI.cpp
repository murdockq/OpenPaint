///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifdef WX_PRECOMP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#else
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "PaletteCtrl.h"
#include "ColorPairCtrl.h"

#include "BrushSamp.h"
#include "IconLoader.h"
#include "OpenPaintGUI.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxAuiMDIParentFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menuNew = new wxMenu();
	wxMenuItem* menuItemNewFile320;
	menuItemNewFile320 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_320, wxString( _("320x240") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile320 );
	
	wxMenuItem* menuItemNewFile640;
	menuItemNewFile640 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_640, wxString( _("640x480") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile640 );
	
	wxMenuItem* menuItemNewFile;
	menuItemNewFile = new wxMenuItem( m_menuNew, wxID_NEW, wxString( _("800x600") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile );
	
	wxMenuItem* menuItemNewFile1024;
	menuItemNewFile1024 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_1024, wxString( _("1024x768") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile1024 );
	
	wxMenuItem* menuItemNewSubmenu;
	menuItemNewSubmenu = m_menuFile->Append( -1, _("New"), m_menuNew );
	menuItemNewSubmenu->SetBitmap( IconLoader::Load( wxT("new"), wxSize( 16,16 ) ) );
	
	wxMenuItem* menuItemOpen;
	menuItemOpen = new wxMenuItem( m_menuFile, wxID_OPEN, wxString( _("Open...") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	menuItemOpen->SetBitmap( IconLoader::Load( wxT("open"), wxSize( 16,16 ) ) );
	m_menuFile->Append( menuItemOpen );
	
	wxMenuItem* menuItemSave;
	menuItemSave = new wxMenuItem( m_menuFile, wxID_SAVE, wxString( _("Save") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	menuItemSave->SetBitmap( IconLoader::Load( wxT("save"), wxSize( 16,16 ) ) );
	m_menuFile->Append( menuItemSave );
	
	wxMenuItem* menuItemSaveAs;
	menuItemSaveAs = new wxMenuItem( m_menuFile, wxID_SAVEAS, wxString( _("Save As...") ) + wxT('\t') + wxT("Ctrl+Shift+S"), wxEmptyString, wxITEM_NORMAL );
	menuItemSaveAs->SetBitmap( IconLoader::Load( wxT("save"), wxSize( 16,16 ) ) );
	m_menuFile->Append( menuItemSaveAs );
	
	m_menuFile->AppendSeparator();
	
	m_menuRecentImages = new wxMenu();
	wxMenuItem* menuItemEMPTYFile;
	menuItemEMPTYFile = new wxMenuItem( m_menuRecentImages, IDX_MENU_EMPTY, wxString( _("Empty") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRecentImages->Append( menuItemEMPTYFile );
	menuItemEMPTYFile->Enable( false );
	
	m_menuFile->Append( -1, _("Recent Files"), m_menuRecentImages );
	
	m_menuFile->AppendSeparator();
	
	wxMenuItem* menuItemExit;
	menuItemExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("Exit") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuItemExit );
	
	m_menubar1->Append( m_menuFile, _("&File") );
	
	m_menuEdit = new wxMenu();
	wxMenuItem* menuItemUndo;
	menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	menuItemUndo->SetBitmap( IconLoader::Load( wxT("undo"), wxSize( 16,16 ) ) );
	m_menuEdit->Append( menuItemUndo );
	menuItemUndo->Enable( false );
	
	wxMenuItem* menuItemRedo;
	menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("Redo") ) + wxT('\t') + wxT("Ctrl+Y"), wxEmptyString, wxITEM_NORMAL );
	menuItemRedo->SetBitmap( IconLoader::Load( wxT("redo"), wxSize( 16,16 ) ) );
	m_menuEdit->Append( menuItemRedo );
	menuItemRedo->Enable( false );
	
	m_menuEdit->AppendSeparator();
	
	wxMenuItem* menuItemCut;
	menuItemCut = new wxMenuItem( m_menuEdit, wxID_CUT, wxString( _("Cut") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemCut );
	
	wxMenuItem* menuItemCopy;
	menuItemCopy = new wxMenuItem( m_menuEdit, wxID_COPY, wxString( _("Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemCopy );
	
	wxMenuItem* menuItemPaste;
	menuItemPaste = new wxMenuItem( m_menuEdit, wxID_PASTE, wxString( _("Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemPaste );
	
	wxMenuItem* menuItemDelete;
	menuItemDelete = new wxMenuItem( m_menuEdit, wxID_DELETE, wxString( _("Delete") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemDelete );
	
	m_menuEdit->AppendSeparator();
	
	wxMenuItem* menuItemSelectAll;
	menuItemSelectAll = new wxMenuItem( m_menuEdit, IDX_SELECT_ALL, wxString( _("Select All") ) + wxT('\t') + wxT("Ctrl+A"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemSelectAll );
	
	m_menuEdit->AppendSeparator();
	
	wxMenuItem* menuItemClear;
	menuItemClear = new wxMenuItem( m_menuEdit, wxID_ANY, wxString( _("Clear") ) + wxT('\t') + wxT("Ctrl+K"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemClear );
	
	wxMenuItem* menuItemFillFGColor;
	menuItemFillFGColor = new wxMenuItem( m_menuEdit, IDX_FILL_FG_COLOR, wxString( _("Fill with FG Color") ) + wxT('\t') + wxT("Ctrl+,"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemFillFGColor );
	
	wxMenuItem* menuItemFillBGColor;
	menuItemFillBGColor = new wxMenuItem( m_menuEdit, IDX_FILL_BG_COLOR, wxString( _("Fill with BG Color") ) + wxT('\t') + wxT("Ctrl+."), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemFillBGColor );
	
	m_menubar1->Append( m_menuEdit, _("&Edit") );
	
	m_menuView = new wxMenu();
	m_menuWindows = new wxMenu();
	wxMenuItem* m_menuItemToolWindow;
	m_menuItemToolWindow = new wxMenuItem( m_menuWindows, IDX_TOOL_WINDOW, wxString( _("Tool Window") ) , wxEmptyString, wxITEM_CHECK );
	m_menuWindows->Append( m_menuItemToolWindow );
	m_menuItemToolWindow->Check( true );
	
	wxMenuItem* m_menuItemColorWindow;
	m_menuItemColorWindow = new wxMenuItem( m_menuWindows, IDX_COLOR_WINDOW, wxString( _("Color Window") ) , wxEmptyString, wxITEM_CHECK );
	m_menuWindows->Append( m_menuItemColorWindow );
	m_menuItemColorWindow->Check( true );
	
	m_menuView->Append( -1, _("Windows"), m_menuWindows );
	
	wxMenuItem* m_menuItemToolbar;
	m_menuItemToolbar = new wxMenuItem( m_menuView, IDX_TOOLBAR, wxString( _("Toolbar") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemToolbar );
	m_menuItemToolbar->Check( true );
	
	wxMenuItem* m_menuItemStatusBar;
	m_menuItemStatusBar = new wxMenuItem( m_menuView, IDX_STATUS_BAR, wxString( _("Status Bar") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemStatusBar );
	m_menuItemStatusBar->Check( true );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* menuItemZoomOut;
	menuItemZoomOut = new wxMenuItem( m_menuView, IDX_ZOOM_OUT, wxString( _("Zoom Out") ) + wxT('\t') + wxT("-"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemZoomOut );
	
	wxMenuItem* menuItemZoomIn;
	menuItemZoomIn = new wxMenuItem( m_menuView, IDX_ZOOM_IN, wxString( _("Zoom In") ) + wxT('\t') + wxT("+"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemZoomIn );
	
	wxMenuItem* menuItemNormalZoom;
	menuItemNormalZoom = new wxMenuItem( m_menuView, IDX_NORMAL_ZOOM, wxString( _("Normal Zoom") ) + wxT('\t') + wxT("1"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemNormalZoom );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemHistogram;
	m_menuItemHistogram = new wxMenuItem( m_menuView, IDX_HISTOGRAM, wxString( _("Histogra&m") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemHistogram );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* menuItemFullscreen;
	menuItemFullscreen = new wxMenuItem( m_menuView, IDX_FULLSCREEN, wxString( _("Fullscreen") ) + wxT('\t') + wxT("F12"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( menuItemFullscreen );
	
	m_menubar1->Append( m_menuView, _("&View") );
	
	m_menuImage = new wxMenu();
	wxMenuItem* menuItemFlipHorizontal;
	menuItemFlipHorizontal = new wxMenuItem( m_menuImage, IDX_FLIP_HORIZONTAL, wxString( _("Flip Horizontal") ) + wxT('\t') + wxT("Ctrl+Shift+H"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemFlipHorizontal );
	
	wxMenuItem* menuItemFlipVertical;
	menuItemFlipVertical = new wxMenuItem( m_menuImage, IDX_FLIP_VERTICAL, wxString( _("Flip Vertical") ) + wxT('\t') + wxT("Ctrl+Shift+V"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemFlipVertical );
	
	m_menuImage->AppendSeparator();
	
	wxMenuItem* menuItemRotate;
	menuItemRotate = new wxMenuItem( m_menuImage, IDX_ROTATE, wxString( _("Rotate") ) + wxT('\t') + wxT("Ctrl+Shift+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemRotate );
	
	m_menuImage->AppendSeparator();
	
	wxMenuItem* menuItemImageSize;
	menuItemImageSize = new wxMenuItem( m_menuImage, IDX_IMAGE_SIZE, wxString( _("Image Size...") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemImageSize );
	
	wxMenuItem* menuItemCanvasSize;
	menuItemCanvasSize = new wxMenuItem( m_menuImage, IDX_CANVAS_SIZE, wxString( _("Canvas Size...") ) + wxT('\t') + wxT("Ctrl+E"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemCanvasSize );
	
	m_menubar1->Append( m_menuImage, _("&Image") );
	
	m_menuTools = new wxMenu();
	wxMenuItem* menuItemSelectLasso;
	menuItemSelectLasso = new wxMenuItem( m_menuTools, IDX_TOOL_SELECT_LASSO, wxString( _("Free-form Select") ) + wxT('\t') + wxT("L"), wxEmptyString, wxITEM_NORMAL );
	menuItemSelectLasso->SetBitmap( IconLoader::Load( wxT("select-lasso"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemSelectLasso );

	wxMenuItem* menuItemSelect;
	menuItemSelect = new wxMenuItem( m_menuTools, IDX_TOOL_SELECT, wxString( _("Select") ) + wxT('\t') + wxT("S"), wxEmptyString, wxITEM_NORMAL );
	menuItemSelect->SetBitmap( IconLoader::Load( wxT("select-rectangular"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemSelect );

	m_menuTools->AppendSeparator();

	wxMenuItem* menuItemEraser;
	menuItemEraser = new wxMenuItem( m_menuTools, IDX_TOOL_ERASER, wxString( _("Eraser") ) + wxT('\t') + wxT("E"), wxEmptyString, wxITEM_NORMAL );
	menuItemEraser->SetBitmap( IconLoader::Load( wxT("draw-eraser"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemEraser );

	wxMenuItem* menuItemFill;
	menuItemFill = new wxMenuItem( m_menuTools, IDX_TOOL_FILL, wxString( _("Fill Bucket") ) + wxT('\t') + wxT("F"), wxEmptyString, wxITEM_NORMAL );
	menuItemFill->SetBitmap( IconLoader::Load( wxT("color-fill"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemFill );

	wxMenuItem* menuItemPickColor;
	menuItemPickColor = new wxMenuItem( m_menuTools, IDX_TOOL_PICK_COLOR, wxString( _("Pick Color") ) + wxT('\t') + wxT("C"), wxEmptyString, wxITEM_NORMAL );
	menuItemPickColor->SetBitmap( IconLoader::Load( wxT("color-picker"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemPickColor );

	wxMenuItem* menuItemMagnify;
	menuItemMagnify = new wxMenuItem( m_menuTools, IDX_TOOL_MAGNIFY, wxString( _("Magnify") ) + wxT('\t') + wxT("M"), wxEmptyString, wxITEM_NORMAL );
	menuItemMagnify->SetBitmap( IconLoader::Load( wxT("page-magnifier"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemMagnify );

	m_menuTools->AppendSeparator();

	wxMenuItem* menuItemPencil;
	menuItemPencil = new wxMenuItem( m_menuTools, IDX_TOOL_PENCIL, wxString( _("Pencil") ) + wxT('\t') + wxT("P"), wxEmptyString, wxITEM_NORMAL );
	menuItemPencil->SetBitmap( IconLoader::Load( wxT("draw-freehand"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemPencil );

	wxMenuItem* menuItemBrush;
	menuItemBrush = new wxMenuItem( m_menuTools, IDX_TOOL_BRUSH, wxString( _("Brush") ) + wxT('\t') + wxT("B"), wxEmptyString, wxITEM_NORMAL );
	menuItemBrush->SetBitmap( IconLoader::Load( wxT("draw-brush"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemBrush );

	wxMenuItem* menuItemSprayCan;
	menuItemSprayCan = new wxMenuItem( m_menuTools, IDX_TOOL_SPRAY_CAN, wxString( _("Airbrush") ) + wxT('\t') + wxT("A"), wxEmptyString, wxITEM_NORMAL );
	menuItemSprayCan->SetBitmap( IconLoader::Load( wxT("draw-airbrush"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemSprayCan );

	wxMenuItem* menuItemText;
	menuItemText = new wxMenuItem( m_menuTools, IDX_TOOL_TEXT, wxString( _("Text") ) + wxT('\t') + wxT("T"), wxEmptyString, wxITEM_NORMAL );
	menuItemText->SetBitmap( IconLoader::Load( wxT("draw-text"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemText );

	m_menuTools->AppendSeparator();

	wxMenuItem* menuItemLine;
	menuItemLine = new wxMenuItem( m_menuTools, IDX_TOOL_LINE, wxString( _("Line") ), wxEmptyString, wxITEM_NORMAL );
	menuItemLine->SetBitmap( IconLoader::Load( wxT("draw-line"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemLine );

	wxMenuItem* menuItemCurve;
	menuItemCurve = new wxMenuItem( m_menuTools, IDX_TOOL_CURVE, wxString( _("Curve") ), wxEmptyString, wxITEM_NORMAL );
	menuItemCurve->SetBitmap( IconLoader::Load( wxT("draw-curve"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemCurve );

	wxMenuItem* menuItemPolygon;
	menuItemPolygon = new wxMenuItem( m_menuTools, IDX_TOOL_POLYGON, wxString( _("Polygon") ), wxEmptyString, wxITEM_NORMAL );
	menuItemPolygon->SetBitmap( IconLoader::Load( wxT("draw-polygon"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemPolygon );

	wxMenuItem* menuItemRectangle;
	menuItemRectangle = new wxMenuItem( m_menuTools, IDX_TOOL_RECTANGLE, wxString( _("Rectangle") ) + wxT('\t') + wxT("R"), wxEmptyString, wxITEM_NORMAL );
	menuItemRectangle->SetBitmap( IconLoader::Load( wxT("draw-rectangle"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemRectangle );

	wxMenuItem* menuItemEllipse;
	menuItemEllipse = new wxMenuItem( m_menuTools, IDX_TOOL_ELLIPSE, wxString( _("Ellipse") ) + wxT('\t') + wxT("O"), wxEmptyString, wxITEM_NORMAL );
	menuItemEllipse->SetBitmap( IconLoader::Load( wxT("draw-ellipse"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemEllipse );

	wxMenuItem* menuItemRectangleRounded;
	menuItemRectangleRounded = new wxMenuItem( m_menuTools, IDX_TOOL_RECTANGLE_ROUNDED, wxString( _("Rounded Rectangle") ) + wxT('\t') + wxT("Q"), wxEmptyString, wxITEM_NORMAL );
	menuItemRectangleRounded->SetBitmap( IconLoader::Load( wxT("draw-rectangle-rounded"), wxSize( 16,16 ) ) );
	m_menuTools->Append( menuItemRectangleRounded );
	
	m_menubar1->Append( m_menuTools, _("&Tools") );
	
	m_menuFilters = new wxMenu();
	wxMenuItem* menuItemInvert;
	menuItemInvert = new wxMenuItem( m_menuFilters, wxID_ANY, wxString( _("Invert Colors") ) + wxT('\t') + wxT("Ctrl+I"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemInvert );
	
	wxMenuItem* menuItemBlur;
	menuItemBlur = new wxMenuItem( m_menuFilters, IDX_BLUR, wxString( _("Blur") ) + wxT('\t') + wxT("Ctrl+B"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemBlur );
	
	wxMenuItem* menuItemPixelize;
	menuItemPixelize = new wxMenuItem( m_menuFilters, IDX_PIXELIZE, wxString( _("Pixelize") ) + wxT('\t') + wxT("Ctrl+P"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemPixelize );
	
	wxMenuItem* menuItemGreyscale;
	menuItemGreyscale = new wxMenuItem( m_menuFilters, IDX_GREYSCALE, wxString( _("Greyscale") ) + wxT('\t') + wxT("Ctrl+G"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemGreyscale );
	
	wxMenuItem* menuItemMonochrome;
	menuItemMonochrome = new wxMenuItem( m_menuFilters, IDX_MONOCHROME, wxString( _("Monochrome") ) + wxT('\t') + wxT("Ctrl+M"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemMonochrome );
	
	m_menubar1->Append( m_menuFilters, _("Filte&rs") );
	
	m_menuOptions = new wxMenu();
	wxMenuItem* m_menuItemFont;
	m_menuItemFont = new wxMenuItem( m_menuOptions, wxID_ANY, wxString( _("Set Font...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuOptions->Append( m_menuItemFont );
	
	m_menuColors = new wxMenu();
	wxMenuItem* menuItemForeground;
	menuItemForeground = new wxMenuItem( m_menuColors, IDX_FOREGROUND, wxString( _("Set Foreground...") ) + wxT('\t') + wxT("Ctrl+Shift+F"), wxEmptyString, wxITEM_NORMAL );
	m_menuColors->Append( menuItemForeground );
	
	wxMenuItem* menuItemBackground;
	menuItemBackground = new wxMenuItem( m_menuColors, IDX_BACKGROUND, wxString( _("Set Background...") ) + wxT('\t') + wxT("Ctrl+Shift+B"), wxEmptyString, wxITEM_NORMAL );
	m_menuColors->Append( menuItemBackground );
	
	m_menuOptions->Append( -1, _("Colors"), m_menuColors );
	
	m_menubar1->Append( m_menuOptions, _("&Options") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* menuItemAbout;
	menuItemAbout = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( _("About...") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( menuItemAbout );
	
	m_menubar1->Append( m_menuHelp, _("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_DOCKABLE|wxTB_FLAT, wxID_ANY );
	// Logical tool size, in DIPs. On HiDPI displays wxWidgets scales the
	// bitmap up to physical pixels automatically, so 24x24 is the modern
	// flat-icon size — the previous 32x32 was inherited from the original
	// 2008 raster set.
	m_toolBar1->SetToolBitmapSize( IconLoader::LogicalToolbarSize() );
	// IconLoader picks the SVG when wxWidgets is built with wxUSE_SVG=1, and
	// falls through to the XPM / legacy wxICON() otherwise, so this works on
	// every existing build.
	m_toolBar1->AddTool( wxID_NEW, _("New"), IconLoader::Load( wxT("new"), IconLoader::LogicalToolbarSize() ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Create a new 800x600 image.") );
	m_toolBar1->AddTool( wxID_OPEN, _("Open"), IconLoader::Load( wxT("open"), IconLoader::LogicalToolbarSize() ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Open an image file.") );
	m_toolBar1->AddTool( wxID_SAVE, _("Save"), IconLoader::Load( wxT("save"), IconLoader::LogicalToolbarSize() ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Save current file.") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( wxID_UNDO, _("Undo"), IconLoader::Load( wxT("undo"), IconLoader::LogicalToolbarSize() ), wxNullBitmap, wxITEM_NORMAL, _("Undo (Ctrl +Z)"), _("Undo the last action.") );
	m_toolBar1->AddTool( wxID_REDO, _("Redo"), IconLoader::Load( wxT("redo"), IconLoader::LogicalToolbarSize() ), wxNullBitmap, wxITEM_NORMAL, _("Redo (Ctrl +Z)"), _("Redo the last action that was undone.") );
	m_toolBar1->AddSeparator();
	m_toolBar1->Realize();
	
	m_statusBar1 = this->CreateStatusBar( 4, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
	this->Connect( menuItemNewFile320->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile320 ) );
	this->Connect( menuItemNewFile640->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile640 ) );
	this->Connect( menuItemNewFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile ) );
	this->Connect( menuItemNewFile1024->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile1024 ) );
	this->Connect( menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnOpenFile ) );
	this->Connect( menuItemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSave ) );
	this->Connect( menuItemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSaveAs ) );
	this->Connect( menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnExit ) );
	this->Connect( menuItemUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUndo ) );
	this->Connect( menuItemRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRedo ) );
	this->Connect( menuItemCut->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCut ) );
	this->Connect( menuItemCopy->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCopy ) );
	this->Connect( menuItemPaste->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPaste ) );
	this->Connect( menuItemDelete->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnDelete ) );
	this->Connect( menuItemSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectAll ) );
	this->Connect( menuItemClear->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnClear ) );
	this->Connect( menuItemFillFGColor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFillFGColor ) );
	this->Connect( menuItemFillBGColor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFillBGColor ) );
	this->Connect( m_menuItemToolWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnToolWindow ) );
	this->Connect( m_menuItemColorWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnColorWindow ) );
	this->Connect( m_menuItemToolbar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnToolbar ) );
	this->Connect( m_menuItemStatusBar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnStatusBar ) );
	this->Connect( menuItemZoomOut->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomOut ) );
	this->Connect( menuItemZoomIn->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomIn ) );
	this->Connect( menuItemNormalZoom->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNormalZoom ) );
	this->Connect( m_menuItemHistogram->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnHistogram ) );
	this->Connect( menuItemFullscreen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFullscreen ) );
	this->Connect( menuItemFlipHorizontal->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFlipHorizontal ) );
	this->Connect( menuItemFlipVertical->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFlipVertical ) );
	this->Connect( menuItemRotate->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRotate ) );
	this->Connect( menuItemImageSize->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnImageSize ) );
	this->Connect( menuItemCanvasSize->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCanvasSize ) );
	this->Connect( menuItemBrush->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBrush ) );
	this->Connect( menuItemEllipse->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEllipse ) );
	this->Connect( menuItemEraser->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEraser ) );
	this->Connect( menuItemFill->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFill ) );
	this->Connect( menuItemMagnify->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMagnify ) );
	this->Connect( menuItemPencil->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPencil ) );
	this->Connect( menuItemPickColor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPickColor ) );
	this->Connect( menuItemLine->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnLine ) );
	this->Connect( menuItemCurve->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCurve ) );
	this->Connect( menuItemPolygon->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPolygon ) );
	this->Connect( menuItemRectangle->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRectangle ) );
	this->Connect( menuItemRectangleRounded->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRectangleRounded ) );
	this->Connect( menuItemSelect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelect ) );
	this->Connect( menuItemSelectLasso->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectLasso ) );
	this->Connect( menuItemSprayCan->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSprayCan ) );
	this->Connect( menuItemText->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnText ) );
	this->Connect( menuItemInvert->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnInvertColors ) );
	this->Connect( menuItemBlur->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBlur ) );
	this->Connect( menuItemPixelize->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPixelize ) );
	this->Connect( menuItemGreyscale->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnGreyscale ) );
	this->Connect( menuItemMonochrome->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMonochrome ) );
	this->Connect( m_menuItemFont->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFont ) );
	this->Connect( menuItemForeground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnForeground ) );
	this->Connect( menuItemBackground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBackground ) );
	this->Connect( menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnAbout ) );
	this->Connect( wxID_REDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnRedo ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile320 ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile640 ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNewFile1024 ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnOpenFile ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUndo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRedo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCut ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCopy ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPaste ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnDelete ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectAll ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnClear ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFillFGColor ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFillBGColor ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnToolWindow ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnColorWindow ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnToolbar ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnStatusBar ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomOut ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomIn ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNormalZoom ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnHistogram ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFullscreen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFlipHorizontal ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFlipVertical ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRotate ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnImageSize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnCanvasSize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBrush ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEllipse ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEraser ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFill ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMagnify ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPencil ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPickColor ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRectangle ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnRectangleRounded ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelect ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectLasso ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSprayCan ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnText ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnInvertColors ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBlur ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPixelize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnGreyscale ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMonochrome ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnFont ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnForeground ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBackground ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnAbout ) );
	this->Disconnect( wxID_REDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnRedo ) );
}

ColorPanel::ColorPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	m_colourPickerPair = new ColorPairCtrl( this, wxID_ANY );
	m_colourPickerPair->SetFGColour( wxColour( 0, 0, 0 ) );
	m_colourPickerPair->SetBGColour( wxColour( 255, 255, 255 ) );
	m_colourPickerPair->SetAltColour( wxColour() );

	sbSizer3->Add( m_colourPickerPair, 0, 0, 0 );
	
	bSizer4->Add( sbSizer3, 0, 0, 0 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 10, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_panelPalette0 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette0->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette0, 0, wxALL, 0 );
	
	m_panelPalette1 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette1->SetBackgroundColour( wxColour( 128, 128, 128 ) );
	
	fgSizer3->Add( m_panelPalette1, 0, wxALL, 0 );
	
	m_panelPalette2 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette2->SetBackgroundColour( wxColour( 128, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette2, 0, wxALL, 0 );
	
	m_panelPalette3 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette3->SetBackgroundColour( wxColour( 128, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette3, 0, wxALL, 0 );
	
	m_panelPalette4 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette4->SetBackgroundColour( wxColour( 0, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette4, 0, wxALL, 0 );
	
	m_panelPalette5 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette5->SetBackgroundColour( wxColour( 255, 128, 64 ) );
	
	fgSizer3->Add( m_panelPalette5, 0, wxALL, 0 );
	
	m_panelPalette6 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette6->SetBackgroundColour( wxColour( 0, 128, 192 ) );
	
	fgSizer3->Add( m_panelPalette6, 0, wxALL, 0 );
	
	m_panelPalette7 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette7->SetBackgroundColour( wxColour( 0, 0, 64 ) );
	
	fgSizer3->Add( m_panelPalette7, 0, wxALL, 0 );
	
	m_panelPalette8 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette8->SetBackgroundColour( wxColour( 128, 128, 255 ) );
	
	fgSizer3->Add( m_panelPalette8, 0, wxALL, 0 );
	
	m_panelPalette9 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette9->SetBackgroundColour( wxColour( 0, 0, 128 ) );
	
	fgSizer3->Add( m_panelPalette9, 0, wxALL, 0 );
	
	m_panelPalette10 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette10->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	fgSizer3->Add( m_panelPalette10, 0, wxALL, 0 );
	
	m_panelPalette11 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette11->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	fgSizer3->Add( m_panelPalette11, 0, wxALL, 0 );
	
	m_panelPalette12 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette12->SetBackgroundColour( wxColour( 255, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette12, 0, wxALL, 0 );
	
	m_panelPalette13 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette13->SetBackgroundColour( wxColour( 255, 255, 0 ) );
	
	fgSizer3->Add( m_panelPalette13, 0, wxALL, 0 );
	
	m_panelPalette14 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette14->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	
	fgSizer3->Add( m_panelPalette14, 0, wxALL, 0 );
	
	m_panelPalette15 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette15->SetBackgroundColour( wxColour( 128, 255, 255 ) );
	
	fgSizer3->Add( m_panelPalette15, 0, wxALL, 0 );
	
	m_panelPalette16 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette16->SetBackgroundColour( wxColour( 0, 0, 255 ) );
	
	fgSizer3->Add( m_panelPalette16, 0, wxALL, 0 );
	
	m_panelPalette17 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette17->SetBackgroundColour( wxColour( 255, 128, 255 ) );
	
	fgSizer3->Add( m_panelPalette17, 0, wxALL, 0 );
	
	m_panelPalette18 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette18->SetBackgroundColour( wxColour( 255, 255, 128 ) );
	
	fgSizer3->Add( m_panelPalette18, 0, wxALL, 0 );
	
	m_panelPalette19 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( 22, 22 ), wxSUNKEN_BORDER );
	m_panelPalette19->SetBackgroundColour( wxColour( 255, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette19, 0, wxALL, 0 );
	
	sbSizer4->Add( fgSizer3, 1, wxEXPAND, 5 );

	bSizer4->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
}

ColorPanel::~ColorPanel()
{
}

ToolPanel::ToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bpButtonSelectLasso = new wxBitmapButton( this, IDX_TOOL_SELECT_LASSO, IconLoader::Load( wxT("select-lasso"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonSelectLasso, 0, wxALL, 0 );

	m_bpButtonSelect = new wxBitmapButton( this, IDX_TOOL_SELECT, IconLoader::Load( wxT("select-rectangular"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonSelect, 0, wxALL, 0 );

	m_bpButtonEraser = new wxBitmapButton( this, IDX_TOOL_ERASER, IconLoader::Load( wxT("draw-eraser"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonEraser, 0, wxALL, 0 );

	m_bpButtonFill = new wxBitmapButton( this, IDX_TOOL_FILL, IconLoader::Load( wxT("color-fill"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonFill, 0, wxALL, 0 );

	m_bpButtonPickColor = new wxBitmapButton( this, IDX_TOOL_PICK_COLOR, IconLoader::Load( wxT("color-picker"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonPickColor, 0, wxALL, 0 );

	m_bpButtonMagnify = new wxBitmapButton( this, IDX_TOOL_MAGNIFY, IconLoader::Load( wxT("page-magnifier"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonMagnify, 0, wxALL, 0 );

	m_bpButtonPencil = new wxBitmapButton( this, IDX_TOOL_PENCIL, IconLoader::Load( wxT("draw-freehand"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonPencil, 0, wxALL, 0 );

	m_bpButtonBrush = new wxBitmapButton( this, IDX_TOOL_BRUSH, IconLoader::Load( wxT("draw-brush"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonBrush, 0, wxALL, 0 );

	m_bpButtonSprayCan = new wxBitmapButton( this, IDX_TOOL_SPRAY_CAN, IconLoader::Load( wxT("draw-airbrush"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonSprayCan, 0, wxALL, 0 );

	m_bpButtonText = new wxBitmapButton( this, IDX_TOOL_TEXT, IconLoader::Load( wxT("draw-text"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonText, 0, wxALL, 0 );

	m_bpButtonLine = new wxBitmapButton( this, IDX_TOOL_LINE, IconLoader::Load( wxT("draw-line"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonLine, 0, wxALL, 0 );

	m_bpButtonCurve = new wxBitmapButton( this, IDX_TOOL_CURVE, IconLoader::Load( wxT("draw-curve"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonCurve, 0, wxALL, 0 );

	m_bpButtonRectangle = new wxBitmapButton( this, IDX_TOOL_RECTANGLE, IconLoader::Load( wxT("draw-rectangle"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonRectangle, 0, wxALL, 0 );

	m_bpButtonEllipse = new wxBitmapButton( this, IDX_TOOL_ELLIPSE, IconLoader::Load( wxT("draw-ellipse"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonEllipse, 0, wxALL, 0 );

	m_bpButtonRectangleRounded = new wxBitmapButton( this, IDX_TOOL_RECTANGLE_ROUNDED, IconLoader::Load( wxT("draw-rectangle-rounded"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonRectangleRounded, 0, wxALL, 0 );

	m_bpButtonPolygon = new wxBitmapButton( this, IDX_TOOL_POLYGON, IconLoader::Load( wxT("draw-polygon"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonPolygon, 0, wxALL, 0 );

	bSizer3->Add( fgSizer2, 0, 0, 5 );
	
	m_sbSizerToolProperties = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Pencil") ), wxVERTICAL );
	
	m_panelTestTool = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 55,-1 ), wxTAB_TRAVERSAL );
	m_sbSizerToolProperties->Add( m_panelTestTool, 0, wxALL, 0 );
	
	bSizer3->Add( m_sbSizerToolProperties, 0, 0, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );
	
	// Connect Events
	m_bpButtonSelect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSelect ), NULL, this );
	m_bpButtonEraser->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnEraser ), NULL, this );
	m_bpButtonFill->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnFill ), NULL, this );
	m_bpButtonPickColor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPickColor ), NULL, this );
	m_bpButtonMagnify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnMagnify ), NULL, this );
	m_bpButtonPencil->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPencil ), NULL, this );
	m_bpButtonBrush->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnBrush ), NULL, this );
	m_bpButtonSprayCan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSprayCan ), NULL, this );
	m_bpButtonText->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnText ), NULL, this );
	m_bpButtonLine->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnLine ), NULL, this );
	m_bpButtonCurve->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnCurve ), NULL, this );
	m_bpButtonRectangle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangle ), NULL, this );
	m_bpButtonEllipse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnEllipse ), NULL, this );
	m_bpButtonRectangleRounded->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangleRounded ), NULL, this );
	m_bpButtonPolygon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPolygon ), NULL, this );
	m_bpButtonSelectLasso->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSelectLasso ), NULL, this );
}

ToolPanel::~ToolPanel()
{
	// Disconnect Events
	m_bpButtonSelect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSelect ), NULL, this );
	m_bpButtonEraser->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnEraser ), NULL, this );
	m_bpButtonFill->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnFill ), NULL, this );
	m_bpButtonPickColor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPickColor ), NULL, this );
	m_bpButtonMagnify->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnMagnify ), NULL, this );
	m_bpButtonPencil->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPencil ), NULL, this );
	m_bpButtonBrush->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnBrush ), NULL, this );
	m_bpButtonSprayCan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSprayCan ), NULL, this );
	m_bpButtonText->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnText ), NULL, this );
	m_bpButtonLine->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnLine ), NULL, this );
	m_bpButtonCurve->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnCurve ), NULL, this );
	m_bpButtonRectangle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangle ), NULL, this );
	m_bpButtonEllipse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnEllipse ), NULL, this );
	m_bpButtonRectangleRounded->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangleRounded ), NULL, this );
	m_bpButtonPolygon->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPolygon ), NULL, this );
	m_bpButtonSelectLasso->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSelectLasso ), NULL, this );
}

namespace
{
    const int BRUSH_TIP_BTN_SIZE = 28;
    const int BRUSH_TIP_PREVIEW_RADIUS = 4;
}

wxBitmap BrushToolPanel::CreateTipBitmap(int tip, int size)
{
    wxBitmap bmp(size, size);
    wxMemoryDC dc(bmp);
    dc.SetBackground(*wxLIGHT_GREY_BRUSH);
    dc.Clear();
    dc.SetBrush(*wxBLACK_BRUSH);
    int cx = size / 2;
    int cy = size / 2;
    StampBrushTip(dc, cx, cy, BRUSH_TIP_PREVIEW_RADIUS, tip);
    dc.SelectObject(wxNullBitmap);
    return bmp;
}

void BrushToolPanel::SelectTip(int tip)
{
    if (tip < 0) tip = 0;
    if (tip > 3) tip = 3;
    m_selectedTip = tip;

    wxColour selCol = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
    wxColour defCol = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);

    m_btnTipRound->SetBackgroundColour(tip == 0 ? selCol : defCol);
    m_btnTipSquare->SetBackgroundColour(tip == 1 ? selCol : defCol);
    m_btnTipVLine->SetBackgroundColour(tip == 2 ? selCol : defCol);
    m_btnTipHLine->SetBackgroundColour(tip == 3 ? selCol : defCol);
}

BrushToolPanel::BrushToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style ), m_selectedTip(0)
{
	this->Hide();
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	// Stack label-above-control so the inputs fill the tool window's
	// narrow width (the previous 2-column layout forced the controls
	// into a half-width column that made the panel feel cramped).
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 4, 1, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fgSizer4->AddGrowableCol( 0 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer4->Add( m_staticText1, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlRadius = new wxSpinCtrl( this, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 10 );
	fgSizer4->Add( m_spinCtrlRadius, 0, wxALL|wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Tip"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* tipGrid = new wxGridSizer( 4, 1, 2, 2 );
	wxSize btnSize(BRUSH_TIP_BTN_SIZE, BRUSH_TIP_BTN_SIZE);

	wxBitmap bmpRound   = CreateTipBitmap(0, BRUSH_TIP_BTN_SIZE);
	wxBitmap bmpSquare  = CreateTipBitmap(1, BRUSH_TIP_BTN_SIZE);
	wxBitmap bmpVLine   = CreateTipBitmap(2, BRUSH_TIP_BTN_SIZE);
	wxBitmap bmpHLine   = CreateTipBitmap(3, BRUSH_TIP_BTN_SIZE);

	m_btnTipRound  = new wxBitmapButton( this, IDX_BRUSH_TIP_ROUND,  bmpRound,  wxDefaultPosition, btnSize, wxBU_AUTODRAW );
	m_btnTipSquare = new wxBitmapButton( this, IDX_BRUSH_TIP_SQUARE, bmpSquare, wxDefaultPosition, btnSize, wxBU_AUTODRAW );
	m_btnTipVLine  = new wxBitmapButton( this, IDX_BRUSH_TIP_VLINE,  bmpVLine,  wxDefaultPosition, btnSize, wxBU_AUTODRAW );
	m_btnTipHLine  = new wxBitmapButton( this, IDX_BRUSH_TIP_HLINE,  bmpHLine,  wxDefaultPosition, btnSize, wxBU_AUTODRAW );

	tipGrid->Add( m_btnTipRound,  0, wxALL, 2 );
	tipGrid->Add( m_btnTipSquare, 0, wxALL, 2 );
	tipGrid->Add( m_btnTipVLine,  0, wxALL, 2 );
	tipGrid->Add( m_btnTipHLine,  0, wxALL, 2 );
	fgSizer4->Add( tipGrid, 0, wxALL|wxEXPAND, 5 );

	bSizer3->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	m_spinCtrlRadius->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrushToolPanel::OnWidth ), NULL, this );
	m_btnTipRound->Connect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipSquare->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipVLine->Connect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipHLine->Connect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
}

BrushToolPanel::~BrushToolPanel()
{
	// Disconnect Events
	m_spinCtrlRadius->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrushToolPanel::OnWidth ), NULL, this );
	m_btnTipRound->Disconnect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipSquare->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipVLine->Disconnect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
	m_btnTipHLine->Disconnect(  wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
}

PencilToolPanel::PencilToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fg;
	fg = new wxFlexGridSizer( 2, 1, 0, 0 );
	fg->SetFlexibleDirection( wxBOTH );
	fg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fg->AddGrowableCol( 0 );

	m_staticTextSize = new wxStaticText( this, wxID_ANY, _("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSize->Wrap( -1 );
	fg->Add( m_staticTextSize, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlSize = new wxSpinCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 30, 1 );
	fg->Add( m_spinCtrlSize, 0, wxALL|wxEXPAND, 5 );

	bSizer->Add( fg, 1, wxEXPAND, 5 );
	this->SetSizer( bSizer );
	this->Layout();

	m_spinCtrlSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PencilToolPanel::OnSize ), NULL, this );
}

PencilToolPanel::~PencilToolPanel()
{
	m_spinCtrlSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PencilToolPanel::OnSize ), NULL, this );
}

EraserToolPanel::EraserToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fg;
	fg = new wxFlexGridSizer( 2, 1, 0, 0 );
	fg->SetFlexibleDirection( wxBOTH );
	fg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fg->AddGrowableCol( 0 );

	m_staticTextSize = new wxStaticText( this, wxID_ANY, _("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSize->Wrap( -1 );
	fg->Add( m_staticTextSize, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlSize = new wxSpinCtrl( this, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 5 );
	fg->Add( m_spinCtrlSize, 0, wxALL|wxEXPAND, 5 );

	bSizer->Add( fg, 1, wxEXPAND, 5 );
	this->SetSizer( bSizer );
	this->Layout();

	m_spinCtrlSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( EraserToolPanel::OnSize ), NULL, this );
}

EraserToolPanel::~EraserToolPanel()
{
	m_spinCtrlSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( EraserToolPanel::OnSize ), NULL, this );
}

SprayCanToolPanel::SprayCanToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fg;
	fg = new wxFlexGridSizer( 2, 1, 0, 0 );
	fg->SetFlexibleDirection( wxBOTH );
	fg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fg->AddGrowableCol( 0 );

	m_staticTextSize = new wxStaticText( this, wxID_ANY, _("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSize->Wrap( -1 );
	fg->Add( m_staticTextSize, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlSize = new wxSpinCtrl( this, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 10 );
	fg->Add( m_spinCtrlSize, 0, wxALL|wxEXPAND, 5 );

	bSizer->Add( fg, 1, wxEXPAND, 5 );
	this->SetSizer( bSizer );
	this->Layout();

	m_spinCtrlSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SprayCanToolPanel::OnSize ), NULL, this );
}

SprayCanToolPanel::~SprayCanToolPanel()
{
	m_spinCtrlSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SprayCanToolPanel::OnSize ), NULL, this );
}

ShapeToolPanel::ShapeToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fg;
	fg = new wxFlexGridSizer( 3, 1, 0, 0 );
	fg->SetFlexibleDirection( wxBOTH );
	fg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fg->AddGrowableCol( 0 );

	m_staticTextWidth = new wxStaticText( this, wxID_ANY, _("Outline width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextWidth->Wrap( -1 );
	fg->Add( m_staticTextWidth, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlWidth = new wxSpinCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 30, 1 );
	fg->Add( m_spinCtrlWidth, 0, wxALL|wxEXPAND, 5 );

	m_checkBoxFilled = new wxCheckBox( this, wxID_ANY, _("Fill with background"), wxDefaultPosition, wxDefaultSize, 0 );
	fg->Add( m_checkBoxFilled, 0, wxALL|wxEXPAND, 5 );

	bSizer->Add( fg, 1, wxEXPAND, 5 );
	this->SetSizer( bSizer );
	this->Layout();

	m_spinCtrlWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ShapeToolPanel::OnWidth ), NULL, this );
	m_checkBoxFilled->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ShapeToolPanel::OnFilled ), NULL, this );
}

ShapeToolPanel::~ShapeToolPanel()
{
	m_spinCtrlWidth->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ShapeToolPanel::OnWidth ), NULL, this );
	m_checkBoxFilled->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ShapeToolPanel::OnFilled ), NULL, this );
}

TextToolPanel::TextToolPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fg;
	fg = new wxFlexGridSizer( 5, 1, 0, 0 );
	fg->SetFlexibleDirection( wxBOTH );
	fg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	fg->AddGrowableCol( 0 );

	m_staticTextFont = new wxStaticText( this, wxID_ANY, _("Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFont->Wrap( -1 );
	fg->Add( m_staticTextFont, 0, wxALL|wxEXPAND, 5 );

	m_textCtrlFont = new wxButton( this, wxID_ANY, _("Font..."), wxDefaultPosition, wxDefaultSize, 0 );
	fg->Add( m_textCtrlFont, 0, wxALL|wxEXPAND, 5 );

	m_staticTextSize = new wxStaticText( this, wxID_ANY, _("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSize->Wrap( -1 );
	fg->Add( m_staticTextSize, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlSize = new wxSpinCtrl( this, wxID_ANY, wxT("12"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 4, 200, 12 );
	fg->Add( m_spinCtrlSize, 0, wxALL|wxEXPAND, 5 );

	m_checkBoxBold = new wxCheckBox( this, wxID_ANY, _("Bold"), wxDefaultPosition, wxDefaultSize, 0 );
	fg->Add( m_checkBoxBold, 0, wxALL, 5 );

	m_checkBoxItalic = new wxCheckBox( this, wxID_ANY, _("Italic"), wxDefaultPosition, wxDefaultSize, 0 );
	fg->Add( m_checkBoxItalic, 0, wxALL, 5 );

	m_checkBoxUnderline = new wxCheckBox( this, wxID_ANY, _("Underline"), wxDefaultPosition, wxDefaultSize, 0 );
	fg->Add( m_checkBoxUnderline, 0, wxALL, 5 );

	bSizer->Add( fg, 1, wxEXPAND, 5 );
	this->SetSizer( bSizer );
	this->Layout();

	m_textCtrlFont->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextToolPanel::OnFont ), NULL, this );
	m_spinCtrlSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( TextToolPanel::OnSize ), NULL, this );
	m_checkBoxBold->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnBold ), NULL, this );
	m_checkBoxItalic->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnItalic ), NULL, this );
	m_checkBoxUnderline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnUnderline ), NULL, this );
}

TextToolPanel::~TextToolPanel()
{
	m_textCtrlFont->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TextToolPanel::OnFont ), NULL, this );
	m_spinCtrlSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( TextToolPanel::OnSize ), NULL, this );
	m_checkBoxBold->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnBold ), NULL, this );
	m_checkBoxItalic->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnItalic ), NULL, this );
	m_checkBoxUnderline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TextToolPanel::OnUnderline ), NULL, this );
}

CanvasSizeDialog::CanvasSizeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Canvas Size") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	m_spinCtrlWidth = new wxSpinCtrl( this, IDX_WIDTH, wxT("1024"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 1024 );
	fgSizer5->Add( m_spinCtrlWidth, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer5->Add( m_staticText4, 1, wxALL, 5 );
	
	m_spinCtrlHeight = new wxSpinCtrl( this, IDX_HEIGHT, wxT("768"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 768 );
	fgSizer5->Add( m_spinCtrlHeight, 1, wxALL, 5 );
	
	sbSizer4->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("\\"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer5->Add( m_staticText9, 0, wxALL, 0 );
	
	m_bpButtonLink = new wxBitmapButton( this, IDX_LINK_PROPORTION, IconLoader::Load( wxT("linked"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer5->Add( m_bpButtonLink, 0, wxALL, 0 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer5->Add( m_staticText10, 0, wxALL, 0 );
	
	sbSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Offset") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer6->Add( m_staticText7, 0, wxALL, 5 );
	
	m_spinCtrlOffsetX = new wxSpinCtrl( this, IDX_OFFSET_X, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -262144, 262144, 0 );
	fgSizer6->Add( m_spinCtrlOffsetX, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer6->Add( m_staticText8, 0, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlOffsetY = new wxSpinCtrl( this, IDX_OFFSET_Y, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -262144, 262144, 0 );
	fgSizer6->Add( m_spinCtrlOffsetY, 0, wxALL, 5 );
	
	sbSizer5->Add( fgSizer6, 0, wxEXPAND, 5 );
	
	m_buttonCenter = new wxButton( this, wxID_ANY, _("Center"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_buttonCenter, 0, wxALL|wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer4->Add( m_sdbSizer1, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_spinCtrlWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnLink ), NULL, this );
	m_spinCtrlOffsetX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetX ), NULL, this );
	m_spinCtrlOffsetY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetY ), NULL, this );
	m_buttonCenter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnCenter ), NULL, this );
}

CanvasSizeDialog::~CanvasSizeDialog()
{
	// Disconnect Events
	m_spinCtrlWidth->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnLink ), NULL, this );
	m_spinCtrlOffsetX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetX ), NULL, this );
	m_spinCtrlOffsetY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetY ), NULL, this );
	m_buttonCenter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnCenter ), NULL, this );
}

ImageSizeDialog::ImageSizeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Image Size") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	m_spinCtrlWidth = new wxSpinCtrl( this, IDX_WIDTH, wxT("1024"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 1024 );
	fgSizer5->Add( m_spinCtrlWidth, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer5->Add( m_staticText4, 1, wxALL, 5 );
	
	m_spinCtrlHeight = new wxSpinCtrl( this, IDX_HEIGHT, wxT("768"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 768 );
	fgSizer5->Add( m_spinCtrlHeight, 1, wxALL, 5 );
	
	sbSizer4->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("\\"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer5->Add( m_staticText9, 0, wxALL, 0 );
	
	m_bpButtonLink = new wxBitmapButton( this, IDX_LINK_PROPORTION, IconLoader::Load( wxT("linked"), IconLoader::LogicalToolbarSize() ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer5->Add( m_bpButtonLink, 0, wxALL, 0 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer5->Add( m_staticText10, 0, wxALL, 0 );
	
	sbSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer4->Add( m_sdbSizer1, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_spinCtrlWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSizeDialog::OnLink ), NULL, this );
}

ImageSizeDialog::~ImageSizeDialog()
{
	// Disconnect Events
	m_spinCtrlWidth->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSizeDialog::OnLink ), NULL, this );
}
