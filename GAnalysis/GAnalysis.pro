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
    Algorithm/algorithm.cpp \
    Command/gcommand.cpp \
    Command/mycommand.cpp \
    Command/mycommandrules.cpp \
    CoordinateSystem/coordinatesystem.cpp \
    Drawing/paintarea.cpp \
    main.cpp \
    mainwindow.cpp \
    GeometricFigure/geometricfigure.cpp \
    setting/settingmainwindow.cpp \
    syntax/codeeditor.cpp \
    syntax/myhighlighter.cpp


HEADERS += \
    Algorithm/algorithm.h \
    Command/gcommand.h \
    Command/mycommand.h \
    Command/mycommandrules.h \
    CoordinateSystem/coordinatesystem.h \
    Drawing/paintarea.h \
    mainwindow.h \
    GeometricFigure/geometricfigure.h \
    setting/settingmainwindow.h \
    syntax/codeeditor.h \
    syntax/myhighlighter.h


FORMS += \
    mainwindow.ui \
    setting/settingmainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


DISTFILES +=
