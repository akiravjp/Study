//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   g_OpenCombinatorialIniFileTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-16 11:38
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _g_OpenCombinatorialIniFileTest_H__
#define _g_OpenCombinatorialIniFileTest_H__

#include "cppunit/extensions/HelperMacros.h"

class KGT_g_OpenCombinatorialIniFileTest : public CppUnit::TestFixture
{ 
    CPPUNIT_TEST_SUITE(KGT_g_OpenCombinatorialIniFileTest);

    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_01);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_02);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_03);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_04);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_05);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_06);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_07);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_08);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_09);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_10);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_11);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_12);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void Test_g_OpenCombinatorialIniFile_01();          //�������ļ�û�м�¼��ini�ļ�������
    void Test_g_OpenCombinatorialIniFile_02();          //�������ļ��м�¼��ini�ļ�û������
    void Test_g_OpenCombinatorialIniFile_03();          //�������ļ�û�м�¼��ini�ļ�û������
    void Test_g_OpenCombinatorialIniFile_04();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section
    void Test_g_OpenCombinatorialIniFile_05();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section,ini�ļ���ֻ��section��û��key
    void Test_g_OpenCombinatorialIniFile_06();          //�������ļ���ini�ļ��������ݣ�2���в�ͬ��section
    void Test_g_OpenCombinatorialIniFile_07();          //�������ļ���ini�ļ��������ݣ�2���в�ͬ��section,ini�ļ���ֻ��section,û��key
    void Test_g_OpenCombinatorialIniFile_08();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key
    void Test_g_OpenCombinatorialIniFile_09();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key
    void Test_g_OpenCombinatorialIniFile_10();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key,��ͬ��value
    void Test_g_OpenCombinatorialIniFile_11();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key,��ͬ��value
    void Test_g_OpenCombinatorialIniFile_12();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key,��ͬ��value,�����е�value=""
    void Test_g_OpenCombinatorialIniFile_13();          //�������ļ���ini�ļ��������ݣ�2������ͬ��section����ͬ��key,��ͬ��value,ini�ļ���value=""
private:

};

#endif //_g_OpenCombinatorialIniFileTest_H__