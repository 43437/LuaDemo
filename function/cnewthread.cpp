#include "cnewthread.h"

CNewThread::CNewThread() : CInvokeLuaBase("newthread.lua")
{
    Init();
}

CNewThread::~CNewThread()
{
    luaL_unref(m_pLuaStat, LUA_REGISTRYINDEX, m_iRefCo);
}

void CNewThread::IndependentStack()
{
    lua_getglobal(m_Co, "g_num");
    qDebug() << "Co Top " << lua_gettop(m_Co);
    NS_INVOKE_LUA_BASE::DumpStack(m_Co);
    lua_settop(m_Co, 0);

    qDebug() << "Stat Top " << lua_gettop(m_pLuaStat);
    NS_INVOKE_LUA_BASE::DumpStack(m_pLuaStat);
    lua_settop(m_pLuaStat, 0);
}

void CNewThread::ChangeGlobalVal()
{
    lua_pushinteger(m_Co, 999);
    lua_setglobal(m_Co, "g_num");
    lua_settop(m_Co, 0);

    lua_getglobal(m_pLuaStat, "g_num");
    qDebug() << "after ChangeGlobalVal g_num[" << lua_tointeger(m_pLuaStat, -1) << "]";
    lua_settop(m_pLuaStat, 0);
}

void CNewThread::ChangeLocalVal()
{
    lua_getglobal(m_Co, "set_l_num");
    lua_pushinteger(m_Co, 999);
    NoError(lua_pcall(m_Co, 1, 0, 0));
    lua_settop(m_Co, 0);

    lua_getglobal(m_pLuaStat, "get_l_num");
    if ( NoError(lua_pcall(m_pLuaStat, 0, 1, 0)) )
    {
        qDebug() << "after ChangeLocalVal l_num[" << lua_tointeger(m_pLuaStat, 1) << "]";
    }
    lua_settop(m_pLuaStat, 0);
}

void CNewThread::CallFunction()
{
//    lua_getglobal(m_pLuaStat, "loc_func");
//    NoError(lua_pcall(m_pLuaStat, 0, 0, 0));

    lua_getglobal(m_Co, "task2");
    if ( NoError(lua_pcall(m_Co, 0, 1, 0)) )
    {
        qDebug() << lua_tostring(m_Co, -1);
    }
    lua_settop(m_Co, 0);
}


void CNewThread::Execute()
{
//    IndependentStack();

//    ChangeGlobalVal();

//    CallFunction();

    ChangeLocalVal();
}

void CNewThread::Init()
{
    m_Co = lua_newthread(m_pLuaStat);
    //保存一个引用，避免被回收
    m_iRefCo =  luaL_ref(m_pLuaStat, LUA_REGISTRYINDEX);
}
