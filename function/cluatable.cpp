#include "cluatable.h"
#include "LuaJsonLib.h"

CLuaTable::CLuaTable() : CInvokeLuaBase("luatable.lua")
{

}

void CLuaTable::GetTableVal(const QString& qstrKey, QString& qstrVal)
{
    int iIndx = lua_gettop(m_pLuaStat);

    lua_getglobal(m_pLuaStat, "t_hello");
    lua_pushstring(m_pLuaStat, qstrKey.toStdString().c_str());
    //由于上一步压入了qstrKey, 所以此时"t_hello"在栈顶的下一个位置
    lua_gettable(m_pLuaStat, -2);
    qstrVal = lua_tostring(m_pLuaStat, -1);     //任何lua数据类型都可以转为string

    lua_settop(m_pLuaStat, iIndx);
}

void CLuaTable::SetTableVal(const QString& qstrKey, const QString& qstrVal)
{
    int iIndx = lua_gettop(m_pLuaStat);

    lua_getglobal(m_pLuaStat, "t_hello");
    lua_pushstring(m_pLuaStat, qstrKey.toStdString().c_str());
    lua_pushstring(m_pLuaStat, qstrVal.toStdString().c_str());

    //由于上一步压入了qstrKey, 所以此时"t_hello"在栈顶的-3的位置
    lua_settable(m_pLuaStat, -3);

    lua_settop(m_pLuaStat, iIndx);
}

void CLuaTable::PrintTable(const QString& qstrTable)
{
    int iIndx = lua_gettop(m_pLuaStat);
    lua_getglobal(m_pLuaStat, qstrTable.toStdString().c_str());
    QString tableJson;
    if ( Table2Json(m_pLuaStat, tableJson) )
    {
        qDebug() << tableJson;
    }
    else
    {
        qDebug() << "CLuaTable::PrintTable not support table.";
    }
    lua_settop(m_pLuaStat, iIndx);
}

void CLuaTable::Execute()
{
    QString strVal;
    GetTableVal("comment", strVal);
    qDebug() << "GetTableVal comment " << strVal;

    SetTableVal("comment", strVal + " change");

    GetTableVal("comment", strVal);
    qDebug() << "GetTableVal comment " << strVal;

    SetTableVal("new_key", "new value");

    PrintTable("t_hello");

    ExecuteEnd();
}
