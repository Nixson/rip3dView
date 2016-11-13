#include "work.h"
#include <iostream>
#include <QDateTime>
#include <QFile>

Work::Work(): MaxAngle(360), MinAngle(0), MaxOffset(BLOCKLANGTH), MinOffset(0), Size(0)
{
    density = false;
    plotWork = false;
    rePlot = false;
    isPlay = false;
}
void Work::Density(bool dens){
    density = dens;
}
void Work::showAll(){
    isPlay = false;
    plot();
}
void Work::play(int v, int r){
    time = new QTimer();
    time->setInterval(v);
    playPosition = -1;
    playR = r;
    isPlay = true;
    connect(time,SIGNAL(timeout()),this,SLOT(plotSlot()));
    time->start();
}
void Work::plotSlot(){
    playPosition++;
    plot();
    unsigned int position = (unsigned int)(playPosition+playR);
    if(position > Size)
        time->stop();
}
void Work::reWork(floatVector &amp, floatVector &ph){
    int binarySize = bSize*BLOCKLANGTH;
    unsigned int *dataResultInt = histA.data();
    float max = 0.0;
    for(int bStep = 0; bStep < binarySize; bStep++){
        if(max < amp[bStep])
            max = amp[bStep];
    }
    //unsigned int *dataResultIntY = histY.data();
    for(int bStep = 0; bStep < binarySize; bStep++){
        *(dataResultInt++)  = (unsigned int)((amp[bStep]/max)*MaxColor);
        //*(dataResultIntY++) = (unsigned int)ph[bStep];
    }
    plot();
}
void Work::doWork(const QByteArray &param){
    dt = QDateTime::currentDateTime();
    emit logLine1(dt.toString()+" Загрузка данных");

    data = QByteArray(param);
    // берем 0, 16, 15, 31 блоки. Соединяем в строку и отправляем в кор обработку. 1024*4 блоков
    // внутри они разбираются и обрабатываются
    Proc();
}
void Work::Proc(){
    int binarySize = data.size()/4;
    bSize = (unsigned int)binarySize/BLOCKLANGTH;
    QVector < quint16 > resultA;
    QVector < quint16 > resultY;
    resultA.resize(binarySize);
    resultY.resize(binarySize);
    char *dataFile = data.data();
    quint16  *dataResultInt = resultA.data();
    memcpy(dataResultInt,dataFile,binarySize*2);
    dataResultInt = resultY.data();
    dataFile += binarySize*2;
    memcpy(dataResultInt,dataFile,binarySize*2);
    {
        histA.clear();
        histY.clear();
        histA.resize(binarySize);
        histY.resize(binarySize);
        unsigned int *dataResultInt = histA.data();
        unsigned int *dataResultIntY = histY.data();
        for(int bStep = 0; bStep < binarySize; bStep++){
            *(dataResultInt++)  = (unsigned int)resultA[bStep];
            *(dataResultIntY++) = (unsigned int)resultY[bStep];
        }
    }
    MaxColor = QUINT16_SIZE;
    emit MaxColorValue(MaxColor);
    Size = (unsigned int)bSize;
    emit setSizeBlock(Size);
    emit progress(100);
    emit hist(histA, histY);
    plot();
}

