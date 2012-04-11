TEMPLATE = app
TARGET = FbSs
QT += core \
    gui \
    network \
    widgets # opengl
HEADERS += src/fb_graphics_view.h \
    src/fb_access.h \
    src/FbSs.h \
    src/network_reader.h
SOURCES += src/fb_graphics_view.cpp \
    src/fb_access.cpp \
    src/FbSs.cpp \
    src/main.cpp \
    src/network_reader.cpp
FORMS += FbSs.ui
RESOURCES += FbSs.qrc
