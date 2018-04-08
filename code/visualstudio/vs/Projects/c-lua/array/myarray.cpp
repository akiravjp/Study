#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <Error.h>
#include <lua.hpp>
extern "C" {
#include <lauxlib.h>
#include <lualib.h>
}

#pragma comment( lib, "D:\\Program Files (x86)\\Lua\\5.1\\lib\\lua5.1.lib")
//��ע���C�������ú�����������ʽ��������������Ѿ�������
//��Ҫ˵�����ǣ��ú���������C����ʽ�����������extern "C"�Ǳ���ġ�
//���������������ͬ�����ﲻ��׸����
extern "C" int add(lua_State* L) 
{
	double op1 = luaL_checknumber(L,1);
	double op2 = luaL_checknumber(L,2);
	lua_pushnumber(L,op1 + op2);
	return 1;
}

extern "C" int sub(lua_State* L)
{
	double op1 = luaL_checknumber(L,1);
	double op2 = luaL_checknumber(L,2);
	lua_pushnumber(L,op1 - op2);
	return 1;
}

extern "C" int l_map(lua_State* L)
{
	int i, n;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TFUNCTION);
	n = luaL_getn(L, 1);
	for (i=1; i <= n; i++)
	{
		lua_pushvalue(L,2);
		lua_rawgeti(L, 1, i);
		lua_call(L, 1, 1);
		lua_rawseti(L, 1, i);
	}
	return 0;
}

static int l_split(lua_State *L){
	const char *s = luaL_checkstring(L,1);
	const char *sep = luaL_checkstring(L, 2);
	const char *e;
	int i = 1;
	lua_newtable(L);
	while ((e = strchr(s, *sep)) != NULL)
	{
		lua_pushlstring(L, s, e-s);
		lua_rawseti(L, -2, i++);
		s = e + 1;
	}
	lua_pushstring(L, s);
	lua_rawseti(L, -2, i);
	lua_pushstring(L, s);

	return 1;

}

//27.3 �հ�
static int counter(lua_State *L);
int newCounter(lua_State *L){
	lua_pushnumber(L, 0);
	lua_pushcclosure(L, &counter, 1);
	return 1;
}
static int counter(lua_State *L){
	double val = lua_tonumber(L, lua_upvalueindex(1));
	lua_pushnumber(L, ++val);
	lua_pushvalue(L, -1);
	lua_replace(L, lua_upvalueindex(1));
	return 1;
}

//luaL_Reg�ṹ��ĵ�һ���ֶ�Ϊ�ַ�������ע��ʱ����֪ͨLua�ú��������֡�
//��һ���ֶ�ΪC����ָ�롣
//�ṹ�������е����һ��Ԫ�ص������ֶξ�ΪNULL��������ʾLuaע�ắ���Ѿ����������ĩβ��
/*
static luaL_Reg mylibs[] = { 
	{"add", add},
	{"sub", sub},
	{"map", l_map},
	{"split", l_split},
	{"newCounter", newCounter},
	{NULL, NULL} 
}; */

//��C���Ψһ��ں������亯��ǩ����ͬ�������ע�ắ���������¼���˵����
//1. ���ǿ��Խ��ú����򵥵����Ϊģ��Ĺ���������
//2. �亯��������Ϊluaopen_xxx������xxx��ʾlibrary���ơ�Lua����require "xxx"��Ҫ��֮��Ӧ��
//3. ��luaL_register�ĵ����У����һ���ַ�������Ϊģ����"xxx"���ڶ�������Ϊ��ע�ắ�������顣
//4. ��Ҫǿ�����ǣ�������Ҫ�õ�"xxx"�Ĵ��룬����C����Lua�������뱣��һ�£�����Lua��Լ����
//   �����޷����á�
/*
extern "C" __declspec(dllexport)
int luaopen_mystudylib(lua_State* L) 
{
	const char* libName = "mystudylib";
	luaL_register(L,libName,mylibs);
	return 1;
}*/

/*
extern "C" __declspec(dllexport)
int luaopen_mystudylib(lua_State *L)
{
	//luaL_openlib(L, "mystudylib", mylibs, 0);
	luaL_register(L,"mystudylib",mylibs);
	return 1;
}*/

//////////////////////////////////////////////////////////////////////////
//2014/03/18/ 28 character
typedef struct NumArray{
	int size;
	double values[1];
}NumArray;

/*
static int newarray(lua_State *L)
{
	int n = luaL_checkint(L, 1);
	size_t nbytes = sizeof(NumArray) + (n-1)*sizeof(double);
	NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
	a->size = n;
	return 1;
}

static int setarray(lua_State *L){
	NumArray *a = (NumArray *)lua_touserdata(L, 1);
	int index = luaL_checkint(L, 2);
	double nValue = luaL_checknumber(L, 3);

	luaL_argcheck(L, a != NULL, 1, "'array' expected");
	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

	a->values[index-1] = nValue;
	return 0;
}

static int getarray(lua_State *L){
	NumArray *a = (NumArray *)lua_touserdata(L, 1);
	int index = luaL_checkint(L, 2);

	luaL_argcheck(L, a!= NULL, 1, "'array' expected");
	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
	lua_pushnumber(L, a->values[index - 1]);
	return 1;
}

static int getsize(lua_State *L){
	NumArray *a = (NumArray*)lua_touserdata(L, 1);
	luaL_argcheck(L, a != NULL, 1, "'array' expected");
	lua_pushnumber(L, a->size);

	return 1;
}*/

