#include<iostream> 
using namespace std; 
class A 
{ 
public: 
    A(int); 
    void fun1(); 
    virtual void fun2(); 
    static void fun3(); 
    int num1; 
    static int num2; 
}; 
A::A(int i) 
{ 
    num1=i; 
} 
void A::fun1() 
{ 
    cout<<"I am in fun1"<<endl; 
} 
void A::fun2() 
{ 
    cout<<"I am in fun2"<<endl; 
} 
void A::fun3() 
{ 
    cout<<"I am in fun3"<<endl; 
} 
int A::num2=1; 
void main() 
{ 
    A a(2); 
    //��ȡ��̬��Ա���ݵĵ�ַ 
    int *ptr_static=&A::num2; 
    cout<<"��̬��Ա���ݵĵ�ַ"<<ptr_static<<endl; 
    ptr_static=&a.num2; 
    cout<<"a.num2��̬��Ա���ݵĵ�ַ"<<ptr_static<<endl; 
    //��ȡ��̬�����ĵ�ַ 
    void (*ptr_staticfun)=A::fun3; 
    cout<<"��̬��Ա�����ĵ�ַ"<<ptr_staticfun<<endl; 
    ptr_staticfun=a.fun3; 
    cout<<"a.fun3��̬��Ա�����ĵ�ַ"<<ptr_staticfun<<endl; 
    //��ȡ��ͨ��Ա�����ĵ�ַ 
    typedef void (A::*ptr_commomfun)(); 
    ptr_commomfun ptr=A::fun1; 
    cout<<"��ͨ��Ա�����ĵ�ַ"<<ptr<<endl; //���ֱ�����ptr�Ļ������������1�����Ӧ�ð�ptr��ַ�е����ݶ����� 
    cout<<"��ͨ��Ա�����ĵ�ַ"<<*((long*)&ptr)<<endl; 
    ptr=a.fun1; 
    cout<<"a.fun1��ͨ��Ա�����ĵ�ַ"<<*((long*)&ptr)<<endl; 
    ptr_commomfun ptr_virtual=A::fun2; //��ȡ�麯���ĵ�ַ 
    cout<<"���Ա�����ĵ�ַ"<<*((long*)&ptr_virtual)<<endl; 
    ptr_virtual=a.fun2; 
    cout<<"a.fun2���Ա�����ĵ�ַ"<<*((long*)&ptr_virtual)<<endl; 
  
    int *p; 
    int A::*q; 
    q=&A::num1; 
    //ָ�����ݳ�Ա��ָ�븳�����һ��Ŀǰ�������ڵ�һ�����Ա�ĵ�ַ���������ַֻ����ʹ��ʵ���������е���ʱ�Ż�������ȷ������ 
    //����˵���໹û�ж���ʱ�򣬳�Ա����ʱû�пռ�ġ� 
    cout<<"��ͨ��Ա���ݵĵ�ַ"<<*((long *)&q)<<endl; 
    p=&a.num1; 
    cout<<"a.num2��ͨ��Ա���ݵĵ�ַ"<<p<<endl; 
}
