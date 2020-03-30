include($$PWD/../../plugins.pri)

HEADERS += decodergmefactory.h \
           decoder_gme.h \
           gmehelper.h
    
SOURCES += decodergmefactory.cpp \
           decoder_gme.cpp \
           gmehelper.cpp

DESTDIR = $$PLUGINS_PREFIX/Input
TARGET = gme

INCLUDEPATH += $$EXTRA_PREFIX/libgme/include

unix{
    unix:android {
        TARGET = plugin_input_gme
        QMAKE_CLEAN = $$DESTDIR/libplugin_input_gme.so
    }else{
        QMAKE_CLEAN = $$DESTDIR/libgme.so
    }
    LIBS += -L$$EXTRA_PREFIX/libgme/lib -lgme$$STATIC_LIBRARY_SUFFIX
}

win32 {
    LIBS += -L$$EXTRA_PREFIX/libgme/lib -lgme.dll
}
