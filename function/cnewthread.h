/**
  演示：lua_newthread使用
  **/
#ifndef CNEWTHREAD_H
#define CNEWTHREAD_H

#include "cinvokeluabase.h"

class CNewThread : public CInvokeLuaBase
{
public:
    CNewThread();
    void Execute() override;
    ~CNewThread();

private:
    void Init();
    void ChangeGlobalVal();
    void IndependentStack();
    void CallFunction();
    void ChangeLocalVal();

private:
    lua_State*  m_Co;
    int         m_iRefCo;
};

#endif // CNEWTHREAD_H
