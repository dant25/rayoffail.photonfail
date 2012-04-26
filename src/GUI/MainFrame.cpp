#include "MainFrame.h"

#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <iostream>
#include "../Importer.h"

#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include "../objects/Sphere.h"
#include "../math/Utilities.h"

using namespace std;


MainFrame::MainFrame( wxWindow* parent )
:
MainFrame_Base( parent )
{
	camera = 0;
	scene = 0;
	rendering = false;
	img = 0;
}


void MainFrame::onStart( wxCommandEvent& event )
{
	if(scene && camera)
	{
		long xres, yres;
		xRes_textCtrl->GetValue().ToLong(&xres);
		yRes_textCtrl->GetValue().ToLong(&yres);
		image = new wxImage((int)xres, (int)yres);
		camera->setResolution(xres, yres);

		if(dof_checkBox->IsChecked())
		{
			camera->depthOfField(true);

			double dist, lensRad;
			dist = strToFloat(dofDistance_textCtrl->GetValue().ToAscii());
			lensRad = strToFloat(lensRadius_textCtrl->GetValue().ToAscii());
			camera->setDepthOfField(dist, lensRad);
		}

		rendering = true;
	}
	else
	{
		statusBar->SetStatusText(_("Falta carregar a cena!"), 0);
	}
}


void MainFrame::onDofCheckBox( wxCommandEvent& event )
{
	dof_panel->Enable(dof_checkBox->IsChecked());
}


void MainFrame::onOpenMenu( wxCommandEvent& event )
{

	const wxChar *types = _("COLLADA (*.dae)|*.dae|");
	//const wxChar *types = _("All Files (*.*)|*.*|");

	wxFileDialog dialog(this, _("Open Scene"), _(""), _(""), types, wxFD_OPEN);

	if (dialog.ShowModal() == wxID_OK)
	{
		statusBar->SetStatusText(_("Carregando a cena..."), 0);
		Importer::load(dialog.GetPath().ToAscii(), &scene, &camera);
		statusBar->SetStatusText(_("Cena carregada."), 0);
      
		//TODO: E a Câmera?
		//camera = new Camera(Vec3(-2.780, -8.000, 2.730, 1.0), normalize(Vec3(0.0, 1.0, 0.0)), Vec3(0.0, 0.0, 1.0), 500, 500);
		//camera = new Camera(Vec3(-11.27431, 13.79502, 6.4117, 1.0), normalize(Vec3(-1.0, 1.0, 0.0)), Vec3(0.0, 0.0, 1.0), 500, 500);
		//camera = new Camera(Vec3(23.599, -24.454, 7.197, 1.0), normalize(Vec3(-1.0, 1.0, 0.0)), Vec3(0.0, 0.0, 1.0), 500, 500);
        //camera = new Camera(Vec3(0, 0, 5.3436, 1.0), normalize(Vec3(0.0, 0.0, -1.0)), Vec3(0.0, 1.0, 0.0), 500, 500);

		//camera->depthOfField(true);
		//camera->setDepthOfField(10.0, 0.5);
		//scene->addLight(new PointLight(Vec3(-2.780, -8.000, 2.730, 1.0), SpectralQuantity(0.2, 0.2, 0.2)));
        //scene->addLight(new SpotLight(SpectralQuantity(0.2, 0.2, 0.2), Vec3(-2.780, -8.000, 2.730, 1.0), Vec3(0.0, 1.0, 0.0), 30.0, 5.0));
		//scene->addObject(new Sphere(Material(SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(0.0, 0.0, 0.0), 100.0, 0.5), 1.0, Vec3(-18.10619, 27.39592, 7.1425, 1.0)));
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
			img = renderer.render(*scene, *camera);
		else
		{
			Image *aux = renderer.render(*scene, *camera);
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
			delete image;
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

	if(savePreviews_checkBox->IsChecked())
		image->SaveFile(_("preview.png"), wxBITMAP_TYPE_PNG);

	statusBar->SetStatusText(_(""), 1);
}
