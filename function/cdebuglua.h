/**
 * 演示：使用Lua Hook监控及调试Lua脚本执行
  **/
#ifndef CDEBUGLUA_H
#define CDEBUGLUA_H

#include "cinvokeluabase.h"

class CDebugLua : public CInvokeLuaBase
{
public:
    CDebugLua();
    void Execute() override;
};

#endif // CDEBUGLUA_H
