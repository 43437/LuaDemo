/**
 * 演示：Lua脚本中使用module
  **/
#ifndef CREQUIREMODULE_H
#define CREQUIREMODULE_H

#include "cinvokeluabase.h"

class CRequireModule : public CInvokeLuaBase
{
public:
    CRequireModule();
    void Execute() override;
};

#endif // CREQUIREMODULE_H
