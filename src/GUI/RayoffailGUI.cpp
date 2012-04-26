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
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( m_panel4, wxID_ANY, wxT("Preview Update Rate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL, 5 );
	
	updateRate_spinCtrl = new wxSpinCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );
	bSizer5->Add( updateRate_spinCtrl, 0, wxALL, 5 );
	
	savePreviews_checkBox = new wxCheckBox( m_panel4, wxID_ANY, wxT("Save previews"), wxDefaultPosition, wxDefaultSize, 0 );
	savePreviews_checkBox->SetValue(true); 
	bSizer5->Add( savePreviews_checkBox, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer5, 0, 0, 0 );
	
	m_staticline1 = new wxStaticLine( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( m_panel4, wxID_ANY, wxT("Samples"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer6->Add( m_staticText2, 0, wxALL, 5 );
	
	samples_spinCtrl = new wxSpinCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 10 );
	bSizer6->Add( samples_spinCtrl, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer6, 0, 0, 5 );
	
	m_staticline2 = new wxStaticLine( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText3 = new wxStaticText( m_panel4, wxID_ANY, wxT("Resolution"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer7->Add( m_staticText3, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( m_panel4, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer8->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	xRes_textCtrl = new wxTextCtrl( m_panel4, wxID_ANY, wxT("500"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( xRes_textCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer8, 0, 0, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( m_panel4, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer9->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	yRes_textCtrl = new wxTextCtrl( m_panel4, wxID_ANY, wxT("500"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( yRes_textCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer7->Add( bSizer9, 0, 0, 5 );
	
	bSizer3->Add( bSizer7, 0, 0, 5 );
	
	m_staticline3 = new wxStaticLine( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	start_button = new wxButton( m_panel4, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( start_button, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer3->Add( bSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel4->SetSizer( bSizer3 );
	m_panel4->Layout();
	bSizer3->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, wxT("Render"), true );
	m_panel5 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel5, wxID_ANY, wxT("DoF") ), wxVERTICAL );
	
	dof_checkBox = new wxCheckBox( m_panel5, wxID_ANY, wxT("On"), wxDefaultPosition, wxDefaultSize, 0 );
	dof_checkBox->SetToolTip( wxT("Habilita o Depth of Field.") );
	
	sbSizer1->Add( dof_checkBox, 0, wxALL, 5 );
	
	dof_panel = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	dof_panel->Enable( false );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( dof_panel, wxID_ANY, wxT("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer11->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	dofDistance_textCtrl = new wxTextCtrl( dof_panel, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, 0 );
	dofDistance_textCtrl->SetToolTip( wxT("Os pontos da cena que estiverem a essa distância da câmera estarão perfeitamente em foco.") );
	
	bSizer11->Add( dofDistance_textCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer12->Add( bSizer11, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( dof_panel, wxID_ANY, wxT("Lens Radius:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer15->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	lensRadius_textCtrl = new wxTextCtrl( dof_panel, wxID_ANY, wxT("0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	lensRadius_textCtrl->SetToolTip( wxT("Quanto maior esse valor, mais brusca será a perda de foco.") );
	
	bSizer15->Add( lensRadius_textCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer12->Add( bSizer15, 1, wxEXPAND, 5 );
	
	dof_panel->SetSizer( bSizer12 );
	dof_panel->Layout();
	bSizer12->Fit( dof_panel );
	sbSizer1->Add( dof_panel, 0, wxALL, 0 );
	
	bSizer16->Add( sbSizer1, 0, 0, 5 );
	
	m_panel5->SetSizer( bSizer16 );
	m_panel5->Layout();
	bSizer16->Fit( m_panel5 );
	m_notebook1->AddPage( m_panel5, wxT("Camera"), false );
	
	bSizer2->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_scrolledWindow1->SetSizer( bSizer2 );
	m_scrolledWindow1->Layout();
	bSizer2->Fit( m_scrolledWindow1 );
	m_panel41 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	imageCanvas = new ImageCanvas(m_panel41);
	bSizer4->Add( imageCanvas, 1, wxALL|wxEXPAND, 5 );
	
	m_panel41->SetSizer( bSizer4 );
	m_panel41->Layout();
	bSizer4->Fit( m_panel41 );
	m_splitter1->SplitVertically( m_scrolledWindow1, m_panel41, 203 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
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
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame_Base::onIdle ) );
	start_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_Base::onStart ), NULL, this );
	dof_checkBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame_Base::onDofCheckBox ), NULL, this );
	this->Connect( open_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onOpenMenu ) );
	this->Connect( saveImage_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onSaveImageMenu ) );
	this->Connect( about_menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onAboutMenu ) );
}

MainFrame_Base::~MainFrame_Base()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame_Base::onIdle ) );
	start_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame_Base::onStart ), NULL, this );
	dof_checkBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame_Base::onDofCheckBox ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onOpenMenu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onSaveImageMenu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_Base::onAboutMenu ) );
}
