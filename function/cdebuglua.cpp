#include "cdebuglua.h"

CDebugLua::CDebugLua() : CInvokeLuaBase("debuglua.lua")
{

}

void debugHook(lua_State *L, lua_Debug *ar)
{
    qDebug() << "hooked. ";
}

void CDebugLua::Execute()
{
    int iTop = lua_gettop(m_pLuaStat);
    int iMask = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE | LUA_MASKCOUNT;
    lua_sethook(m_pLuaStat, debugHook, iMask
                , 0/*only meaningful when the mask includes LUA_MASKCOUNT*/);
    lua_getglobal(m_pLuaStat, "main");
    if ( NoError(lua_pcall(m_pLuaStat, 0, 1, 0)) )
    {
        QString str = lua_tostring(m_pLuaStat, -1);
        qDebug() << str;
    }

    lua_settop(m_pLuaStat, iTop);

    ExecuteEnd();
}
