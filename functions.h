//Список функций, используемых через Lua


int IsBetween(lua_State *L);
int RetFewValues(lua_State *L);
int IsIntOrDbl(lua_State *L);
int RegFunction(lua_State *L);
int TableReverse(lua_State *L);
int Serialize(lua_State *L);



//Формирование списка экспорта
static struct luaL_reg ls_lib[] = {
	{ "IsBetween", IsBetween },
	{ "RetFewValues", RetFewValues },
	{ "IsIntOrDbl", IsIntOrDbl },
	{ "RegFunction", RegFunction },
	{ "TableReverse", TableReverse },
	{ "Serialize", Serialize },
	{ NULL, NULL }
};