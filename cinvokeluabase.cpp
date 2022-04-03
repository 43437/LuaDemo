#include "cinvokeluabase.h"
#include <QCoreApplication>
#include <QUuid>
#include "LuaJsonLib.h"

namespace NS_INVOKE_LUA_BASE {

void DumpStack(lua_State* L)
{
    int argc = lua_gettop(L);
    qDebug() << "current stack size " << argc;

    for (int i = 1; i <= argc; i++) {

        int type = lua_type(L, i);
        const char* chType = lua_typename(L, type);
        qDebug() << "[" << i << "]" << chType << lua_tostring(L, i);
    }
}

LUALIB_API int CreateLib(lua_State *L) {

    luaL_Reg arrayFunc[] = {
        {nullptr, nullptr}
    };
    luaL_newlib(L, arrayFunc);
    return 1;
}

void RegistLib(lua_State* L, const char* lib_name, luaL_Reg arrayFunc[])
{
    int iTop = lua_gettop(L);
    lua_getglobal(L, lib_name);
    if ( LUA_TTABLE != lua_type(L, -1) )
    {
        //创建一个库
        luaL_requiref(L, lib_name, CreateLib, 1);
    }
    luaL_setfuncs(L, arrayFunc, 0);

    lua_settop(L, iTop);
}

void LuaAddPath(lua_State *ls, const char *name, const char *value) {
    string v;

    lua_getglobal(ls, "package");
    lua_getfield(ls, -1, name);
    v.append(lua_tostring(ls, -1));
    v.append(";");
    v.append(value);
    lua_pushstring(ls, v.c_str());
    lua_setfield(ls, -3, name);
    lua_pop(ls, 2);
}

int Log(lua_State* L)
{
    int iTop = lua_gettop(L);
    int iParam = iTop;
    QString str("");
    QString strTmp("");
    while (iParam > 0)
    {
        switch (lua_type(L, -1))
        {
        case LUA_TTABLE:
            Table2Json(L, strTmp);
            break;
        case LUA_TBOOLEAN:
            {
                if (lua_toboolean(L, -1))
                {
                    strTmp = "true";
                }
                else
                {
                    strTmp = "false";
                }
            }
            break;
        case LUA_TNIL:
            strTmp = "nil";
            break;
        default:
            strTmp=QString("%1").arg(lua_tostring(L, -1));
            break;
        }
        --iParam;
        lua_pop(L, 1);
        str.insert(0, strTmp.append(" "));
    }
    qDebug() << str;
    return 0;
}

luaL_Reg arrayFunc[] = {
    {"log", Log},
    {nullptr, nullptr}
};

}

CInvokeLuaBase::CInvokeLuaBase(const QString& qstrScript, QObject* parant)
    : QObject(parant)
    , m_pLuaStat(nullptr)
{
    m_qstrScript = QCoreApplication::applicationDirPath() + "/script/" + qstrScript;
    Init();
}

CInvokeLuaBase::~CInvokeLuaBase()
{
    if (nullptr != m_pLuaStat)
    {
        lua_close(m_pLuaStat);
        m_pLuaStat = nullptr;
    }
}

void CInvokeLuaBase::Reload()
{
    if (nullptr != m_pLuaStat)
    {
        QString path = QCoreApplication::applicationDirPath() + "\\?.lua";
        string strpath = path.toStdString();
        NS_INVOKE_LUA_BASE::LuaAddPath(m_pLuaStat, "path", strpath.c_str());
        NoError(luaL_dofile(m_pLuaStat, m_qstrScript.toStdString().c_str()));
        NS_INVOKE_LUA_BASE::RegistLib(m_pLuaStat, "gy", NS_INVOKE_LUA_BASE::arrayFunc);
    }
    else
    {
        qCritical() << "CInvokeLuaBase::Reload but m_pLuaStat null. ";
    }
}

QString CInvokeLuaBase::GetUUID() const
{
    return m_qstrUUID;
}

void CInvokeLuaBase::Init()
{
    QUuid id = QUuid::createUuid();
    m_qstrUUID = id.toString();

    if (nullptr == m_pLuaStat)
    {
        m_pLuaStat = luaL_newstate();
    }
    luaL_openlibs(m_pLuaStat);

    Reload();
}

void CInvokeLuaBase::SetScriptFile(QString &qstrScript)
{
    m_qstrScript = qstrScript;
}

void CInvokeLuaBase::ExecuteEnd()
{
    emit sigExecuted(GetUUID());
}

bool CInvokeLuaBase::NoError(int iRet)
{
    bool bRet = true;
    if (0 != iRet)
    {
        bRet = false;
        QString qstrError;
        if (nullptr != m_pLuaStat)
        {
            if (lua_isstring(m_pLuaStat, -1))
            {
                const char* pErrorMsg = lua_tostring(m_pLuaStat, -1);
                qstrError.append(pErrorMsg);
                lua_pop(m_pLuaStat, 1);
            }
            else
            {
                qstrError.append("unknow error.");
            }
        }
        else
        {
            qstrError.append("m_pLuaStat is null. ");
        }
        qDebug() << qstrError;
    }
    return bRet;
}
