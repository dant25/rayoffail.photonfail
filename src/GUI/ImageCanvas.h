#ifndef __ImageCanvas__
#define __ImageCanvas__

#include <wx/window.h>
#include <wx/scrolwin.h>

class wxBitmap;

class ImageCanvas: public wxScrolledWindow{
public:
    ImageCanvas(wxWindow *parent, wxWindowID = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    void setBitmap(wxBitmap*);
    wxBitmap* getBitmap();

private:
    wxBitmap *bitmap;

    void draw( wxPaintEvent& evt );
    void onSize( wxSizeEvent& evt );

    DECLARE_EVENT_TABLE()
};

#endif
