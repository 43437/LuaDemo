#include "LuaJsonLib.h"

bool CheckArrary(lua_State* L, int iIndex)
{
	lua_pushnil(L);
	while (lua_next(L, iIndex) != 0)
	{
		switch (lua_type(L, -2))
		{
		case LUA_TSTRING:
			lua_pop(L, 2);
			return false;
		case LUA_TNUMBER:
			break;
		default:
			luaL_argcheck(L, false, 1, (string("key not support to dump: ") + lua_typename(L, -2)).c_str());
			break;
		}
		lua_pop(L, 1);
	}
	return true;
}

void LuaTable2CJson(cJSON*& pJsonNode, int iIndex, lua_State* L)
{
	lua_pushnil(L);
	if (CheckArrary(L, iIndex))
	{
		pJsonNode = cJSON_CreateArray();
		while (lua_next(L, iIndex))
		{
			switch (lua_type(L, -1))
			{
			case LUA_TNIL:
				cJSON_AddItemToArray(pJsonNode, cJSON_CreateNull());
				break;
			case LUA_TBOOLEAN:
				cJSON_AddItemToArray(pJsonNode, cJSON_CreateBool(lua_toboolean(L, -1)));
				break;
			case LUA_TNUMBER:
                cJSON_AddItemToArray(pJsonNode, cJSON_CreateDouble(lua_tonumber(L, -1), -1));
				break;
			case LUA_TSTRING:
				cJSON_AddItemToArray(pJsonNode, cJSON_CreateString(lua_tostring(L, -1)));
				break;
            case LUA_TFUNCTION:
                cJSON_AddItemToArray(pJsonNode, cJSON_CreateString("function"));
                break;
			case LUA_TTABLE:
			{
				cJSON* pNewJsonNode = nullptr;
				LuaTable2CJson(pNewJsonNode, lua_gettop(L), L);
				cJSON_AddItemToArray(pJsonNode, pNewJsonNode);
			}
			break;
			default:
				luaL_argcheck(L, false, 1, (string("value not support to dump: [") + lua_tostring(L, -2) + "]" + lua_typename(L, -1)).c_str());
				break;
			}
			lua_pop(L, 1);
		}
	}
	else
	{
		pJsonNode = cJSON_CreateObject();
		while (lua_next(L, iIndex))
		{
			string strKey;
			if (lua_type(L, -2) == LUA_TSTRING)
				strKey = lua_tostring(L, -2);
			else
				strKey = to_string(lua_tointeger(L, -2));
			switch (lua_type(L, -1))
			{
			case LUA_TNIL:
				cJSON_AddItemToObject(pJsonNode, strKey.c_str(), cJSON_CreateNull());
				break;
			case LUA_TBOOLEAN:
				cJSON_AddItemToObject(pJsonNode, strKey.c_str(), cJSON_CreateBool(lua_toboolean(L, -1)));
				break;
			case LUA_TNUMBER:
                cJSON_AddItemToObject(pJsonNode, strKey.c_str(), cJSON_CreateDouble(lua_tonumber(L, -1), -1));
				break;
			case LUA_TSTRING:
				cJSON_AddItemToObject(pJsonNode, strKey.c_str(), cJSON_CreateString(lua_tostring(L, -1)));
				break;
            case LUA_TFUNCTION:
                cJSON_AddItemToObject(pJsonNode, strKey.c_str(), cJSON_CreateString("function"));
                break;
			case LUA_TTABLE:
			{
				cJSON* pNewJsonNode = nullptr;
				LuaTable2CJson(pNewJsonNode, lua_gettop(L), L);
				cJSON_AddItemToObject(pJsonNode, strKey.c_str(), pNewJsonNode);
			}
			break;
			default:
				luaL_argcheck(L, false, 1, (string("value not support to dump: [") + strKey.c_str() + "]" + lua_typename(L, -1)).c_str());
				break;
			}
			lua_pop(L, 1);
		}
	}
}

