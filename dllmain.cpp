// dllmain.cpp: определяет точку входа для приложения DLL.



#include "stdafx.h"


//Эту функцию lua будет искать при подключении dll, её название заканчиваться названием dll, luaopen_ИМЯВАШЕЙDLL
extern "C" LUALIB_API int luaopen_PlugEx(lua_State *L) {
	//Регистрация функций
	luaL_openlib(L, "PlugEx", ls_lib, 0);
	//Тут по желанию можно зарегистрировать глобальные переменные.
	
	//Просто переменная
	lua_pushinteger(L, 10000); //Значение переменной по умолчанию
	lua_setfield(L, -STACK_TOP + 1, "SomeVar"); //Регаем

	//Регистрация глобальной переменной-таблицы Vars с 3 переменными внутри
	lua_createtable(L, 0, 3);
	lua_pushinteger(L, 0);
	lua_setfield(L, -STACK_TOP + 2, "Var1");
	lua_pushinteger(L, 0);
	lua_setfield(L, -STACK_TOP + 2, "Var2");
	lua_pushinteger(L, 0);
	lua_setfield(L, -STACK_TOP + 2, "Var3");
	lua_setfield(L, -STACK_TOP + 1, "Vars");
	
	//Разумеется, вложенность не ограничена.
	return 0;
}