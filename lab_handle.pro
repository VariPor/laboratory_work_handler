QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++20

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
    models/colordelegate.cpp \
    models/comboboxdelegate.cpp \
    models/instrument_model.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    models/measurement_model.cpp \
    models/naming_model.cpp \
    plots/plot_2d.cpp \
    plots/plot_choise.cpp \
    plots/plot_hist.cpp \
    plots/plot_scatter.cpp \
    qcustomplot.cpp \
    strategy_io.cpp \
    variable_data.cpp \
    models/visual_model.cpp

HEADERS += \
    block.h \
    models/colordelegate.h \
    models/comboboxdelegate.h \
    editor_odf.h \
    models/instrument_model.h \
    mainwindow.h \
    manager.h \
    measurement_model.h \
    models/naming_model.h \
    plots/plot.h \
    plots/plot_2d.h \
    plots/plot_choise.h \
    plots/plot_hist.h \
    plots/plot_scatter.h \
    qcustomplot.h \
    strategy_io.h \
    variable_data.h \
    models/visual_model.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
