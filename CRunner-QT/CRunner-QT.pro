#-------------------------------------------------
#
# Project created by QtCreator 2017-08-05T06:41:58
#
#-------------------------------------------------
# ---- Qt 6 project configuration ----

# This project uses Qt modules. For a GUI app with QMainWindow,
# you MUST include the Widgets module.
QT += widgets

# If you previously had this in Qt 5, it's still OK in Qt 6:
# QT += core gui widgets

# Tell qmake we want modern C++
CONFIG += c++11

# Your sources / headers (example)
SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui
