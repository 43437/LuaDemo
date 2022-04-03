#ifndef _LUAJSONLIB_H_

#include "cJSON.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
#include <fstream>
#include <sstream>
#include <QString>
using namespace std;

#define LIB_API extern "C" int

bool CheckArrary(lua_State* L, int iIndex);

void LuaTable2CJson(cJSON*& pJsonNode, int iIndex, lua_State* L);

void CJson2LuaObj(cJSON* pJsonNode, lua_State* L);

char* LuaVaule2JSONStr(lua_State* L, bool bIsFormat);

bool Table2Json(lua_State* L, QString& json);

LIB_API api_Load(lua_State* L);

LIB_API api_LoadFromFile(lua_State* L);

LIB_API api_Dump(lua_State* L);

LIB_API api_DumpToFile(lua_State* L);

#endif // !_LUAJSONLIB_H_