// 28.2
/*
static int newarray(lua_State *L)
{
	int n = luaL_checkint(L, 1);
	size_t nbytes = sizeof(NumArray) + (n-1)*sizeof(double);
	NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

	luaL_getmetatable(L, "LuaBook.array");
	lua_setmetatable(L, -2);
	a->size = n;
	return 1;
}

static NumArray *checkarray(lua_State *L){
	void *ud = luaL_checkudata(L, 1, "luaBook.array");
	luaL_argcheck(L, ud != NULL, 1, "'array' expected");
	return (NumArray*)ud;
}

static double *getelem(lua_State *L){
	NumArray *a = checkarray(L);
	int index = luaL_checkint(L, 2);

	luaL_argcheck(L, 1<=index && index <= a->size, 2, "index out of ranget");

	return &a->values[index-1];
}
static int setarray(lua_State *L){
	double nValue = luaL_checknumber(L, 3);

	*getelem(L) = nValue;
	return 0;
}

static int getarray(lua_State *L){
	lua_pushnumber(L, *getelem(L));
	return 1;
}

static int getsize(lua_State *L){
	NumArray *a = checkarray(L);
	lua_pushnumber(L, a->size);

	return 1;
}

static const struct luaL_reg arraylib [] = {
	{"new", newarray},
	{"set", setarray},
	{"get", getarray},
	{"size", getsize},
	{NULL, NULL},
};

extern "C" __declspec(dllexport)
int luaopen_array(lua_State *L){
	luaL_newmetatable(L, "LuaBook.array");
	luaL_register(L,"array",arraylib);
	return 1;
}*/

//////////////////////////////////////////////////////////////////////////
//28.3
/*
static int newarray(lua_State *L)
{
	int n = luaL_checkint(L, 1);
	size_t nbytes = sizeof(NumArray) + (n-1)*sizeof(double);
	NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

	luaL_getmetatable(L, "LuaBook.array");
	lua_setmetatable(L, -2);
	a->size = n;
	return 1;
}

static NumArray *checkarray(lua_State *L){
	void *ud = luaL_checkudata(L, 1, "LuaBook.array");
	luaL_argcheck(L, ud != NULL, 1, "'array' expected");
	return (NumArray*)ud;
}

static double *getelem(lua_State *L){
	NumArray *a = checkarray(L);
	int index = luaL_checkint(L, 2);

	luaL_argcheck(L, 1<=index && index <= a->size, 2, "index out of ranget");

	return &a->values[index-1];
}
static int setarray(lua_State *L){
	double nValue = luaL_checknumber(L, 3);

	*getelem(L) = nValue;
	return 0;
}

static int getarray(lua_State *L){
	lua_pushnumber(L, *getelem(L));
	return 1;
}

static int getsize(lua_State *L){
	NumArray *a = checkarray(L);
	//NumArray *a = (NumArray *)luaL_checkudata(L, 1, "LuaBook.array"); //ͬ�����Ӳ������ͺ�metatable�ļ��
	lua_pushnumber(L, a->size);

	return 1;
}

int array2string(lua_State *L){
	NumArray *a = checkarray(L);
	lua_pushfstring(L, "array(%d)", a->size);
	return 1;
}

static const struct luaL_reg arraylib_f [] = {
	{"new", newarray},
	{NULL, NULL},
};

static const struct luaL_reg arraylib_m [] = {
	{"__tostring", array2string},
	{"set", setarray},
	{"get", getarray},
	{"size", getsize},
	{NULL, NULL},
};

extern "C" __declspec(dllexport)
int luaopen_array(lua_State *L){
	luaL_newmetatable(L, "LuaBook.array");

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);

	luaL_register(L,NULL,arraylib_m);
	luaL_register(L,"array",arraylib_f);

	return 1;
}*/

/////////////////////////////////////////////////////////
//29.1

static int dir_iter(lua_State *L);

static int l_dir (lua_State *L){
	const char *path = luaL_checkstring(L, 1);

	DIR **d = (DIR **)lua_newuserdata(L, sizeof(DIR *));

	/* set its metable */
	luaL_getmetatable(L, "LuaBook.dir");
	lua_setmetatable(L, -2);

	/* try to open the given directory */
	*d = opendir(path);
	if (*d == NULL)
	{
		luaL_error(L, "cannot open %s: %s", path, strerror(errno));
	}
	/* creates and returns the iterator function */
	lua_pushcclosure(L, dir_iter, 1);
}