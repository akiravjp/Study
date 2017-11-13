#include "Test.hpp"

#include <cstdint>
#include <iostream>
#include <windows.h>

//#include "lstate.h"

using namespace std;

Test g_objTest;

void myPrintLuaStack(lua_State *L);
void callLuaFuncDemo(lua_State* L);
int TestLuaStack();

USING_NAMESPACE_LUAREG

// eg: 1
template<class T> void f( T);				// (b) ����ģ��
template<class T> void f( int, T,double );	// (c) ����ģ������
template<class T> void f( T*);				// (d) ����ģ������
template<> void f<int>( int);				// (e) ����ģ��(b)�ػ�
void f( double);							// (f) ��ģ�庯��������


// eg: 2
template<class T>	 // (a2) һ������ģ��
void func( T );

template<class T>	 // (b2) ��һ������ģ�棬(a2)�����ذ汾
void func( T* );		 //     ������ģ��û��ƫ�ػ������������������

template<>			 // (c2) (b2)ģ���ȫ�ػ�
void func<>(int*);

// eg: 3
// (a3) ��֮ǰһ���Ļ���ģ��
template<class T> 
void f3( T )
{
	cout << "a3 function" << endl;
}
// (c3) ���(a3)����ȫ�ػ�
template<>       
void f3<>(int*)
{
	cout << "c3 function" << endl;
}
// (b3) ��һ������ģ�棬��(a3)������
template<class T> 
void f3( T* )
{
	cout << "b3 function" << endl;
}

void LuaCheckGC()
{
	lua_State* L = g_luaReg->GetLuaState();
	int nMemCount = lua_gc(L, LUA_GCCOUNT, 0);
	nMemCount >>= 4;	//�����������ǰ�������ڴ��С��16��֮1���ڴ�
	if (nMemCount < 2)
	{
		nMemCount = 2;
	}
	lua_gc(L, LUA_GCSTEP, nMemCount);
}

void LuaTest() {
	//REGISTER_LUA_CALSS(Base2);
	//REGISTER_LUA_CALSS(Base);
	//REGISTER_LUA_CALSS(Test);
	//REGISTER_LUA_CALSS(SubTest);
 // 
	//Test* test = new Test();
 // 
	//test->m_data = 1001;
	//test->m_data2 = 1002;
	//g_luaReg->RegisterObject("test", test);

	//Base* base = (Base*)test;
	//g_luaReg->RegisterObject("base", base);
 // 
	//// base2 constructor is private
	//Base2* base2 = Base2::GetInstance();
	//g_luaReg->RegisterObject("base2", base2);

	//lua_State* L = g_luaReg->GetLuaState();
  
	//struct lua_State* pL = (struct lua_State*)L;
	//cout << pL->stacksize << endl;

	// register c++ function to lua
	//int nSize = sizeof(GameScriptFuns)  / sizeof(GameScriptFuns[0]) - 1;
	//for (size_t i = 0; i < nSize; ++i)
	//{
	//	lua_pushcfunction(L, GameScriptFuns[i].func);
	//	lua_setglobal(L, GameScriptFuns[i].name);
	//}

	g_luaReg->DoScript("Test.lua");

	// make a loop
	//int nRetCode = true;
	//int nTick = 0;
	//while (true)
	//{
	//	if (!nRetCode)
	//	{
	//		nRetCode = true;
	//		Sleep(1000);
	//		continue;
	//	}
	//	// todo
	//	cout << "Tick: " << nTick << endl;
	//	LuaCheckGC();

	//	if (nTick %5 == 0)
	//	{
	//		g_luaReg->DoScript("Test1.lua");
	//	}

	//	++nTick;
	//	nRetCode = false;
	//}
}

int main() {
	LuaInit();
	LuaTest();
	//game
	int nCount = 0;
	while(true){
		int bEven = nCount %2 == 0;
		if(!bEven)
		{
			Sleep(1000);
			++nCount;
			continue;
		}
		++nCount;
		// do something
		printf("11111111111111111111\n");
	}
	// game end
	LuaClear();

	// test 1
	//bool b = true;
	//int i = 1;
	//double d = 1.1f;
	//f( b);        // ����(b)ģ�� ģ�����T = bool
	//f( i, 42, d ); // ����(c)ģ�� T = int
	//f( &i);       // ����(d)ģ�� T = int
	//f( i);        // ����(e)ģ��
	//f( d);        // ����(f)����

	//// test 2
	//int n = 2;
	//int *p = &n;
	//func( p);           // ����(c2)

	//// test3
	//f3(p);

	// lua stack test
	//TestLuaStack();

	cout<< "Input Enter key to exit." << endl;
	getchar();
	return 0;
}
 
