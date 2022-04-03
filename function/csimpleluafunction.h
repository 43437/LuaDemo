/**
 * 演示：调用Lua函数
  **/
#ifndef CSIMPLELUAFUNCTION_H
#define CSIMPLELUAFUNCTION_H

#include "cinvokeluabase.h"

class CSimpleLuaFunction : public CInvokeLuaBase
{
public:
    CSimpleLuaFunction();

    virtual void Execute();
};

#endif // CSIMPLELUAFUNCTION_H
