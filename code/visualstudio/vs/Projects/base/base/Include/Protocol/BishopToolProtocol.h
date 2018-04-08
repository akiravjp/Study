#ifndef _BISHOP_TOOL_PROTOCOL_H_
#define _BISHOP_TOOL_PROTOCOL_H_

#include "AccountLoginDef.h"

#define BISHOP_TOOL_PROTOCOL_VERSION  1

// Tools --> bishop protocols 
enum T2B_PROTOCOL_ID
{
    T2B_PROTOCOL_BEGIN,
    T2B_LOGIN,                       // ����, ref : tagSEXYLogin
    T2B_LOGOUT,                      // �ǳ�, ref : tagSEXYLogout
    T2B_VIRTUAL_CURRENCY_COUNT,      // �����������, ref : tagVirtualCurrencyCount
    T2B_PROTOCOL_END,
};

#pragma	pack(push, 1)

struct tagToolsLogin : tagProtoHeader
{
    unsigned int    uProtocolVersion;
    unsigned int    uReserve[32];
};

struct tagToolsLogout : tagProtoHeader
{
};

struct tagVirtualCurrencyCount : tagProtoHeader
{
    int         nVirtualCurrencyTypeCount;     // ����������͵�����

#ifdef WIN32
    __int64     nllVirtualCurrencyCount[8];
#else
    long long   nllVirtualCurrencyCount[8];
#endif
};

#pragma pack(pop)

#endif
