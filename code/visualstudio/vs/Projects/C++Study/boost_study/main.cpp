#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>

namespace bip = boost::interprocess;
using namespace std;

static const char* shareMemoryBlockName = "MySharedMemory";
static int32_t sharedMemoryBlockTotalSize = 65536;

int main()
{
	//���������ڴ�
	bip::managed_shared_memory segment(bip::create_only,
		shareMemoryBlockName,  //segment name
		sharedMemoryBlockTotalSize);

	//����attach�����ڴ�
	//������Ҫattach��share memory block
	//bip::managed_shared_memory segment(bip::open_only,
	//	shareMemoryBlockName  //segment name
	//);


	//ͬʱ���ٹ����ڴ�
	bool isRemoved = bip::shared_memory_object::remove(shareMemoryBlockName);
	if (isRemoved)
	{
		cout << "Share Memory=[" << shareMemoryBlockName << "] removed!" << endl;
	}
	else
	{
		cout << "Share Memory=[" << shareMemoryBlockName << "] not removed!" << endl;
	}
}
