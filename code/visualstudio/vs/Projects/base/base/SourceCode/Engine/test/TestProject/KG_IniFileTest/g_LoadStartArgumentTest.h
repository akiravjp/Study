//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   g_LoadStartArgumentTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-17 10:26
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _g_LoadStartArgumentTest_H__
#define _g_LoadStartArgumentTest_H__

#include "cppunit/extensions/HelperMacros.h"

class KGT_g_LoadStartArgumentTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_g_LoadStartArgumentTest);

    CPPUNIT_TEST(Test_g_LoadStartArgument_01);
    CPPUNIT_TEST(Test_g_LoadStartArgument_02);
    CPPUNIT_TEST(Test_g_LoadStartArgument_03);
    CPPUNIT_TEST(Test_g_LoadStartArgument_04);
    CPPUNIT_TEST(Test_g_LoadStartArgument_05);
    CPPUNIT_TEST(Test_g_LoadStartArgument_06);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    //////////////////////////////������û��--section����////////////////////////
    void Test_g_LoadStartArgument_01();         //FileNameָʾ���ļ�������
    void Test_g_LoadStartArgument_02();         //FileNameָʾ���ļ�����,����û������
    void Test_g_LoadStartArgument_03();         //FileNameָʾ���ļ�����,��������

    //////////////////////////////��������--section����////////////////////////
    void Test_g_LoadStartArgument_04();         //FileNameָʾ���ļ�������
    void Test_g_LoadStartArgument_05();         //FileNameָʾ���ļ�����,����û������
    void Test_g_LoadStartArgument_06();         //FileNameָʾ���ļ�����,��������
private:

};

#endif //_g_LoadStartArgumentTest_H__