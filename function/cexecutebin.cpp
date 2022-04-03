#include "cexecutebin.h"

CExecuteBin::CExecuteBin() : CInvokeLuaBase("executebin.bin")
{

}

void CExecuteBin::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    if (NoError(lua_pcall(m_pLuaStat, 0, 1, 0)))
    {
        QString strRet = lua_tostring(m_pLuaStat, -1);
        qDebug() << strRet;
    }
    lua_pop(m_pLuaStat, 1);

    ExecuteEnd();
}
