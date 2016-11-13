#ifndef RIP3D_H
#define RIP3D_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include "cloudtypelist.h"
#include "scobject.h"
#include "plotgl.h"
#include "rcontrol.h"

namespace Ui {
class Rip3d;
}

class Rip3d : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit Rip3d(QWidget *parent = 0);
    ~Rip3d();
signals:
    void xValueChanged(int);
    void yValueChanged(int);
    void zValueChanged(int);
    void verticalSliderChanged(int);
    void operate(const QByteArray &param);
    void ArgMinChanged(int);
    void ArgMaxChanged(int);
    void PhMinChanged(int);

private slots:
    void on_loadFile_triggered();
    void on_xRotation_valueChanged(int value);
    void on_yRotation_valueChanged(int value);
    void on_zRotation_valueChanged(int value);
    void on_colorValue_valueChanged(int arg1);
    void on_scale_valueChanged(int value);
    void xRotationChanged(int);
    void yRotationChanged(int);
    void zRotationChanged(int);
    void MaxColorValue(int);
    void setSizeBlock(int);

    void progress(int);
    void progressTimer();
    void progressTimerNum();
    void logLine1(QString);
    void logLine2(QString);
    void handleResults(const Clowd &result);
    void on_verticalSlider_valueChanged(int value);
    void on_ArgMin_valueChanged(int value);
    void on_ArgMax_valueChanged(int value);
    void on_PhMin_valueChanged(int value);
    void setArgMin(int val);
    void setArgMax(int val);
    void setPhMin(int val);



    void on_action_triggered();

    void on_playV_valueChanged(int arg1);

    void on_playR_valueChanged(int arg1);

    void on_playButton_clicked();

    void on_playButton_2_clicked();

    void on_Fourier_clicked();

private:
    Ui::Rip3d *ui;
    PlotGl *plotGl;
    ScObject *sc;
    bool first;
    Rcontrol control;
    QTimer *timer;
    bool timerOn;
};

#endif // RIP3D_H
