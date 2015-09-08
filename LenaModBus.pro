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
    libmodbus/src/modbus-data.c \
    libmodbus/src/modbus-rtu.c \
    libmodbus/src/modbus-tcp.c \
    libmodbus/src/modbus.c \
    libmodbus/tests/bandwidth-client.c \
    libmodbus/tests/bandwidth-server-many-up.c \
    libmodbus/tests/bandwidth-server-one.c \
    libmodbus/tests/random-test-client.c \
    libmodbus/tests/random-test-server.c \
    libmodbus/tests/unit-test-client.c \
    libmodbus/tests/unit-test-server.c \
    libmodbus/tests/version.c


HEADERS  += widget.h \
    modbusmanagement.h \
    modbusprotocols.h \
    main.h \
    LCD/LCD_registers.h \
    libmodbus/src/modbus-private.h \
    libmodbus/src/modbus-rtu-private.h \
    libmodbus/src/modbus-rtu.h \
    libmodbus/src/modbus-tcp-private.h \
    libmodbus/src/modbus-tcp.h \
    libmodbus/src/modbus-version.h \
    libmodbus/src/modbus.h \
    libmodbus/tests/unit-test.h \
    libmodbus/config.h


FORMS    += widget.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lmodbus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lmodbus
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lmodbus

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include
