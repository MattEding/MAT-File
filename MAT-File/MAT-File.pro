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

QMAKE_CXXFLAGS += -std=c++17

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

INCLUDEPATH += src include

SOURCES += \
    src/ArrayDataElement.cpp \
    src/DataElement.cpp \
    src/Enums.cpp \
    src/Header.cpp \
    src/Malloc.cpp \
    src/MatFile.cpp \
    src/MatFile_p.h \
    src/Print.cpp \
    src/Swab.hpp \
    src/Swab.inl \
    src/TypeTraits.hpp \
    src/Utils.hpp \
    test/Main.cpp

HEADERS += \
    include/ArrayDataElement.h \
    include/DataElement.h \
    include/Enums.h \
    include/Header.h \
    include/Macros.h \
    include/Malloc.h \
    include/MatFile.h \
    include/Print.h \
    include/TypeDefs.h \
    test/TestFiles.hpp
