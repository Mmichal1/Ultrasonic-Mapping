QT       += core gui
QT       += uitools
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/changeposewindow.cpp \
    ../src/crc16.cpp \
    ../src/devicepoint.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/map.cpp \
    ../src/obstaclepoint.cpp \
    ../src/plotwindow.cpp \
    ../src/poselabel.cpp \
    ../src/posetextedit.cpp \
    ../src/qcustomplot.cpp \
    ../src/welcomedialog.cpp

HEADERS += \
    ../inc/changeposewindow.h \
    ../inc/crc16.h \
    ../inc/devicepoint.h \
    ../inc/mainwindow.h \
    ../inc/map.h \
    ../inc/obstaclepoint.h \
    ../inc/plotwindow.h \
    ../inc/poselabel.h \
    ../inc/posetextedit.h \
    ../inc/qcustomplot.h \
    ../inc/welcomedialog.h

FORMS += \
    ../ui/changeposewindow.ui \
    ../ui/mainwindow.ui \
    ../ui/plotwindow.ui \
    ../ui/welcomedialog.ui

RESOURCES += ../res/icons.qrc

TRANSLATIONS += \
    mapowanie_en.ts \
    mapowanie_pl.ts

CONFIG += lrelease
CONFIG += embed_translations

INCLUDEPATH += ~/Desktop/WDS/QtUltrasonicMappingApp/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

