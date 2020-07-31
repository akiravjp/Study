#include "TestBase.h"
#include <typeinfo>
//#include <typeinfo.h>



TestBase::TestBase(int i)
	:baseI(i)
{
}


TestBase::~TestBase()
{
}

//////////////////////////////////////////////////////////////////////////
void TestObjectModel()
{
	// base
	//TestBase b(100);
	//TestBaseFunction(b);

	// derive
	//TestDeriveFunction();

	// multiple derive
	//TestMultiDeriveFunction();

	// diamond derive
	//TestDiamondDeriveFunction();
	

	// virtual derive
	//TestVirtualDeriveFunction();

	// virtual diamond derive
	TestVirtualDiamondDeriveFunction();
}
//
void TestBaseFunction(TestBase&p)
{
	cout << "������ڴ���ʼ��ַ��" << &p << endl;
	cout << "type_info��Ϣ:" << endl;
	// ע�⣺�����64λ����intȥƫ���ǲ��Եģ�64λ����ָ��ʽ8λ�ģ�Ҫ��int����long
	// (int*)(&p)�����vprt�ĵ�ַ��ȡ��ַ����*(int*)(&p)���������vptr
	RTTICompleteObjectLocator str = *((RTTICompleteObjectLocator*)*((int*)*(int*)(&p) - 1));


	string classname(str.pTypeDescriptor->name);
	classname = classname.substr(4, classname.find("@@") - 4);
	cout << "����type_info��Ϣ�������:" << classname << endl;

	cout << "�麯�����ַ:" << (int *)(&p) << endl;

	//��֤���
	cout << "�麯�����һ�������ĵ�ַ��" << (int *)*((int*)(&p)) << endl;
	cout << "���������ĵ�ַ:" << (int*)*(int *)*((int*)(&p)) << endl;
	cout << "��һ�������ĵ�ַ:" << (int*)*(((int*)*(int*)(&p) + 1)) << endl;
	cout << "�麯�����У��ڶ����麯����print�����ĵ�ַ��" << ((int*)*(int*)(&p) + 1) << endl;

	//ͨ����ַ�����麯��print����
	typedef void(*Fun)(void);
	Fun IsPrint = (Fun)* ((int*)*(int*)(&p) + 1);
	cout << endl;
	cout << "�������麯��";
	IsPrint(); //����ַ��ȷ���������Base����麯��print����
	cout << endl;

	//����static�����ĵ�ַ
	p.countI();//�ȵ��ú����Բ���һ��ʵ��
	cout << "static����countI()�ĵ�ַ��" << p.countI << endl;

	//��֤nonstatic���ݳ�Ա
	cout << "�Ʋ�nonstatic���ݳ�ԱbaseI�ĵ�ַ��" << (int *)(&p) + 1 << endl;
	cout << "�����Ʋ���ĵ�ַ������õ�ַ��ֵ��" << *((int *)(&p) + 1) << endl;
	cout << "Base::getI():" << p.getI() << endl;

}

typedef void(*Fun)(void);

void TestDeriveFunction()
{
	TestDerive d(2000);
	//[0]
	cout << "[0]Base::vptr";
	cout << "\t��ַ��" << (int *)(&d) << endl;
	//vprt[0]
	cout << "  [0]";
	Fun fun1 = (Fun)*((int *)*((int *)(&d)));
	fun1();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d))) << endl;

	//vprt[1]���������޷�ͨ����ַ���ã����ֶ����
	cout << "  [1]" << "Derive::~Derive" << endl;

	//vprt[2]
	cout << "  [2]";
	Fun fun2 = (Fun)*((int *)*((int *)(&d)) + 2);
	fun2();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 2) << endl;
	//[1]
	cout << "[2]Base::baseI=" << *(int*)((int *)(&d) + 1);
	cout << "\t��ַ��" << (int *)(&d) + 1;
	cout << endl;
	//[2]
	cout << "[2]Derive::DeriveI=" << *(int*)((int *)(&d) + 2);
	cout << "\t��ַ��" << (int *)(&d) + 2;
	cout << endl;
}

