#include "MainFrame.h"

#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <iostream>
#include "../Importer.h"

#include "../lights/PointLight.h"
#include "../objects/Sphere.h"

using namespace std;


MainFrame::MainFrame( wxWindow* parent )
:
MainFrame_Base( parent )
{
	camera = new Camera(Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, -1.0), Vec3(0.0, 1.0, 0.0), 500, 500);
	scene = new Scene();
	rendering = false;
	img = 0;

	scene->addLight(new PointLight(Vec3(0.0, 0.0, 10.0), SpectralQuantity(0.7, 0.7, 0.7)));
	scene->addObject(new Sphere(Material(SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.1, 0.1, 0.1), 32.0, 0.0), 5.0, Vec3(0.0, 0.0, 0.0)));
}


void MainFrame::onStart( wxCommandEvent& event )
{
	if(scene && camera)
	{
		long xres, yres;
		xRes_textCtrl->GetValue().ToLong(&xres);
		yRes_textCtrl->GetValue().ToLong(&yres);
		camera->setResolution(xres, yres);

		image = new wxImage((int)xres, (int)yres);

		rendering = true;
	}
	else
	{
		statusBar->SetStatusText(_("Falta carregar a cena!"), 0);
	}
}


void MainFrame::onOpenMenu( wxCommandEvent& event )
{

	const wxChar *types = _("COLLADA (*.dae)|*.dae|");
	//const wxChar *types = _("All Files (*.*)|*.*|");

	wxFileDialog dialog(this, _("Open Scene"), _(""), _(""), types, wxFD_OPEN);

	if (dialog.ShowModal() == wxID_OK)
	{
		statusBar->SetStatusText(_("Carregando a cena..."), 0);
		scene = Importer::load(dialog.GetPath().ToAscii());
		statusBar->SetStatusText(_("Cena carregada."), 0);

		//TODO: E a Câmera?
	}
}


void MainFrame::onSaveImageMenu( wxCommandEvent& event )
{
	// Salvando a imagem
	const wxChar *types = _("Imagem PNG (*.png)|*.png|");
	wxFileDialog dialog(this, _("Save Image"), _(""), _(""), types, wxFD_SAVE);

	if (dialog.ShowModal() == wxID_OK)
	{
		statusBar->SetStatusText(_("Salvando imagem..."), 0);
		imageCanvas->getBitmap()->SaveFile(dialog.GetPath(), wxBITMAP_TYPE_PNG);
		statusBar->SetStatusText(_("Imagem Salva."), 0);
	}
}


void MainFrame::onAboutMenu( wxCommandEvent& event )
{
    wxString msg;
    msg.Printf(wxT("Trabalho:\n\t- Distributed Ray Tracing\n\nDisciplina:\n\t- CGII\n\nAutores:\n\t- Jonas Deyson\n\t- Caio\n\nProfessor:\n\t- Joaquim Bento"));
    wxMessageBox(msg, wxT("About"), wxOK | wxICON_INFORMATION, this);
}


void MainFrame::onIdle( wxIdleEvent& event )
{
	static int frame = 0;

	if(rendering)
	{
		++frame;
		statusBar->SetStatusText(wxString::Format(_("Rendering...\tFrame = %d"), frame), 0);

		//Apenas um loop de cada vez.
		//O resultado deve ser acumulado em img.
		if(!img)
			img = renderer->render(*scene, *camera);
		else
		{
			Image *aux = renderer->render(*scene, *camera);
			for(int y=0; y < aux->getHeight(); y++)
			{
				for(int x=0; x < aux->getWidth(); x++)
				{
					SpectralQuantity color = aux->getPixel(x, y);
					img->setPixel(x, y, (img->getPixel(x, y)*(frame - 1.0) + color)/(float)frame);
				}
			}
			delete aux;
		}

		if(frame == samples_spinCtrl->GetValue())
		{
			rendering = false;
			refreshPreview();
			delete img;
			img = 0;
			frame = 0;

			statusBar->SetStatusText(_("Done."), 0);
		}
		else if((frame % updateRate_spinCtrl->GetValue()) == 0)
		{
			refreshPreview();
			event.RequestMore();
		}
	}
}

void MainFrame::refreshPreview()
{
	statusBar->SetStatusText(_("Refreshing preview..."), 1);

	// Convertendo de Image para wxBitmap
	// FIXME: Alguma forma mais eficiente?

	for(int y=0; y < img->getHeight(); y++)
	{
		for(int x=0; x < img->getWidth(); x++)
		{
			SpectralQuantity color = img->getPixel(x, y);
			int r = color.data[0]*255;
			int g = color.data[1]*255;
			int b = color.data[2]*255;
			image->SetRGB(x, y, r, g, b);
		}
	}

	delete bitmap;
	bitmap = new wxBitmap(*image);
	imageCanvas->setBitmap(bitmap);
	imageCanvas->Refresh();
	Refresh();

	statusBar->SetStatusText(_(""), 1);
}
