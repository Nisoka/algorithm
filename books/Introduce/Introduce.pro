TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    chapter02/insert_sort.cpp \
    chapter02/merge_sort.cpp \
    common/common_int.cpp \
    chapter04/sub_array.cpp \
    common/common_array.cpp \
    chapter06/heapsort.cpp \
    common/datamanager.cpp \
    chapter06/ds-heap.cpp \
    common/base_types.cpp \
    common/nan_debug.cpp \
    chapter06/ds-pri-queue.cpp

HEADERS += \
    common/common.h \
    common/common_int.h \
    chapter04/sub_array.h \
    common/common_array.h \
    chapter06/heapsort.h \
    common/datamanager.h \
    chapter06/ds-heap.h \
    common/base_types.h \
    common/nan_debug.h \
    chapter06/common_heap.h \
    chapter06/ds-pri-queue.h
