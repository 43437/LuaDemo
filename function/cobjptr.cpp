#include "cobjptr.h"

namespace NS_OBJ_PTR {

int CallBack(lua_State* L)
{
    if ( lua_isnumber(L, -1) )
    {
        int iVal = lua_tointeger(L, -1);
        lua_getglobal(L, "c_objPtr");
        CObjPtr *p = (CObjPtr*)lua_topointer(L, -1);
        p->OnCallBack(iVal);
    }
    else
    {
        qCritical() << "NS_OBJ_PTR::CallBack-1 NAN.";
    }

    return 0;
}

luaL_Reg arrayFunc[] = {
    {"callback", CallBack},
    {nullptr, nullptr}
};

}

CObjPtr::CObjPtr() : CInvokeLuaBase("objptr.lua")
{
    Export();
}

void CObjPtr::Export()
{
    int iTop = lua_gettop(m_pLuaStat);
    //保存自身对象的指针
    lua_pushlightuserdata(m_pLuaStat, (void*)this);
    lua_setglobal(m_pLuaStat, "c_objPtr");

    NS_INVOKE_LUA_BASE::RegistLib(m_pLuaStat, "c_obj", NS_OBJ_PTR::arrayFunc);
    lua_settop(m_pLuaStat, iTop);
}

void CObjPtr::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    lua_pushinteger(m_pLuaStat, 10);
    lua_pushinteger(m_pLuaStat, 20);
    NoError(lua_pcall(m_pLuaStat, 2, 0, 0));

    ExecuteEnd();
}

void CObjPtr::OnCallBack(int iVal)
{
    qDebug() << "CObjPtr::OnCallBack iVal[" << iVal << "]";
}
