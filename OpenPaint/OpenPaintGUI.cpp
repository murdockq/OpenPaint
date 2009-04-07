///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  6 2007)
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

#include "OpenPaintGUI.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxAuiMDIParentFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->Centre( wxBOTH );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menuNew = new wxMenu();
	wxMenuItem* menuItemNewFile320 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_320, wxString( wxT("320x240") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile320 );
	wxMenuItem* menuItemNewFile640 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_640, wxString( wxT("640x480") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile640 );
	wxMenuItem* menuItemNewFile = new wxMenuItem( m_menuNew, wxID_NEW, wxString( wxT("800x600") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile );
	wxMenuItem* menuItemNewFile1024 = new wxMenuItem( m_menuNew, IDX_NEW_FILE_1024, wxString( wxT("1024x768") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuNew->Append( menuItemNewFile1024 );
	m_menuFile->Append( -1, wxT("New"), m_menuNew );
	
	wxMenuItem* menuItemOpen = new wxMenuItem( m_menuFile, wxID_OPEN, wxString( wxT("Open...") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuItemOpen );
	wxMenuItem* menuItemSave = new wxMenuItem( m_menuFile, wxID_SAVE, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuItemSave );
	wxMenuItem* menuItemSaveAs = new wxMenuItem( m_menuFile, wxID_SAVEAS, wxString( wxT("Save As...") ) + wxT('\t') + wxT("Ctrl+Shift+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuItemSaveAs );
	
	m_menuFile->AppendSeparator();
	m_menuRecentImages = new wxMenu();
	wxMenuItem* menuItemEMPTYFile = new wxMenuItem( m_menuRecentImages, IDX_MENU_EMPTY, wxString( wxT("Empty") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRecentImages->Append( menuItemEMPTYFile );
	menuItemEMPTYFile->Enable( false );
	
	m_menuFile->Append( -1, wxT("Recent Files"), m_menuRecentImages );
	
	
	m_menuFile->AppendSeparator();
	wxMenuItem* menuItemExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( wxT("Exit") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuItemExit );
	m_menubar1->Append( m_menuFile, wxT("&File") );
	
	m_menuEdit = new wxMenu();
	wxMenuItem* menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( wxT("Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemUndo );
	menuItemUndo->Enable( false );
	
	wxMenuItem* menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( wxT("Redo") ) + wxT('\t') + wxT("Ctrl+Y"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemRedo );
	menuItemRedo->Enable( false );
	
	
	m_menuEdit->AppendSeparator();
	wxMenuItem* menuItemCut = new wxMenuItem( m_menuEdit, wxID_CUT, wxString( wxT("Cut") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemCut );
	wxMenuItem* menuItemCopy = new wxMenuItem( m_menuEdit, wxID_COPY, wxString( wxT("Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemCopy );
	wxMenuItem* menuItemPaste = new wxMenuItem( m_menuEdit, wxID_PASTE, wxString( wxT("Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemPaste );
	wxMenuItem* menuItemDelete = new wxMenuItem( m_menuEdit, wxID_DELETE, wxString( wxT("Delete") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemDelete );
	
	m_menuEdit->AppendSeparator();
	wxMenuItem* menuItemSelectAll = new wxMenuItem( m_menuEdit, IDX_SELECT_ALL, wxString( wxT("Select All") ) + wxT('\t') + wxT("Ctrl+A"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemSelectAll );
	
	m_menuEdit->AppendSeparator();
	wxMenuItem* menuItemClear = new wxMenuItem( m_menuEdit, wxID_ANY, wxString( wxT("Clear") ) + wxT('\t') + wxT("Ctrl+K"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemClear );
	wxMenuItem* menuItemFillFGColor = new wxMenuItem( m_menuEdit, IDX_FILL_FG_COLOR, wxString( wxT("Fill with FG Color") ) + wxT('\t') + wxT("Ctrl+,"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemFillFGColor );
	wxMenuItem* menuItemFillBGColor = new wxMenuItem( m_menuEdit, IDX_FILL_BG_COLOR, wxString( wxT("Fill with BG Color") ) + wxT('\t') + wxT("Ctrl+."), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuItemFillBGColor );
	m_menubar1->Append( m_menuEdit, wxT("&Edit") );
	
	m_menuView = new wxMenu();
	wxMenuItem* menuItemZoomOut = new wxMenuItem( m_menuView, IDX_ZOOM_OUT, wxString( wxT("Zoom Out") ) + wxT('\t') + wxT("-"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemZoomOut );
	wxMenuItem* menuItemZoomIn = new wxMenuItem( m_menuView, IDX_ZOOM_IN, wxString( wxT("Zoom In") ) + wxT('\t') + wxT("+"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemZoomIn );
	wxMenuItem* menuItemNormalZoom = new wxMenuItem( m_menuView, IDX_NORMAL_ZOOM, wxString( wxT("Normal Zoom") ) + wxT('\t') + wxT("1"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( menuItemNormalZoom );
	
	m_menuView->AppendSeparator();
	wxMenuItem* menuItemFullscreen = new wxMenuItem( m_menuView, IDX_FULLSCREEN, wxString( wxT("Fullscreen") ) + wxT('\t') + wxT("F12"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( menuItemFullscreen );
	m_menubar1->Append( m_menuView, wxT("&View") );
	
	m_menuImage = new wxMenu();
	wxMenuItem* menuItemFlipHorizontal = new wxMenuItem( m_menuImage, IDX_FLIP_HORIZONTAL, wxString( wxT("Flip Horizontal") ) + wxT('\t') + wxT("Ctrl+Shift+H"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemFlipHorizontal );
	wxMenuItem* menuItemFlipVertical = new wxMenuItem( m_menuImage, IDX_FLIP_VERTICAL, wxString( wxT("Flip Vertical") ) + wxT('\t') + wxT("Ctrl+Shift+V"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemFlipVertical );
	
	m_menuImage->AppendSeparator();
	wxMenuItem* menuItemRotate = new wxMenuItem( m_menuImage, IDX_ROTATE, wxString( wxT("Rotate") ) + wxT('\t') + wxT("Ctrl+Shift+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemRotate );
	
	m_menuImage->AppendSeparator();
	wxMenuItem* menuItemImageSize = new wxMenuItem( m_menuImage, IDX_IMAGE_SIZE, wxString( wxT("Image Size...") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemImageSize );
	wxMenuItem* menuItemCanvasSize = new wxMenuItem( m_menuImage, IDX_CANVAS_SIZE, wxString( wxT("Canvas Size...") ) + wxT('\t') + wxT("Ctrl+E"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuItemCanvasSize );
	m_menubar1->Append( m_menuImage, wxT("&Image") );
	
	m_menuTools = new wxMenu();
	wxMenuItem* menuItemBrush = new wxMenuItem( m_menuTools, IDX_TOOL_BRUSH, wxString( wxT("Brush") ) + wxT('\t') + wxT("B"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemBrush->SetBitmaps( wxICON( IDI_ICON_DRAW_BRUSH ) );
	#elif defined( __WXGTK__ )
	menuItemBrush->SetBitmap( wxICON( IDI_ICON_DRAW_BRUSH ) );
	#endif
	m_menuTools->Append( menuItemBrush );
	wxMenuItem* menuItemEllipse = new wxMenuItem( m_menuTools, IDX_TOOL_ELLIPSE, wxString( wxT("Ellipse") ) + wxT('\t') + wxT("O"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemEllipse->SetBitmaps( wxICON( IDI_ICON_DRAW_ELLIPSE ) );
	#elif defined( __WXGTK__ )
	menuItemEllipse->SetBitmap( wxICON( IDI_ICON_DRAW_ELLIPSE ) );
	#endif
	m_menuTools->Append( menuItemEllipse );
	wxMenuItem* menuItemEraser = new wxMenuItem( m_menuTools, IDX_TOOL_ERASER, wxString( wxT("Eraser") ) + wxT('\t') + wxT("E"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemEraser->SetBitmaps( wxICON( IDI_ICON_DRAW_ERASER ) );
	#elif defined( __WXGTK__ )
	menuItemEraser->SetBitmap( wxICON( IDI_ICON_DRAW_ERASER ) );
	#endif
	m_menuTools->Append( menuItemEraser );
	wxMenuItem* menuItemFill = new wxMenuItem( m_menuTools, IDX_TOOL_FILL, wxString( wxT("Fill Bucket") ) + wxT('\t') + wxT("F"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemFill->SetBitmaps( wxICON( IDI_ICON_COLOR_FILL ) );
	#elif defined( __WXGTK__ )
	menuItemFill->SetBitmap( wxICON( IDI_ICON_COLOR_FILL ) );
	#endif
	m_menuTools->Append( menuItemFill );
	wxMenuItem* menuItemMagnify = new wxMenuItem( m_menuTools, IDX_TOOL_MAGNIFY, wxString( wxT("Magnify") ) + wxT('\t') + wxT("M"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemMagnify->SetBitmaps( wxICON( IDI_ICON_PAGE_MAGNIFIER ) );
	#elif defined( __WXGTK__ )
	menuItemMagnify->SetBitmap( wxICON( IDI_ICON_PAGE_MAGNIFIER ) );
	#endif
	m_menuTools->Append( menuItemMagnify );
	wxMenuItem* menuItemPencil = new wxMenuItem( m_menuTools, IDX_TOOL_PENCIL, wxString( wxT("Pencil") ) + wxT('\t') + wxT("P"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemPencil->SetBitmaps( wxICON( IDI_ICON_DRAW_FREEHAND ) );
	#elif defined( __WXGTK__ )
	menuItemPencil->SetBitmap( wxICON( IDI_ICON_DRAW_FREEHAND ) );
	#endif
	m_menuTools->Append( menuItemPencil );
	wxMenuItem* menuItemPickColor = new wxMenuItem( m_menuTools, IDX_TOOL_PICK_COLOR, wxString( wxT("Pick Color") ) + wxT('\t') + wxT("C"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemPickColor->SetBitmaps( wxICON( IDI_ICON_COLOR_PICKER ) );
	#elif defined( __WXGTK__ )
	menuItemPickColor->SetBitmap( wxICON( IDI_ICON_COLOR_PICKER ) );
	#endif
	m_menuTools->Append( menuItemPickColor );
	wxMenuItem* menuItemPolyline = new wxMenuItem( m_menuTools, IDX_TOOL_POLYLINE, wxString( wxT("Polyline") ) + wxT('\t') + wxT("P"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemPolyline->SetBitmaps( wxICON( IDI_ICON_DRAW_POLYLINE ) );
	#elif defined( __WXGTK__ )
	menuItemPolyline->SetBitmap( wxICON( IDI_ICON_DRAW_POLYLINE ) );
	#endif
	m_menuTools->Append( menuItemPolyline );
	menuItemPolyline->Enable( false );
	
	wxMenuItem* menuItemRectangle = new wxMenuItem( m_menuTools, IDX_TOOL_RECTANGLE, wxString( wxT("Rectangle") ) + wxT('\t') + wxT("R"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemRectangle->SetBitmaps( wxICON( IDI_ICON_DRAW_RECTANGLE ) );
	#elif defined( __WXGTK__ )
	menuItemRectangle->SetBitmap( wxICON( IDI_ICON_DRAW_RECTANGLE ) );
	#endif
	m_menuTools->Append( menuItemRectangle );
	wxMenuItem* menuItemRectangleRounded = new wxMenuItem( m_menuTools, IDX_TOOL_RECTANGLE_ROUNDED, wxString( wxT("Rounded Rectangle") ) + wxT('\t') + wxT("Q"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemRectangleRounded->SetBitmaps( wxICON( IDI_ICON_DRAW_RECTANGLE_ROUNDED ) );
	#elif defined( __WXGTK__ )
	menuItemRectangleRounded->SetBitmap( wxICON( IDI_ICON_DRAW_RECTANGLE_ROUNDED ) );
	#endif
	m_menuTools->Append( menuItemRectangleRounded );
	wxMenuItem* menuItemSelect = new wxMenuItem( m_menuTools, IDX_TOOL_SELECT, wxString( wxT("Select") ) + wxT('\t') + wxT("S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemSelect->SetBitmaps( wxICON( IDI_ICON_SELECT_RECTANGULAR ) );
	#elif defined( __WXGTK__ )
	menuItemSelect->SetBitmap( wxICON( IDI_ICON_SELECT_RECTANGULAR ) );
	#endif
	m_menuTools->Append( menuItemSelect );
	wxMenuItem* menuItemSelectLasso = new wxMenuItem( m_menuTools, IDX_TOOL_SELECT_LASSO, wxString( wxT("Select Lasso") ) + wxT('\t') + wxT("L"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemSelectLasso->SetBitmaps( wxICON( IDI_ICON_SELECT_LASSO ) );
	#elif defined( __WXGTK__ )
	menuItemSelectLasso->SetBitmap( wxICON( IDI_ICON_SELECT_LASSO ) );
	#endif
	m_menuTools->Append( menuItemSelectLasso );
	menuItemSelectLasso->Enable( false );
	
	wxMenuItem* menuItemSprayCan = new wxMenuItem( m_menuTools, IDX_TOOL_SPRAY_CAN, wxString( wxT("Spray Can") ) + wxT('\t') + wxT("A"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemSprayCan->SetBitmaps( wxICON( IDI_ICON_DRAW_AIRBRUSH ) );
	#elif defined( __WXGTK__ )
	menuItemSprayCan->SetBitmap( wxICON( IDI_ICON_DRAW_AIRBRUSH ) );
	#endif
	m_menuTools->Append( menuItemSprayCan );
	wxMenuItem* menuItemText = new wxMenuItem( m_menuTools, IDX_TOOL_TEXT, wxString( wxT("Text") ) + wxT('\t') + wxT("T"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuItemText->SetBitmaps( wxICON( IDI_ICON_DRAW_TEXT ) );
	#elif defined( __WXGTK__ )
	menuItemText->SetBitmap( wxICON( IDI_ICON_DRAW_TEXT ) );
	#endif
	m_menuTools->Append( menuItemText );
	m_menubar1->Append( m_menuTools, wxT("&Tools") );
	
	m_menuFilters = new wxMenu();
	wxMenuItem* menuItemInvert = new wxMenuItem( m_menuFilters, wxID_ANY, wxString( wxT("Invert Colors") ) + wxT('\t') + wxT("Ctrl+I"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemInvert );
	wxMenuItem* menuItemBlur = new wxMenuItem( m_menuFilters, IDX_BLUR, wxString( wxT("Blur") ) + wxT('\t') + wxT("Ctrl+B"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemBlur );
	wxMenuItem* menuItemPixelize = new wxMenuItem( m_menuFilters, IDX_PIXELIZE, wxString( wxT("Pixelize") ) + wxT('\t') + wxT("Ctrl+P"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemPixelize );
	wxMenuItem* menuItemGreyscale = new wxMenuItem( m_menuFilters, IDX_GREYSCALE, wxString( wxT("Greyscale") ) + wxT('\t') + wxT("Ctrl+G"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemGreyscale );
	wxMenuItem* menuItemMonochrome = new wxMenuItem( m_menuFilters, IDX_MONOCHROME, wxString( wxT("Monochrome") ) + wxT('\t') + wxT("Ctrl+M"), wxEmptyString, wxITEM_NORMAL );
	m_menuFilters->Append( menuItemMonochrome );
	m_menubar1->Append( m_menuFilters, wxT("Filte&rs") );
	
	m_menuColors = new wxMenu();
	wxMenuItem* menuItemForeground = new wxMenuItem( m_menuColors, IDX_FOREGROUND, wxString( wxT("Set Foreground...") ) + wxT('\t') + wxT("Ctrl+Shift+F"), wxEmptyString, wxITEM_NORMAL );
	m_menuColors->Append( menuItemForeground );
	wxMenuItem* menuItemBackground = new wxMenuItem( m_menuColors, IDX_BACKGROUND, wxString( wxT("Set Background...") ) + wxT('\t') + wxT("Ctrl+Shift+B"), wxEmptyString, wxITEM_NORMAL );
	m_menuColors->Append( menuItemBackground );
	m_menubar1->Append( m_menuColors, wxT("&Colors") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* menuItemAbout = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( wxT("About...") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( menuItemAbout );
	m_menubar1->Append( m_menuHelp, wxT("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_DOCKABLE|wxTB_FLAT, wxID_ANY );
	m_toolBar1->SetToolBitmapSize( wxSize( 32,32 ) );
	m_toolBar1->AddTool( wxID_NEW, wxT("New"), wxICON( IDI_ICON_NEW ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Create a new 800x600 image.") );
	m_toolBar1->AddTool( wxID_OPEN, wxT("Open"), wxICON( IDI_ICON_OPEN ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Open an image file.") );
	m_toolBar1->AddTool( wxID_SAVE, wxT("Save"), wxICON( IDI_ICON_SAVE ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Save current file.") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( wxID_UNDO, wxT("Undo"), wxICON( IDI_ICON_UNDO ), wxNullBitmap, wxITEM_NORMAL, wxT("Undo (Ctrl +Z)"), wxT("Undo the last action.") );
	m_toolBar1->AddTool( wxID_REDO, wxT("Redo"), wxICON( IDI_ICON_REDO ), wxNullBitmap, wxITEM_NORMAL, wxT("Redo (Ctrl +Z)"), wxT("Redo the last action that was undone.") );
	m_toolBar1->AddSeparator();
	m_toolBar1->Realize();
	
	
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
	this->Connect( menuItemZoomOut->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomOut ) );
	this->Connect( menuItemZoomIn->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnZoomIn ) );
	this->Connect( menuItemNormalZoom->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNormalZoom ) );
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
	this->Connect( menuItemPolyline->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnPolyline ) );
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
	this->Connect( menuItemForeground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnForeground ) );
	this->Connect( menuItemBackground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnBackground ) );
	this->Connect( menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnAbout ) );
	this->Connect( wxID_REDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnRunProcess ) );
}

ColorPanel::ColorPanel( wxWindow* parent, int id, wxPoint pos, wxSize size, int style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxEmptyString ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_colourPickerForeground = new wxColourPickerCtrl( this, IDX_FOREGROUND, wxColour( 0, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer4->Add( m_colourPickerForeground, 0, wxALL, 0 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 0 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 0 );
	
	m_colourPickerBackground = new wxColourPickerCtrl( this, IDX_BACKGROUND, wxColour( 255, 255, 255 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer4->Add( m_colourPickerBackground, 0, wxALL, 0 );
	
	sbSizer3->Add( fgSizer4, 0, wxEXPAND, 0 );
	
	bSizer4->Add( sbSizer3, 0, 0, 0 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxEmptyString ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 10, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_panelPalette0 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette0->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette0, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette1 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette1->SetBackgroundColour( wxColour( 128, 128, 128 ) );
	
	fgSizer3->Add( m_panelPalette1, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette2 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette2->SetBackgroundColour( wxColour( 128, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette2, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette3 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette3->SetBackgroundColour( wxColour( 128, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette3, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette4 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette4->SetBackgroundColour( wxColour( 0, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette4, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette5 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette5->SetBackgroundColour( wxColour( 255, 128, 64 ) );
	
	fgSizer3->Add( m_panelPalette5, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette6 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette6->SetBackgroundColour( wxColour( 0, 128, 192 ) );
	
	fgSizer3->Add( m_panelPalette6, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette7 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette7->SetBackgroundColour( wxColour( 0, 0, 64 ) );
	
	fgSizer3->Add( m_panelPalette7, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette8 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette8->SetBackgroundColour( wxColour( 128, 128, 255 ) );
	
	fgSizer3->Add( m_panelPalette8, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette9 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette9->SetBackgroundColour( wxColour( 0, 0, 128 ) );
	
	fgSizer3->Add( m_panelPalette9, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette10 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette10->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	fgSizer3->Add( m_panelPalette10, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette11 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette11->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	fgSizer3->Add( m_panelPalette11, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette12 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette12->SetBackgroundColour( wxColour( 255, 0, 0 ) );
	
	fgSizer3->Add( m_panelPalette12, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette13 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette13->SetBackgroundColour( wxColour( 255, 255, 0 ) );
	
	fgSizer3->Add( m_panelPalette13, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette14 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette14->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	
	fgSizer3->Add( m_panelPalette14, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette15 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette15->SetBackgroundColour( wxColour( 128, 255, 255 ) );
	
	fgSizer3->Add( m_panelPalette15, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette16 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette16->SetBackgroundColour( wxColour( 0, 0, 255 ) );
	
	fgSizer3->Add( m_panelPalette16, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette17 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette17->SetBackgroundColour( wxColour( 255, 128, 255 ) );
	
	fgSizer3->Add( m_panelPalette17, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette18 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette18->SetBackgroundColour( wxColour( 255, 255, 128 ) );
	
	fgSizer3->Add( m_panelPalette18, 1, wxEXPAND | wxALL, 0 );
	
	m_panelPalette19 = new PaletteCtrl( this, IDX_PALETTE, wxDefaultPosition, wxSize( -1,-1 ), wxSUNKEN_BORDER );
	m_panelPalette19->SetBackgroundColour( wxColour( 255, 128, 0 ) );
	
	fgSizer3->Add( m_panelPalette19, 1, wxEXPAND | wxALL, 0 );
	
	sbSizer4->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer4, 0, 0, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	// Connect Events
	m_colourPickerForeground->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ColorPanel::OnForegroundSet ), NULL, this );
	m_colourPickerBackground->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ColorPanel::OnBackgroundSet ), NULL, this );
}

ToolPanel::ToolPanel( wxWindow* parent, int id, wxPoint pos, wxSize size, int style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bpButtonSelect = new wxBitmapButton( this, IDX_TOOL_SELECT, wxICON( IDI_ICON_SELECT_RECTANGULAR ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonSelect, 0, wxALL, 0 );
	
	m_bpButtonEraser = new wxBitmapButton( this, IDX_TOOL_ERASER, wxICON( IDI_ICON_DRAW_ERASER ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonEraser, 0, wxALL, 0 );
	
	m_bpButtonFill = new wxBitmapButton( this, IDX_TOOL_FILL, wxICON( IDI_ICON_COLOR_FILL ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonFill, 0, wxALL, 0 );
	
	m_bpButtonPickColor = new wxBitmapButton( this, IDX_TOOL_PICK_COLOR, wxICON( IDI_ICON_COLOR_PICKER ), wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonPickColor, 0, wxALL, 0 );
	
	m_bpButtonMagnify = new wxBitmapButton( this, IDX_TOOL_MAGNIFY, wxICON( IDI_ICON_PAGE_MAGNIFIER ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonMagnify, 0, wxALL, 0 );
	
	m_bpButtonPencil = new wxBitmapButton( this, IDX_TOOL_PENCIL, wxICON( IDI_ICON_DRAW_FREEHAND ), wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonPencil, 0, wxALL, 0 );
	
	m_bpButtonBrush = new wxBitmapButton( this, IDX_TOOL_BRUSH, wxICON( IDI_ICON_DRAW_BRUSH ), wxDefaultPosition, wxSize( -1,-1 ), wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonBrush, 0, wxALL, 0 );
	
	m_bpButtonSprayCan = new wxBitmapButton( this, IDX_TOOL_SPRAY_CAN, wxICON( IDI_ICON_DRAW_AIRBRUSH ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonSprayCan, 0, wxALL, 0 );
	
	m_bpButtonText = new wxBitmapButton( this, IDX_TOOL_TEXT, wxICON( IDI_ICON_DRAW_TEXT ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonText, 0, wxALL, 0 );
	
	m_bpButtonRectangle = new wxBitmapButton( this, IDX_TOOL_RECTANGLE, wxICON( IDI_ICON_DRAW_RECTANGLE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonRectangle, 0, wxALL, 0 );
	
	m_bpButtonEllipse = new wxBitmapButton( this, IDX_TOOL_ELLIPSE, wxICON( IDI_ICON_DRAW_ELLIPSE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonEllipse, 0, wxALL, 0 );
	
	m_bpButtonRectangleRounded = new wxBitmapButton( this, IDX_TOOL_RECTANGLE_ROUNDED, wxICON( IDI_ICON_DRAW_RECTANGLE_ROUNDED ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer2->Add( m_bpButtonRectangleRounded, 0, wxALL, 0 );
	
	m_bpButtonPolyline = new wxBitmapButton( this, IDX_TOOL_POLYLINE, wxICON( IDI_ICON_DRAW_POLYLINE ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPolyline->Hide();
	
	m_bpButtonPolyline->Hide();
	
	fgSizer2->Add( m_bpButtonPolyline, 0, wxALL, 0 );
	
	m_bpButtonSelectLasso = new wxBitmapButton( this, IDX_TOOL_SELECT_LASSO, wxICON( IDI_ICON_SELECT_LASSO ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonSelectLasso->Hide();
	
	m_bpButtonSelectLasso->Hide();
	
	fgSizer2->Add( m_bpButtonSelectLasso, 0, wxALL, 0 );
	
	bSizer3->Add( fgSizer2, 0, 0, 5 );
	
	m_sbSizerToolProperties = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxT("Pencil") ), wxVERTICAL );
	
	m_panelTestTool = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 55,-1 ), wxTAB_TRAVERSAL );
	m_sbSizerToolProperties->Add( m_panelTestTool, 1, wxALL|wxEXPAND, 0 );
	
	bSizer3->Add( m_sbSizerToolProperties, 1, 0, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
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
	m_bpButtonRectangle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangle ), NULL, this );
	m_bpButtonEllipse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnEllipse ), NULL, this );
	m_bpButtonRectangleRounded->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnRectangleRounded ), NULL, this );
	m_bpButtonPolyline->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnPolyline ), NULL, this );
	m_bpButtonSelectLasso->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolPanel::OnSelectLasso ), NULL, this );
}

BrushToolPanel::BrushToolPanel( wxWindow* parent, int id, wxPoint pos, wxSize size, int style ) : wxPanel( parent, id, pos, size, style )
{
	this->Hide();
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer4->Add( m_staticText1, 0, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlRadius = new wxSpinCtrl( this, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 10);
	fgSizer4->Add( m_spinCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Tip"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );
	
	m_comboBoxTip = new wxComboBox( this, wxID_ANY, wxT("Round"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_comboBoxTip->Append( wxT("Round") );
	m_comboBoxTip->Append( wxT("Square") );
	m_comboBoxTip->Append( wxT("Vertical Line") );
	m_comboBoxTip->Append( wxT("Horizontal Line") );
	fgSizer4->Add( m_comboBoxTip, 0, wxALL|wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	m_spinCtrlRadius->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrushToolPanel::OnWidth ), NULL, this );
	m_comboBoxTip->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( BrushToolPanel::OnTip ), NULL, this );
}

CanvasSizeDialog::CanvasSizeDialog( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->Centre( wxBOTH );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxT("Canvas Size") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	m_spinCtrlWidth = new wxSpinCtrl( this, IDX_WIDTH, wxT("1024"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 1024);
	fgSizer5->Add( m_spinCtrlWidth, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer5->Add( m_staticText4, 1, wxALL, 5 );
	
	m_spinCtrlHeight = new wxSpinCtrl( this, IDX_HEIGHT, wxT("768"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 768);
	fgSizer5->Add( m_spinCtrlHeight, 1, wxALL, 5 );
	
	sbSizer4->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("\\"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer5->Add( m_staticText9, 0, wxALL, 0 );
	
	m_bpButtonLink = new wxBitmapButton( this, IDX_LINK_PROPORTION, wxICON( IDI_ICON_LINKED ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer5->Add( m_bpButtonLink, 0, wxALL, 0 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer5->Add( m_staticText10, 0, wxALL, 0 );
	
	sbSizer4->Add( bSizer5, 0, wxEXPAND, 5 );
	
	bSizer4->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxT("Offset") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer6->Add( m_staticText7, 0, wxALL, 5 );
	
	m_spinCtrlOffsetX = new wxSpinCtrl( this, IDX_OFFSET_X, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -262144, 262144, 0);
	fgSizer6->Add( m_spinCtrlOffsetX, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer6->Add( m_staticText8, 0, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlOffsetY = new wxSpinCtrl( this, IDX_OFFSET_Y, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -262144, 262144, 0);
	fgSizer6->Add( m_spinCtrlOffsetY, 0, wxALL, 5 );
	
	sbSizer5->Add( fgSizer6, 0, wxEXPAND, 5 );
	
	m_buttonCenter = new wxButton( this, wxID_ANY, wxT("Center"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	// Connect Events
	m_spinCtrlWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnLink ), NULL, this );
	m_spinCtrlOffsetX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetX ), NULL, this );
	m_spinCtrlOffsetY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSizeDialog::OnOffsetY ), NULL, this );
	m_buttonCenter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CanvasSizeDialog::OnCenter ), NULL, this );
}

ImageSizeDialog::ImageSizeDialog( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->Centre( wxBOTH );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, -1, wxT("Image Size") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	m_spinCtrlWidth = new wxSpinCtrl( this, IDX_WIDTH, wxT("1024"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 1024);
	fgSizer5->Add( m_spinCtrlWidth, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer5->Add( m_staticText4, 1, wxALL, 5 );
	
	m_spinCtrlHeight = new wxSpinCtrl( this, IDX_HEIGHT, wxT("768"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 262144, 768);
	fgSizer5->Add( m_spinCtrlHeight, 1, wxALL, 5 );
	
	sbSizer4->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("\\"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer5->Add( m_staticText9, 0, wxALL, 0 );
	
	m_bpButtonLink = new wxBitmapButton( this, IDX_LINK_PROPORTION, wxICON( IDI_ICON_LINKED ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer5->Add( m_bpButtonLink, 0, wxALL, 0 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("/"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	// Connect Events
	m_spinCtrlWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnWidth ), NULL, this );
	m_spinCtrlHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ImageSizeDialog::OnHeight ), NULL, this );
	m_bpButtonLink->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSizeDialog::OnLink ), NULL, this );
}
