# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("luado")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#include(/Users/eugenemakei/Library/Android/sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/darwin-x86_64/lib64/clang/12.0.8/include/stdarg.h)

add_library( # Sets the name of the library.
        luado

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        lua/lapi.c
        lua/lapi.h
        lua/lauxlib.h
        lua/lauxlib.c
        lua/lbaselib.c
        lua/lcode.c
        lua/lcode.h
        lua/lcorolib.c
        lua/lctype.c
        lua/lctype.h
        lua/ldblib.c
        lua/ldebug.c
        lua/ldebug.h
        lua/ldo.c
        lua/ldo.h
        lua/ldump.c
        lua/lfunc.c
        lua/lfunc.h
        lua/lgc.c
        lua/lgc.h
        lua/linit.c
        lua/liolib.c
        lua/ljumptab.h
        lua/llex.c
        lua/llex.h
        lua/llimits.h
        lua/lmathlib.c
        lua/lmem.c
        lua/lmem.h
        lua/loadlib.c
        lua/lobject.c
        lua/lobject.h
        lua/lopcodes.c
        lua/lopcodes.h
        lua/lopnames.h
        lua/loslib.c
        lua/lparser.c
        lua/lparser.h
        lua/lprefix.h
        lua/lstate.c
        lua/lstate.h
        lua/lstring.c
        lua/lstring.h
        lua/lstrlib.c
        lua/ltable.c
        lua/ltable.h
        lua/ltablib.c
        lua/ltm.c
        lua/ltm.h
        lua/lua.c
        lua/lua.h
        lua/lua.hpp
        lua/luaconf.h
        lua/lualib.h
        lua/lundump.c
        lua/lundump.h
        lua/lutf8lib.c
        lua/lvm.c
        lua/lvm.h
        lua/lzio.c
        lua/lzio.h

        sqlite/sqlite3ext.h
        sqlite/sqlite3.h
        sqlite/sqlite3.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        luado

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})