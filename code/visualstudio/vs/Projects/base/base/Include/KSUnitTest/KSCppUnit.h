//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSCppUnit.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-10-26
//  Comment     :   ��ʼ��cppunit���ṩ���ֽ�������ʽ����ʹ��cppunit���е�Ԫ����ʱ
//                  ��main�����е��ýӿں���KSCppUnitTest()
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_CPP_UNIT_H_
#define _KS_CPP_UNIT_H_

#include "def.h"
#include "PrintSTDTxt.h"
#include "PrintHTML.h"
#include "KSCppUnit_TestResultCollector.h"

KSCppUnit_TestResultCollector g_KS_CPPUNIT_result;

//������  IN TestName ��������,��:paysys bishop
//         IN ResultPath ���Խ�����·��
//         IN OutputType ��������ʽ����def.h�ж���
//����ֵ��1 ���Բ��԰���ִ�гɹ�
//         0 ��Щ����ִ��ʧ��
int KSCppUnitTest(
    const char cszTestName[], 
    const char cszResultPath[], 
    int nOutputType
);

int KSCppUnitTest(
    const char cszTestName[], 
    const char cszResultPath[], 
    int nOutputType
)
{
    int nResult  = false;
    int nRetCode = false;

    char szStartTime[32];
    char szEndTime[32];
    
    assert(cszTestName);
    assert(cszResultPath);

    CPPUNIT_NS::TestResult TRController;    
    TRController.addListener(&g_KS_CPPUNIT_result);

#ifdef _CONSOLE
    // Add a listener that print dots as test run.
    CppUnit::TextTestProgressListener TTprogress;
    TRController.addListener( &TTprogress );
#endif

    // Add the top suite to the test runner
    CPPUNIT_NS::TestRunner TRunner;
    CPPUNIT_NS::TestFactoryRegistry &registry =
        CppUnit::TestFactoryRegistry::getRegistry();

    TRunner.addTest(registry.makeTest());

    nRetCode = GetTime(szStartTime,32);
    KGLOG_PROCESS_ERROR(nRetCode);

    TRunner.run(TRController);//ִ�а���

    nRetCode = GetTime(szEndTime,32);
    KGLOG_PROCESS_ERROR(nRetCode);

    if (nOutputType & STD_OUTPUT)
    {
        Print_STD(&g_KS_CPPUNIT_result, cszTestName, szStartTime, szEndTime);
    }

    if (nOutputType & TXT_OUTPUT)
    {
        Print_TXT(&g_KS_CPPUNIT_result, cszTestName, cszResultPath, szStartTime, szEndTime);
    }

    if (nOutputType & HTML_OUTPUT)
    {
        Print_HTML(&g_KS_CPPUNIT_result, cszTestName, cszResultPath, szStartTime, szEndTime);
    }
    
    nRetCode = g_KS_CPPUNIT_result.WasSuccessful();
    KG_PROCESS_ERROR(nRetCode);

    nResult = true;
Exit0:
    return nResult;
}


#endif //_KS_CPP_UNIT_H_