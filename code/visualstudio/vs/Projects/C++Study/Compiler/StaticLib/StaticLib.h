#pragma once
#include <vector>

//struct KVec2Test;
struct KVec2;  // ������ͷ�ļ��û�����-----����	C2036	��KVec2* ��: δ֪�Ĵ�С	CompilersPrinciplesStudy
class StalicLib
{
public:
	StalicLib() {}
	~StalicLib() {};

	//void UseStrcutInOtherStaticLib(KVec2Test v2Test);
	//void UseStrcutInOtherStaticLib1(std::vector<KVec2Test> vecTests);
	void UseStrcutInOtherStaticLib2(std::vector<KVec2>& vecTests);
	void UseStrcutInOtherStaticLib3();
	void UseStrcutInOtherStaticLib4(KVec2& v2Test);
};

void TestUseStrcutInOtherStaticLib();