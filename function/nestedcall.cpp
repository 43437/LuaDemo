#include "nestedcall.h"

namespace NS_CALL_INFO {

int callback0(lua_State* L)
{
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);

    lua_getglobal(L, "c_objPtr");
    CNestedCall *p = (CNestedCall*)lua_topointer(L, -1);
    p->CallLuaFunc();

    int z = x + y;
    lua_pushinteger(L, z);
    return 1;
}

int callback1(lua_State* L)
{
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);

    lua_pushinteger(L, x+1);
    lua_pushinteger(L, y+1);
    return 2;
}

luaL_Reg arrayFunc[] = {
    {"callback0", callback0},
    {"callback1", callback1},
    {nullptr, nullptr}
};

}

CNestedCall::CNestedCall() : CInvokeLuaBase("callinfo.lua")
{
    ExportFunction();
    ExportThis();
}

void CNestedCall::ExportFunction()
{
    int iIndex = lua_gettop(m_pLuaStat);

    NS_INVOKE_LUA_BASE::RegistLib(m_pLuaStat, "callinfo", NS_CALL_INFO::arrayFunc);
    lua_settop(m_pLuaStat, iIndex);
}

void CNestedCall::CallLuaFunc()
{
    int iTop = lua_gettop(m_pLuaStat);
    lua_getglobal(m_pLuaStat, "func0");
    lua_pushinteger(m_pLuaStat, 2);
    lua_pushinteger(m_pLuaStat, 1);
    NoError(lua_pcall(m_pLuaStat, 2, 2, 0));
    lua_settop(m_pLuaStat, iTop);
}

void CNestedCall::ExportThis()
{
    int iTop = lua_gettop(m_pLuaStat);

    //保存自身对象的指针
    lua_pushlightuserdata(m_pLuaStat, (void*)this);
    lua_setglobal(m_pLuaStat, "c_objPtr");

    lua_settop(m_pLuaStat, iTop);
}

void CNestedCall::Execute()
{
    int iIndex = lua_gettop(m_pLuaStat);
    lua_getglobal(m_pLuaStat, "main");
    lua_pushinteger(m_pLuaStat, 2);
    lua_pushinteger(m_pLuaStat, 1);
    NoError(lua_pcall(m_pLuaStat, 2, 0, 0));

    lua_settop(m_pLuaStat, iIndex);

    ExecuteEnd();
}
