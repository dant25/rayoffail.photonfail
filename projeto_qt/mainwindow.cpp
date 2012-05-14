#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <iostream>

#include "../src/Importer.h"

#include "../src/lights/PointLight.h"
#include "../src/lights/SpotLight.h"
#include "../src/objects/Sphere.h"
#include "../src/math/Utilities.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camera = 0;
    scene = 0;
    img = 0;

    connect(&timer, SIGNAL(timeout()), this, SLOT(on_render()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_preview_spinBox_valueChanged(int arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_sample_spinBox_valueChanged(int arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_x_spinBox_valueChanged(int arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_y_spinBox_valueChanged(int arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_startButton_clicked()
{
    if(scene && camera)
    {
        int xres, yres;
        xres = ui->x_spinBox->value();
        yres = ui->y_spinBox->value();
        image = new QImage((int)xres, (int)yres, QImage::Format_RGB32);
        camera->setResolution(xres, yres);

        if(ui->dof_groupBox->isChecked())
        {
            camera->depthOfField(true);

            double dist, lensRad;
            dist = ui->distance_doubleSpinBox->value();
            lensRad = ui->radius_doubleSpinBox->value();
            camera->setDepthOfField(dist, lensRad);
        }

        timer.start(ui->preview_spinBox->value()*1000);
    }
    else
    {
        ui->statusBar->showMessage("Falta carregar a cena!");
    }
}

void MainWindow::on_distance_doubleSpinBox_valueChanged(double arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_radius_doubleSpinBox_valueChanged(double arg1)
{
    std::cout << "VALOR: " << arg1 << std::endl;
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QDir::currentPath(),
                                                  tr("COLLADA (*.dae *.dae"));

    if(!fileName.isNull())
    {
        ui->statusBar->showMessage(("Carregando a cena..."));

        Importer::load(fileName.toAscii(), &scene, &camera);

        ui->statusBar->showMessage(("Cena carregada."));
    }
}

void MainWindow::on_action_Save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                QDir::homePath(),
                                tr("Imagem PNG (*.png *.png"));

    if (!fileName.isNull())
    {
        ui->statusBar->showMessage("Salvando imagem...");
        image->save(fileName, "PNG");
        ui->statusBar->showMessage("Imagem Salva.");
    }

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PhotonFail"),
            tr("<p>Bem Vindos!!!</p>"));
}

void MainWindow::on_render()
{
    static int frame = 0;

    ++frame;
    ui->statusBar->showMessage( QString("Rendering...\tFrame = %1").arg(frame) );

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

    if( frame == ui->sample_spinBox->value() )
    {
        timer.stop();
        refreshPreview();

        delete img;
        delete image;
        img = 0;
        frame = 0;

        ui->statusBar->showMessage("Done.");
    }
    else if(frame % ui->preview_spinBox->value() == 0)
    {
        refreshPreview();
        //event.RequestMore();
    }

}

void MainWindow::refreshPreview()
{
    ui->statusBar->showMessage(("Refreshing preview..."), 1);

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
            image->setPixel(x, y, qRgb(r, g, b));
        }
    }

    if(ui->graphicsView->scene() == 0)
    {
        QGraphicsScene *s= new QGraphicsScene();
                s->addPixmap(QPixmap::fromImage(*image));

        ui->graphicsView->setScene(s);
    }
    else
    {
        ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(*image));
    }


    ui->graphicsView->show();

    if(ui->save_checkBox->isChecked())
        image->save("preview.png");

    ui->statusBar->showMessage((""), 1);
}