// (b) ����ģ��
template<class T> void f( T)
{
	cout << "(b)" << endl;
}

// (c) ����ģ������
template<class T> void f( int, T,double )
{
	cout << "(c)" << endl;
}

// (d) ����ģ������
template<class T> void f( T*)
{
	cout << "(d)" << endl;
}

// (e) ����ģ��(b)�ػ�
template<> void f<int>( int)
{
	cout << "(e)" << endl;
}

// (f) ��ģ�庯��������
void f( double)
{
	cout << "(f)" << endl;
}

//////////////////////////////////////////////////////////////////////////
 // (a2) һ������ģ��
template<class T>	
void func( T )
{
	cout << "a2 func" << endl;
}

// (b2) ��һ������ģ�棬(a2)�����ذ汾������ģ��û��ƫ�ػ������������������
template<class T>
void func( T* )
{
	cout << "b2 func" << endl;
}

// (c2) (b2)ģ���ȫ�ػ�
template<>
void func<>(int*)
{
	cout << "c2 func" << endl;
}

//////////////////////////////////////////////////////////////////////////
// lua stack
int TestLuaStack(){
	lua_State* L=luaL_newstate();
	if(L){
		luaL_openlibs(L); 
		//����foo.lua 	    
		if(!luaL_dofile (L,"stack_test.lua"))
		{  
		lua_pushstring(L,"http://blog.163.com/mr_zyf");//Ϊ����ʾ��ѹ��һ���ַ���
         
			myPrintLuaStack(L);//����lua��foo����ǰ����ʾջ����Ϣ
			/**
			--ջ��(v)(1)--
			(i:1) string(http://blog.163.com/mr_zyf)
			--ջ��--
			**/
			callLuaFuncDemo(L);//����lua��foo����
         
			myPrintLuaStack(L); //����lua��foo��������ʾջ����Ϣ
		/**
			--ջ��(v)(1)--
			(i:1) string(http://blog.163.com/mr_zyf)
			--ջ��--
			**/       
		}else
	printf("error:%s\n",lua_tostring(L,-1));
        
		lua_close(L);      
	}else
		printf("error:new lua_State failed!");
	return 0;
}

//����lua��foo��������ʾ����
void callLuaFuncDemo(lua_State* L){
	int error;
    lua_getglobal(L,"foo");//ѹ�뺯����
    lua_pushnumber(L,1);//ѹ���һ����ֵ������1
    lua_pushnumber(L,2);//ѹ��ڶ�����ֵ������2
    myPrintLuaStack(L);//��ʾջ����Ϣ
    /**
    --ջ��(v)(4)--
    (i:4) number(2)
    (i:3) number(1)
    (i:2) function((null))
    (i:1) string(http://blog.163.com/mr_zyf)
	--ջ��--
	**/

    error=lua_pcall(L,2,2,0);//����foo�������������������������������
    if (!error) {
		//��ⷵ��ֵ�Ƿ�ѹջ
		if (!lua_isstring(L,-1))
			printf("error:must return a value!\n");
		else
		{
			myPrintLuaStack(L);
			/**
			--ջ��(v)(3)--
			(i:3) string(result val2)
			(i:2) string(result val1!)
			(i:1) string(http://blog.163.com/mr_zyf)
			--ջ��--
			���ú���ջ�еĺ��������ͺ��������Զ����������صĽ����ѹ��ջ��
			**/
			printf("return:%s\n",lua_tostring(L,-1));
			printf("return:%s\n",lua_tostring(L,-2));
			//ע�⣺�������lua_pop(L,-1)�������ջ
			//lua_pop(L,2);//��ջ������2��Ԫ��
			int nMemCount = lua_gc(L, LUA_GCCOUNT, 0);
			lua_gc(L, LUA_GCSTEP, nMemCount);
			printf("return:%s\n",lua_tostring(L,-1));
		}
    }else {     
		printf("error:%s.\n",lua_tostring(L,-1));
		//��ջ������1��Ԫ��
		lua_pop(L,1);
    }
}
//��ʾջ��Ϣ�ĺ���
void myPrintLuaStack(lua_State *L){
	int stackTop=lua_gettop(L);//��ȡջ��������ֵ
	int index,t;
	printf("--ջ��(v)(%d)--\n",stackTop);
	//��ʾջ�е�Ԫ��
	for(index=stackTop;index>0;--index)
		{  t=lua_type(L,index);
		printf("(i:%d) %s(%s)\n",index,lua_typename(L,t),lua_tostring(L,index));	     
		}
	printf("--ջ��--\n");
}