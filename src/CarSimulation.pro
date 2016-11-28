######################################################################
# Automatically generated by qmake (2.01a) czw. kwi 14 01:06:15 2016
######################################################################

QT       += core gui
QT  += opengl

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarSimulation
TEMPLATE = app

INCLUDEPATH += /usr/local/include/Box2D
LIBS += -L"/usr/local/lib"
LIBS += -lBox2D

# Input
HEADERS += utilfunctions.h \
            simulation/car.h \
            simulation/ground.h \
            simulation/object.h \
            simulation/world.h \
            simulation/element/box.h \
            simulation/element/element.h \
            simulation/element/polygon.h \
            simulation/element/wheel.h \
            genetic/geneticalgorithm.h \
            genetic/selection/rouletteselection.h \
            genetic/selection/selection_h.h \
            genetic/selection/selection.h \
            genetic/selection/selectiontypes.h \
            genetic/selection/tournamentselection.h \
            genetic/gene/bodygene.h \
            genetic/gene/gene.h \
            genetic/gene/wheelgene.h \
            genetic/operation/geneticoperation.h \
            genetic/operation/mutation.h \
            genetic/operation/crossover.h \
            simulation/buffer.h \
            generator.h \
            genetic/operation/geneticoperationgenerator.h \
            genetic/operation/wheelmutation.h \
            genetic/operation/bodymutation.h \
            genetic/operation/twopointcrossover.h \
            genetic/operation/onepointcrossover.h \
            genetic/operation/wheelcrossover.h \
            genetic/operation/operation.h
SOURCES += main.cpp \
            utilfunctions.cpp \
            simulation/car.cpp \
            simulation/ground.cpp \
            simulation/object.cpp \
            simulation/world.cpp \
            simulation/element/box.cpp \
            simulation/element/element.cpp \
            simulation/element/polygon.cpp \
            simulation/element/wheel.cpp \
            genetic/geneticalgorithm.cpp \
            genetic/selection/rouletteselection.cpp \
            genetic/selection/selection.cpp \
            genetic/selection/selectiontypes.cpp \
            genetic/selection/tournamentselection.cpp \
            genetic/gene/bodygene.cpp \
            genetic/gene/gene.cpp \
            genetic/gene/wheelgene.cpp \
            genetic/operation/geneticoperation.cpp \
            genetic/operation/mutation.cpp \
            genetic/operation/crossover.cpp \
            simulation/buffer.cpp \
            genetic/operation/geneticoperationgenerator.cpp \
            genetic/operation/wheelmutation.cpp \
            genetic/operation/bodymutation.cpp \
            genetic/operation/twopointcrossover.cpp \
            genetic/operation/onepointcrossover.cpp \
            genetic/operation/wheelcrossover.cpp
