/**********************************************************************
* Դ��������: futu_data_types.h
* �������Ȩ: �������ӹɷ����޹�˾
* ϵͳ����  : 06�汾�ڻ�ϵͳ
* ģ������  : �����ڻ��ܱ߽ӿ�
* ����˵��  : �ܱ߽ӿڳ����������Ͷ���
* ��    ��  : xdx
* ��������  : 20110315
* ��    ע  : �������Ͷ���   
* �޸���Ա  ��
* �޸�����  ��
* �޸�˵��  ��20110315 ����
**********************************************************************/
#ifndef _FUTU_DATA_TYPES_H_
#define _FUTU_DATA_TYPES_H_

/**********************************************************************/
/*                                                                    */
/*                                 ��������                           */
/*                                                                    */
/**********************************************************************/
//����SDK�İ汾��Ϣ
//ÿ�θ���SDK,��ֵ�����,�ͻ���������˰汾������,��ʹͷ�ļ������SDK��ƥ��
//������ο�ʾ��demo
#define HSFUSDK_VERSION     0x10000010
#define HSFUSDK_VERSTRING   "V1.0.0.10" 

//�������ӷ�������
const int SERVICE_TYPE_TRADE = 1;//���׷���
const int SERVICE_TYPE_QUOTE = 2;//����ر�����

//���鳣������(ȫ�г�����Ķ��Ĵ���)
const char* const ALLWWW = "ALLWWW";

//��������
enum REGType
{
	NAType          = -1,     // δ֪����
	SingleCode      = 0,      // ��������
	RspReport       = 1,      // ί�лر�
	CombinCode      = 2,      // �������
	OnlineMsg       = 3       // ������Ϣ
};

//����ʽ(���Ļ��˶�) 
enum REGAction
{
	NAAction        = -1,     // δ֪����ʽ
	Subscription    = 0,      // ����ˢ��(��Ҫָ����)
	CxlAll          = 1,      // ȡ��ȫ���Ķ���
	CxlFlag         = 2,      // �����ƶ����Ͷ���
	Snapshot        = 3       // ��ѯ����(��Ҫָ����)
};

//���ӵ�״̬
enum CONState
{
	Uninitialized   = -1,     // ����δ��ʼ��
	Disconnected	= 0x0000, // δ����
	Connecting		= 0x0001, // socket��������
	Connected		= 0x0002, // socket������
	SafeConnecting	= 0x0004, // ���ڽ�����ȫ����
	SafeConnected	= 0x0008, // �ѽ�����ȫ����
	Registering		= 0x0010, // ��ע��
	Registered		= 0x0020, // ��ע��
	Rejected		= 0x0040  // ���ܾ�,�����ر�
};

//��Ϣģʽ����(����Ӧ�����Ͷ���)
enum FUTU_MSG_MODE
{
	MSG_MODE_UNKNOWN = -1, //δ֪��Ϣģʽ
	MSG_MODE_REQUEST = 0,  //��ʾ��������Ϣ
	MSG_MODE_ANSWER  = 1   //��ʾ��Ӧ����Ϣ
};

//�ڻ���Ϣ����(ע�⣺�Կͻ����Ŵ�ͷ�ļ���ʱ����Ҫ���β�����Ϣ����)
enum FUTU_MSG_TYPE
{
	MSG_TYPE_UNKNOWN               = -1, //δ֪��Ϣ����

	MSG_TYPE_USER_LOGIN            = 100,//�û���¼
	MSG_TYPE_USER_LOGOUT           = 101,//UFT�ͻ�ע��
	MSG_TYPE_CONFIRM_BILL          = 102,//�ͻ�ȷ���˵�
	MSG_TYPE_CHECK_CONTRACT_CODE   = 103,//����Լ����(����)
	MSG_TYPE_CHECK_ENTRUST_PRICE   = 104,//���ί�м۸�
	MSG_TYPE_NEW_SINGLE_ORDER      = 105,//ί���µ�
	MSG_TYPE_CANCEL_ORDER          = 106,//ί�г���
	MSG_TYPE_BANK_TRANSFER         = 107,//����ת��
	MSG_TYPE_MODIFY_PASSWORD       = 108,//�ͻ��޸�����

	//20110822 luyj �������ί�� �޸ĵ���:20110819035
	MSG_TYPE_CHECK_COMBIN_CODE     = 109,//�����Ϻ�Լ����
	MSG_TYPE_NEW_COMBIN_ORDER      = 110,//���ί��ȷ��
	//20110822 end

