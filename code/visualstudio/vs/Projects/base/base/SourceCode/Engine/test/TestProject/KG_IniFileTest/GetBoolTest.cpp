#include "GetBoolTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetBoolTest::setUp()
{

}
void KGT_GetBoolTest::tearDown()
{

}

void KGT_GetBoolTest::TestGetBool_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "version";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSectionΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}


void KGT_GetBoolTest::TestGetBool_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "";
    int  nBool = -1;

    KG_CASE_INFO("�����lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��,����������Ϊ��", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "name";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSection���ڣ��������lpKeyName������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Server";
    char *pszKey = "version";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSection������", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Test.bool1=YES",
        "--Test.bool2=NO",
        "--Test.bool3=TRUE",
        "--Test.bool4=FALSE",
        "--Test.bool5=1",
        "--Test.bool6=0"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Test";
    char szKeyName[32];
    szKeyName[0] = '\0';
    int  nBool = -1;

    KG_CASE_INFO("valueֵΪȫ��д��\"YES\",��\"TRUE\"(��\"NO\",\"FALSE\")", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    for (int i = 1; i < nArgc; i++)
    {
        nRetCode = _snprintf(
            szKeyName,
            sizeof(szKeyName) / sizeof(szKeyName[0]),
            "bool%d",
            i
        );
        KG_PROCESS_ERROR(nRetCode > (int)strlen("bool"));
        szKeyName[sizeof(szKeyName) / sizeof(szKeyName[0]) - 1] = '\0';

        nRetCode = piIniFile->GetBool(pszSection, szKeyName, &nBool);
        KG_PROCESS_ERROR(nRetCode);

        nRetCode = i % 2 ? true : false;
        KG_PROCESS_ERROR(nBool == nRetCode);
    }

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Test.bool1=yes",
        "--Test.bool2=no",
        "--Test.bool3=true",
        "--Test.bool4=false",
        "--Test.bool5=1",
        "--Test.bool6=0"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Test";
    char szKeyName[32];
    szKeyName[0] = '\0';
    int  nBool = -1;

    KG_CASE_INFO("valueֵΪȫСд��\"yes\",��\"true\"(��\"no\",\"false\")", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    for (int i = 1; i < nArgc; i++)
    {
        nRetCode = _snprintf(
            szKeyName,
            sizeof(szKeyName) / sizeof(szKeyName[0]),
            "bool%d",
            i
            );
        KG_PROCESS_ERROR(nRetCode > (int)strlen("bool"));
        szKeyName[sizeof(szKeyName) / sizeof(szKeyName[0]) - 1] = '\0';

        nRetCode = piIniFile->GetBool(pszSection, szKeyName, &nBool);
        KG_PROCESS_ERROR(nRetCode);

        nRetCode = i % 2 ? true : false;
        KG_PROCESS_ERROR(nBool == nRetCode);
    }

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Test.bool1=Yes",
        "--Test.bool2=No",
        "--Test.bool3=tRue",
        "--Test.bool4=fAlse",
        "--Test.bool5=1",
        "--Test.bool6=0"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Test";
    char szKeyName[32];
    szKeyName[0] = '\0';
    int  nBool = -1;

    KG_CASE_INFO("valueֵΪȫСд��\"Yes\",��\"tRue\"(��\"nO\",\"fAlse\")", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    for (int i = 1; i < nArgc; i++)
    {
        nRetCode = _snprintf(
            szKeyName,
            sizeof(szKeyName) / sizeof(szKeyName[0]),
            "bool%d",
            i
        );
        KG_PROCESS_ERROR(nRetCode > (int)strlen("bool"));
        szKeyName[sizeof(szKeyName) / sizeof(szKeyName[0]) - 1] = '\0';

        nRetCode = piIniFile->GetBool(pszSection, szKeyName, &nBool);
        KG_PROCESS_ERROR(nRetCode);

        nRetCode = i % 2 ? true : false;
        KG_PROCESS_ERROR(nBool == nRetCode);
    }

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=dsdsd"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int  nBool = -1;

    KG_CASE_INFO("valueֵ������Ч�ؼ���", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version="
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int  nBool = -1;

    KG_CASE_INFO("valueΪ��ֵ", "�����ļ����������м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ��ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetBoolTest::TestGetBool_12()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int  nBool = -1;

    KG_CASE_INFO("�����lpSection��lpKeyNameΪ�ǿ�ֵ", "�����ļ���������û�м�¼");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetBool(pszSection, pszKey, &nBool);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nBool == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}