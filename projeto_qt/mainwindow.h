#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>

#include "../src/Scene.h"
#include "../src/Camera.h"
#include "../src/Renderer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_preview_spinBox_valueChanged(int arg1);

    void on_sample_spinBox_valueChanged(int arg1);

    void on_x_spinBox_valueChanged(int arg1);

    void on_y_spinBox_valueChanged(int arg1);

    void on_startButton_clicked();

    void on_distance_doubleSpinBox_valueChanged(double arg1);

    void on_radius_doubleSpinBox_valueChanged(double arg1);

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_actionAbout_triggered();

    void    on_render();

    void refreshPreview();

private:
    Ui::MainWindow *ui;
    QTimer timer;


    Renderer renderer;
    Scene *scene;
    Camera *camera;

    Image *img;
    QImage *image;
};

#endif // MAINWINDOW_H
