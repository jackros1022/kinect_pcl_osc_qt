#############################################################################
# Makefile for building: kinect_pcl_osc_qt
# Generated by qmake (2.01a) (Qt 4.8.1) on: Mon Mar 3 14:51:38 2014
# Project:  kinect_pcl_osc_qt.pro
# Template: app
# Command: /usr/bin/qmake -unix CONFIG+=debug -o Makefile kinect_pcl_osc_qt.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -IKPO_Base -IKPO_Curses -IKPO_GUI -I. -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = KPO_Base/kpo_base.cpp \
		KPO_Base/kpoAnalyzerThread.cpp \
		KPO_Base/kpoBaseApp.cpp \
		KPO_Base/kpoMatcherThread.cpp \
		KPO_Base/kpoOscSender.cpp \
		KPO_Curses/kpoAppCurses.cpp \
		KPO_Curses/main.cpp \
		KPO_GUI/BlobRenderer.cpp \
		KPO_GUI/kpoAppGui.cpp moc_BlobRenderer.cpp \
		moc_kpoAppGui.cpp
OBJECTS       = kpo_base.o \
		kpoAnalyzerThread.o \
		kpoBaseApp.o \
		kpoMatcherThread.o \
		kpoOscSender.o \
		kpoAppCurses.o \
		main.o \
		BlobRenderer.o \
		kpoAppGui.o \
		moc_BlobRenderer.o \
		moc_kpoAppGui.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		kinect_pcl_osc_qt.pro
QMAKE_TARGET  = kinect_pcl_osc_qt
DESTDIR       = 
TARGET        = kinect_pcl_osc_qt

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_kpoAppGui.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: kinect_pcl_osc_qt.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -unix CONFIG+=debug -o Makefile kinect_pcl_osc_qt.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix CONFIG+=debug -o Makefile kinect_pcl_osc_qt.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/kinect_pcl_osc_qt1.0.0 || $(MKDIR) .tmp/kinect_pcl_osc_qt1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/kinect_pcl_osc_qt1.0.0/ && $(COPY_FILE) --parents KPO_Base/BlobFinder.h KPO_Base/kpo_base.h KPO_Base/KPO_Base_global.h KPO_Base/kpo_types.h KPO_Base/kpoAnalyzerThread.h KPO_Base/kpoBaseApp.h KPO_Base/kpoMatcherThread.h KPO_Base/kpoOscSender.h KPO_Curses/kpoAppCurses.h KPO_GUI/BlobRenderer.h KPO_GUI/kpoAppGui.h .tmp/kinect_pcl_osc_qt1.0.0/ && $(COPY_FILE) --parents KPO_Base/kpo_base.cpp KPO_Base/kpoAnalyzerThread.cpp KPO_Base/kpoBaseApp.cpp KPO_Base/kpoMatcherThread.cpp KPO_Base/kpoOscSender.cpp KPO_Curses/kpoAppCurses.cpp KPO_Curses/main.cpp KPO_GUI/BlobRenderer.cpp KPO_GUI/kpoAppGui.cpp .tmp/kinect_pcl_osc_qt1.0.0/ && $(COPY_FILE) --parents KPO_GUI/kpoAppGui.ui .tmp/kinect_pcl_osc_qt1.0.0/ && (cd `dirname .tmp/kinect_pcl_osc_qt1.0.0` && $(TAR) kinect_pcl_osc_qt1.0.0.tar kinect_pcl_osc_qt1.0.0 && $(COMPRESS) kinect_pcl_osc_qt1.0.0.tar) && $(MOVE) `dirname .tmp/kinect_pcl_osc_qt1.0.0`/kinect_pcl_osc_qt1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/kinect_pcl_osc_qt1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_BlobRenderer.cpp moc_kpoAppGui.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_BlobRenderer.cpp moc_kpoAppGui.cpp
moc_BlobRenderer.cpp: KPO_GUI/BlobRenderer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) KPO_GUI/BlobRenderer.h -o moc_BlobRenderer.cpp

