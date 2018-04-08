#include "GetIntegerTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetIntegerTest::setUp()
{

}
void KGT_GetIntegerTest::tearDown()
{

}

void KGT_GetIntegerTest::TestGetInteger_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSectionΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "name";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSection����,�������lpKeyName������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Server";
    char *pszKey = "name";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSection������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,valueΪ�����ַ�������Ϊ����", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=-2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = 0;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,valueΪ�����ַ�������Ϊ����", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == -2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,valueΪ��ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=abcd",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,valueΪ�������ַ���", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int nDefault = 10;
    int nRetValue = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetIntegerTest::TestGetInteger_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nDefault = 10;
    int nRetValue = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ�ǿ�ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(pszSection, pszKey, nDefault, &nRetValue);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nRetValue == nDefault);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}