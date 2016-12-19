#ifndef _BISHOP_PAYSYS_H_
#define _BISHOP_PAYSYS_H_

#include "../ProtocolBasic.h"
#include "AccountLoginDef.h"

enum B2P_PROTOCOL_ID // Bishop ==> Paysys
{
    B2P_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2P_BISHOP_IDENTITY_VERIFY = 36,           // Bishop�������״ε�½�����֤, ref : KServerAccountUserLoginInfo��ע�⣬����Paysys�ǣ�KServerAccountUserLoginInfo2
    B2P_BISHOP_RECONNECT_IDENTITY_VERIFY = 37, // Bishop�������������֤, ref : ͬB2P_BISHOP_IDENTITY_VERIFY
    B2P_BISHOP_LOGOUT = 39,                    // Bishop�˳��� ref : KServerAccountUserLoginInfo
    B2P_PLAYER_IDENTITY_VERIFY = 33,           // ��������֤, ref : KAccountUserLoginInfo
    B2P_PLAYER_ENTER_GAME = 34,                // ��ҽ�����Ϸ, ref : KAccountUser
    B2P_PLAYER_LEAVE_GAME = 35,                // ����뿪��Ϸ, ref : KAccountUserLogout
    B2P_EXT_POINTS_OPERATION = 40,             // ���ӵ����, ref : KAccountUserChangeExtPoint
    B2P_CLEANUP_ACCOUNT_FREE_TIME = 42,        // ����������ʱ��, ref : TRYOUT_TIMEOUT_ASK
    B2P_PING = 112,                            // ping��, ref : PING_COMMAND
    B2P_USE_SPREADER_CDKEY = 50,               // ���ʹ���ƹ�Աcdkey, ref : TAccountCDKEY

    // IB Mode.
    B2P_IB_PLAYER_BUY_ITEM = 60,               // �����IBģʽ�¹�����Ʒ��
    B2P_IB_PLAYER_USE_ITEM = 61,               // �����IBģʽ��ʹ����Ʒ��
    B2P_IB_PLAYER_IDENTITY_VERIFY = 62,        // �����IBģʽ�µĵ�����֤��
    B2P_PLAYER_SET_CHARGE_FLAG    = 63,        // �������ChargeFlag
    B2P_PLAYER_EXCHANGE = 65,                  // ��Ҷһ�
    B2P_PLAYER_TRANSFER = 66,                  // ���ת��
    B2P_PLAYER_QUERY_TRANSFER = 67,            // ���ת�ʲ�ѯ
    B2P_PLAYER_FREEZE_FEE = 68,                // ��Ҷ������
    B2P_GAMEWORLD_2_PAYSYS = 69,               // ͨ��Э��: ��Ϸ���絽Paysys������ 
    
    B2P_CHANGE_ACCOUNT_STATE = 70,
  
    B2P_IB_PLAYER_BUY_MULTI_ITEM = 71,         // �����IBģʽ�¹�������Ʒ
    B2P_IB_PLAYER_USE_MULTI_ITEM = 72,         // �����IBģʽ��ʹ�ö����Ʒ
    
    B2P_PLAYER_INFO    = 73,
    
    B2P_PLAYER_PASSPOD_VERIFY = 74,            // �ܱ���֤  
    
    B2P_IB_PLAYER_BUY_ITEM_SD = 75,            // �����IBģʽ�¹�����Ʒ��
    B2P_IB_PLAYER_BUY_MULTI_ITEM_SD = 76,      // �����IBģʽ�¹�������Ʒ

    B2P_PLAYER_IDENTITY_VERIFY_SD = 77,        // ʢ�����ר�еĵ�����֤, ���ذ���Ȼʹ��P2B_PLAYER_IDENTITY_VERIFY_RESULT
    B2P_IB_PLAYER_IDENTITY_VERIFY_SD = 78,     // ʢ�������IBģʽ�µĵ�����֤, ���ذ�ʹ��P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT
    B2P_GET_ZONE_CHARGE_FLAG = 79,             // ��ȡ�������������շѱ�־

    B2P_PLAYER_EXCHANGE_EX = 80,               // ��Ҽ���Э��

    B2P_PLAYER_PASSPOD_VERIFY_EX = 81,         // �ܱ���֤��չ��֧���µ��ܱ���֤

