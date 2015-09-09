#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T13:58:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lena_ModBus
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    modbusmanagement.cpp \
    modbusprotocols.cpp \
    masterdb.cpp


HEADERS  += widget.h \
    modbusmanagement.h \
    modbusprotocols.h \
    main.h \
    masterdb.h \
    LCD/lcd_registers.h \
    General/general_registers.h \
    EC/EC_registers.h


FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lmodbus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lmodbus
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lmodbus

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include
