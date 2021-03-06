#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T13:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Golden" "Cone" "Graphics
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
    ui/dlgloginscreen.cpp \
    main.cpp \
    models/shapecircle.cpp \
    models/shapeellipse.cpp \
    models/shapeline.cpp \
    models/shapepolyline.cpp \
    models/shapepolygon.cpp \
    models/shapetext.cpp \
    ui/winmain.cpp \
    services/svcjson.cpp \
    ui/dlgtestimonialcreate.cpp \
    viewmodels/vmtestimonialcreate.cpp \
    gimme.cpp \
    models/shaperect.cpp \
    models/ishape.cpp \
    ui/dlgcontactform.cpp \
    viewmodels/vmcanvas.cpp \
    models/shapesquare.cpp \
    models/jsonshape.cpp \
    models/jsoncustomerinquiry.cpp \
    ui/lcshapelayer.cpp \
    ui/lceditvertex.cpp \
    ui/dlgeditorvertices.cpp \
    viewmodels/vmeditorvertices.cpp \
    ui/dlgeditorrectframe.cpp \
    viewmodels/vmeditorrectframe.cpp \
    ui/dlgeditortext.cpp \
    ui/dlgshapereport.cpp \
    models/shapetriangle.cpp

HEADERS += \
    ui/dlgloginscreen.h \
    models/shapecircle.h \
    models/shapeellipse.h \
    models/shapeline.h \
    models/shapepolyline.h \
    models/shapepolygon.h \
    models/shapetext.h \
    ui/winmain.h \
    services/svcjson.h \
    ui/dlgtestimonialcreate.h \
    viewmodels/vmtestimonialcreate.h \
    gimme.h \
    models/ishape.h \
    models/shaperect.h \
    util/goldenconevector.h \
    ui/dlgcontactform.h \
    viewmodels/vmcanvas.h \
    models/jsonshape.h \
    models/shapesquare.h \
    models/dtocustomerinquiry.h \
    models/jsoncustomerinquiry.h \
    ui/lcshapelayer.h \
    ui/lceditvertex.h \
    ui/dlgeditorvertices.h \
    viewmodels/vmeditorvertices.h \
    ui/dlgeditorrectframe.h \
    viewmodels/vmeditorrectframe.h \
    ui/dlgeditortext.h \
    ui/dlgshapereport.h \
    util/customsorts.h \
    models/shapetriangle.h

FORMS += \
    ui/dlgloginscreen.ui \
    ui/winmain.ui \
    ui/dlgtestimonialcreate.ui \
    ui/dlgcontactform.ui \
    ui/dlgeditorrectframe.ui \
    ui/lcshapelayer.ui \
    ui/lceditvertex.ui \
    ui/dlgeditorvertices.ui \
    ui/dlgeditortext.ui \
    ui/dlgshapereport.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cone.qrc \
    logo.qrc
