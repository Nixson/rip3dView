#include "tmath.h"

TMath::TMath(const IntVector &mi, const IntVector &mv, int num, QObject *parent) : QObject(parent)
  ,iInput(mi), vInput(mv), rNum(num)
{
    length = iInput.size();
    rArg.resize(length);
    rPh.resize(length);
    m_input.resize(length);
}


void TMath::run(){
    work(iInput, rArg);
    work(vInput, rPh);
    emit resp(rArg,rPh,rNum);
}
void TMath::work(const IntVector &input, floatVector &out){
    for( int i = 0; i < length; ++i){
        m_input[i].re = (double)input[i];
        m_input[i].im = 0.0;
    }
    universal_fft(m_input.data(),length,false);

    for( int i = 0; i < length; ++i){
        out[i] = (float)m_input[i].re;
    }
}
