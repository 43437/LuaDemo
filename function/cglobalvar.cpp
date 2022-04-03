#include "cglobalvar.h"

CGlobalVar::CGlobalVar() : CInvokeLuaBase("globalvar.lua")
{
    SetGlobalVal();
}

void CGlobalVar::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    if (NoError(lua_pcall(m_pLuaStat, 0, 1, 0)))
    {
        if (lua_isstring(m_pLuaStat, -1))
        {
            qDebug() << "CGlobalVar::Execute ret-1 " << lua_tostring(m_pLuaStat, -1);
        }
        else
        {
            qCritical() << "CGlobalVar::Execute ret-1 not string.";
        }
    }

    ExecuteEnd();
}

void CGlobalVar::SetGlobalVal()
{
    lua_pushstring(m_pLuaStat, "i am string param");
    lua_setglobal(m_pLuaStat, "g_strParam");
    lua_pushinteger(m_pLuaStat, 20);
    lua_setglobal(m_pLuaStat, "g_iParam");
}
