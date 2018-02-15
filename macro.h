//������� ��� ������ �� ������ Lua
#define STACK_BOTTOM 1 //��� �����(1 ��� dll �������, 0 ��� ����������  Lua).
#define STACK_TOP lua_gettop(L) //���� �����. L - ����������� ��� ������.
#define PARAM(index) (STACK_BOTTOM + index) //�������� �������� �� �������(�� 1).
#define STACK_POP lua_pop(L, 1) //������� 1 ������� �� �����.
#define STACK_POP_N(N) lua(L, N) //������� N ��������� �� �����.
#define PARAM_COUNT (lua_gettop(L) - STACK_BOTTOM) //������� � ������ �������. �������� ���-�� ����������.
//Debug
//��� �������. ���������� �������� ����� � ������ ������� (��� ����������).
//� ����� ������� �������� ������.
#define STACK_ASSERT(old) if (lua_gettop(L) > old) { \
						  lua_pushstring(L, "Stack corrupted !!!"); \
						  return 1;}