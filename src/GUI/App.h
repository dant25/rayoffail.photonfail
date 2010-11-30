#ifndef _APP_H_
#define _APP_H_

#define USE_GUI false

#if USE_GUI

#include <wx/app.h>

class App : public wxApp
{
    public:
        virtual bool OnInit();
};

#else

int main(int argc, char *argv[]);

#endif //#if USE_GUI

#endif //#ifndef _APP_H_
