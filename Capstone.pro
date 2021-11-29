QT += \
    core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QT/main.cpp \
    QT/mainwindow.cpp \
    external/ECE496-Backend/src/TestClass.cpp \
    $$files(external/ECE496-Backend/stk/src/*.cpp)

HEADERS += \
    QT/mainwindow.h \
    external/ECE496-Backend/inc/TestClass.h \
    $$files(external/ECE496-Backend/stk/include/*.h) \
    $$files(external/ECE496-Backend/stk/src/include/*.h)

FORMS += \
    QT/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    .gitmodules \
    README.md \
    external/ECE496-Backend/.gitignore \
    external/ECE496-Backend/README.md

INCLUDEPATH += \
    $$PWD/external/ECE496-Backend/inc/ \
    $$PWD/external/ECE496-Backend/stk/include/ \
    $$PWD/external/ECE496-Backend/stk/src/include/

DEFINES += \
    __WINDOWS_DS__ \

LIBS += \
    -lole32 \
    -lwinmm \
    -ldsound \
    -lws2_32 \
    -luser32
