//---------------------------------------------------------------------------
// ������Ե�����2 GameMasterCentral ������ͨ
// ��Ȩ����:       2006-2007 ��ɽ���(Kingsoft)
// ��������������: 2006.5 Խ��(wooy)
//---------------------------------------------------------------------------
//	GameMasterCentral����Ϸ���⻥����ͨ�����࣬��һ����Ҫ���ܾ��ǰ���Ϸ�����
//GameMaster��������Ϸ������ĸ���Ӧ��ϵͳ�ҽ�������GameMasterCentral��ת����
//Ϸ�����ṩ�ĸ���GameMaster���񣬴�ͷ�ļ������������GameMaster�������������
//�������йص���Ϣ��GMЭ�齫���õ���Щ���塣��ο�"GameMasterCentral��GM����Э����ϵ.wps"
//�ĵ��˽�GMЭ����ϵ��
//---------------------------------------------------------------------------
#ifndef __GAME_MASTER_CENTRAL_GAME_MASTER_SERVICE_DEF_H__
#define __GAME_MASTER_CENTRAL_GAME_MASTER_SERVICE_DEF_H__

//����GameMasterCentral��MasterService����������ṩ�ķ��������
enum MASTER_SERVICE_TYPE
{
	MST_GAME_ONLINE_OBJECTIVE	= 0x01,		//�ṩ��������Ϸ����Ĳ���
	MST_GAME_OFFLINE_OBJECTIVE	= 0x02,		//�ṩ�Է�������Ϸ����Ĳ���
	MST_SERVER_RUNTIME_INFO		= 0x04,		//�ṩ�������������Ϣ״̬����
	MST_SERVER_MAINTENTANCE		= 0x08,		//�ṩ�������ά������
	MST_GAME_DATA_MAINTENTANCE	= 0x10,		//�ṩ��Ϸ����ά������
};

//GameMasterЭ������ķ���ؼ���
enum GAME_MASTER_OPERATION_FAMILY
{
	GMOF_RESERVED = 0,
	GMOF_SYSTEM,		//����ϵͳ����
	GMOF_RET,			//������Ϣ(����������ݰ�)

	GMOF_SINFO,			//ϵͳ��Ϣ����
	GMOF_SNCTRL,		//��Ϸ����ϵͳһ�����
	GMOF_SSCTRL,		//��Ϸ����ϵͳ�������
	GMOF_ANCTRL,		//�ʺ�һ�����
	GMOF_RNCTRL,		//��ɫһ�����
	GMOF_RSCTRL,		//��ɫ�������
	GMOF_RINFO,			//��ɫ��Ϣ��ѯ
	GMOF_GSINFO,		//��Ϸ������Ϣ
	GMOF_GSCTRL,		//��Ϸ�������
	GMOF_GMCTRL,		//GM�ʺŽ�ɫ����
	GMOF_ASTINFO,		//������Ϣ(��ҷ���GM����Ϣ��������Ϣ�������Ͷ�Ѷ��)

	GMOF_NUM,
};

//�������Դ������
enum	MSG_PORT_TYPE
{
	MSG_PORT_TYPE_NONE = 0,
	MSG_PORT_TYPE_GAMESPACE,			//��Ϸ����
	MSG_PORT_TYPE_CONSOLE,				//��������ֱ������/��
	MSG_PORT_TYPE_ACCOUNT_SYS,			//�ʺŷ�����
	MSG_PORT_TYPE_SVR_DOOR,				//�����ṩGM����Ľ����
	MSG_PORT_TYPE_SVR_DOOR_SECURITY,	//�����ܵĶ����ṩGM����Ľӿ�
	MSG_PORT_TYPE_GAMESPACE_MAINTENANCE,//��Ϸ�����ά��������������
};

#pragma	pack(push, 1)

//�������ˮ��
union SERIAL_NO
{
	struct	SERIAL_NO_BY_DETAIL
	{
		unsigned int	uBatchNo;			//���κ�
		unsigned char	cSourceIndex;		//��Դ����(����ط���������ÿһ���������ֻ��256�����ӣ�)
		unsigned char	cSourceType;		//ȡֵ��MSG_PORT_TYPE
		unsigned short	cValidatNo;			//��֤��
	}		ByDetail;
	struct SERIAL_NO_BY_REF_NO
	{
		unsigned int	uRefNo[2];			//��Ϻ����ˮ��
	}		ByRefNo;
};

//GMЭ��Ļ�����Ϣ
struct GAME_MASTER_PROTOCOL_INFO 
{
	enum
	{
		OPERATION_KEY_WORD_MAX_LEN = 12,
	};
	unsigned char	OperationFamily;	//Э�����ؼ�ֵ,ȡֵ����ö��GAME_MASTER_OPERATION_FAMILY
	SERIAL_NO		SerialNo;
	char			szOperationKeyWord[OPERATION_KEY_WORD_MAX_LEN];
};

//������Ϣ
struct GAME_MASTER_SERVICE_SVR
{
	short	nAreaIndex;						//��������
	short	nGroupIndex;					//�����������ȼ����ҷ��е��ң�
};

//������Ϣ������������һ���˺�����һ����ɫ����һ��������ȷ�ʽ������ָ��һ������
struct NAMED_OBJECT_IDENTIFIER
{
	enum
	{
		OBJECT_NAME_MAX_LEN = 32,
	};
	char				szName[OBJECT_NAME_MAX_LEN];
};

//��������
struct DATA_CONTENT
{
	unsigned short	uContentLength;
	char			Content[1];		//ʵ�ʴ洢����ΪuContentLengthָ������ô��
};

//--------------------------------------------------------------
//	���ϲ����Ѿ���wooy���ȷ����Ҫ����
//--------------------------------------------------------------
enum COMMAND_TYPE
{
	SHOW_SERVER_LIST,		// ��ʾ�������б�
	GMTOOLS_COMMAND,		// ������ģ��ִ��gmtools��Э��

	COMMAND_NUM,
};

struct COMMAND_CELL
{
	enum
	{
		MAX_COMMAND_TYPE_LEN = 16,
		MAX_COMMAND_TEXT_LEN = 256,
	};

	char	szCommandType[MAX_COMMAND_TYPE_LEN];
	char	szCommandText[MAX_COMMAND_TEXT_LEN];
};

#pragma	pack(pop)

#endif //__GAME_MASTER_CENTRAL_GAME_MASTER_SERVICE_DEF_H__
