#pragma once
#include "item27.h"
#include "item28.h"

//////////////////////////////////////////////////////////////////////////
// test function

namespace effective_study {
	void TestNewHeapOrStack()
	{
		// ��Ϊ��Ա������operate new��˽������ʧЧ��
		Asset* pa = new Asset(100);
	}


	void TestSmartPtrFunction()
	{
		auto t = new TestSmartPtr(5);
		auto_ptr<TestSmartPtr> ptn(t);

		// error C2678: �����ơ�==��: û���ҵ����ܡ�std::auto_ptr<effective_study::TestSmartPtr>�����͵���������������(��û�пɽ��ܵ�ת��)
		//if (ptn == 0)
		//{
		//	cout << "null pointer" << endl;
		//}

		// error C2451: ��std::auto_ptr<effective_study::TestSmartPtr>�����͵��������ʽ�ǷǷ���
		//if (ptn)
		//{
		//	cout << "not null pointer" << endl;
		//}
		
		// error C2675 : һԪ��!�� : ��std::auto_ptr<effective_study::TestSmartPtr>����������������Ԥ����������ɽ������͵�ת��
		//if (!ptn)
		//{
		//	cout << "null pointer" << endl;
		//}
		ptn->PrintNumber();	// ok

		t = new TestSmartPtr(6);
		SmartPtr<TestSmartPtr> ptnSelf(t);
		ptnSelf->PrintNumber();

		// OK����ʽת��֮ǰ������һ���Ĵ���
		if (ptnSelf == 0)
		{
			cout << "null pointer" << endl;
		}

		// OK����ʽת��֮ǰ������һ���Ĵ���
		if (ptnSelf)
		{
			cout << "not null pointer" << endl;
		}

		// OK����ʽת��֮ǰ������һ���Ĵ���
		if (!ptnSelf)
		{
			cout << "null pointer" << endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void TestEffectiveStudy()
	{
		//TestNewHeapOrStack();
		TestSmartPtrFunction();
	}

	
	


}

