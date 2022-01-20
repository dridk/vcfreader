QT -= gui
QT += testlib
CONFIG += c++11 console

SOURCES+= src/utils.cpp \
    src/record.cpp \
    src/value.cpp \
    src/test.cpp \
 \    #src/vcfreader.cpp
    src/vcfreader.cpp

TARGET=testvcfreader

HEADERS +=\
    src/record.h \
    src/utils.h \
    src/value.h \
    src/test.h \
 \    #src/vcfreader.h
    src/vcfreader.h

LIBS+=-lz
INCLUDEPATH+=zlib zstr lest

CONFIG += c++11 console
CONFIG -= app_bundle


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
