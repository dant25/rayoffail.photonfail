

#include "App.h"
#include "MainFrame.h"

IMPLEMENT_APP(App);


bool App::OnInit()
{
    bool wxsOK = true;

    if ( wxsOK )
    {
    	MainFrame* frame = new MainFrame(0);
    	frame->Show();
    	SetTopWindow(frame);
    }

    return true;
}
