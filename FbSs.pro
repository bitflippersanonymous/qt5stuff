TEMPLATE = app
TARGET = FbSs
QT += core \
    gui \
    network \
    widgets
HEADERS += src/FbSs.h \
    src/network_reader.h
SOURCES += src/FbSs.cpp \
    src/network_reader.cpp \
    src/main.cpp
FORMS += FbSs.ui
RESOURCES += 
