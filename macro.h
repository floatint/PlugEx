//Макросы для работы со стеком Lua
#define STACK_BOTTOM 1 //дно стека(1 для dll плагина, 0 для автономной  Lua).
#define STACK_TOP lua_gettop(L) //верх стека. L - стандартное имя машины.
#define PARAM(index) (STACK_BOTTOM + index) //получить параметр по индексу(от 1).
#define STACK_POP lua_pop(L, 1) //удалить 1 элемент из стека.
#define STACK_POP_N(N) lua(L, N) //удалить N элементов из стека.
#define PARAM_COUNT (lua_gettop(L) - STACK_BOTTOM) //вызвать в начале функции. Получить кол-во параметров.
//Debug
//Для отладки. Запоминаем значение стека в начале функции (без параметров).
//в конце функции вызываем макрос.
#define STACK_ASSERT(old) if (lua_gettop(L) > old) { \
						  lua_pushstring(L, "Stack corrupted !!!"); \
						  return 1;}