//////////////////////////////////////////////////////////////////////////
// Macro study
// pk
// 2013/05/23
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

//1. ʹ��#�Ѻ������Ϊһ���ַ���,��##�����������������һ��.
#define  STR(s) #s
#define  CONS(a, b) int(a##e##b)

//2.��Ҫע����Ƿ��궨��������'#'��'##'�ĵط�������ǲ�����չ��.
#define  TWO (2)
#define MUL(a,b) (a*b)
#define  A (2)
//#define STR(s) #s
//#define CONS
/************************************************************************/
/* summary *
INT_MAX��A�������ٱ�չ��, Ȼ������������ķ����ܼ�. �Ӷ�һ���м�ת����.
������������ǰ����к�Ĳ����������ȫ��չ��, ��ô��ת���������һ����(_STR)���ܵõ���ȷ�ĺ����.
#define A           (2)
#define _STR(s)     #s
#define STR(s)      _STR(s)          // ת����
#define _CONS(a,b)  int(a##e##b)
#define CONS(a,b)   _CONS(a,b)       // ת����
printf("int max: %s/n", STR(INT_MAX));          // INT_MAX,int�͵����ֵ��Ϊһ������ ��i nclude<climits>
���Ϊ: int max: 0x7fffffff
STR(INT_MAX) -->  _STR(0x7fffffff) Ȼ����ת�����ַ�����
printf("%d/n", CONS(A, A));
���Ϊ��200
CONS(A, A)  -->  _CONS((2), (2))  --> int((2)e(2))
*/
/************************************************************************/

int main(){
	//1
	printf(STR(vck));
	printf("%d\n", CONS(2,3));	//2e3 = 2000

	//2
	printf("%d*%d = %d\n", TWO, TWO, MUL(TWO, TWO));
	printf("int max:%s\n", STR(INT_MAX));		//INT_MAX #include<climits>
	//printf("%s\n", CONS(A, A));					//Error	1	error C2065: 'AeA' : undeclared identifier


	getchar();
	return 0;
}