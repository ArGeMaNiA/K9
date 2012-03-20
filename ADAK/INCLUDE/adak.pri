CONFIG += qt debug
DEFINES += USING_PCH
win32 { 
    OBJDIR   = WIN32
    LIB_ext  = a
    SO_ext   = dll
    DEFINES += WIN32
}
macx {
    OBJDIR   = MACOSX
    LIB_ext  = a
    SO_ext   = dylib
    DEFINES += MACOSX
}
!macx & !win32 { 
    ADAK_ARCH=$$system('uname -m')
    !contains(ADAK_ARCH , x86_64) {
        OBJDIR   = LNX32
        DEFINES += LNX32
    }
    contains(ADAK_ARCH , x86_64) {
        OBJDIR   = LNX64
        DEFINES += LNX64
    }
    LIB_ext  = a
    SO_ext   = so
    DEFINES += LINUX
}

release_mode=$$(ADAK_RELEASE)
!isEmpty(release_mode) {
    CONFIG  -= debug
    CONFIG  += release
}

OBJECTS_DIR = $$OBJDIR
MOC_DIR     = $$OBJDIR
RCC_DIR     = $$OBJDIR
UI_DIR      = $$OBJDIR
DESTDIR     = $$OBJDIR
