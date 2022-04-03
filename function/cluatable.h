/**
 * 演示：Lua Table操作
  **/
#ifndef CLUATABLE_H
#define CLUATABLE_H

#include <cinvokeluabase.h>

class CLuaTable : public CInvokeLuaBase
{
public:
    CLuaTable();
    void Execute() override;

private:
    void SetTableVal(const QString& qstrKey, const QString& qstrVal);
    void GetTableVal(const QString& qstrKey, QString& qstrVal);
    void PrintTable(const QString& qstrTable);
};

#endif // CLUATABLE_H
