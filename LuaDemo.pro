QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        LuaJsonLib/LuaJsonLib.cpp \
        json/cJSON.c \
        cinvokeluabase.cpp \
        cinvokeluafuncexecutor.cpp \
        function/ccoroutine.cpp \
        function/cdebuglua.cpp \
        function/cexecutebin.cpp \
        function/cglobalvar.cpp \
        function/cluatable.cpp \
        function/cnewthread.cpp \
        function/cobjptr.cpp \
        function/coop.cpp \
        function/crequiremodule.cpp \
        function/csimplecfunction.cpp \
        function/csimpleluafunction.cpp \
        function/nestedcall.cpp \
        lua/lapi.c \
        lua/lauxlib.c \
        lua/lbaselib.c \
        lua/lcode.c \
        lua/lcorolib.c \
        lua/lctype.c \
        lua/ldblib.c \
        lua/ldebug.c \
        lua/ldo.c \
        lua/ldump.c \
        lua/lfunc.c \
        lua/lgc.c \
        lua/linit.c \
        lua/liolib.c \
        lua/llex.c \
        lua/lmathlib.c \
        lua/lmem.c \
        lua/loadlib.c \
        lua/lobject.c \
        lua/lopcodes.c \
        lua/loslib.c \
        lua/lparser.c \
        lua/lstate.c \
        lua/lstring.c \
        lua/lstrlib.c \
        lua/ltable.c \
        lua/ltablib.c \
        lua/ltm.c \
        lua/lundump.c \
        lua/lutf8lib.c \
        lua/lvm.c \
        lua/lzio.c \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    release.bat \
    script/callinfo.lua \
    script/common.lua \
    script/coroutine.lua \
    script/debuglua.lua \
    script/executebin.bin \
    script/executebin.lua \
    script/globalvar.lua \
    script/luatable.lua \
    script/newthread.lua \
    script/objptr.lua \
    script/oop.lua \
    script/requiremodule.lua \
    script/simplecfuntion.lua \
    script/simpleluafuntion.lua

HEADERS += \
    LuaJsonLib/LuaJsonLib.h \
    json/cJSON.h \
    cinvokeluabase.h \
    cinvokeluafuncexecutor.h \
    function/ccoroutine.h \
    function/cdebuglua.h \
    function/cexecutebin.h \
    function/cglobalvar.h \
    function/cluatable.h \
    function/cnewthread.h \
    function/cobjptr.h \
    function/coop.h \
    function/crequiremodule.h \
    function/csimplecfunction.h \
    function/csimpleluafunction.h \
    function/nestedcall.h \
    lua/lapi.h \
    lua/lauxlib.h \
    lua/lcode.h \
    lua/lctype.h \
    lua/ldebug.h \
    lua/ldo.h \
    lua/lfunc.h \
    lua/lgc.h \
    lua/ljumptab.h \
    lua/llex.h \
    lua/llimits.h \
    lua/lmem.h \
    lua/lobject.h \
    lua/lopcodes.h \
    lua/lopnames.h \
    lua/lparser.h \
    lua/lprefix.h \
    lua/lstate.h \
    lua/lstring.h \
    lua/ltable.h \
    lua/ltm.h \
    lua/lua.h \
    lua/lua.hpp \
    lua/luaconf.h \
    lua/lualib.h \
    lua/lundump.h \
    lua/lvm.h \
    lua/lzio.h


INCLUDEPATH += LuaJsonLib \
                lua       \
                json
