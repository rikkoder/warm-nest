QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# adding compilation flags
QMAKE_CXXFLAGS += -lmariadbcpp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    complaint.cpp \
    complaintsform.cpp \
    connector.cpp \
    hosteler.cpp \
    hostelersform.cpp \
    loginprompt.cpp \
    main.cpp \
    mainwindow.cpp \
    remarkinput.cpp \
    staff.cpp \
    staffsform.cpp \
    utilities.cpp

HEADERS += \
    complaint.h \
    complaintsform.h \
    connector.h \
    hosteler.h \
    hostelersform.h \
    loginprompt.h \
    mainwindow.h \
    remarkinput.h \
    staff.h \
    staffsform.h \
    utilities.h

FORMS += \
    complaintsform.ui \
    hostelersform.ui \
    loginprompt.ui \
    mainwindow.ui \
    remarkinput.ui \
    staffsform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
