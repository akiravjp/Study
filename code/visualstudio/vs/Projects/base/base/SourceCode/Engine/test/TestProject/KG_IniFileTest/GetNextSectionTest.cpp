#include "GetNextSectionTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetNextSectionTest::setUp()
{
}

void KGT_GetNextSectionTest::tearDown()
{

}

void KGT_GetNextSectionTest::TestGetNextSection_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("��ֵ����һ��section", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    //KG_IniFile����map�洢���ʰ���ĸ����
    nRetCode = strcmp(szNextSection, "AVersion");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root", 
        "--DLogServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "AVersion";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("��һ����¼����һ��section", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    //KG_IniFile����map�洢���ʰ���ĸ����
    nRetCode = strcmp(szNextSection, "BDatabase");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root", 
        "--DLogServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "BDatabase";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("�м�һ����¼����һ��section(�������һ��section)", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    //KG_IniFile����map�洢���ʰ���ĸ����
    nRetCode = strcmp(szNextSection, "CNameServer");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root", 
        "--DLogServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "CNameServer";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("�����ڶ�����¼����һ��section", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    //KG_IniFile����map�洢���ʰ���ĸ����
    nRetCode = strcmp(szNextSection, "DLogServer");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root", 
        "--DLogServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "DLogServer";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("���һ����¼����һ��section", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';
    
    KG_PROCESS_ERROR(szNextSection[0] == '\0');    //szNextSection���ֲ���

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2", 
        "--BDatabase.user=root", 
        "--CNameServer.user=root", 
        "--DLogServer.user=root"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "EGoddessServer";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("�����ڵļ�¼����һ��section", "KG_Ini_SectionMap�ж�����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    KG_PROCESS_ERROR(szNextSection[0] == '\0');    //szNextSection���ֲ���

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("��ֵ����һ��section", "KG_Ini_SectionMapֻ��1����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    nRetCode = strcmp(szNextSection, "AVersion");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "AVersion";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("���ڵļ�¼����һ��section", "KG_Ini_SectionMapֻ��1����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    KG_PROCESS_ERROR(szNextSection[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe", 
        "--AVersion.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Database";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("�����ڵļ�¼����һ��section", "KG_Ini_SectionMapֻ��1����¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    KG_PROCESS_ERROR(szNextSection[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("��ֵ��һ��section", "KG_Ini_SectionMapû�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    KG_PROCESS_ERROR(szNextSection[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextSectionTest::TestGetNextSection_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char szNextSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextSection[0] = '\0';

    KG_CASE_INFO("�ǿ�ֵ��һ��section", "KG_Ini_SectionMapû�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextSection(pszSection, szNextSection);
    KG_PROCESS_ERROR(!nRetCode);
    szNextSection[sizeof(szNextSection) - 1] = '\0';

    KG_PROCESS_ERROR(szNextSection[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}