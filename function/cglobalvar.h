/**
 * 演示：设置Lua的全局变量
  **/
#ifndef CGLOBALVAR_H
#define CGLOBALVAR_H

#include "cinvokeluabase.h"

class CGlobalVar : public CInvokeLuaBase
{
public:
    CGlobalVar();
    void Execute();

private:
    void SetGlobalVal();
};

#endif // CGLOBALVAR_H