    B2P_IB_PLAYER_IDENTITY_VERIFY_EX = 82,     // ������IB���У�֧�ּ���
    B2P_PLAYER_INFO_EX = 85,                   // ���������У�֧�ּ���

	B2P_IB_PLAYER_IDENTITY_VERIFY_SD_EX = 86   // ʢ�������У�����������
};



enum P2B_PROTOCOL_ID // Paysys ==> Bishop
{
    P2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    P2B_BISHOP_IDENTITY_VERIFY_RESULT = 36,     // Bishop��½Paysys��У����, ref : KAccountUserReturnVerify
    P2B_PLAYER_IDENTITY_VERIFY_RESULT = 33,     // �����֤���, ref : KAccountUserReturnExt
    P2B_EXT_POINTS_OPERATION_RESULT = 40,       // �޸ĸ��ӵ�Ľ������, ref : KAccountUserReturnExt2
    P2B_LEAVE_GAME_RESPOND = 35,                // B2P_PLAYER_LEAVE_GAMEЭ�����Ӧ���, Ŀǰ����
    P2B_ACCOUNT_FREE_TIME_CLEANING_RESULT = 64, // ����������ʱ��Ĳ������, ref : TRYOUT_TIMEOUT_ANS
    P2B_PING = 130,                             // ��ping, ref : PING_COMMAND
    P2B_USE_SPREADER_CDKEY_RESULT = 50,         // ���ʹ���ƹ�Աcdkey�ķ��ؽ��, ref : TAccountCDKEYRet

    // IB Mode.
    P2B_IB_PLAYER_BUY_ITEM_RESULT = 60,         // �����IBģʽ�¹�����Ʒ�Ļ�Ӧ����
    P2B_IB_PLAYER_USE_ITEM_RESULT = 61,         // �����IBģʽ��ʹ����Ʒ�Ļ�Ӧ����
    P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT = 62,  // �����IBģʽ�µ�����֤�Ļ�Ӧ����
    P2B_PLAYER_SET_CHARGE_FLAG_RESULT    = 63,  // �������ChargeFlag
    P2B_PLAYER_EXCHANGE = 65,                   // ��Ҷһ�
    P2B_PLAYER_TRANSFER = 66,                   // ���ת��
    P2B_PLAYER_QUERY_TRANSFER = 67,             // ���ת�ʲ�ѯ
    P2B_PLAYER_FREEZE_FEE = 68,                 // ��Ҷ������
    P2B_PAYSYS_2_GAMEWORLD = 69,                // ͨ��Э��: Paysys����Ϸ����Ļ�Ӧ��

    P2B_CHANGE_ACCOUNT_STATE = 70,

    P2B_IB_PLAYER_BUY_MULTI_ITEM_RESULT = 71,   // �����IBģʽ�¹�������Ʒ�Ļ�Ӧ��
    P2B_IB_PLAYER_USE_MULTI_ITEM_RESULT = 72,   // �����IBģʽ��ʹ�ö����Ʒ�Ļ�Ӧ��
    
    P2B_PLAYER_INFO_RESULT    = 73,
    
    P2B_PLAYER_PASSPOD_VERIFY = 74,              // �ܱ���֤ 

    P2B_IB_PLAYER_BUY_ITEM_RESULT_SD = 75,       // ʢ�������IBģʽ�¹�����Ʒ�Ļ�Ӧ��
    P2B_IB_PLAYER_BUY_MULTI_ITEM_RESULT_SD = 76, // ʢ�������IBģʽ�¹�������Ʒ�Ļ�Ӧ��

    P2B_GET_ZONE_CHARGE_FLAG = 79,               // ��ȡ�������������շѱ�־�Ļ�Ӧ��
    P2B_PLAYER_EXCHANGE_EX = 80,                 // ��Ҽ���Э���Ӧ��
    P2B_PLAYER_PASSPOD_VERIFY_EX = 81,           // �ܱ���֤��Э��
    P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT_EX = 82,// �����IBģʽ�µ�����֤�Ļ�Ӧ����ref : KAccountUserReturnExtIB2
 
    P2B_PLAYER_INFO_RESULT_EX = 85               // ��ȡ�����Ϣ����������չ��ref ��KAccountUserInfoRetExt
};

#endif

