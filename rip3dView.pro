include(rip3dView.pri)

TEMPLATE = subdirs

# Ensure that library is built before application
CONFIG  += ordered

SUBDIRS += 3rdparty/fftreal
SUBDIRS += app

TARGET = rip3dView
