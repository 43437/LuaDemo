#include "cinvokeluafuncexecutor.h"
#include "function/csimpleluafunction.h"
#include "function/csimplecfunction.h"
#include "function/cglobalvar.h"
#include "function/cobjptr.h"
#include "function/cluatable.h"
#include "function/nestedcall.h"
#include "function/cdebuglua.h"
#include "function/cexecutebin.h"
#include "function/crequiremodule.h"
#include "function/coop.h"
#include "function/ccoroutine.h"
#include "function/cnewthread.h"

static CInvokeLuaBase* Creator(const EFuncNo eFunNo);

CInvokeLuaFuncExecutor& CInvokeLuaFuncExecutor::instance()
{
    static CInvokeLuaFuncExecutor instance;
    return instance;
}

CInvokeLuaFuncExecutor::CInvokeLuaFuncExecutor()
{

}

CInvokeLuaFuncExecutor::~CInvokeLuaFuncExecutor()
{
    for (auto itFunc = m_mapFunc.begin(); m_mapFunc.end() != itFunc; ++itFunc)
    {
        CInvokeLuaBase* pFunc = itFunc.value();
        if (nullptr != pFunc)
        {
            delete pFunc;
            pFunc = nullptr;
        }
    }
    m_mapFunc.clear();
}

void CInvokeLuaFuncExecutor::Execute(const EFuncNo eFunNo)
{
    CInvokeLuaBase *pFunc = Creator(eFunNo);
    if (nullptr != pFunc)
    {
        QString qstrUUID = pFunc->GetUUID();
        if ( m_mapFunc.end() != m_mapFunc.find(qstrUUID) )
        {
            if ( nullptr != m_mapFunc[qstrUUID] )
            {
                delete m_mapFunc[qstrUUID];
                m_mapFunc[qstrUUID] = nullptr;
                qCritical() << "m_mapFunc[" << qstrUUID << "] already exsit.";
            }
        }

        m_mapFunc[qstrUUID] = pFunc;
        connect(pFunc, SIGNAL(sigExecuted(QString)), this, SLOT(OnExecuted(QString)));

        pFunc->Execute();
    }
    else
    {
        qDebug() << "CInvokeLuaFuncExecutor::Execute pFunc is null. ";
    }
}

void CInvokeLuaFuncExecutor::OnExecuted(QString qstrUUID)
{
    auto pos = m_mapFunc.find(qstrUUID);
    if ( m_mapFunc.end() != pos )
    {
        CInvokeLuaBase* pFunc = pos.value();
        if (nullptr != pFunc)
        {
            delete pFunc;
        }
        m_mapFunc.erase(pos);
    }
    else
    {
        qCritical() << "CInvokeLuaFuncExecutor::OnExecuted " << qstrUUID << "not found. ";
    }
}

static CInvokeLuaBase* Creator(const EFuncNo eFunNo)
{
    CInvokeLuaBase* pFunc = nullptr;
    switch (eFunNo)
    {
    case eFuncNo_SimpleLuaFunction:
        pFunc = new CSimpleLuaFunction();
        break;
    case eFuncNo_SimpleCFuncion:
        pFunc = new CSimpleCFunction();
        break;
    case eFuncNo_OBJ_Ptr:
        pFunc = new CObjPtr();
        break;
    case eFuncNo_Global_Val:
        pFunc = new CGlobalVar();
        break;
    case eFuncNo_Table:
        pFunc = new CLuaTable();
        break;
    case eFuncNo_NestedCall:
        pFunc = new CNestedCall();
        break;
    case eFuncNo_Debug:
        pFunc = new CDebugLua();
        break;
    case eFuncNo_ExecuteBin:
        pFunc = new CExecuteBin();
        break;
    case eFuncNo_RequireModule:
        pFunc = new CRequireModule();
        break;
    case eFuncNo_OOP:
        pFunc = new COOP();
        break;
    case eFuncNo_Coroutine:
        pFunc = new CCoroutine();
        break;
    case eFuncNo_NewThread:
        pFunc = new CNewThread();
        break;
    default:
        break;
    }
    return pFunc;
}
