/**
  功能：
  加载脚本
  错误信息打印
  遍历全局栈
  **/
#ifndef CINVOKELUABASE_H
#define CINVOKELUABASE_H

#include <QString>
#include <QDebug>
#include "LuaJsonLib.h"
#include <QObject>

namespace NS_INVOKE_LUA_BASE {
void RegistLib(lua_State* L, const char* lib_name, luaL_Reg arrayFunc[]);
void DumpStack(lua_State* L);
}

class CInvokeLuaBase : public QObject
{
    Q_OBJECT
public:
    CInvokeLuaBase(const QString& qstrScript, QObject* parant = nullptr);
    virtual ~CInvokeLuaBase();
    virtual void Reload();
    void SetScriptFile(QString& qstrScript);
    virtual void Execute() = 0;
    QString GetUUID() const;

protected:
    virtual void ExecuteEnd();
    bool NoError(int iRet);

signals:
    void sigExecuted(QString qstrUUID);

protected:
    lua_State*  m_pLuaStat;

private:
    void Init();

private:
    QString     m_qstrScript;
    QString     m_qstrUUID;
};

#endif // CINVOKELUABASE_H
