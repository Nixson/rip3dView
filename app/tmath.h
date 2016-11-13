#ifndef TMATH_H
#define TMATH_H

#include "cloudtypelist.h"
#include <QObject>
#include "QRunnable"
#include "fft.h"


class TMath : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit TMath(const IntVector &mi, const IntVector &mv, int num, QObject *parent = 0);
    void run();
    void work(const IntVector &w, floatVector &out);

signals:
    void resp(floatVector &mi, floatVector &mv ,int num);

public slots:
private:
    IntVector                                   iInput;
    IntVector                                   vInput;
    int                                         rNum, length;
    QVector<ShortComplex>                           m_input;
    floatVector rArg, rPh;
};

#endif // TMATH_H
