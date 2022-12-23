QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fileview.cpp \
    licenseview.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    fileview.h \
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

unix|win32: LIBS += -L$$PWD/lib/ -llibd2c

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lslm_runtime_api
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lslm_runtime_api_dev
else:unix: LIBS += -L$$PWD/lib/ -lslm_runtime_api

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
