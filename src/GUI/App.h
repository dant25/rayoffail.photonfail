#ifndef _APP_H_
#define _APP_H_

#define USE_GUI false

#include <wx/app.h>

class App : public wxApp
{
    public:
        virtual bool OnInit();
};

#if (!USE_GUI)

int main(int argc, char *argv[]);

#endif //#if (!USE_GUI)

#endif //#ifndef _APP_H_
