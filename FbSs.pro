TEMPLATE = app
TARGET = FbSs
QT += core \
    gui \
    network \
    widgets
HEADERS += src/FbObject.h \
    src/FbSs.h \
    src/network_reader.h
SOURCES += src/FbObject.cpp \
    src/FbSs.cpp \
    src/main.cpp \
    src/network_reader.cpp
FORMS += FbSs.ui \
    FbSs.ui
RESOURCES += 
