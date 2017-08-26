#include "Test.hpp"

#include <cstdint>
#include <iostream>

using namespace std;

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

void LuaTest() {
  REGISTER_LUA_CALSS(Test);
  
  Test* test = new Test();
  
  test->m_data = 1001;
  test->m_data2 = 1002;
  g_luaReg->RegisterObject("test", test);
  g_luaReg->DoScript("Test.lua");
}

int main() {
  LuaInit();
  LuaTest();
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