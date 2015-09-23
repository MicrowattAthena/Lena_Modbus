#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T13:58:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lena_ModBus
target.files = Lena_ModBus
target.path = /home/root
INSTALLS = target
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    modbusmanagement.cpp \
    modbusprotocols.cpp \
    masterdb.cpp \
    dialog.cpp \
    workerthread.cpp \
    ec_saloon.cpp \
    ec_bedroom.cpp


HEADERS  += widget.h \
    modbusmanagement.h \
    modbusprotocols.h \
    main.h \
    masterdb.h \
    LCD/lcd_registers.h \
    General/general_registers.h \
    EC/EC_registers.h \
    dialog.h \
    workerthread.h \
    ec_saloon.h \
    ec_bedroom.h


FORMS    += widget.ui \
    dialog.ui \
    ec_saloon.ui \
    ec_bedroom.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lmodbus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lmodbus
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lmodbus

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

RESOURCES += \
    interface.qrc