void TestMultiDeriveFunction()
{
	TestDriveMultiBase d(3000);
	//[0]
	cout << "[0]Base::vptr";
	cout << "\t��ַ��" << (int *)(&d) << endl;

	//vprt[0]
	cout << "  [0]";
	Fun fun1 = (Fun)*((int *)*((int *)(&d)));
	fun1();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d))) << endl;

	//vprt[1]���������޷�ͨ����ַ���ã����ֶ����
	cout << "  [1]" << "Derive::~Derive" << endl;

	//vprt[2]
	cout << "  [2]";
	Fun fun2 = (Fun)*((int *)*((int *)(&d)) + 2);
	fun2();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 2) << endl;


	//[1]
	cout << "[1]Base::baseI=" << *(int*)((int *)(&d) + 1);
	cout << "\t��ַ��" << (int *)(&d) + 1;
	cout << endl;


	//[2]
	cout << "[2]Base2::vptr";
	cout << "\t��ַ��" << (int *)(&d) + 2 << endl;

	//vprt[0]
	cout << "  [0]";
	Fun fun4 = (Fun)*((int *)*((int *)(&d) + 2));
	fun4();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d))) << endl;

	//vprt[1]���������޷�ͨ����ַ���ã����ֶ����
	cout << "  [1]" << "Drive_multyBase::~Derive" << endl;

	//[3]
	cout << "[3]Base_2::base2I=" << *(int*)((int *)(&d) + 3);
	cout << "\t��ַ��" << (int *)(&d) + 3;
	cout << endl;

	//[4]
	cout << "[4]Drive_multyBase::Drive_multyBaseI=" << *(int*)((int *)(&d) + 4);
	cout << "\t��ַ��" << (int *)(&d) + 4;
	cout << endl;
}

void TestDiamondDeriveFunction()
{
	test_derive::D d(3000);
	//d[0]
	cout << "[0]B1::vptr";
	cout << "\t��ַ��" << (int *)(&d) << endl;

	//B1 vprt[0]
	cout << "  [0]";
	Fun fun1 = (Fun)*((int *)*((int *)(&d)));
	fun1();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d))) << endl;

	//B1 vprt[1]
	cout << "  [1]";
	Fun fun2 = (Fun)*((int *)*((int *)(&d)) + 1);
	fun2();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 1) << endl;

	//B1 vprt[2]
	cout << "  [2]";
	Fun fun3 = (Fun)*((int *)*((int *)(&d)) + 2);
	fun3();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 2) << endl;

	//B1 vprt[3]
	cout << "  [3]";
	Fun fun4 = (Fun)*((int *)*((int *)(&d)) + 3);
	fun4();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 3) << endl;

	//B1 vprt[4]
	cout << "  [4]";
	Fun fun5 = (Fun)*((int *)*((int *)(&d)) + 4);
	fun5();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d)) + 4) << endl;

	//d[1]
	cout << "[1]B::ib=" << *(int*)((int *)(&d) + 1);
	cout << "\t��ַ��" << (int *)(&d) + 1;
	cout << endl;

	//d[2]
	cout << "[2]B1::ib1=" << *(int*)((int *)(&d) + 2);
	cout << "\t��ַ��" << (int *)(&d) + 2;
	cout << endl;

	//d[3]
	cout << "[3]B2::vptr";
	cout << "\t��ַ��" << (int *)(&d) + 3 << endl;

	//B2 vprt[0]
	cout << "  [0]";
	Fun B2fun1 = (Fun)*((int *)*((int *)(&d) + 3));
	B2fun1();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d))) << endl;

	//B2 vprt[1]
	cout << "  [1]";
	Fun B2fun2 = (Fun)*((int *)*((int *)(&d) + 3) + 1);
	B2fun2();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d) + 3) + 1) << endl;

	//B2 vprt[2]
	cout << "  [2]";
	Fun B2fun3 = (Fun)*((int *)*((int *)(&d) + 3) + 2);
	B2fun3();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d) + 3) + 2) << endl;

	//B2 vprt[3]
	cout << "  [3]";
	Fun B2fun4 = (Fun)*((int *)*((int *)(&d) + 3) + 3);
	B2fun4();
	cout << "\t��ַ:\t" << *((int *)*((int *)(&d) + 3) + 3) << endl;

	//d[4]
	cout << "[4]B::ib=" << *(int*)((int *)(&d) + 4);
	cout << "\t��ַ��" << (int *)(&d) + 4;
	cout << endl;

	//d[5]
	cout << "[4]B2::ib2=" << *(int*)((int *)(&d) + 5);
	cout << "\t��ַ��" << (int *)(&d) + 5;
	cout << endl;

	//d[6]
	cout << "[5]D::id=" << *(int*)((int *)(&d) + 6);
	cout << "\t��ַ��" << (int *)(&d) + 6;
	cout << endl;

	cout << endl;
}

