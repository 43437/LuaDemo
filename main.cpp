#include <QCoreApplication>
#include "cinvokeluafuncexecutor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CInvokeLuaFuncExecutor::instance().Execute(eFuncNo_SimpleLuaFunction);

    return a.exec();
}
