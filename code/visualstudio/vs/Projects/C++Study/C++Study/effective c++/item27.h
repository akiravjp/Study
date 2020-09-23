#pragma once
#include <iostream>
using namespace std;

namespace effective_study {
	class UPNumber {
	private:
		static void *operator new(size_t size);
		static void operator delete(void* ptr);
	};

	class Asset {
	public:
		Asset(int initValue);
	private:
		UPNumber value;
	};

	//////////////////////////////////////////////////////////////////////////
	// UPNumber
	inline void* UPNumber::operator new(size_t size) {
		//operator new
		cout << "size_t = " << size << endl;
		return malloc(size);
	}
	inline void UPNumber::operator delete(void* ptr) {
		//operator delete������ʱ��ӡ������Ϣ
		free(ptr);
	}
	
	//////////////////////////////////////////////////////////////////////////
	// Asset
	Asset::Asset(int initValue) {

	}
}