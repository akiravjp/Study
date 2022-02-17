#pragma once
#include <Windows.h>


#ifdef WIN32		// is windows.
#ifdef _DEBUG		// is debug.
#ifdef _WIN64		// is x64
#define DUMPER_DLL	L".\\DumperD64.dll"
#else				// is x86
#define DUMPER_DLL	L".\\DumperD.dll"
#endif				// _WIN64
#else				// is release.
#ifdef _WIN64		// is x64
#define DUMPER_DLL	L".\\Dumper64.dll"
#else				// is x86
#define DUMPER_DLL	L".\\Dumper.dll"
#endif				// _WIN64
#endif				// _DEBUG
#else				// is not windows.
// do nothing ...
#endif // WIN32

	// Dump���������в�������ö��ֵ
#if _MSC_VER>=1700		// visual studio 2012,  vs2005��֧��enum class�﷨
enum class DumpCommandType
#else
enum DumpCommandType
#endif
{
	enumDump_Begin = 0,

	enumDump_BackgroundExecutionFlag = enumDump_Begin,		// ��̨�ϴ�崻���Ϣ������ʾDumpReport���棩
	enumDump_ForceUpload,									// Dump�Ƿ�ǿ���ϱ������������DumpReport�����ϵ�ѡ��
	enumDump_LogDirectory,									// ����log�ļ�·��
	enumDump_CollectFile,									// �������ռ����ļ���
	enumDump_LogDirectory_UTF8,								// ����log�ļ�·�����������ΪUTF8��Unity/UE ʹ�ô˲�����
	enumDump_CollectFile_UTF8,								// �������ռ����ļ������������ΪUTF8��Unity/UE ʹ�ô˲�����

	enumDump_GM_TEST,										// GM����ָ��

	enumDump_Count
};

namespace KDumper
{

	typedef void(*OnMiniDumpCreateCallback)(BOOL bCaptureSucceed, const char* cpszCrashReportFile);

	// ��ʼ��
	BOOL InitKDumper(const char* pszProject, const char* pszVersionEx, const char* pszVersion);
	// �ͷ���Դ
	void UnInitKDumper();

	// ����崻���׽��Ļص�����
	BOOL SetMiniDumpCreateCallback(OnMiniDumpCreateCallback pCallback);

	// nCommandType Ϊ DumpCommandType ����
	BOOL SetConfig(const int nCommandType, const void* pArg);
}