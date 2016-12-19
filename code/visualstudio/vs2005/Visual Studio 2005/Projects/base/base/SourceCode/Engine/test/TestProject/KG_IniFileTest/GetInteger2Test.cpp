#include "GetInteger2Test.h"
#include "KGT_IniFileTest.h"

void KGT_GetInteger2Test::setUp()
{

}
void KGT_GetInteger2Test::tearDown()
{

}

void KGT_GetInteger2Test::TestGetInteger2_01()
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
    int  nValue1 = -1;
    int  nValue2 = -1;

    KG_CASE_INFO("�����lpSectionΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_02()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_03()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_04()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection����,�������lpKeyName������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_05()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_06()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����1��ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2,3",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����2����ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == 2 && nValue2 == 3);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2,3,4",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����3��ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=-2,-3",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����2����ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == -2 && nValue2 == -3);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_10()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection����,�������lpKeyName����,valueΪ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=ab,cd",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection����,�������lpKeyName����,valueΪ�������ַ���", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == 0 && nValue2 == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_12()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_13()
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
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ�ǿ�ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}