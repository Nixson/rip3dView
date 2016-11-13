#ifndef WORK_H
#define WORK_H

#include <QDateTime>
#include <QObject>
#include <QMap>
#include "cloudtypelist.h"
#include <QTimer>

class Work : public QObject
{
    Q_OBJECT
public:
    Work();
public slots:
    void doWork(const QByteArray &param);
    void reWork(floatVector &amp,floatVector &ph);
    void Density(bool);
    void setMax(unsigned int b);
    void setAngle(int min,int max);
    void setOffset(unsigned int min,unsigned int max);
    void sChangeInt(QString, int);
    void sChangeDouble(QString, double);
    void sChangeBool(QString, bool);
    void sChangeString(QString, QString);

    void play(int,int);
    void plotSlot();
    void showAll();

signals:
    void resultReady(const Clowd &result);
    void progress(int);
    void saveProgress(int);
    void logLine1(QString);
    void logLine2(QString);
    void progressTimer();
    void run1();
    void run2();
    void Buffer1(const MathVector &buf, int numStart, int numEnd);
    void Buffer2(const MathVector &buf, int numStart, int numEnd);
    void BufferNext1(int num);
    void BufferNext2(int num);
    void initPulse(int leSubBufNum, double leFreq);
    void MaxColorValue(int);
    void hist(const IntVector &amp,const IntVector &ph);
    void setSizeBlock(unsigned int);
private:
    unsigned int bSize,bSizeProgress, progressTimerVal;
    bool density,end1,end2, end3;
    QByteArray data;
    unsigned int MaxBarier;
    unsigned int MaxAngle;
    unsigned int MinAngle;
    unsigned int MaxOffset;
    unsigned int MinOffset;
    unsigned int MaxColor;
    GLfloat *sObjectLink;
    QMap <QString, int> cInt;
    QMap <QString, double> cDouble;
    QMap <QString, bool> cBool;
    QMap <QString, QString> cString;
    MathVector dataResult0;
    MathVector dataResult1;
    MathVector dataResult2;
    MathVector dataDouble;
    QVector <unsigned int> histA;
    QVector <unsigned int> histY;
    GLfloat centerX;
    GLfloat centerY;
    GLfloat centerZ;
    GLfloat delY;
    Clowd sObject;
    void Proc();
    void plot();
    void plotFlower(int x,int y,int z, unsigned int color);
    void appendPoint(int x,int y,int z, int color);
    unsigned int Size;
    bool rePlot, plotWork;
    QDateTime dt;
    void smooth(double *input, double *output, int n, int window);
    QVector < quint16 > resultXXA;
    QVector < quint16 > resultXXY;
    QVector < quint16 > resultYYA;
    QVector < quint16 > resultYYY;

    int playR;
    int playPosition;
    bool isPlay;
    QTimer* time;
};

#endif // WORK_H
