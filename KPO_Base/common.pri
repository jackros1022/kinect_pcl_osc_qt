
QT += concurrent
CONFIG += c++11

SOURCES += \
    kpoPclFunctions.cpp \
    kpoOscSender.cpp \
    kpoObjectDescription.cpp \
    kpoBaseApp.cpp \
    kpoMatcherThread.cpp

HEADERS += \
    kpo_types.h \
    kpoPclFunctions.h \
    kpoOscSender.h \
    kpoObjectDescription.h \
    kpoBaseApp.h \
    kpoMatcherThread.h \
    kpoMatcherThread.h


LIBS += -L/usr/lib/pcl-1.7

INCLUDEPATH += /usr/include/vtk-5.8 /usr/include/pcl-1.7 /usr/include/eigen3 /usr/include/flann


INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -loscpack
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -loscpack
else:symbian: LIBS += -loscpack
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -loscpack

INCLUDEPATH += $$PWD/../../../usr/include/oscpack
DEPENDPATH += $$PWD/../../../usr/include/oscpack


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lboost_system
else:symbian: LIBS += -lboost_system
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lboost_system



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lvtkFiltering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lvtkFiltering
else:symbian: LIBS += -lvtkFiltering
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lvtkFiltering



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcl_common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcl_common
else:symbian: LIBS += -lpcl_common
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcl_common


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lOpenNI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lOpenNI
else:symbian: LIBS += -lOpenNI
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lOpenNI

INCLUDEPATH += /usr/include/openni/


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcl_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcl_io
else:symbian: LIBS += -lpcl_io
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcl_io

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcl_octree
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcl_octree
else:symbian: LIBS += -lpcl_octree
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcl_octree


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcl_io_ply
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcl_io_ply
else:symbian: LIBS += -lpcl_io_ply
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcl_io_ply



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lboost_thread
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lboost_thread
else:symbian: LIBS += -lboost_thread
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lboost_thread


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_filters
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_filters
else:symbian: LIBS += -lpcl_filters
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_filters


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_search
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_search
else:symbian: LIBS += -lpcl_search
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_search


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_features
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_features
else:symbian: LIBS += -lpcl_features
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_features


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_surface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_surface
else:symbian: LIBS += -lpcl_surface
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_surface


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_keypoints
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_keypoints
else:symbian: LIBS += -lpcl_keypoints
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_keypoints


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpcl_recognition
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpcl_recognition
else:symbian: LIBS += -lpcl_recognition
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpcl_recognition
