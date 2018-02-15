#include "stdafx.h"

void dumpType(lua_State *L, int type, int idx)
{
	switch (type)
	{
	case LUA_TBOOLEAN:
	{
		cout << LUA_TBOOLEAN << '\t';
		cout << lua_toboolean(L, PARAM(idx)) << '\t';
		break;
	};
	case LUA_TFUNCTION:
	{
		//cout << endl << lua_type(L, PARAM(idx)) << endl;
		cout << LUA_TFUNCTION << '\t';
		cout << lua_topointer(L, PARAM(idx)) << '\t';
		break;
	};
	case LUA_TNIL:
	{
		cout << LUA_TNIL << '\t';
		cout << "nil" << '\t';
		break;
	};
	case LUA_TNUMBER:
	{
		cout << LUA_TNUMBER << '\t';
		double tmp;
		//modf(lua_tonumber(L, STACK_TOP), &tmp);
		if (modf(lua_tonumber(L, PARAM(idx)), &tmp) != 0)
		{
			//float-point number
			cout << lua_tonumber(L, PARAM(idx)) << '\t';
		}
		else
		{
			//int
			cout << lua_tointeger(L, PARAM(idx)) << '\t';
		};
		break;
	};
	case LUA_TSTRING:
	{
		cout << LUA_TSTRING << '\t';
		cout << lua_objlen(L, PARAM(idx)) << '\t';
		cout << lua_tostring(L, PARAM(idx)) << '\t';
		break;
	};
	case LUA_TTABLE:
	{
		//MessageBoxA(0, "", "", 0);
		int elementCnt = 0;
		elementCnt = luaL_getn(L, PARAM(idx));
		cout << LUA_TTABLE << '\t'; //write type identifier
		cout << elementCnt << '\t'; //write count of table elements
		for (int i = 1; i <= elementCnt; i++)
		{
			lua_rawgeti(L, PARAM(idx), i);
			if (lua_type(L, STACK_TOP) == LUA_TTABLE)
			{
				dumpType(L, LUA_TTABLE, STACK_TOP - 1);
			}
			else
			{
				dumpType(L, lua_type(L, STACK_TOP), STACK_TOP - 1);
			};
			STACK_POP;
		};
		break;
	};
	}
};