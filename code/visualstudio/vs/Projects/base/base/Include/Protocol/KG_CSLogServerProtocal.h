////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_LogServerProtocal.h
//  Version     : 1.0
//  Creator     : Wu Caizhong
//  Create Date : 2008-6-13 11:21:52
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_LOGSERVERPROTOCAL_H_
#define _INCLUDE_KG_LOGSERVERPROTOCAL_H_

#include "ProtocolBasic.h"

#pragma	pack(push, 1)

////////////////////////////////////////////////////////////////////////////////
const unsigned KG_LOG_SERVER_MAX_PACKET_SIZE = 4096;

enum KG_LOG_SERVER_C2S_PROTOCAL_ID
{
    LOGC2S_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,
    LOGC2S_LOG_LOGIN,              // must be first command, ref: KGCSLogServerLogin
    LOGC2S_LOG_ITEM_OPERATION,     // ref: KGItemLog
    LOGC2S_LOG_PLAYER_ACTION       // ref: KGPlayerActionLog
};

enum KG_LOG_SERVER_S2C_PROTOCAL_ID
{
    LOGS2C_PING_RESULT = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,
    LOGC2S_LOG_LOGIN_RESULT,            // ref: TProcessData 
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    LOGS2C_LOG_ITEM_OPERATION_RESULT,   // ref: TProcessData
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    LOGS2C_LOG_PLAYER_ACTION_RESULT     // ref: TProcessData
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
};

////////////////////////////////////////////////////////////////////////////////
struct KGCSLogServerLogin : tagProtocolHeader2
{
    char szGatewayName[_NAME_LEN];
};

//////////////////////////////////////////////////////////////////////////
const unsigned LOG_ITEM_RESTORE_DATA_MAX_SIZE   = 1024;
const unsigned LOG_COMMENT_MAX_SIZE             = 2048;

enum LOG_RETURN_CODE
{
    LOG_RETURN_FAILED  = 0,
    LOG_RETURN_SUCCESS = 1,
    LOG_RETURN_FILTER  = 2
};

enum ITEM_OPERATION_TYPE
{
    ITEM_OPERATION_TYPE_IN  = 0, // �����Ʒ
    ITEM_OPERATION_TYPE_OUT = 1, // ʧȥ��Ʒ

    ITEM_OPERATION_TYPE_COUNT
};

struct KGItemLog : tagProtocolHeader2
{
    ITEM_OPERATION_TYPE eOperationType;
    char                szAccountName[_NAME_LEN];
    char                szRoleName[_NAME_LEN];
    unsigned long long  ullItemID;               // ��ƷID������Ψһ��ʶһ���ض�����Ʒ
    char                szItemName[_NAME_LEN];
    unsigned            uItemValue;              // ��Ʒ��ֵ��
    unsigned            uItemRestoreDataSize;    // include string's terminal '\0', max size is LOG_ITEM_RESTORE_DATA_MAX_SIZE
    unsigned            uCommentSize;            // include string's terminal '\0', max size is LOG_COMMENT_MAX_SIZE, set to 0 for none comment
    unsigned char       pbyData[1];       // following data size is :uItemRestoreDataSize + uCommentSize
};

//////////////////////////////////////////////////////////////////////////
enum PLAYER_ACTION_TYPE
{
    PLAYER_ACTION_PLAYER_LEVELUP        = 0,    // �������
    PLAYER_ACTION_PLAYER_LEVELDOWN      = 1,    // ��ҽ���

    PLAYER_ACTION_JOIN_FACTION          = 2,    // ��������
    PLAYER_ACTION_LEAVE_FACTION         = 3,    // �˳�����

    PLAYER_ACTION_JOIN_TONG             = 4,    // �������
    PLAYER_ACTION_LEAVE_TONG            = 5,    // �Ƴ�����
    PLAYER_ACTION_KICK_TONG             = 6,    // �߳�����
    PLAYER_ACTION_FIGURECHANGE_TONG     = 7,    // ְλ���

    PLAYER_ACTION_ACCEPT_TASK           = 8,    // ��������
    PLAYER_ACTION_FINISH_TASK           = 9,    // �������
    PLAYER_ACTION_CANCEL_TASK           = 10,   // ȡ������

    PLAYER_ACTION_ACCEPT_AWARD          = 11,   // ��ȡ����
    PLAYER_ACTION_ACCEPT_REPAIR         = 12,   // ��ȡ����

    PLAYER_ACTION_LOGIN                 = 13,   // ��¼
    PLAYER_ACTION_LOGOUT                = 14,   // ��������
    PLAYER_ACTION_BEGIN_OFFLIVE         = 15,   // �����йܿ�ʼ
    PLAYER_ACTION_END_OFFLIVE           = 16,   // �����йܽ���
    PLAYER_ACTION_KICK_OFFLIVE          = 17,   // �����й��ߺ�

    PLAYER_ACTION_CHOOSE_SKILLROUTE     = 18,   // ѡ����·��
    PLAYER_ACTION_SKILL_LEVELUP         = 19,   // ��������
    PLAYER_ACTION_RESET_SKILL           = 20,   // ϴ��

    PLAYER_ACTION_TRADE                 = 21,   // ����

    PLAYER_ACTION_MARRY                 = 22,   // ���
    PLAYER_ACTION_UNMARRY               = 23,   // ���

    PLAYER_ACTION_JOIN_ACTIVITY         = 24,   // �μӻ
    PLAYER_ACTION_LEAVE_ACTIVITY        = 25,   // �����

    PLAYER_ACTION_DELETE_ROLE           = 26,   // ɾ����ɫ
    PLAYER_ACTION_RESTORE_ROLE          = 27,   // �ָ���ɫ
    PLAYER_ACTION_FREEZE_ROLE           = 28,   // �����ɫ
    PLAYER_ACTION_UNFREEZE_ROLE         = 29,   // �����ɫ
    PLAYER_ACTION_RENAME_ROLE           = 30,   // ��ɫ����

    PLAYER_ACTION_SKILLPOINT_CHANGE     = 31,   // ���ܵ�仯
    PLAYER_ACTION_PROPPOINT_CHANGE      = 32,   // Ǳ�ܵ�仯
    PLAYER_ACTION_GATHERPOINT_CHANGE    = 33,   // ����ֵ�仯
    PLAYER_ACTION_MAKEPOINT_CHANGE      = 34,   // ����ֵ�仯
    
    PLAYER_ACTION_TYPE_COUNT // must be the last one
};

struct KGPlayerActionLog : public tagProtocolHeader2
{
    unsigned            uActionLevel;   // ��Ϊ��Ҫ�̶�
    PLAYER_ACTION_TYPE  eActionType;
    char                szActionTarget[_NAME_LEN];  // ��ΪĿ�꣬��ĳ���������������
    char                szAccountName[_NAME_LEN];
    char                szRoleName[_NAME_LEN]; 
    unsigned            uCommentSize;    // include string's terminal '\0', max size is LOG_COMMENT_MAX_SIZE, set to 0 for none comment
    unsigned char       pbyData[1]; // following data size is uCommentSize
};

#pragma	pack(pop)

#endif //_INCLUDE_KG_LOGSERVERPROTOCAL_H_
