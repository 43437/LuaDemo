#ifndef CINVOKELUAFUNCFATORY_H
#define CINVOKELUAFUNCFATORY_H

#include <QObject>
#include "cinvokeluabase.h"

enum EFuncNo
{
    eFuncNo_UnKnow = -1,
    eFuncNo_SimpleLuaFunction,
    eFuncNo_SimpleCFuncion,
    eFuncNo_OBJ_Ptr,
    eFuncNo_Global_Val,
    eFuncNo_Table,
    eFuncNo_NestedCall,
    eFuncNo_Debug,
    eFuncNo_ExecuteBin,
    eFuncNo_RequireModule,
    eFuncNo_OOP,
    eFuncNo_Coroutine,
    eFuncNo_NewThread,
};

class CInvokeLuaFuncExecutor : public QObject
{
    Q_OBJECT
public:
    static CInvokeLuaFuncExecutor& instance();
    void Execute(const EFuncNo eFunNo);

private:
    CInvokeLuaFuncExecutor();
    ~CInvokeLuaFuncExecutor();

public slots:
    void OnExecuted(QString qstrUUID);

private:
    QMap<QString, CInvokeLuaBase*>   m_mapFunc;
};

#endif // CINVOKELUAFUNCFATORY_H
