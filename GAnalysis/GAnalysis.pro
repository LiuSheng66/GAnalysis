QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Algorithm/DDA/circulararcdda.cpp \
    Algorithm/DDA/straightlinedda.cpp \
    Algorithm/algorithm.cpp \
    Algorithm/ptpcm/circulararcptpcm.cpp \
    Algorithm/ptpcm/straightlineptpcm.cpp \
    Command/gcommand.cpp \
    Command/mycommand.cpp \
    Command/mycommandrules.cpp \
    Drawing/mygraphicsview.cpp \
    Global/global.cpp \
    main.cpp \
    mainwindow.cpp \
    GeometricFigure/geometricfigure.cpp \
    setting/algorithmWindow/algorithmset.cpp \
    setting/settingmainwindow.cpp \
    setting/textEdit/texteditset.cpp \
    syntax/codeeditor.cpp \
    syntax/myhighlighter.cpp


HEADERS += \
    Algorithm/DDA/circulararcdda.h \
    Algorithm/DDA/straightlinedda.h \
    Algorithm/algorithm.h \
    Algorithm/ptpcm/circulararcptpcm.h \
    Algorithm/ptpcm/straightlineptpcm.h \
    Command/gcommand.h \
    Command/mycommand.h \
    Command/mycommandrules.h \
    Drawing/mygraphicsview.h \
    Global/global.h \
    mainwindow.h \
    GeometricFigure/geometricfigure.h \
    setting/algorithmWindow/algorithmset.h \
    setting/settingmainwindow.h \
    setting/textEdit/texteditset.h \
    syntax/codeeditor.h \
    syntax/myhighlighter.h


FORMS += \
    mainwindow.ui \
    setting/algorithmWindow/algorithmset.ui \
    setting/settingmainwindow.ui \
    setting/textEdit/texteditset.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


DISTFILES +=
