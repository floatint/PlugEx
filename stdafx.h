// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

//Стандартные библиотеки
#include "targetver.h"
#include <Windows.h>
#include <vector>
#include <iostream>

using namespace std;


//LUA API
//Описание работы стека и функций Lua смотреть на
//http://pgl.yoyo.org/luai/i/lua_toboolean
//(искать описание по имени функций)
extern "C" {
#include "lualib\lauxlib.h"
#include "lualib\lua.h"
}

//Заголовки исходников плагина
#include "macro.h" //макросы для работы с Lua
#include "functions.h" //функции плагина
