include (../../ADAK/INCLUDE/adak.pri)

ROOT_DIR    = ../../

QT -= gui
QT += sql


TARGET = MUH_ONAR

CONFIG += console

CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../ADAK/INCLUDE . ..

SOURCES += k9_onar_main.cpp \
           k9_onar_utils.cpp \
           ../MUHASEBE/muh_console_utils.cpp


HEADERS += muh_onar.h

LIBS           += ../../ADAK/$$OBJDIR/libADAK.a
PRE_TARGETDEPS += ../../ADAK/$$OBJDIR/libADAK.a

win32: {LIBS+= -liphlpapi}
