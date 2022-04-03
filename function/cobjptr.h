/**
 * 演示：Lua保存c++指针
  **/
#ifndef CPTR_H
#define CPTR_H

#include "cinvokeluabase.h"

class CObjPtr : public CInvokeLuaBase
{
public:
    CObjPtr();
    void Execute() override;
    void OnCallBack(int iVal);

private:
    void Export();
};

#endif // CPTR_H
