//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetNextSectionTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-6-30 14:36
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetNextSectionTest_h__
#define _GetNextSectionTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetNextSectionTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetNextSectionTest);

    CPPUNIT_TEST(TestGetNextSection_01);
    CPPUNIT_TEST(TestGetNextSection_02);
    CPPUNIT_TEST(TestGetNextSection_03);
    CPPUNIT_TEST(TestGetNextSection_04);
    CPPUNIT_TEST(TestGetNextSection_05);
    CPPUNIT_TEST(TestGetNextSection_06);
    CPPUNIT_TEST(TestGetNextSection_07);
    CPPUNIT_TEST(TestGetNextSection_08);
    CPPUNIT_TEST(TestGetNextSection_09);
    CPPUNIT_TEST(TestGetNextSection_10);
    CPPUNIT_TEST(TestGetNextSection_11);
    
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////////KG_Ini_SectionMap�ж�����¼////////////////////////////
    void TestGetNextSection_01();           //��ֵ����һ��section
    void TestGetNextSection_02();           //��һ����¼����һ��section
    void TestGetNextSection_03();           //�м�һ����¼����һ��section(�������һ��section)
    void TestGetNextSection_04();           //�����ڶ�����¼����һ��section
    void TestGetNextSection_05();           //���һ����¼����һ��section
    void TestGetNextSection_06();           //�����ڵļ�¼����һ��section
    
    /////////////////////////////KG_Ini_SectionMapֻ��1����¼///////////////////////////
    void TestGetNextSection_07();           //��ֵ����һ��section
    void TestGetNextSection_08();           //���ڵļ�¼����һ��section
    void TestGetNextSection_09();           //�����ڵļ�¼����һ��section

    ////////////////////////////KG_Ini_SectionMapû�м�¼///////////////////////////////
    void TestGetNextSection_10();           //��ֵ����һ��section
    void TestGetNextSection_11();           //�ǿ�ֵ����һ��section
};

#endif // GetNextSectionTest_h__