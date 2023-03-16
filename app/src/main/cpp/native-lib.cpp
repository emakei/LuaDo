#include <jni.h>
#include <string>
#include "lua/lua.hpp"
//#include "sqlite/sqlite3ext.h"

#define LUA_USE_POSIX 1

static lua_State * L;
static int topPrev = -1;
static int topCurr = -1;

extern "C" JNIEXPORT jstring JNICALL
Java_pro_emakei_luado_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "Created by Yauhen Makei\n\n";
    hello.append(LUA_COPYRIGHT);
    hello.append("\n\n");
    hello.append(LUA_AUTHORS);
    hello.append("\n\n");

    L = luaL_newstate();
    luaL_openlibs(L);

    if (L == NULL)
        hello.append("\n\ncannot create state: not enough memory");

    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_pro_emakei_luado_MainActivity_evaluateExpression(
        JNIEnv* env,
        jobject, /* this */
        jstring exp) {

    std::string msg;

    if (L) {
        const char *s = env->GetStringUTFChars(exp, 0);

        topPrev = lua_gettop(L);

        bool error = true;

        if (s[0] == '=') {
            std::string s1{s}, s2;
            s2.append("return ");
            s2.append(s1.substr(1));
            error = luaL_dostring(L, s2.c_str());
        }
        else {
            msg.append(">");
            error = luaL_dostring(L, s);
        }

        topCurr = lua_gettop(L);

        msg.append(s);
        msg.append("\n");

        if (error) {
            msg.append(lua_tostring(L, -1));
            lua_pop(L, 1);  /* pop error message from the stack */
            --topCurr;
        } else {
            for (int i = topPrev-topCurr; i < 0; i++) {
                auto str = lua_tostring(L, i);
                auto isTable = lua_istable(L, i);
                auto isFunction = lua_isfunction(L, i);
                auto isBoolean = lua_isboolean(L, i);

                auto typeName = lua_typename(L, i);
                if (str)
                    msg.append(str);
                else if (isTable)
                    msg.append("table");
                else if (isFunction)
                    msg.append("function");
                else if (isBoolean) {
                    bool val = (bool) lua_toboolean(L, i);
                    msg.append(std::to_string(val));
                }
                else
                    msg.append(typeName);
                msg.append("\t");
            }
        }
    } else {
        msg.append("state isn't created");
    }

    return env->NewStringUTF(msg.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_pro_emakei_luado_MainActivity_freeMemory(
        JNIEnv* env,
jobject /* this */) {
    lua_close(L);
    L = NULL;
}
