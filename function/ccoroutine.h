/**
 * 演示：协程使用
  **/
#ifndef CCOROUTINE_H
#define CCOROUTINE_H

#include "cinvokeluabase.h"
#include "QList"

class CCoroutine : public CInvokeLuaBase
{
    Q_OBJECT
public:
    CCoroutine();
    ~CCoroutine();
    void Execute() override;
    void SendCommand(QList<int>& lstCmd);

private:
    void Init();
    void ExportFunction();

private:
    lua_State* m_Co;
    int m_iRefCo;

public slots:
    void onReceiveResult();
};

#endif // CCOROUTINE_H
