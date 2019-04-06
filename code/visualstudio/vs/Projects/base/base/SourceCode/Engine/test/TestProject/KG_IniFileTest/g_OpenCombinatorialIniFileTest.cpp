#include "g_OpenCombinatorialIniFileTest.h"
#include "KGT_IniFileTest.h"

const char *g_pcszDataFileName = "HaveData.ini";
const char *g_pcszNoDataFileName = "NoData.ini";

void KGT_g_OpenCombinatorialIniFileTest::setUp()
{

}
void KGT_g_OpenCombinatorialIniFileTest::tearDown()
{

}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nRetValue = 0;

    KG_CASE_INFO("�������ļ�û�м�¼��ini�ļ�������", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nRetCode = piStartArgument->GetInteger("Version1", "version", -1, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);
    
    KG_PROCESS_ERROR(nRetValue == 1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=1"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nRetValue = 0;

    KG_CASE_INFO("�������ļ��м�¼��ini�ļ�û������", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszNoDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nRetCode = piStartArgument->GetInteger("Version", "version", -1, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("�������ļ�û�м�¼��ini�ļ�û������", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszNoDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nRetCode = piStartArgument->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_04()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version2.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    nRetCode = piCmdArguments->GetSectionCount();

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_05()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version3.version=3"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nRetValue = 0;
    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section,ini�ļ���ֻ��section��û��key", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR((nSectionCount1 + 1) == nSectionCount2);

    nRetCode = piStartArgument->GetInteger("Version3", "version", 0, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 3);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_06()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2���в�ͬ��section", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Database", "name", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(!nRetCode);

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nRetCode = piStartArgument->GetString("Database", "name", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szRetValue, "mysql");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_07()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    KG_CASE_INFO("�������ļ���ini�ļ���������,2���в�ͬ��section,ini�ļ���ֻ��section,û��key", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Database", "name", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(!nRetCode);

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nRetCode = piStartArgument->GetString("Database", "name", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szRetValue, "mysql");
    KG_PROCESS_ERROR(nRetCode == 0);
    
    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_08()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version5.version=4"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';
    char szKey[32];
    szKey[0] = '\0';
    char szNextKey[32];
    szNextKey[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;
    int nKeyCount1 = 0;
    int nKeyCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version5", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    nSectionCount1 = piIniFile->GetSectionCount();

    szNextKey[0] = '\0';
    while (true)
    {
        strncpy(szKey, szNextKey, sizeof(szKey) / sizeof(szKey[0]) - 1);
        szKey[sizeof(szKey) / sizeof(szKey[0]) - 1] = '\0';

        nRetCode = piIniFile->GetNextKey("Version5", szKey, szNextKey);
        szNextKey[sizeof(szNextKey) / sizeof(szNextKey[0]) - 1] = '\0';
        if (!nRetCode)  //������
            break;
        nKeyCount1++;
    }

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    szNextKey[0] = '\0';
    while (true)
    {
        strncpy(szKey, szNextKey, sizeof(szKey) / sizeof(szKey[0]) - 1);
        szKey[sizeof(szKey) / sizeof(szKey[0]) - 1] = '\0';

        nRetCode = piStartArgument->GetNextKey("Version5", szKey, szNextKey);
        szNextKey[sizeof(szNextKey) / sizeof(szNextKey[0]) - 1] = '\0';
        if (!nRetCode)  //������
            break;
        nKeyCount2++;
    }

    KG_PROCESS_ERROR(nKeyCount1 == nKeyCount2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_09()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version6.version=6"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version6", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(!nRetCode);

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nRetCode = piStartArgument->GetString("Version6", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "6");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_10()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version7.version=7"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key����ͬ��value", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version7", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "7");
    KG_PROCESS_ERROR(nRetCode == 0);

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nRetCode = piStartArgument->GetString("Version7", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "7");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_11()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version8.version=10"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key����ͬ��value", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version8", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nRetCode = piStartArgument->GetString("Version8", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "10");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_12()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version9.version="
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key����ͬ��value,�����е�value=�մ�", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version9", "version", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(szRetValue[0] != '\0');

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nRetCode = piStartArgument->GetString("Version9", "version", "dsdfdfdf", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    KG_PROCESS_ERROR(szRetValue[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenCombinatorialIniFileTest::Test_g_OpenCombinatorialIniFile_13()
{
    int nResult = false;
    int nRetCode = 0;

    IIniFile *piCmdArguments = NULL;
    IIniFile *piIniFile = NULL;
    IIniFile *piStartArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version10.version=10"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[32];
    szRetValue[0] = '\0';

    int nSectionCount1 = 0;
    int nSectionCount2 = 0;

    KG_CASE_INFO("�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key����ͬ��value,ini�ļ���value=�մ�", "");

    piCmdArguments = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piCmdArguments);

    piIniFile = g_OpenIniFile(g_pcszDataFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Version10", "version", "dsdddd", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(szRetValue[0] == '\0');

    nSectionCount1 = piIniFile->GetSectionCount();

    piStartArgument = g_OpenCombinatorialIniFile(piCmdArguments, piIniFile);
    KG_PROCESS_ERROR(piStartArgument);

    nSectionCount2 = piStartArgument->GetSectionCount();

    KG_PROCESS_ERROR(nSectionCount1 == nSectionCount2);

    nRetCode = piStartArgument->GetString("Version10", "version", "dsdfdfdf", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "10");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piStartArgument);
    KG_COM_RELEASE(piIniFile);
    KG_COM_RELEASE(piCmdArguments);
    CPPUNIT_ASSERT(nResult);
}