	MSG_TYPE_GET_TRADING_CODE      = 200,//���ױ����ѯ
	MSG_TYPE_GET_PROFIT            = 201,//�ڻ��ͻ��ʽ�Ȩ���ѯ
	MSG_TYPE_GET_HOLDSINFO         = 202,//�ֲֲ�ѯ
	MSG_TYPE_GET_ENTRUST_ORDERS    = 203,//ί�в�ѯ
	MSG_TYPE_GET_TRANS_DETAIL      = 204,//�ɽ���ϸ��ѯ
	MSG_TYPE_GET_FUNDJOUR          = 205,//��ʷ�ʽ���ˮ��ѯ
	MSG_TYPE_GET_FUND_HISTRANSJOUR = 206,//����ʷת����ˮ
	MSG_TYPE_GET_BANK_ACCOUNT      = 207,//�����˺Ų�ѯ   
	MSG_TYPE_GET_BANK_TRANSJOUR    = 208,//����ת����ˮ��ѯ
	MSG_TYPE_GET_BANKBALA          = 209,//�����˻�����ѯ
	MSG_TYPE_GET_MARKET_DATA       = 210,//�ڻ������ѯ
	MSG_TYPE_GET_MARGIN            = 211,//��Լ��֤���ѯ
	MSG_TYPE_GET_FUTU_BANKINFO     = 212,//�ڻ��Ǽ�������Ϣ��ѯ
	MSG_TYPE_GET_EXCH_TIME         = 213,//������ʱ����ѯ 
	MSG_TYPE_GET_FMMC_PWD          = 214,//������Ľ��㵥ϵͳ�����ѯ
	MSG_TYPE_GET_BILL              = 215,//���㵥��ѯ
	MSG_TYPE_GET_HIS_ENTRUST       = 216,//��ʷί�в�ѯ
	MSG_TYPE_GET_HIS_BUSINESS      = 217,//��ʷ�ɽ���ѯ
	MSG_TYPE_GET_HIS_FUND          = 218,//��ʷ�ʽ��ѯ
	MSG_TYPE_UFT_ORDERHSACK        = 219,//ί�з���
	MSG_TYPE_UFT_ORDEREXACK        = 220, //�ɽ�����

	//20110822 luyj �������ί����ز�ѯ(06) �޸ĵ���:20110819035
	MSG_TYPE_GET_COMBIN_CODE       = 221, //��ѯ��ϴ���
	MSG_TYPE_GET_COMBIN_QUOTE      = 222,  //��ѯ�������
	MSG_TYPE_CHECK_PWD             = 223   //У������
	//20110822 end


};

/**********************************************************************/
/*                                                                    */
/*                              ���ݽṹ����                          */
/*                                                                    */
/**********************************************************************/
//4�ֽڶ���
#pragma pack(push,4)

//���嵥������Ľṹ
struct CMarketInfo
{
	char            contract_code[13];  //0 ��Լ����,
	double          pre_square_price;   //1 ���ս�������
	double          futu_open_price;    //2 ���̼�
	double          futu_last_price;    //3 ���¼۸�
	double          buy_high_price;     //4 ��������
	unsigned int    buy_high_amount;    //5 ������������
	unsigned int    buy_total_amount;   //6 ȫ������
	double          sale_low_price;     //7 ������ۼ۸�
	unsigned int    sale_low_amount;    //8 �����������
	unsigned int    sale_total_amount;  //9 ȫ������
	double          futu_high_price;    //10 ��߼�
	double          futu_low_price;     //11 ��ͼ�
	double          average_price;      //12 ����
	double          change_direction;   //13 ����
	int             business_amount;    //14 �ɽ���
	int             bear_amount;        //15 �ܳ���
	double          business_balance;   //16 �ɽ���
	double          uplimited_price;    //17 ��ͣ��
	double          downlimited_price;  //18 ��ͣ��
	char            futu_exch_type[3];  //19 �������
	double          form_buy_price;     //20 �������۸�
	double          form_sale_price;    //21 ��������۸�
	int             form_buy_amount;    //22 �����������
	int             form_sale_amount;   //23 �����������
	double          pre_close_price;    //24 �������̼�
	double          pre_open_interest;  //25 ���տ�����
	double          futu_close_price;   //26 �������̼�
	double          square_price;       //27 �����
	double          pre_delta;          //28 ������ʵ��
	double          curr_delta;         //29 ������ʵ��
	double          bid_price2;         //30 �����
	unsigned int    bid_volume2;        //31 �����
	double          bid_price3;         //32 ������
	unsigned int    bid_volume3;        //33 ������
	double          bid_price4;         //34 ���ļ�
	unsigned int    bid_volume4;        //35 ������
	double          bid_price5;         //36 �����
	unsigned int    bid_volume5;        //37 ������
	double          ask_price2;         //38 ������
	unsigned int    ask_volume2;        //39 ������
	double          ask_price3;         //40 ������
	unsigned int    ask_volume3;        //41 ������
	double          ask_price4;         //42 ���ļ�
	unsigned int    ask_volume4;        //43 ������
	double          ask_price5;         //44 �����
	unsigned int    ask_volume5;        //45 ������
};


