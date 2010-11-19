#include "App.h"

#include "MainFrame.h"

#if USE_GUI

IMPLEMENT_APP(App);

#endif //#if USE_GUI

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

#if (!USE_GUI)

#include <iostream>
#include <sstream>

#include "../Importer.h"
#include <wx/bitmap.h>

#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Please, specify input and output filenames" << endl;

		return 0;
	}

	MPI::Init(argc, argv);

	int rank = MPI::COMM_WORLD.Get_rank();
	int size = MPI::COMM_WORLD.Get_size();

	stringstream input, output;

	input << argv[1];
	output << argv[2];

	Renderer renderer;
	Scene *scene;
	Camera *camera;

	Importer::load(input.str().c_str(), &scene, &camera);

	if(scene && camera)
	{
		long xres = 1000;
		long yres = 1000;

		camera->setResolution(xres, yres);

		camera->depthOfField(false);

		Image *img = renderer.render(*scene, *camera, rank, size);

		if (img)
		{
			img->save(output.str().c_str());
			/*wxInitAllImageHandlers();

			wxImage image((int)xres, (int)yres);

			for(int y=0; y < image.GetHeight(); y++)
			{
				for(int x=0; x < image.GetWidth(); x++)
				{
					SpectralQuantity color = img->getPixel(x, y);
					int r = color.data[0]*255;
					int g = color.data[1]*255;
					int b = color.data[2]*255;
					image.SetRGB(x, y, r, g, b);
				}
			}

			wxString outfile(output.str().c_str(), wxMBConvLibc());

			image.SaveFile(outfile, wxBITMAP_TYPE_PNG);*/

			delete img;
		}

		delete scene;
		delete camera;
	}
	else
	{
		cout << "Error on loading scene" << endl;
	}

	MPI::Finalize();

	return 0;
}

#endif //#if (!USE_GUI)
