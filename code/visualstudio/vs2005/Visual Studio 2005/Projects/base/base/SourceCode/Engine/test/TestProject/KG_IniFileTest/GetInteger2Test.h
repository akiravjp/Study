//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetInteger2Test.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 14:40
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetInteger2Test_h__
#define _GetInteger2Test_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetInteger2Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetInteger2Test);

    CPPUNIT_TEST(TestGetInteger2_01);
    CPPUNIT_TEST(TestGetInteger2_02);
    CPPUNIT_TEST(TestGetInteger2_03);
    CPPUNIT_TEST(TestGetInteger2_04);
    CPPUNIT_TEST(TestGetInteger2_05);
    CPPUNIT_TEST(TestGetInteger2_06);
    CPPUNIT_TEST(TestGetInteger2_07);
    CPPUNIT_TEST(TestGetInteger2_08);
    CPPUNIT_TEST(TestGetInteger2_09);
    CPPUNIT_TEST(TestGetInteger2_10);
    CPPUNIT_TEST(TestGetInteger2_11);
    CPPUNIT_TEST(TestGetInteger2_12);
    CPPUNIT_TEST(TestGetInteger2_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////�����ļ����������м�¼///////////////////////
    void TestGetInteger2_01();           //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetInteger2_02();           //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetInteger2_03();           //�����lpSection��lpKeyName��Ϊ�գ�����������Ϊ��
    void TestGetInteger2_04();           //�����lpSection���ڣ��������lpKeyName������
    void TestGetInteger2_05();           //�����lpSection������
    void TestGetInteger2_06();           //�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����1��ֵ
    void TestGetInteger2_07();           //�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����2����ֵ
    void TestGetInteger2_08();           //�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����3��ֵ
    void TestGetInteger2_09();           //�����lpSection���ڣ��������lpKeyName����,value��Ϊ��,����2����ֵ
    void TestGetInteger2_10();           //�����lpSection���ڣ��������lpKeyName����,valueΪ��
    void TestGetInteger2_11();           //�����lpSection���ڣ��������lpKeyName����,valueΪ�������ַ���

    /////////////////////////////�����ļ���������û�м�¼///////////////////////
    void TestGetInteger2_12();           //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetInteger2_13();           //�����lpSection��lpKeyNameΪ�ǿ�ֵ
};

#endif // GetInteger2Test_h__