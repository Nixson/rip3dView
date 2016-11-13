#include "rip3d.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
        format.setVersion(4, 3);
        format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setRenderableType(QSurfaceFormat::OpenGLES);
        format.setDepthBufferSize(64);
        format.setStencilBufferSize(32);
        QSurfaceFormat::setDefaultFormat(format);
    qRegisterMetaType<Clowd>("Clowd");
    qRegisterMetaType<MathVector>("MathVector");
    qRegisterMetaType<IntVector>("IntVector");
    qRegisterMetaType<IntVector>("IntVector&");
    qRegisterMetaType<floatVector>("floatVector");
    qRegisterMetaType<floatVector>("floatVector&");

    QCoreApplication::setOrganizationName("Nixson LLC");
    QCoreApplication::setOrganizationDomain("nixson.ru");
    QCoreApplication::setApplicationName("Rip3dView");
    Rip3d w;
    w.show();

    return a.exec();
}