//�����������Ľṹ
struct CArgMarketInfo
{
	char         arbicontract_id[31];  //0 ������Լ��
	char         futu_exch_type[3];    //1 �������
	char         first_code[13];       //2 ��һ��
	char         second_code[13];      //3 �ڶ���
	char         arbi_type;            //4 �������1-SPD, 2 -IPS
	double       buy_price;            //5 ��������
	unsigned int buy_amount;           //6 ������������
	unsigned int buy_total_amount;     //7 ȫ������
	double       sale_price;           //8 ������ۼ۸�
	unsigned int sale_amount;          //9 �����������
	unsigned int sale_total_amount;    //10 ȫ������
	double       futu_high_price;      //11 ��߼�
	double       futu_low_price;       //12 ��ͼ�
	double       uplimited_price;      //13 ��ͣ��۸�
	double       downlimited_price;    //14 ��ͣ��۸�
};


//ί�з�����Ϣ
struct COrderRspInfo
{
	int          entrust_no;            //0 ί�к�
	char         futures_account[21];   //1 ���ױ���
	char         futu_exch_type[11];    //2 ���������
	char         contract_code[13];     //3 ��Լ����
	char         entrust_bs[9];       //4 ������ʶ
	char         entrust_direction[9];     //6 ��ƽ��ʶ
	char         hedge_type[9];         //7 �ױ���ʶ
	int          fund_account;          //8 �ʽ��˻�
	char         futu_report_no[21];    //9 ���ص���
	char         firm_no[9];            //10 ��Ա��
	char         operator_no[9];        //11 ����Ա��
	int          client_group;          //12 �ͻ����
	int          entrust_amount;        //13 ί������
	int          business_total_amount; //14 �ɽ�������
	int          cacel_amount;          //15 ��������
	double       entrust_price;         //16 ί�м۸�
	char         entrust_status;        //17 ί��״̬
	int          branch_no;             //18 Ӫҵ����
	int          batch_no;              //19 ί������
	char         futu_entrust_type;     //20 ί������
	int          amount_per_hand;       //21 ��Լ����
	char         forceclose_reason;     //22 ǿƽԭ��
	int          init_date;             //23 ��������
	int          curr_time;             //24 ��ǰʱ��
	char         confirm_no [21];       //25 ��������
	int          weave_type;            //26 ���ί������
	char         arbitrage_code [21];   //27 ������Լ����
	int          time_condition;        //28 ��Ч������
	int          volume_condition;      //29 �ɽ�������
	int          futu_entrust_prop;     //30 �ڻ�ί������
	double       frozen_fare;           //31 �����ܷ���
};

//�ɽ�������Ϣ
struct CRealRspInfo
{
	int          entrust_no;            //0 ί�к�
	char         futures_account[21];   //1 ���ױ���
	char         futu_exch_type[11];    //2 ���������
	char         business_no[21];       //3 �ɽ����
	char         contract_code[13];     //4 ��Լ����
	char         entrust_bs[9];		//5 ������ʶ
	char         entrust_direction[8];     //6 ��ƽ��ʶ
	double       business_price;        //7 �ɽ��۸�
	double       business_amount;       //8 �ɽ�����  
	char         hedge_type[9];         //9 �ױ���ʶ
	int          fund_account;          //10 �ʽ��˻�
	char         futu_report_no[21];    //11 ���ص���
	char         firm_no[9];            //12 ��Ա��
	char         operator_no[9];        //13 ����Ա��
	int          client_group;          //14 �ͻ����
	int          entrust_amount;        //15 ί������
	int          business_total_amount; //16 �ɽ�������
	int          cacel_amount;          //17 ��������
	double       entrust_price;         //18 ί�м۸�
	char         entrust_status;        //19 ί��״̬
	int          branch_no;             //20 Ӫҵ����
	int          batch_no;              //21 ί������
	char         futu_entrust_type;     //22 ί������
	int          amount_per_hand;       //23 ��Լ����
	char         forceclose_reason;     //24 ǿƽԭ��
	int          init_date;             //25 ��������
	int          business_time;         //26 �ɽ�ʱ��
	char         confirm_no[21];        //27 ��������
	double       frozen_fare;           //28 �����ܷ���
};

#pragma pack(pop)

#endif//end of futu_data_types.h


