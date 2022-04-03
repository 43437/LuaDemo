#include "ccoroutine.h"
#include <QThread>
#include <QTimer>

namespace NS_COROUTINE{

lua_KContext k;

int command_result(lua_State *L, int status, lua_KContext ctx)
{
    int iIndex = lua_gettop(L);
    qDebug() << "command_result " << iIndex;
    return 2;
}

int command(lua_State* L)
{
    QString strOP = lua_tostring(L, -3);
    int x = lua_tointeger(L, -2);
    int y = lua_tointeger(L, 1);
    QList<int> listParam;
    listParam << x << y;
    lua_pop(L, 3);

    lua_getglobal(L, "ptrCo");
    CCoroutine *pCo = (CCoroutine*)lua_topointer(L, -1);
    pCo->SendCommand(listParam);
    lua_pop(L, 1);

    //yield返回的参数
    lua_pushinteger(L, 999);
    return lua_yieldk(L, 1, k, command_result);
}

luaL_Reg arrayFunc[] = {
    {"command", command},
    {nullptr, nullptr}
};

}

void CCoroutine::ExportFunction()
{
    int iIndex = lua_gettop(m_pLuaStat);

    lua_pushlightuserdata(m_pLuaStat, (void*)this);
    lua_setglobal(m_pLuaStat, "ptrCo");

    NS_INVOKE_LUA_BASE::RegistLib(m_pLuaStat, "co", NS_COROUTINE::arrayFunc);
    lua_settop(m_pLuaStat, iIndex);
}

CCoroutine::CCoroutine() : CInvokeLuaBase("coroutine.lua")
                         , m_Co(nullptr)
{
    ExportFunction();
    Init();
}

CCoroutine::~CCoroutine()
{
    luaL_unref(m_pLuaStat, LUA_REGISTRYINDEX, m_iRefCo);
}

void CCoroutine::Init()
{
    m_Co = lua_newthread(m_pLuaStat);
    m_iRefCo = luaL_ref(m_pLuaStat, LUA_REGISTRYINDEX);
}

void CCoroutine::onReceiveResult()
{
    int nRet = 0;
    lua_pushinteger(m_Co, 100);
    lua_pushinteger(m_Co, 101);
    int iStatus = lua_resume(m_Co, nullptr, 0, &nRet);
    qDebug() << "lua_resume ret: " << nRet << " status: " << iStatus;

    qDebug() << lua_tointeger(m_Co, -1);
    qDebug() << lua_tointeger(m_Co, -2);

    lua_pop(m_Co, nRet);

    qDebug() << "final end, stack top " << lua_gettop(m_Co);
    //执行结束
    ExecuteEnd();
}

void CCoroutine::SendCommand(QList<int>& lstCmd)
{
    qDebug() << "CCoroutine::SendCommand " << lstCmd;
    //模拟耗时
    QTimer::singleShot(20, this, SLOT(onReceiveResult()));
}

void CCoroutine::Execute()
{
    lua_getglobal(m_Co, "task");
    int nRet = 0;

    int iStatus = lua_resume(m_Co, nullptr, 0, &nRet);
    QList<QString> qstrRet;
    qstrRet << tr("lua_resume ret: %1 status: %2").arg(nRet).arg(iStatus);

    for (int i = 0; i < nRet; ++i)
    {
        qstrRet << lua_tostring(m_Co, -1);
        lua_pop(m_Co, 1);
    }
    qDebug() << qstrRet;

    qDebug() << "Execute end. " << lua_gettop(m_Co);
}
