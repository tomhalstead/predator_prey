#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T21:46:45
#
#-----------------------------------------------

QT       += core gui opengl

TARGET = predator_prey
TEMPLATE = app


SOURCES +=  main.cpp\
            mainwindow.cpp\
            coords.cpp \
            CreatureGrid.cpp \
            creatures.cpp\
            random.cpp \
            hunterPreyGL.cpp

HEADERS  += mainwindow.h\
            coords.h \
            CreatureGrid.h \
            creatures.h\
            LinkedList.h \
            random.h \
            hunterPreyGL.h

FORMS    += mainwindow.ui
