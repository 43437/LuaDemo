#include "crequiremodule.h"

CRequireModule::CRequireModule() : CInvokeLuaBase("requiremodule.lua")
{

}

void CRequireModule::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    if (NoError(lua_pcall(m_pLuaStat, 0, 1, 0)) )
    {
        QString str = lua_tostring(m_pLuaStat, -1);
        qDebug() << str;
    }

    ExecuteEnd();
}