void Work::setAngle(int min, int max){
    MinAngle = (unsigned int)min+180;
    MaxAngle = (unsigned int)max+180;
    delY = 32.0f/(181-max);
    plot();
}
void Work::setOffset(unsigned int min, unsigned int max){
    MinOffset = min;
    MaxOffset = max;
    plot();
}
void Work::setMax(unsigned int b){
    MaxBarier = b;
    plot();
}
void Work::plot(){
    if(histA.length() == 0)
        return;
    if(plotWork){
        rePlot = true;
        return;
    }
    emit logLine1("Start");
    rePlot = false;
    plotWork = true;

    sObject.clear();
    //размер = длина * ширина * 24 точки по 6 координат в каждой
    sObject.resize( (MaxOffset-MinOffset) * Size * 144);

    sObjectLink = sObject.data();


    centerX = (GLfloat)Size/2;
    centerY =  MinAngle + (GLfloat) ( MaxAngle - MinAngle ) /2;
    centerZ = MinOffset + (GLfloat) ( MaxOffset - MinOffset ) /2;
    int realSize = 0;
    if(isPlay){
        for( int x = playPosition; x < (int)Size && x < (playR + playPosition); x++){
            //номер пачки
            int packet = x*BLOCKLANGTH;
            for(unsigned int z = MinOffset; z < MaxOffset; z++){
                unsigned int y = histY[packet+z];
                if(y >= MinAngle && y <= MaxAngle){
                    unsigned int color = histA[packet+z];
                    if(color >= MaxBarier){
                        plotFlower((int)x,(int)y,(int)z,color);
                        realSize++;
                    }
                }
            }

        }
    }else {
        for( unsigned int x = 0; x < Size; x++){
            //номер пачки
            int packet = x*BLOCKLANGTH;
            for(unsigned int z = MinOffset; z < MaxOffset; z++){
                unsigned int y = histY[packet+z];
                if(y >= MinAngle && y <= MaxAngle){
                    unsigned int color = histA[packet+z];
                    if(color >= MaxBarier){
                        plotFlower((int)x,(int)y,(int)z,color);
                        realSize++;
                    }
                }
            }

        }
    }

    sObject.resize(realSize*24*6);
    emit resultReady(sObject);
    emit logLine1("Done");
    plotWork = false;
    if(rePlot){
        plot();
    }

}
void Work::appendPoint(int x,int y,int z, int color){
    *(sObjectLink++) = (centerX-x)/MAXBYTEFLOAT;
    *(sObjectLink++) = (centerY-y)/(MAXBYTEFLOAT*delY);
    *(sObjectLink++) = -(centerZ-z)/MAXBYTEFLOAT;
    if(color == 0) {
        *(sObjectLink++) = 0.0f;
        *(sObjectLink++) = 0.0f;
        *(sObjectLink++) = (float)(MAXBYTEFLOAT - color)/MAXBYTEFLOAT;
    }
    else {
        *(sObjectLink++) = (float)color/MAXBYTEFLOAT;
        *(sObjectLink++) = 0.0f;
        *(sObjectLink++) = (float)(MAXBYTEFLOAT - color)/MAXBYTEFLOAT;
    }
}
void Work::plotFlower(int x,int y,int z, unsigned int color){
    double NormalColor = (double)(QUINT16_SIZE);
    int nColor = (int)MAXBYTE*((double)color)/NormalColor;
    if(nColor > MAXBYTE)
        nColor = MAXBYTE;
    //appendPoint(x,y,z,nColor);
    appendPoint(x-1,y,z-1,nColor);
    appendPoint(x+1,y,z-1,nColor);
    appendPoint(x,y+1,z,nColor);
    appendPoint(x-1,y,z+1,nColor);
    appendPoint(x+1,y,z+1,nColor);
    appendPoint(x,y+1,z,nColor);
    appendPoint(x+1,y,z-1,nColor);
    appendPoint(x+1,y,z+1,nColor);
    appendPoint(x,y+1,z,nColor);
    appendPoint(x-1,y,z-1,nColor);
    appendPoint(x-1,y,z+1,nColor);
    appendPoint(x,y+1,z,nColor);

    appendPoint(x-1,y,z-1,nColor);
    appendPoint(x+1,y,z-1,nColor);
    appendPoint(x,y-1,z,nColor);
    appendPoint(x-1,y,z+1,nColor);
    appendPoint(x+1,y,z+1,nColor);
    appendPoint(x,y-1,z,nColor);
    appendPoint(x+1,y,z-1,nColor);
    appendPoint(x+1,y,z+1,nColor);
    appendPoint(x,y-1,z,nColor);
    appendPoint(x-1,y,z-1,nColor);
    appendPoint(x-1,y,z+1,nColor);
    appendPoint(x,y-1,z,nColor);
}
void Work::smooth(double *input, double *output, int n, int window)
{
   int i,j,z,k1,k2,hw;
   double tmp;
   if(fmod(window,2)==0) window++;
   hw=(window-1)/2;
   output[0]=input[0];

   for (i=1;i<n;i++){
       tmp=0;
       if(i<hw){
           k1=0;
           k2=2*i;
           z=k2+1;
       }
       else if((i+hw)>(n-1)){
           k1=i-n+i+1;
           k2=n-1;
           z=k2-k1+1;
       }
       else{
           k1=i-hw;
           k2=i+hw;
           z=window;
       }

       for (j=k1;j<=k2;j++){
           tmp=tmp+input[j];
       }
       output[i]=tmp/z;
   }
}

void Work::sChangeInt(QString name, int val){
    cInt[name] = val;
}
void Work::sChangeDouble(QString name, double val){
    cDouble[name] = val;
}
void Work::sChangeBool(QString name, bool val){
    cBool[name] = val;
}
void Work::sChangeString(QString name, QString val){
    cString[name] = val;
}
