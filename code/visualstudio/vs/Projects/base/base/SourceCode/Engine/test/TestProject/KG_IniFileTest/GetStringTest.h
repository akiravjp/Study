//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetStringTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 17:07
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetStringTest_h__
#define _GetStringTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetStringTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetStringTest);

    CPPUNIT_TEST(TestGetString_01);
    CPPUNIT_TEST(TestGetString_02);
    CPPUNIT_TEST(TestGetString_03);
    CPPUNIT_TEST(TestGetString_04);
    CPPUNIT_TEST(TestGetString_05);
    CPPUNIT_TEST(TestGetString_06);
    CPPUNIT_TEST(TestGetString_07);
    CPPUNIT_TEST(TestGetString_08);
    CPPUNIT_TEST(TestGetString_09);
    CPPUNIT_TEST(TestGetString_10);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void TestGetString_01();        //������ȷ�ԣ�default=null
    /////////////////////////////////�����ļ����������м�¼/////////////////
    void TestGetString_02();        //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetString_03();        //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetString_04();        //�����lpSection��lpKeyName��Ϊ�գ�����������Ϊ��
    void TestGetString_05();        //�����lpSection���ڣ��������lpKeyName������
    void TestGetString_06();        //�����lpSection������
    void TestGetString_07();        //�����lpSection���ڣ��������lpKeyName���ڣ�value����Ϊ0
    void TestGetString_08();        //�����lpSection���ڣ��������lpKeyName���ڣ�value���Ȳ�Ϊ0

    /////////////////////////////////�����ļ���������û�м�¼/////////////////
    void TestGetString_09();        //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetString_10();        //�����lpSection��lpKeyNameΪ�ǿ�ֵ
};

#endif // GetStringTest_h__