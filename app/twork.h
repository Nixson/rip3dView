#ifndef TWORK_H
#define TWORK_H

#include "cloudtypelist.h"
#include <QObject>
#include <QThreadPool>
#include "tmath.h"

class Twork : public QObject
{
    Q_OBJECT
public:
    explicit Twork(QObject *parent = 0);

signals:
    void Ready(floatVector &amp, floatVector &ph);

public slots:
    void inData(const IntVector &amp, const IntVector &ph);
    void onReady(floatVector &a, floatVector &v, int num);
    void doFourie(int min, int max);

protected:
    floatVector outI;
    int cntr, length;
    floatVector outV;
    QThreadPool m_threadPool;
    IntVector iData;
    IntVector vData;
    void norm();
    int minOffset, maxOffset;
};

#endif // TWORK_H
