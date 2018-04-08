//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetMultiIntegerTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 15:54
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetMultiIntegerTest_h__
#define _GetMultiIntegerTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetMultiIntegerTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetMultiIntegerTest);
    
    CPPUNIT_TEST(TestGetMultiInteger_01);
    CPPUNIT_TEST(TestGetMultiInteger_02);
    CPPUNIT_TEST(TestGetMultiInteger_03);
    CPPUNIT_TEST(TestGetMultiInteger_04);
    CPPUNIT_TEST(TestGetMultiInteger_05);
    CPPUNIT_TEST(TestGetMultiInteger_06);
    CPPUNIT_TEST(TestGetMultiInteger_07);
    CPPUNIT_TEST(TestGetMultiInteger_08);
    CPPUNIT_TEST(TestGetMultiInteger_09);
    CPPUNIT_TEST(TestGetMultiInteger_10);
    CPPUNIT_TEST(TestGetMultiInteger_11);
    CPPUNIT_TEST(TestGetMultiInteger_12);
    CPPUNIT_TEST(TestGetMultiInteger_13);


    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void teatDown();
public:
    /////////////////////////////�����ļ����������м�¼///////////////////////
    void TestGetMultiInteger_01();           //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetMultiInteger_02();           //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetMultiInteger_03();           //�����lpSection��lpKeyName��Ϊ�գ�����������Ϊ��
    void TestGetMultiInteger_04();           //�����lpSection���ڣ��������lpKeyName������
    void TestGetMultiInteger_05();           //�����lpSection������
    void TestGetMultiInteger_06();           //�����nCount<=0��nCount>INI_MAX_SUPPORT_MULTI_VALUE_COUNT
    void TestGetMultiInteger_07();           //�����lpSection���ڣ��������lpKeyName����,value�ĸ���С�������nCount
    void TestGetMultiInteger_08();           //�����lpSection���ڣ��������lpKeyName����,value�ĸ������������nCount
    void TestGetMultiInteger_09();           //�����lpSection���ڣ��������lpKeyName����,value�ĸ������������nCount
    void TestGetMultiInteger_10();           //�����lpSection���ڣ��������lpKeyName����,valueΪ��ֵ
    void TestGetMultiInteger_11();           //�����lpSection���ڣ��������lpKeyName����,valueΪ�������ַ���

    /////////////////////////////�����ļ���������û�м�¼///////////////////////
    void TestGetMultiInteger_12();           //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetMultiInteger_13();           //�����lpSection��lpKeyNameΪ�ǿ�ֵ
};

#endif // GetMultiIntegerTest_h__