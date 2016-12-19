//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   g_OpenIniFileFromArgumentsTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-14 11:07
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _g_OpenIniFileFromArgumentsTest_h__
#define _g_OpenIniFileFromArgumentsTest_h__

#include "cppunit/extensions/HelperMacros.h"

#define MAX_ERROR_INPUT_FILE 1024 * 10

class KGT_g_OpenIniFileFromArgumentsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_g_OpenIniFileFromArgumentsTest);

    CPPUNIT_TEST(Test_g_OpenFileFromArguments_01);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_02);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_03);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_04);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_05);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_06);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_07);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_08);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_09);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_10);
    CPPUNIT_TEST(Test_g_OpenFileFromArguments_11);
    CPPUNIT_TEST(Test_ErrorInput);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void Test_g_OpenFileFromArguments_01();         //��ͬ��section��ͬ��key
    void Test_g_OpenFileFromArguments_02();         //��ͬ��section��ͬ��key
    void Test_g_OpenFileFromArguments_03();         //��ͬ��section��ͬ��key
    void Test_g_OpenFileFromArguments_04();         //��ͬ��section��ͬ��key
    void Test_g_OpenFileFromArguments_05();         //section�ĳ���Ϊ���ֵ
    void Test_g_OpenFileFromArguments_06();         //section�ĳ��ȴ������ֵ
    void Test_g_OpenFileFromArguments_07();         //key�ĳ���Ϊ���ֵ
    void Test_g_OpenFileFromArguments_08();         //key�ĳ��ȴ������ֵ
    void Test_g_OpenFileFromArguments_09();         //value�ĳ���Ϊ0
    void Test_g_OpenFileFromArguments_10();         //value�ĳ���Ϊ���ֵ
    void Test_g_OpenFileFromArguments_11();         //value�ĳ��ȴ������ֵ
    void Test_ErrorInput();                         //�Ƿ�����
private:
    int _LoadFile();
    int _DataGenerator(int nSize, char szRetString[]);
    char m_szErrorInput[MAX_ERROR_INPUT_FILE];
};

#endif // g_OpenIniFileFromArgumentsTest_h__