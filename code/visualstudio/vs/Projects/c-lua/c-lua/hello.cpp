/*
 * hello.cpp
 * 
 * 
 * Author:
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <functional>


using namespace std;

//#include "lua.hpp"
#ifdef _USE_LUA_JIT
#include "..\\include\\luajit\\lua.hpp"

//#pragma comment( lib, "..\\lib\\luajit\\luajit.lib")
//#pragma comment( lib, "..\\lib\\luajit\\lua51.lib")
//#pragma comment( lib, "F:\\study\\lua\\LuaJIT-2.0.5\\src\\luajit.lib")
#else
#include "..\\include\\lua515\\lua.hpp"

//#ifdef _DEBUG
//#pragma comment( lib, "..\\lib\\lua515\\Lua515D.lib")
//#else
//#pragma comment( lib, "..\\lib\\lua515\\Lua515.lib")
//#endif //_DEBUG

#endif // _USE_LUA_JIT

struct info{
	string name;
	int age;
};

typedef struct info info;
 
//---------------------------------------------------------------------------
// ����:	KLuaScript::CallFunction
// ����:	����Lua�ű��ڵĺ���
// ����:	char* cFuncName
// ����:	int nResults
// ����:	char* cFormat  ����ʱ�������������� 
//			n:������(double) d:����(int) s:�ַ����� f:C������  n:Nil v:Value p:Point
//        v��ΪLua֧�ֵģ�����Ϊ���ε���index��ָ����index��ָ��ջ�ı�����Ϊ
//			 �ú����ĵ��ò�����
//	ע�⣺���ڸú����в���������,�������֣�ϵͳ����ȷ��������double������int
//  ���ڣ����ֱ�����ʽ�ǲ�ͬ�ġ������Ҫע�⵱�������������ʱ����ʽ��Ӧ��d
//  ��������n,����ǿ�иı�Ϊdouble�Ρ��������ּ���Ĵ���
//   
// ����:	...
// ����:	bool 
//---------------------------------------------------------------------------
bool CallFunction(lua_State* L, const char* cFuncName, int nResults, const char* cFormat, va_list vlist)
{
	double nNumber;
	char* cString = NULL;
	void* pPoint = NULL;
	//Lua_CFunction CFunc;
	int i = 0;
	int nArgnum = 0;
	int nIndex = 0;
	int nRetcode;		//���ýű�������ķ�����
	int ErrFunc = 0;

	lua_getglobal(L, cFuncName); //�ڶ�ջ�м�����Ҫ���õĺ�����

	while (cFormat[i] != '\0')
	{
		switch (cFormat[i])
		{
			case 'f'://�����������double�� NUMBER��Lua��˵��Double��
			{
				//nNumber = va_arg(vlist, double);
				int64_t nNumber1 = va_arg(vlist, int64_t);
				lua_pushnumber(L, nNumber1);
				nArgnum++;

			}
			break;

			case 'd'://���������Ϊ����
			{
				nNumber = (double)(va_arg(vlist, int));
				lua_pushnumber(L, (double)nNumber);
				nArgnum++;
			}
			break;
		}

		i++;
	}


	nRetcode = lua_pcall(L, nArgnum, nResults, ErrFunc);

	if (nRetcode != 0)
	{
		return false;
	}


	return	true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::CallFunction
//---------------------------------------------------------------------------
bool CallFunction(lua_State* L, const char* cFuncName, int nResults, const char* cFormat, ...)
{
	bool bResult = false;
	//strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
	//strncpy(g_szRunningFunction, cFuncName, sizeof(g_szRunningFunction));
	va_list vlist;
	va_start(vlist, cFormat);
	// MikeDai[2004-12-14]
	// Potential function Invoking confusion between the following two functions:
	// bool KLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
	// bool KLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
	bResult = CallFunction(L, (char*)cFuncName, nResults, cFormat, vlist);
	va_end(vlist);
	return bResult;
}


int main(int argc, char **argv){
	int status;
	string RootPath, NewFilePath, OldFilePath, ResultFileName;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	//lua_State *L = lua_open();

	// lua math.floor(19.9 * 100) = 1989
	int a = floor(19.9 * 100);

	/* Load the file containing the script we are going to run */
	status = luaL_loadfile(L, "script/main.lua");
	//status = luaL_loadfile(L, "script/coroutine_xpcall.lua");
	if (status) {
		/* If something went wrong, error message is at the top of */
		/* the stack */
		fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
		exit(1);
	}
	status = lua_pcall(L, 0, 0, 0);

	CallFunction(L, "OnSelectFromUI", 3, "fdd", 1, 2, 4);
	//info employee;
	//status = luaL_dofile(L, "./test.lua");
	//if (status) {
	//	/* If something went wrong, error message is at the top of */
	//	/* the stack */
	//	fprintf(stderr, "Couldn't do file: %s\n", lua_tostring(L, -1));
	//	exit(1);
	//}

//	lua_getglobal(L, "name");
//	lua_getglobal(L, "age");

//	employee.name = lua_tostring(L, -2);
//	employee.age = lua_tonumber(L, -1);

//	std::cout << employee.name << endl;
//	std::cout << employee.age << endl;

	//luaL_dofile(L, "main.lua");
	//lua_getglobal(L, "RootPath");
	//lua_getglobal(L, "NewFilePath");
	//lua_getglobal(L, "OldFilePath");
	//lua_getglobal(L, "ResultFileName");

	//RootPath = lua_tostring(L, -4);
	//NewFilePath = lua_tostring(L, -3);
	//OldFilePath = lua_tostring(L, -2);
	//ResultFileName = lua_tostring(L, -1);

	//cout << RootPath << endl;
	//cout << NewFilePath << endl;
	//cout << OldFilePath << endl;
	//cout << ResultFileName << endl;

	std::function<int(int)> Fibonacci= [&Fibonacci](int n)
	{
		if (n < 2)
			return n;
		return n * Fibonacci(n - 1);
	};
	std::cout << Fibonacci(5) << std::endl;

	getchar();
	return 0;
}

//static int l_sin(lua_State *L){
//	double d = lua_tonumber(L, 1);
//	lua_pushnumber(L, sin(d));
//	return 1;
//}

//����ȡ��
//double my_floor(double x)
//{
//	register double ret;
//	unsigned short int temp1, temp2;
//
//	__asm__("fnstcw %0" : "=m" (temp1));
//	temp2 = (temp1 & 0xf3ff) | 0x0400; /* rounding down */
//	__asm__("fldcw %0" : : "m" (temp2));
//	__asm__("frndint" : "=t" (ret) : "0" (x));
//	__asm__("fldcw %0" : : "m" (temp1));
//
//	return ret;
//}