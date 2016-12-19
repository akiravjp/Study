//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetStructTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 17:30
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetStructTest_h__
#define _GetStructTest_h__

#include "cppunit/extensions/HelperMacros.h"
#include "time.h"

typedef struct MAN
{
    int nAge;
    char szName[32];
} MAN;
typedef struct PERSON    
{
    int nAge;
    char szName[32];
    long lMoney;
    bool bMan;
    float fScore;
    tm    dBirthday;
    MAN   man;
} TEST_STRUCT;

class KGT_GetStructTest : public CppUnit::TestFixture  
{
    CPPUNIT_TEST_SUITE(KGT_GetStructTest);

    CPPUNIT_TEST(TestGetStruct_01);
    CPPUNIT_TEST(TestGetStruct_02);
    CPPUNIT_TEST(TestGetStruct_03);
    CPPUNIT_TEST(TestGetStruct_04);
    CPPUNIT_TEST(TestGetStruct_05);
    CPPUNIT_TEST(TestGetStruct_06);
    CPPUNIT_TEST(TestGetStruct_07);
    CPPUNIT_TEST(TestGetStruct_08);
    CPPUNIT_TEST(TestGetStruct_09);
    CPPUNIT_TEST(TestGetStruct_10);
    CPPUNIT_TEST(TestGetStruct_11);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////�����ļ����������м�¼///////////////////////
    void TestGetStruct_01();        //�����lpSectionΪ�գ�����������Ϊ��
    void TestGetStruct_02();        //�����lpKeyNameΪ�գ�����������Ϊ��
    void TestGetStruct_03();        //�����lpSection��lpKeyNameΪ�գ�����������Ϊ��
    void TestGetStruct_04();        //�����lpSection���ڣ��������lpKeyName������
    void TestGetStruct_05();        //�����lpSection������
    void TestGetStruct_06();        //struct�ĳ���*2=value�ĳ���,ֵ����
    void TestGetStruct_07();        //struct�ĳ���*2=value�ĳ���,��value��ֵ����0-f������ַ���
    void TestGetStruct_08();        //struct�ĳ���*2!=value�ĳ���
    void TestGetStruct_09();        //struct�ĳ���*2=value�ĳ���,��value��ֵΪ��ֵ

    /////////////////////////////�����ļ���������û�м�¼///////////////////////
    void TestGetStruct_10();        //�����lpSection��lpKeyNameΪ��ֵ
    void TestGetStruct_11();        //�����lpSection��lpKeyNameΪ�ǿ�ֵ
private:
    TEST_STRUCT m_TestStruct;
};

#endif // GetStructTest_h__