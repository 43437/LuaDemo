/**
 * 演示：复杂的调用，函数嵌套调用 c->lua->c->lua
  **/
#ifndef CCALLINFO_H
#define CCALLINFO_H

#include "cinvokeluabase.h"

class CNestedCall : public CInvokeLuaBase
{
public:
    CNestedCall();
    void Execute() override;
    void CallLuaFunc();

private:
    void ExportThis();
    void ExportFunction();
};

#endif // CCALLINFO_H
