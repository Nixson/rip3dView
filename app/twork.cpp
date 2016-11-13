#include "twork.h"
#include <cmath>

Twork::Twork(QObject *parent) : QObject(parent)
{

}
void Twork::doFourie(int min, int max){
    minOffset = min;
    maxOffset = max;
    cntr = maxOffset-minOffset;
    IntVector taskI;
    IntVector taskV;
    taskI.resize(length);
    taskV.resize(length);
    for(int i = minOffset; i < maxOffset; ++i){
        for( int j = 0; j < length; ++j){
            int position = j*BLOCKLANGTH+i;
            taskI[j] = iData[position];
            taskV[j] = vData[position];
        }

        TMath* task = new TMath( taskI, taskV, i );
        connect( task, &TMath::resp, this, &Twork::onReady );
        m_threadPool.start(task);
    }
}
void Twork::inData(const IntVector &amp, const IntVector &ph){
    iData = amp;
    vData = ph;
    int lLength = iData.length();
    length = lLength/BLOCKLANGTH;

    outI.resize(lLength);
    outV.resize(lLength);
    cntr = BLOCKLANGTH;
}
void Twork::norm(){
    float MinA, MinP;
    MinA = outI[0];
    MinP = outV[0];
    for(int i = 1; i < length*BLOCKLANGTH; ++i){
        if(MinA > outI[i])
            MinA = outI[i];
        if(MinP > outV[i])
            MinP = outV[i];
    }
    MinA = abs(MinA);
    MinP = abs(MinP);
    for(int i = 1; i < length*BLOCKLANGTH; ++i){
        outI[i]+=MinA;
        outV[i]+=MinP;
    }
    emit Ready(outI,outV);
}
void Twork::onReady(floatVector &mi, floatVector &mv, int num){
    for(int j = 0; j < length; ++j){
        int position = j*BLOCKLANGTH+num;
        outI[position] = mi[j];
        outV[position] = mv[j];
    }
    --cntr;
    if(cntr == 0){
        norm();
    }

}