void TestVirtualDeriveFunction()
{

	test_derive::VB1 a;
	cout << "B1�����ڴ��СΪ��" << sizeof(a) << endl;

	//ȡ��B1���麯����
	cout << "[0]B1::vptr";
	cout << "\t��ַ��" << (int *)(&a) << endl;

	//������B1::vptr�еĺ���
	for (int i = 0; i < 2; ++i)
	{
		cout << "  [" << i << "]";
		Fun fun1 = (Fun)*((int *)*(int *)(&a) + i);
		fun1();
		cout << "\t��ַ��\t" << *((int *)*(int *)(&a) + i) << endl;
	}

	//[1]
	cout << "[1]vbptr ";
	cout << "\t��ַ��" << (int *)(&a) + 1 << endl;  //���ָ��ĵ�ַ
													//��������ָ����Ŀ��ָ������
	for (int i = 0; i < 2; i++)
	{
		cout << "  [" << i << "]";

		cout << *(int *)((int *)*((int *)(&a) + 1) + i);

		cout << endl;
	}


	//[2]
	cout << "[2]B1::ib1=" << *(int*)((int *)(&a) + 2);
	cout << "\t��ַ��" << (int *)(&a) + 2;
	cout << endl;

	//[3]
	cout << "[3]ֵ=" << *(int*)((int *)(&a) + 3);
	cout << "\t\t��ַ��" << (int *)(&a) + 3;
	cout << endl;

	//[4]
	cout << "[4]B::vptr";
	cout << "\t��ַ��" << (int *)(&a) + 3 << endl;

	//���B::vptr�е��麯��
	for (int i = 0; i < 2; ++i)
	{
		cout << "  [" << i << "]";
		Fun fun1 = (Fun)*((int *)*((int *)(&a) + 4) + i);
		fun1();
		cout << "\t��ַ:\t" << *((int *)*((int *)(&a) + 4) + i) << endl;
	}

	//[5]
	cout << "[5]B::ib=" << *(int*)((int *)(&a) + 5);
	cout << "\t��ַ: " << (int *)(&a) + 5;
	cout << endl;
}

void TestVirtualDiamondDeriveFunction()
{
	test_derive::VD d;
	cout << "D�����ڴ��СΪ��" << sizeof(d) << endl;

	//ȡ��B1���麯����
	cout << "[0]B1::vptr";
	cout << "\t��ַ��" << (int *)(&d) << endl;

	//������B1::vptr�еĺ���
	for (int i = 0; i < 3; ++i)
	{
		cout << "  [" << i << "]";
		Fun fun1 = (Fun)*((int *)*(int *)(&d) + i);
		fun1();
		cout << "\t��ַ��\t" << *((int *)*(int *)(&d) + i) << endl;
	}

	//[1]
	cout << "[1]B1::vbptr ";
	cout << "\t��ַ��" << (int *)(&d) + 1 << endl;  //���ָ��ĵ�ַ
													//��������ָ����Ŀ��ָ������
	for (int i = 0; i < 2; i++)
	{
		cout << "  [" << i << "]";

		cout << *(int *)((int *)*((int *)(&d) + 1) + i);

		cout << endl;
	}


	//[2]
	cout << "[2]B1::ib1=" << *(int*)((int *)(&d) + 2);
	cout << "\t��ַ��" << (int *)(&d) + 2;
	cout << endl;

	//[3]
	cout << "[3]B2::vptr";
	cout << "\t��ַ��" << (int *)(&d) + 3 << endl;

	//���B2::vptr�е��麯��
	for (int i = 0; i < 2; ++i)
	{
		cout << "  [" << i << "]";
		Fun fun1 = (Fun)*((int *)*((int *)(&d) + 3) + i);
		fun1();
		cout << "\t��ַ:\t" << *((int *)*((int *)(&d) + 3) + i) << endl;
	}

	//[4]
	cout << "[4]B2::vbptr ";
	cout << "\t��ַ��" << (int *)(&d) + 4 << endl;  //���ָ��ĵ�ַ
													//��������ָ����Ŀ��ָ������
	for (int i = 0; i < 2; i++)
	{
		cout << "  [" << i << "]";

		cout << *(int *)((int *)*((int *)(&d) + 4) + i);

		cout << endl;
	}

	//[5]
	cout << "[5]B2::ib2=" << *(int*)((int *)(&d) + 5);
	cout << "\t��ַ: " << (int *)(&d) + 5;
	cout << endl;

	//[6]
	cout << "[6]D::id=" << *(int*)((int *)(&d) + 6);
	cout << "\t��ַ: " << (int *)(&d) + 6;
	cout << endl;

	//[7]
	cout << "[7]ֵ=" << *(int*)((int *)(&d) + 7);
	cout << "\t\t��ַ��" << (int *)(&d) + 7;
	cout << endl;

	//��Ӹ���
	//[8]
	cout << "[8]B::vptr";
	cout << "\t��ַ��" << (int *)(&d) + 8 << endl;

	//���B::vptr�е��麯��
	for (int i = 0; i < 2; ++i)
	{
		cout << "  [" << i << "]";
		Fun fun1 = (Fun)*((int *)*((int *)(&d) + 8) + i);
		fun1();
		cout << "\t��ַ:\t" << *((int *)*((int *)(&d) + 8) + i) << endl;
	}

	//[9]
	cout << "[9]B::id=" << *(int*)((int *)(&d) + 9);
	cout << "\t��ַ: " << (int *)(&d) + 9;
	cout << endl;
}