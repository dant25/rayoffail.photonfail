
#include "ImageCanvas.h"
#include <wx/dcclient.h>
#include <wx/image.h>


BEGIN_EVENT_TABLE(ImageCanvas, wxWindow)
    EVT_PAINT(ImageCanvas::draw)
    EVT_SIZE(ImageCanvas::onSize)
END_EVENT_TABLE()


ImageCanvas::ImageCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
:   wxScrolledWindow(parent, id, pos, size)
{
	wxInitAllImageHandlers();
    bitmap = NULL;
}

void ImageCanvas::setBitmap(wxBitmap* bmp){
    bitmap = bmp;
    if(bmp)
    {
        SetSize(bitmap->GetWidth(), bitmap->GetHeight());
        SetScrollbars(1,1, bitmap->GetWidth(), bitmap->GetHeight(), 0, 0);
        Refresh();
    }
}

wxBitmap* ImageCanvas::getBitmap(){
    return bitmap;
}

void ImageCanvas::draw( wxPaintEvent& evt ){
    wxPaintDC dc(this);
    DoPrepareDC(dc);

    if (bitmap)
        dc.DrawBitmap(*bitmap, 0, 0);
}

void ImageCanvas::onSize( wxSizeEvent& evt ){
    evt.Skip();
}
