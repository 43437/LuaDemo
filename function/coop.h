/**
 * 演示：面向对象，继承
  **/
#ifndef COOP_H
#define COOP_H

#include "cinvokeluabase.h"

class COOP : public CInvokeLuaBase
{
public:
    COOP();
    void Execute() override;
};

#endif // COOP_H
