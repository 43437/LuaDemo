#include "csimplecfunction.h"

namespace NS_SIMPLE_FUNC {

int add(lua_State* L)
{
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);

    int z = x + y;
    lua_pushinteger(L, z);
    return 1;
}

int sub(lua_State* L)
{
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);

    int z = x - y;
    lua_pushinteger(L, z);
    return 1;
}

luaL_Reg arrayFunc[] = {
    {"add", add},
    {"sub", sub},
    {nullptr, nullptr}
};
}

void CSimpleCFunction::ExportFunction()
{
    int iIndex = lua_gettop(m_pLuaStat);

    NS_INVOKE_LUA_BASE::RegistLib(m_pLuaStat, "simple_func", NS_SIMPLE_FUNC::arrayFunc);
    lua_settop(m_pLuaStat, iIndex);
}

CSimpleCFunction::CSimpleCFunction() : CInvokeLuaBase("simplecfuntion.lua")
{
    ExportFunction();
}


void CSimpleCFunction::Execute()
{
    int iIndex = lua_gettop(m_pLuaStat);

    lua_getglobal(m_pLuaStat, "main");
    lua_pushinteger(m_pLuaStat, 10);
    lua_pushinteger(m_pLuaStat, 20);
    lua_pushstring(m_pLuaStat, "add");
    if (NoError(lua_pcall(m_pLuaStat, 3, 2, 0)))
    {
        if (lua_isstring(m_pLuaStat, -1))
        {
            qDebug() << lua_tostring(m_pLuaStat, -1);
        }
        else
        {
            qCritical() << "CSimpleCFunction::Execute ret-1 not string.";
        }
        if (lua_isstring(m_pLuaStat, -2))
        {
            qDebug() << lua_tointeger(m_pLuaStat, -2);
        }
        else
        {
            qCritical() << "CSimpleCFunction::Execute ret-2 not integer.";
        }
    }

    lua_settop(m_pLuaStat, iIndex);

    ExecuteEnd();
}
