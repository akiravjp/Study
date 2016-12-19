//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetBoolTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-3 14:37
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetBoolTest_h__
#define _GetBoolTest_h__

#include "cppunit/extensions/HelperMacros.h"

#pragma warning(disable:4996)

class KGT_GetBoolTest : public CppUnit::TestFixture   
{
    CPPUNIT_TEST_SUITE(KGT_GetBoolTest);

    CPPUNIT_TEST(TestGetBool_01);
    CPPUNIT_TEST(TestGetBool_02);
    CPPUNIT_TEST(TestGetBool_03);
    CPPUNIT_TEST(TestGetBool_04);
    CPPUNIT_TEST(TestGetBool_05);
    CPPUNIT_TEST(TestGetBool_06);
    CPPUNIT_TEST(TestGetBool_07);
    CPPUNIT_TEST(TestGetBool_08);
    CPPUNIT_TEST(TestGetBool_09);
    CPPUNIT_TEST(TestGetBool_10);
    CPPUNIT_TEST(TestGetBool_11);
    CPPUNIT_TEST(TestGetBool_12);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////�����ļ����������м�¼///////////////////////
    void TestGetBool_01();        //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetBool_02();        //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetBool_03();        //�����lpSection��lpKeyNameΪ�գ�����������Ϊ��
    void TestGetBool_04();        //�����lpSection���ڣ��������lpKeyName������
    void TestGetBool_05();        //�����lpSection������
    void TestGetBool_06();        //valueֵΪȫ��д��"YES",��"TRUE"(��"NO","FALSE")
    void TestGetBool_07();        //valueֵΪȫСд��"yes",��"true"(��"no","false")
    void TestGetBool_08();        //valueֵΪ��Сд��ϵ�"yEs",��"True"(��"No","False")
    void TestGetBool_09();        //valueֵ������Ч�ؼ���
    void TestGetBool_10();        //valueֵΪ��ֵ

    /////////////////////////////�����ļ���������û�м�¼///////////////////////
    void TestGetBool_11();        //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetBool_12();        //�����lpSection��lpKeyNameΪ�ǿ�ֵ
};

#endif // GetBoolTest_h__