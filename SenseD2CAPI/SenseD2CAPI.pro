QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/cJSON/cJSON.c \
    common/common.c \
    common/ss_help.c \
    fileview.cpp \
    licenseview.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    common/cJSON/cJSON.h \
    common/common.h \
    common/ss_help.h \
    common/ss_iob_func.h \
    fileview.h \
    inc/d2c.h \
    inc/ss_define.h \
    inc/ss_error.h \
    inc/ss_lm_control.h \
    inc/ss_lm_runtime.h \
    inc/ss_x509.h \
    licenseview.h \
    widget.h

FORMS += \
    fileview.ui \
    licenseview.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# LoadLibrary libd2c
win32: LIBS += -L$$PWD/lib/ -llibd2c

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.


# LoadLibrary slm_runtime
win32: LIBS += -L$$PWD/lib/ -lslm_runtime

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.


# LoadLibrary slm_control
win32: LIBS += -L$$PWD/lib/ -lslm_control

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.


# LoadLibrary libx509
win32: LIBS += -L$$PWD/lib/ -llibx509

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
