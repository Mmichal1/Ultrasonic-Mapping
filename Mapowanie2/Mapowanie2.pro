QT       += core gui
QT       += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeposebutton.cpp \
    changeposewindow.cpp \
    devicepoint.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    obstaclepoint.cpp \
    poselabel.cpp \
    resetbutton.cpp

HEADERS += \
    changeposebutton.h \
    changeposewindow.h \
    devicepoint.h \
    mainwindow.h \
    map.h \
    obstaclepoint.h \
    poselabel.h \
    resetbutton.h

FORMS += \
    changeposewindow.ui \
    mainwindow.ui

RESOURCES += \
    point.svg \
    point_prev.svg \
    device_pos.svg \
    device_pos_prev.svg \
    dev_point.svg

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