char* LuaVaule2JSONStr(lua_State* L, bool bIsFormat)
{
	cJSON* pJsonRoot = nullptr;
    int iTop = lua_gettop(L);
    switch (lua_type(L, iTop))
	{
	case LUA_TNIL:
		pJsonRoot = cJSON_CreateNull();
		break;
	case LUA_TBOOLEAN:
        pJsonRoot = cJSON_CreateBool(lua_toboolean(L, iTop));
		break;
	case LUA_TNUMBER:
        pJsonRoot = cJSON_CreateDouble(lua_tonumber(L, iTop), -1);
		break;
	case LUA_TSTRING:
        pJsonRoot = cJSON_CreateString(lua_tostring(L, iTop));
		break;
	case LUA_TTABLE:
        LuaTable2CJson(pJsonRoot, iTop, L);
		break;
	default:
        luaL_argcheck(L, false, iTop, string(lua_typename(L, iTop)).append(" not support to dump").c_str());
		break;
	}
    char* json = bIsFormat ? cJSON_Print(pJsonRoot) : cJSON_PrintUnformatted(pJsonRoot);
	cJSON_Delete(pJsonRoot);
    return json;
}

void CJson2LuaObj(cJSON* pJsonNode, lua_State* L)
{
	if (pJsonNode->string)
	{
		int iKey = atoi(pJsonNode->string);
		if (iKey)
			lua_pushinteger(L, iKey);
		else
			lua_pushstring(L, pJsonNode->string);
	}
	switch (pJsonNode->type)
	{
	case cJSON_False:
		lua_pushboolean(L, false);
		break;
	case cJSON_True:
		lua_pushboolean(L, true);
		break;
    case cJSON_Int:
    case cJSON_Double:
		lua_pushnumber(L, pJsonNode->valuedouble);
		break;
	case cJSON_String:
		lua_pushstring(L, pJsonNode->valuestring);
		break;
	case cJSON_Array:
	{
		lua_newtable(L);
		cJSON* pElement = pJsonNode->child;
		size_t iIndex = 1;
		while (pElement)
		{
			lua_pushnumber(L, iIndex++);
			CJson2LuaObj(pElement, L);
			pElement = pElement->next;
			lua_settable(L, -3);
		}
	}
	break;
	case cJSON_Object:
	{
		lua_newtable(L);
		cJSON* pElement = pJsonNode->child;
		while (pElement)
		{
			CJson2LuaObj(pElement, L);
			pElement = pElement->next;
		}
	}
	break;
	default:
		lua_pushnil(L);
		break;
	}
	if (pJsonNode->string) lua_settable(L, -3);
}

LIB_API api_Load(lua_State* L)
{
    const char* crep;
    cJSON* pJsonRoot = cJSON_Parse(luaL_checkstring(L, 1), &crep);
//	luaL_argcheck(L, pJsonRoot, 1, string("JSON parse error before: ").append(cJSON_GetErrorPtr()).c_str());
	CJson2LuaObj(pJsonRoot, L);
	cJSON_Delete(pJsonRoot);
	return 1;
}

LIB_API api_LoadFromFile(lua_State* L)
{
	ifstream fin(luaL_checkstring(L, 1));
	luaL_argcheck(L, fin.good(), 1, "no such JSON file");
	stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();
    const char* crep;
    cJSON* pJsonRoot = cJSON_Parse(ssContent.str().c_str(), &crep);
//	luaL_argcheck(L, pJsonRoot, 1, string("JSON parse error before: ").append(cJSON_GetErrorPtr()).c_str());
	CJson2LuaObj(pJsonRoot, L);
	ssContent.clear(); cJSON_Delete(pJsonRoot);
	return 1;
}

LIB_API api_Dump(lua_State* L)
{
    char* strJSON = LuaVaule2JSONStr(L, false);
	lua_pushstring(L, strJSON);
	free(strJSON);
	return 1;
}

LIB_API api_DumpToFile(lua_State* L)
{
	ofstream fout(luaL_checkstring(L, 2));
	luaL_argcheck(L, fout.good(), 1, "cannot open or create such JSON file");
	char* strJSON = LuaVaule2JSONStr(L, lua_toboolean(L, 3));
	fout << strJSON << endl;
	fout.close(); fout.clear();
	free(strJSON);
	return 0;
}

bool Table2Json(lua_State* L, QString& json)
{
    int iTop = lua_gettop(L);
    bool bRet = false;
    char* strJSON = LuaVaule2JSONStr(L, false);
    if (nullptr != strJSON)
    {
        json = QString("%1").arg(strJSON);
        free(strJSON);
        bRet = true;
    }
    lua_settop(L, iTop);
    return bRet;
}

static luaL_Reg cMethods[] = {
	{ "Load", api_Load },
	{ "LoadFromFile", api_LoadFromFile },
	{ "Dump", api_Dump },
	{ "DumpToFile", api_DumpToFile },
	{ nullptr, nullptr }
};
