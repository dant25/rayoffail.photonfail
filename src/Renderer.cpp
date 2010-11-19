#include "Renderer.h"

#include <iostream>
#include <sstream>

#include <omp.h>
#include <mpi.h>

Image *Renderer::render(const Scene& s, const Camera& c, int minw, int incrw, int maxw, int minh, int incrh, int maxh)
{
    Image *img = new Image(c.getWidth(), c.getHeight());
//    int numSamples = 32;

	if (maxw == -1)
	{
		maxw = img->getWidth();
	}

	if (maxh == -1)
	{
		maxh = img->getHeight();
	}

    //Loop principal, cria numSamples raios pra cada pixel
    //
    SpectralQuantity color;
    //#pragma omp parallel for shared(img, minw, maxw, incrw, minh, maxh, incrh) schedule(dynamic)
    //for(int i = 0; i < img->getWidth(); i++){
    for(int i = minw; i < maxw; i += incrw){
        //for(int j = 0; j < img->getHeight(); j++) {
        for(int j = minh; j < maxh; j += incrh) {
			Ray r = c.generateRay(i, j);
			SpectralQuantity color = s.render(r);
			img->setPixel(i, j, img->getPixel(i, j) + color);
        }
    }

    double *data = img->makeData();

    int size = img->getWidth()*img->getHeight()*3;

    double *recv = NULL;

    if (MPI::COMM_WORLD.Get_rank() == 0)
	{
		recv = new double[size];

		for (int i = 0; i < size; i++)
		{
			recv[i] = 0.0;
		}
	}

	/*//debug
	if (MPI::COMM_WORLD.Get_rank() != 0)
	{
		recv = new double[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = 0.0;
		}
	}
	//endebug*/

    MPI::COMM_WORLD.Reduce(data, recv, img->getWidth()*img->getHeight()*3, MPI::DOUBLE, MPI::SUM, 0);

    delete [] data;

    if (MPI::COMM_WORLD.Get_rank() == 0)
	{
		img->setData(recv);

		delete [] recv;
	}
	else
	{
		delete img;

		img = NULL;
	}

    return img;
}
