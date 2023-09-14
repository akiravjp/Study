#pragma once
// ����1�� ����ģ�溯��
template<typename T>
inline void PushData(T data) {
	printf("[PushData]Template 1\n");
	// Code...
};
// ����2������ģ�溯��(����ָ��)
template<typename T>
inline void PushData(T* data) {
	printf("[PushData]Template 2\n");
	// Code...
};
// ����3���ػ���ģ�溯��
template<>
inline void PushData(const char* data) {
	printf("[PushData]Template 3\n");
	// Code...
}


void TestTemplate()
{
	PushData<char*>("String");
	PushData("String");
}