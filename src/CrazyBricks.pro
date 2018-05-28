#-------------------------------------------------
#
# Project created by QtCreator 2012-11-02T18:46:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrazyBricks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    physicsystem.cpp \
    body.cpp \
    vector2d.cpp \
    shape.cpp \
    block.cpp \
    platform.cpp \
    pbehaviour.cpp \
    playercontroledbehaviour.cpp \
    smartbehaviour.cpp \
    dumbbehaviour.cpp \
    ball.cpp \
    mapobject.cpp \
    mapbuilder.cpp \
    map.cpp \
    standardbuilder.cpp \
    crazybricks.cpp \
    stateblock.cpp \
    stateblockinitial.cpp \
    stateblockfinal.cpp \
    stateblockcollided.cpp \
    objectfactory.cpp \
    standardfactory.cpp \
    stateblockwall.cpp \
    stateball.cpp \
    stateballtopcontrol.cpp \
    stateballbottomcontrol.cpp \
    paintvisitor.cpp \
    simplepaintvisitor.cpp \
    pixmappaintvisitor.cpp \
    bonus.cpp \
    bonusdecorator.cpp \
    lifesbonusdecorator.cpp \
    freezeplatbonusdecorator.cpp \
    bonuscomponent.cpp \
    easyfactory.cpp \
    crossbuilder.cpp \
    dualbuilder.cpp

HEADERS  += mainwindow.h \
    physicsystem.h \
    body.h \
    idgenerator.h \
    vector2d.h \
    shape.h \
    block.h \
    platform.h \
    pbehaviour.h \
    playercontroledbehaviour.h \
    smartbehaviour.h \
    dumbbehaviour.h \
    ball.h \
    mapobject.h \
    mapbuilder.h \
    map.h \
    standardbuilder.h \
    crazybricks.h \
    stateblock.h \
    stateblockinitial.h \
    stateblockfinal.h \
    stateblockcollided.h \
    objectfactory.h \
    standardfactory.h \
    stateblockwall.h \
    stateball.h \
    stateballtopcontrol.h \
    stateballbottomcontrol.h \
    paintvisitor.h \
    simplepaintvisitor.h \
    pixmappaintvisitor.h \
    bonus.h \
    bonusdecorator.h \
    lifesbonusdecorator.h \
    freezeplatbonusdecorator.h \
    bonuscomponent.h \
    easyfactory.h \
    crossbuilder.h \
    dualbuilder.h

FORMS    +=

OTHER_FILES += \
    TODO

RESOURCES += \
    images.qrc
