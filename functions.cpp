#include "stdafx.h"
//—торонние функции
#include "common.h"

//Use example
/*
	log(PlugEx.IsBetween(4, 1.25, 10))
*/
int IsBetween(lua_State *L)
{
	int paramCnt = PARAM_COUNT; //получаем кол-во параметров
	if (paramCnt < 3)
	{
		lua_pushboolean(L, false); //вернем false
		return 1; //вернем 1 значение
	};

	double f = lua_tonumber(L, PARAM(1)); //первый параметр - провер€емое число
	double b1 = lua_tonumber(L, PARAM(2)); //второй параметр - нижн€€ граница
	double b2 = lua_tonumber(L, PARAM(3)); //третий параметр - нижн€€ граница

	if ((f >= b1) && (f <= b2))
	{
		lua_pushboolean(L, true);
		return 1;
	};
	lua_pushboolean(L, false);
	return 1;
};

//Use example
/*
	a, b, c = PlugEx.RetFewValues()
	log(a)
	log(b)
	log(c)
*/
int RetFewValues(lua_State *L)
{
	//ничего не считаем, просто вернем значени€
	lua_pushboolean(L, true);
	lua_pushstring(L, "hello");
	lua_pushinteger(L, 12);
	return 3;
};

//Use example
/*
	log(PlugEx.IsIntOrDbl(5))
	log(PlugEx.IsIntOrDbl(5.343))
*/
int IsIntOrDbl(lua_State *L)
{
	//т.к в луа нет разделени€ на int и double, то приходитс€ изобретать велосипед
	//чтобы узнать, что нам передали.
	double tmp;
	//если первый параметр не число
	if (lua_type(L, PARAM(1)) != LUA_TNUMBER)
	{
		lua_pushstring(L, "Invalid data type.");
		return 1;
	};
	if (modf(lua_tonumber(L, PARAM(1)), &tmp) != 0)
	{
		lua_pushstring(L, "double");
		return 1;
	};
	lua_pushstring(L, "integer");
	return 1;
};

//Use example
/*
	PlugEx.RegFunction()
	PlugEx.Func1(7)
*/
int RegFunction(lua_State *L)
{
	//создадим функцю, дубликат предыдущей
	lua_pushcfunction(L, IsIntOrDbl);
	lua_setfield(L, -STACK_TOP, "Func1");
	return 0; //не возвращаем результат
};

//Use example
/*
	t = PlugEx.TableReverse({12, 342, "sda", print})
	for i = 1, table.getn(t), 1 do
		log(t[i])
	end
*/
int TableReverse(lua_State *L)
{
	//перевернем таблицу
	if (lua_type(L, PARAM(1)) != LUA_TTABLE)
	{
		lua_pushstring(L, "Require table argument.");
		return 1;
	};
	int tableSize = luaL_getn(L, PARAM(1));
	if (tableSize == 0)
	{
		lua_pushstring(L, "Table is empty.");
		return 1;
	};

	lua_createtable(L, 0, tableSize);
	for (int i = 1; i <= tableSize; i++)
	{
		//lua_pushinteger(L, i);
		lua_rawgeti(L, PARAM(1), (tableSize - i) + 1); //низкоуровнева€ функци€. работа с таблицей как с массивом.
		lua_rawseti(L, -STACK_TOP + 2, i);
	};
	return 1;
};

//Use example
/*
	t = PlugEx.Serialize("dump.txt", 2378, "sdasd", {nil, "test", {1, print, "oh"}, 342}, "end")
*/
int Serialize(lua_State *L)
{
	int paramCnt = PARAM_COUNT;
	if (paramCnt < 2)
	{
		lua_pushstring(L, "Function requires >= 2 arguments.");
		return 1;
	};
	if ((lua_type(L, PARAM(1)) != LUA_TSTRING) || (lua_strlen(L, PARAM(1)) == 0))
	{
		lua_pushstring(L, "First argument must be string and not equal NULL.");
		return 1;
	};
	//Link file with stdout for easy work with file
	FILE *file;
	errno_t error = freopen_s(&file, lua_tostring(L, PARAM(1)), "w", stdout);
	if (error != 0)
	{
		lua_pushstring(L, "Error while openning stdout.");
		return 1;
	};
	//parse arguments
	for (int i = 2; i <= paramCnt; i++)
	{
		dumpType(L, lua_type(L, PARAM(i)), i);
	};
	//get data size in bytes
	int size = cout.tellp();
	fclose(file);
	lua_pushinteger(L, size);
	return 1;
};