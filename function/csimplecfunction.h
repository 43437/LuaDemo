/**
 * 演示：Lua中调用C函数
  **/
#ifndef CSIMPLECFUNCTION_H
#define CSIMPLECFUNCTION_H

#include "cinvokeluabase.h"

class CSimpleCFunction : public CInvokeLuaBase
{
public:
    CSimpleCFunction();
    void Execute();

private:
    void ExportFunction();
};

#endif // CSIMPLECFUNCTION_H
