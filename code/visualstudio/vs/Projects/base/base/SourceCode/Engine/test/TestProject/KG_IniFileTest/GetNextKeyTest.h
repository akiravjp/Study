//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetNextKeyTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 9:16
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetNextKeyTest_h__
#define _GetNextKeyTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetNextKeyTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetNextKeyTest);

    CPPUNIT_TEST(TestGetNextKey_01);
    CPPUNIT_TEST(TestGetNextKey_02);
    CPPUNIT_TEST(TestGetNextKey_03);
    CPPUNIT_TEST(TestGetNextKey_04);
    CPPUNIT_TEST(TestGetNextKey_05);
    CPPUNIT_TEST(TestGetNextKey_06);
    CPPUNIT_TEST(TestGetNextKey_07);
    CPPUNIT_TEST(TestGetNextKey_08);
    CPPUNIT_TEST(TestGetNextKey_09);
    CPPUNIT_TEST(TestGetNextKey_10);
    CPPUNIT_TEST(TestGetNextKey_11);
    CPPUNIT_TEST(TestGetNextKey_12);
    CPPUNIT_TEST(TestGetNextKey_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    ///////////////////////////section���ڣ����ж��key////////////////////////////
    void TestGetNextKey_01();            //��ֵ����һ��key
    void TestGetNextKey_02();            //��һ����¼����һ��key
    void TestGetNextKey_03();            //�м�һ����¼����һ��key���������һ��key��
    void TestGetNextKey_04();            //�����ڶ�����¼����һ��key
    void TestGetNextKey_05();            //���һ����¼����һ��key
    void TestGetNextKey_06();            //�����ڵļ�¼����һ��key

    ///////////////////////////section���ڣ���ֻ��һ��key///////////////////////////
    void TestGetNextKey_07();            //��ֵ����һ��key
    void TestGetNextKey_08();            //���ڼ�¼����һ��key
    void TestGetNextKey_09();            //�����ڼ�¼����һ��key

    ///////////////////////////section���ڣ���û��key///////////////////////////////
    void TestGetNextKey_10();            //��ֵ����һ��key
    void TestGetNextKey_11();            //�ǿ�ֵ����һ��key

    /////////////////////////section������////////////////////////////////////////
    void TestGetNextKey_12();            //��ֵ����һ��key
    void TestGetNextKey_13();            //�ǿ�ֵ����һ��key
};

#endif // GetNextKeyTest_h__