moc_kpoAppGui.cpp: ui_kpoAppGui.h \
		KPO_Base/kpoBaseApp.h \
		KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h \
		KPO_Base/kpoOscSender.h \
		KPO_Base/kpoMatcherThread.h \
		KPO_Base/KPO_Base_global.h \
		KPO_Base/BlobFinder.h \
		KPO_GUI/BlobRenderer.h \
		KPO_GUI/kpoAppGui.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) KPO_GUI/kpoAppGui.h -o moc_kpoAppGui.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_kpoAppGui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_kpoAppGui.h
ui_kpoAppGui.h: KPO_GUI/kpoAppGui.ui
	/usr/bin/uic-qt4 KPO_GUI/kpoAppGui.ui -o ui_kpoAppGui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

kpo_base.o: KPO_Base/kpo_base.cpp KPO_Base/kpo_base.h \
		KPO_Base/KPO_Base_global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpo_base.o KPO_Base/kpo_base.cpp

kpoAnalyzerThread.o: KPO_Base/kpoAnalyzerThread.cpp KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoAnalyzerThread.o KPO_Base/kpoAnalyzerThread.cpp

kpoBaseApp.o: KPO_Base/kpoBaseApp.cpp KPO_Base/kpoBaseApp.h \
		KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h \
		KPO_Base/kpoOscSender.h \
		KPO_Base/kpoMatcherThread.h \
		KPO_Base/KPO_Base_global.h \
		KPO_Base/BlobFinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoBaseApp.o KPO_Base/kpoBaseApp.cpp

kpoMatcherThread.o: KPO_Base/kpoMatcherThread.cpp KPO_Base/kpoMatcherThread.h \
		KPO_Base/kpo_types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoMatcherThread.o KPO_Base/kpoMatcherThread.cpp

kpoOscSender.o: KPO_Base/kpoOscSender.cpp KPO_Base/kpoOscSender.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoOscSender.o KPO_Base/kpoOscSender.cpp

kpoAppCurses.o: KPO_Curses/kpoAppCurses.cpp KPO_Curses/kpoAppCurses.h \
		KPO_Base/kpoBaseApp.h \
		KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h \
		KPO_Base/kpoOscSender.h \
		KPO_Base/kpoMatcherThread.h \
		KPO_Base/KPO_Base_global.h \
		KPO_Base/BlobFinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoAppCurses.o KPO_Curses/kpoAppCurses.cpp

main.o: KPO_Curses/main.cpp KPO_Curses/kpoAppCurses.h \
		KPO_Base/kpoBaseApp.h \
		KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h \
		KPO_Base/kpoOscSender.h \
		KPO_Base/kpoMatcherThread.h \
		KPO_Base/KPO_Base_global.h \
		KPO_Base/BlobFinder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o KPO_Curses/main.cpp

BlobRenderer.o: KPO_GUI/BlobRenderer.cpp KPO_GUI/BlobRenderer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BlobRenderer.o KPO_GUI/BlobRenderer.cpp

kpoAppGui.o: KPO_GUI/kpoAppGui.cpp KPO_GUI/kpoAppGui.h \
		ui_kpoAppGui.h \
		KPO_Base/kpoBaseApp.h \
		KPO_Base/kpoAnalyzerThread.h \
		KPO_Base/kpo_types.h \
		KPO_Base/kpoOscSender.h \
		KPO_Base/kpoMatcherThread.h \
		KPO_Base/KPO_Base_global.h \
		KPO_Base/BlobFinder.h \
		KPO_GUI/BlobRenderer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kpoAppGui.o KPO_GUI/kpoAppGui.cpp

moc_BlobRenderer.o: moc_BlobRenderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_BlobRenderer.o moc_BlobRenderer.cpp

moc_kpoAppGui.o: moc_kpoAppGui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_kpoAppGui.o moc_kpoAppGui.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
