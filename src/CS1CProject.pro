#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T13:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS1CProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    models/shapeellipse.cpp \
    models/shapepolygon.cpp \
    models/shapetext.cpp \
    ui/winmain.cpp \
    services/svcjson.cpp \
    ui/dlgtestimonialcreate.cpp \
    viewmodels/vmtestimonialcreate.cpp \
    gimme.cpp \
    models/shaperect.cpp \
    models/ishape.cpp \
    ui/dlgshapeselector.cpp \
    ui/dlgcontactform.cpp \
    viewmodels/vmcanvas.cpp \
    ui/dlgshapeadderrect.cpp

HEADERS += \
    models/shapeellipse.h \
    models/shapepolygon.h \
    models/shapetext.h \
    ui/winmain.h \
    services/svcjson.h \
    ui/dlgtestimonialcreate.h \
    viewmodels/vmtestimonialcreate.h \
    gimme.h \
    models/ishape.h \
    models/shaperect.h \
    ui/dlgshapeselector.h \
    models/ishape.h \
    util/goldenconevector.h \
    ui/dlgcontactform.h \
    viewmodels/vmcanvas.h \
    ui/dlgshapeadderrect.h \
    models/jsonshape.h

FORMS += \
    ui/winmain.ui \
    ui/dlgtestimonialcreate.ui \
    ui/dlgshapeselector.ui \
    ui/dlgcontactform.ui \
    ui/dlgshapeadderrect.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
