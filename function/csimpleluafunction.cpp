#include "csimpleluafunction.h"

CSimpleLuaFunction::CSimpleLuaFunction() : CInvokeLuaBase("simpleluafuntion.lua")
{

}

void CSimpleLuaFunction::Execute()
{
    lua_getglobal(m_pLuaStat, "main");
    {
        lua_pushstring(m_pLuaStat, "hello");
        if (NoError(lua_pcall(m_pLuaStat, 1, 1, 0)))
        {
            if (lua_isstring(m_pLuaStat, -1))
            {
                QString strRet("");
                strRet += lua_tostring(m_pLuaStat, -1);
                qDebug() << "CSimpleLuaFunction::Execute return " << strRet;
            }
            else
            {
                qCritical() << "CSimpleLuaFunction::Execute return is not string.";
            }
        }
    }

    ExecuteEnd();
}
