//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetIntegerTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 11:09
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetIntegerTest_h__
#define _GetIntegerTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetIntegerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetIntegerTest);

    CPPUNIT_TEST(TestGetInteger_01);
    CPPUNIT_TEST(TestGetInteger_02);
    CPPUNIT_TEST(TestGetInteger_03);
    CPPUNIT_TEST(TestGetInteger_04);
    CPPUNIT_TEST(TestGetInteger_05);
    CPPUNIT_TEST(TestGetInteger_06);
    CPPUNIT_TEST(TestGetInteger_07);
    CPPUNIT_TEST(TestGetInteger_08);
    CPPUNIT_TEST(TestGetInteger_09);
    CPPUNIT_TEST(TestGetInteger_10);
    CPPUNIT_TEST(TestGetInteger_11);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////�����ļ����������м�¼///////////////////////
    void TestGetInteger_01();           //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetInteger_02();           //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetInteger_03();           //�����lpSection��lpKeyName��Ϊ�գ�����������Ϊ��
    void TestGetInteger_04();           //�����lpSection���ڣ��������lpKeyName������
    void TestGetInteger_05();           //�����lpSection������
    void TestGetInteger_06();           //�����lpSection���ڣ��������lpKeyName����,valueΪ�����ַ�������Ϊ����
    void TestGetInteger_07();           //�����lpSection���ڣ��������lpKeyName����,valueΪ�����ַ�������Ϊ����
    void TestGetInteger_08();           //�����lpSection���ڣ��������lpKeyName����,valueΪ��ֵ
    void TestGetInteger_09();           //�����lpSection���ڣ��������lpKeyName����,valueΪ�������ַ���

    /////////////////////////////�����ļ���������û�м�¼///////////////////////
    void TestGetInteger_10();           //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetInteger_11();           //�����lpSection��lpKeyNameΪ�ǿ�ֵ
};

#endif // GetIntegerTest_h__