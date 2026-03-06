QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET = moliqi


include(src/xlsx/qtxlsx.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogfasheset.cpp \
    dragdroptablewidget.cpp \
    draggablebutton.cpp \
    draggabletable.cpp \
    droptargettable.cpp \
    main.cpp \
    mainwindow.cpp \
    mofeiudpbig.cpp \
    onlyudpsender.cpp \
    roundbtn.cpp \
    securitycontrolset.cpp \
    singleinstanceguard.cpp \
    telemetrychannelset.cpp \
    telemetrypcmset.cpp \
    telemetryradiofrequencyset.cpp \
    udpmanager.cpp \
    udpreceiverthread.cpp \
    uppercomputer.cpp \
    worker.cpp \
    mofeibufferwrite.cpp \
    squeue.cpp \
    sreplay.cpp \
    filemacrodialog.cpp \
    logger.cpp \
    workerprocessing.cpp \
    notify.cpp \
    notifymanager.cpp \
    gnssworker.cpp \
    machinestatus.cpp \
    intrangedelegate.cpp \
    maxlengthdelegate.cpp \
    sendermanger.cpp \
    childworkerandparentworker.cpp \
    dataquery.cpp \
    databackworker.cpp \
    txtworker.cpp \
    customdialog.cpp

HEADERS += \
    dialogfasheset.h \
    dragdroptablewidget.h \
    draggablebutton.h \
    draggabletable.h \
    droptargettable.h \
    mainwindow.h \
    mofeiudpbig.h \
    mstrut.h \
    onlyudpsender.h \
    roundbtn.h \
    securitycontrolset.h \
    singleinstanceguard.h \
    telemetrychannelset.h \
    telemetrypcmset.h \
    telemetryradiofrequencyset.h \
    udpmanager.h \
    udpreceiverthread.h \
    uppercomputer.h \
    worker.h \
    mofeibufferwrite.h \
    squeue.h \
    sreplay.h \
    filemacrodialog.h \
    logger.h \
    workerprocessing.h \
    notify.h \
    notifymanager.h \
    gnssworker.h \
    machinestatus.h \
    intrangedelegate.h \
    maxlengthdelegate.h \
    sendermanger.h \
    childworkerandparentworker.h \
    dataquery.h \
    databackworker.h \
    txtworker.h \
    customdialog.h

FORMS += \
    dialogfasheset.ui \
    mainwindow.ui \
    securitycontrolset.ui \
    telemetrychannelset.ui \
    telemetrypcmset.ui \
    telemetryradiofrequencyset.ui \
    filemacrodialog.ui \
    popupwidget.ui \
    machinestatus.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    zaibo.qrc

DISTFILES += \
    qrc/green.png
