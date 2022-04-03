/**
 * 演示：执行二进制bin文件
  **/
#ifndef CEXECUTEBIN_H
#define CEXECUTEBIN_H

#include "cinvokeluabase.h"

class CExecuteBin : public CInvokeLuaBase
{
public:
    CExecuteBin();
    void Execute() override;
};

#endif // CEXECUTEBIN_H
