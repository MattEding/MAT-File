CONFIG += \
    c++17 \
    console \
    no_keywords \
    sdk_no_version_check

CONFIG -= \
    app_bundle \
#    qt

QT += core gui

TEMPLATE = \
    app
#    lib

#QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -std=c++2a

QMAKE_CXXFLAGS += \
    -pedantic \
    -Wall \
    -Wextra

QMAKE_CXXFLAGS_DEBUG += \
    -Og

QMAKE_CFLAGS_RELEASE += \
    -fno-rtti \
    -O3

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
}

INCLUDEPATH +=

SOURCES += \
    Main.cpp \
    MatFile.cpp \
    Header.cpp \
    DataElement.cpp \
    ArrayDataElement.cpp \
    Malloc.cpp \
    Enums.cpp \
    Print.cpp

HEADERS += \
    MatFile.h \
    TypeDefs.h \
    Macros.h \
    Enums.h \
    Header.h \
    DataElement.h \
    ArrayDataElement.h \
    Malloc.h \
    TestFiles.hpp \
    Print.h \
    Swab.hpp \
    Swab.inl \
    Utils.hpp \
    MatFile_p.h \
    TypeTraits.hpp
