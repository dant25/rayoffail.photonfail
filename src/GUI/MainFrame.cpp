#include "MainFrame.h"

#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <iostream>
#include "../Importer.h"

using namespace std;


MainFrame::MainFrame( wxWindow* parent )
:
MainFrame_Base( parent )
{
	scene = 0;
	camera = 0;
}


void MainFrame::onStart( wxCommandEvent& event )
{
	if(scene && camera)
	{
		Image *img = renderer->render(*scene, *camera);
		//TODO: Mostrar a imagem na tela

		// Salvando a imagem
		const wxChar *types = _("Imagem TarGA (*.tga)|*.tga|");
		wxFileDialog dialog(this, _("Save Image"), _(""), _(""), types, wxFD_SAVE);

		if (dialog.ShowModal() == wxID_OK)
		{
			img->save(dialog.GetPath().ToAscii());
		}
	}
	else
	{
		//TODO: Exibir esse erro na status bar.
		cout << "Erro: Falta carregar a cena!" << endl;
	}
}


void MainFrame::onOpenMenu( wxCommandEvent& event )
{

	const wxChar *types = _("COLLADA (*.dae)|*.dae|");

	wxFileDialog dialog(this, _("Open Scene"), _(""), _(""), types, wxFD_OPEN);

	if (dialog.ShowModal() == wxID_OK)
	{
		scene = Importer::load(dialog.GetPath().ToAscii());
		//TODO: E a Câmera?
	}
}


void MainFrame::onSaveImageMenu( wxCommandEvent& event )
{
	//TODO: Implementar
}


void MainFrame::onAboutMenu( wxCommandEvent& event )
{
    wxString msg;
    msg.Printf(wxT("Trabalho:\n\t- Distributed Ray Tracing\n\nDisciplina:\n\t- CGII\n\nAutores:\n\t- Jonas Deyson\n\t- Caio\n\nProfessor:\n\t- Joaquim Bento"));
    wxMessageBox(msg, wxT("About"), wxOK | wxICON_INFORMATION, this);
}
