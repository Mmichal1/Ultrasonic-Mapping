QT       += core gui
QT       += uitools
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeposewindow.cpp \
    devicepoint.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    obstaclepoint.cpp \
    plotwindow.cpp \
    poselabel.cpp \
    posetextedit.cpp \
    qcustomplot.cpp \
    welcomedialog.cpp

HEADERS += \
    changeposewindow.h \
    devicepoint.h \
    mainwindow.h \
    map.h \
    obstaclepoint.h \
    plotwindow.h \
    poselabel.h \
    posetextedit.h \
    qcustomplot.h \
    welcomedialog.h

FORMS += \
    changeposewindow.ui \
    mainwindow.ui \
    plotwindow.ui \
    welcomedialog.ui

RESOURCES += \
    point.svg \
    point_prev.svg \
    device_pos.svg \
    device_pos_prev.svg \
    connection_bad.svg \
    connection_ok.svg

TRANSLATIONS += \
    mapowanie_en.ts \
    mapowanie_pl.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

