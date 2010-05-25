///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "RayoffailGUI.h"

///////////////////////////////////////////////////////////////////////////

MainFrame_Base::MainFrame_Base( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame_Base::m_splitter1OnIdle ), NULL, this );
	m_scrolledWindow1 = new wxScrolledWindow( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	start_button = new wxButton( m_panel4, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( start_button, 0, wxALL, 5 );
	
	m_panel4->SetSizer( bSizer3 );
	m_panel4->Layout();
	bSizer3->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, wxT("Render"), true );
	m_panel5 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel5, wxT("Scene"), false );
	
	bSizer2->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_scrolledWindow1->SetSizer( bSizer2 );
	m_scrolledWindow1->Layout();
	bSizer2->Fit( m_scrolledWindow1 );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_splitter1->SplitVertically( m_scrolledWindow1, m_panel2, 174 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* open_menuItem;
	open_menuItem = new wxMenuItem( file_menu, wxID_OPEN, wxString( wxT("&Open Scene") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( open_menuItem );
	
	wxMenuItem* m_separator1;
	m_separator1 = file_menu->AppendSeparator();
	
	wxMenuItem* saveImage_menuItem;
	saveImage_menuItem = new wxMenuItem( file_menu, wxID_SAVE, wxString( wxT("&Save Image") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( saveImage_menuItem );
	
	m_menubar1->Append( file_menu, wxT("&File") );
	
	help_menu = new wxMenu();
	wxMenuItem* about_menuItem;
	about_menuItem = new wxMenuItem( help_menu, wxID_ABOUT, wxString( wxT("&About") ) , wxEmptyString, wxITEM_NORMAL );
	help_menu->Append( about_menuItem );
	
	m_menubar1->Append( help_menu, wxT("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	
	// Connect Events
	start_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_Base::onStart ), NULL, this );
	this->Connect( open_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onOpenMenu ) );
	this->Connect( saveImage_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onSaveImageMenu ) );
	this->Connect( about_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onAboutMenu ) );
}

MainFrame_Base::~MainFrame_Base()
{
	// Disconnect Events
	start_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_Base::onStart ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onOpenMenu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onSaveImageMenu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onAboutMenu ) );
}
