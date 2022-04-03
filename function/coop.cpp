#include "coop.h"

COOP::COOP() : CInvokeLuaBase("oop.lua")
{

}

void COOP::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    if (NoError(lua_pcall(m_pLuaStat, 0, 1, 0)))
    {
        QString str = lua_tostring(m_pLuaStat, -1);
        qDebug().noquote() << str;
    }

    ExecuteEnd();
}
