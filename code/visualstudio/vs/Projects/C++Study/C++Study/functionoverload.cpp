//////////////////////////////////////////////////////////////////////////
// ��������
// 2018/11/09
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdlib.h>
using namespace std;
//////////////////////////////////////////////////////////////////////////
// 1.���غ���ƥ�����
// ���⣺c#����c++ CLI�ӿڣ�UInt64û��ƥ�䵽__int64������ƥ�䵽��float�����Ǿ�����

void pritnfA(int a)
{
	printf("prinfA(int a)\n");
}

void pritnfA(__int64 a)
{
	printf("prinfA(__int64 a)\n");
}

void pritnfA(float a)
{
	printf("prinfA(float a)\n");
}

void TestOverloadMatchRule()
{
	__int64 a = 5;					// __int64
	//unsigned __int64 a = 5;		// error: ambious
	long b = 6;						// int
	unsigned int c = 7;
	//pritnfA(c);					// error C2668: 'pritnfA' : ambiguous call to overloaded function
}