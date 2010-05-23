///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __RayoffailGUI__
#define __RayoffailGUI__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame_Base
///////////////////////////////////////////////////////////////////////////////
class MainFrame_Base : public wxFrame 
{
	private:
	
	protected:
		wxSplitterWindow* m_splitter1;
		wxScrolledWindow* m_scrolledWindow1;
		wxNotebook* m_notebook1;
		wxPanel* m_panel4;
		wxButton* start_button;
		wxPanel* m_panel5;
		wxPanel* m_panel2;
		wxStatusBar* statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* file_menu;
		wxMenu* help_menu;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOpenMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaveImageMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAboutMenu( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame_Base( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("RayTracing"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrame_Base();
		void m_splitter1OnIdle( wxIdleEvent& )
		{
		m_splitter1->SetSashPosition( 174 );
		m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame_Base::m_splitter1OnIdle ), NULL, this );
		}
		
	
};

#endif //__RayoffailGUI__
