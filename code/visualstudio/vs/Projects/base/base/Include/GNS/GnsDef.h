//--------------------------------------------------------------
// ��Ӱ��˵�����  GmcNetworkSystem(GNS)
// ��Ȩ����:        2010 ��ɽ���(Kingsoft)
// ��������������: 2010-2-11 Golton Gao
//--------------------------------------------------------------
#ifndef __GMC_NETWORK_SYSTEM_DEF_H__
#define __GMC_NETWORK_SYSTEM_DEF_H__
/*--------------------------------------------------------------
[���ʽ���]
	GNS(GMC Network System)��GMC����ϵͳ����GMC�ͽ���GMC����������ڵ���ɡ�
	GNE(GMC Network Entity)��GMC����ʵ�壬GMC�����еĽڵ�ĳ���
	GNM(GMC Network Message)��GMC������Ϣ��GNE����ͨ����Ϣ����ʵ�֡�
/-------------------------------------------------------------*/
#include <assert.h>
#include <string.h>
#include <stdio.h>

#pragma pack(1)

// === GNE��ʶ�� ===//
/*
	GNE�ı�ʶ���е�ַ��·�����֣�����֮����Ի���任��
	1��GNE��ַ������(Segment)��ɣ���һ��ΪGNE�����ͣ��ڶ���λGNE��ʵ����
	2��GNE�����ͱ�ʶGNE�����ʣ�Ҳ�������ṩ�ķ���������ͬ��GNE���ṩ�ķ�������ͬ�ġ�
	3��GNE��ʵ����ʶ��ͬ����GNE�Ĳ�ͬ����ʵ����
	4��ÿ����ַ�ζ���һ���ַ�����ֻ��ȡӢ���ַ������ֺ��»��ߡ��������»���'_'��ʼ�Ķ���Ϊ�ڲ������ġ�
	5��GNE·������ɷ�ʽΪ������/ʵ�����м���'/'�ָ
*/

// == GNE��ַ ==//
#define GNE_ADDR_SEGMENT_MAX_LEN	15
typedef char						GNE_ADDR_SEGMENT[GNE_ADDR_SEGMENT_MAX_LEN + 1];
#define GNE_ADDR_SEGMENT_ANY		"%"

struct GNE_ADDR
{
	GNE_ADDR_SEGMENT	Type;
	GNE_ADDR_SEGMENT	Inst;
};

// == GNE_PATH ==//
#define GNE_PATH_MAX_LEN	(GNE_ADDR_SEGMENT_MAX_LEN * 2 + 1)
typedef char				GNE_PATH[GNE_PATH_MAX_LEN + 1];		// ���ӣ�"DataCube/ForStat"

// === �����ʶ�� ===//
/* 
	1������(Service)��·��(Path)����ʶ��
	2��·���ɶ༶Ŀ¼��ɣ�ÿ��֮����'/'��Ϊ�ָ�����
	3��'/'������Ϊ·������ʼ�ַ���
	4��·����Ϊ����·��(PathLocal)��ȫ��·��(PathGlobal)���ࡣ
	5������·��Ϊ�����GNE�����·����
	6��ȫ��·��Ϊ�����GNSȫ�ֵ�·����

	���ӣ�
	��Ϸ�������ṩ�ġ��ƶ���ҵ�ָ��λ�á�����
	����·����"Player/Move/ToLocation"
	ȫ��·����"GameSpace/Gateway00101/Player/Move/ToLocation"
*/

#define GNE_SERVICE_PATH_LOCAL_MAX_LEN	40
typedef char							GNE_SERVICE_PATH_LOCAL[GNE_SERVICE_PATH_LOCAL_MAX_LEN + 1];
#define GNE_SERVICE_PATH_GLOBAL_MAX_LEN (GNE_PATH_MAX_LEN + 1 + GNE_SERVICE_PATH_LOCAL_MAX_LEN)
typedef char							GNE_SERVICE_PATH_GLOBAL[GNE_SERVICE_PATH_GLOBAL_MAX_LEN + 1];


// === ��Ϣ����ģʽ ===//
/*
	GNS�н���ͨ����Ϣ�������еġ�GNM�ǽ����Ļ�����Ԫ��
	1��ĿǰGNS֧��������Ϣ����ģʽ��Reuqest-Replyģʽ��Request-NoReplyģʽ��
	2����ˣ���ϢҲ�����ࣺRequest��Ϣ��Reply��Ϣ��
	3������Reply��Ϣ���ṩ�������ֶΣ����ڱ��������
	4��GNM��Ϊͷ��HEAD������)���غ�LOAD�����֡�
	5���غ�LOAD������Ӧ�ò�ͬ����ͬ��
	6���غɿ����в�ͬ�ĸ�ʽ���û������Զ����ʽ��ֻ��Ҫ����˫��һ�¼��ɡ�
*/

// == GNM����ģʽ ==//
enum GNM_EXCHANGE_PATTERN
{
	GNM_EXCHANGE_PATTERN_REQUEST_REPLY = 0,
	GNM_EXCHANGE_PATTERN_REQUEST_NO_REPLY
};

// == GNM���� ==//
enum GNM_TYPE
{
	GNM_TYPE_REQUEST = 0,			// Request��Ϣ
	GNM_TYPE_REPLY,					// Reply��Ϣ
};

// == ��Ӧ���͵�GNM�ķ����� ==//
enum GNM_RET_CODE
{
	// GNSͨ�÷����룬ͨ�ù���0��ʾ�ɹ�����0��ʾ�ɹ����������
	GRC_SUCCESS					= 0,	// ����ɹ�
	GRC_FAILED					= 1,	// ����ʧ��
	GRC_TIMEOUT					= 2,	// ����ʱ
	GRC_SERVICE_UNAVAILABLE		= 3,	// ��ǰ���񲻿���
	GRC_NOT_SUPPORT				= 4,	// ����֧��
	GRC_NOT_RECOGNIZED			= 5,	// ���������޷�ʶ�𣨸�ʽ����
	GRC_UNKOWN					= 6,	// ������δ֪

	// GNS���������Ϣ·��ʱ�����ķ�����
	GRC_CENTER_INTERNAL_ERROR	= 100,
	GRC_CENTER_MSG_FILTERED		= 101,	// ��Ϣ��������ˣ�û��Ȩ�ޣ�
	GRC_CENTER_DEST_OFFLINE		= 102,	// ��Ϣ·�ɵ�Ŀ�ĵز�����
	GRC_CENTER_TRANSFER_FAILED	= 103,	// ��Ϣ·��ת��ʧ��

	GRC_USER					= 1000,	// >= GPC_USER��Ϊ�û��Զ���ķ�����
};

// == GNM��Ϣ�в����ĸ�ʽ ==//
enum GNM_LOAD_FORMAT
{
	// == �ı���ʽ ==//
	GNM_LOAD_FORMAT_TEXT_PLAIN	= 0,	// ��ͨ�ı���ʽ
	GNM_LOAD_FORMAT_TEXT_JSON	= 1,	// JSON�ı���ʽ
	GNM_LOAD_FORMAT_TEXT_XML	= 2,	// XML�ı���ʽ

	// == �����Ƹ�ʽ ==//
	GNM_LOAD_FORMAT_BIN_PLAIN	= 50,	// ��ͨ�����Ƹ�ʽ

	// == �Զ����ʽ ==//
	GNM_LOAD_FORMAT_USER		= 100,	// ��GNM_LOAD_FORMAT_USER��ʼ�ĸ�ʽ��ű�ʾ���û��Զ���ĸ�ʽ
};

// == GNM��Ϣ��ͷ���Ķ��� ==//
struct GNM_HEAD
{
	unsigned char			ExchangePattern;		// ��Ϣ�������ͣ��ο���GNM_EXCHANGE_PATTERN
	unsigned char			Type;					// ��Ϣ���ͣ��ο���GNM_TYPE
	unsigned short			RetCode;				// �����룬������Reply��Ϣ�����塣�ο���GNM_RET_CODE
	GNE_ADDR				Src;					// ��Ϣ��Դ��
	GNE_ADDR				Dest;					// ��ϢĿ�ĵ�
	GNE_SERVICE_PATH_LOCAL	ServicePath;			// ����·������Ϣ�����漰�����ĸ�����
	unsigned int			Sn;						// ��Ϣ���кţ�һ����Ϣ��������Ψһ��ʶ����
	unsigned char			LoadFormat;				// ��Ϣ�غɵĸ�ʽ���ο���GNM_LOAD_FORMAT
};

// == GNM��Ϣ���غɵĶ��� ==//
#define GNM_LOAD_MAX_LEN	(1024 * 40)				// GNM��Ϣ�غɵĵ���󳤶�Ϊ40K

#pragma pack()

// === ���ø������� ===//
// ��ͨGNE_ADDR_SEGMENT�е��ַ���ȡֵ��Χ
static inline bool IS_NORMAL_GNE_ADDR_SEGMENT_CHAR(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z') || 
		(ch >= '0' && ch <= '9') ||
		(ch == '_'));
}

// �ж��Ƿ�Ϊ��ͨGNE_ADDR_SEGMENT
static inline bool IS_NORMAL_GNE_ADDR_SEGMENT(const char* szSegment)
{
	char* pChar = (char*)szSegment;
	while(*pChar)
	{
		if (pChar - szSegment + 1 > GNE_ADDR_SEGMENT_MAX_LEN)
			return false;
		else if (!IS_NORMAL_GNE_ADDR_SEGMENT_CHAR(*pChar))
			return false;
		else
		{
			pChar++;
			continue;
		}
	}
	return true;
}

// �ж��Ƿ�Ϊͨ��GNE_ADDR_SEGMENT
static inline bool IS_ANY_GNE_ADDR_SEGMENT(const char* szSegment)
{
	return strcmp(szSegment, GNE_ADDR_SEGMENT_ANY) == 0;
}

// �ж�GNE_TYPE�Ƿ����
static inline bool IS_GNE_ADDR_SEGMENT_EQUAL(const char* szSegment1, const char* szSegment2)
{
	return strcmp(szSegment1, szSegment2) == 0;
}

// �ж��Ƿ�Ϊһ���Ϸ���GNE_ADDR
static inline bool IS_VALID_GNE_ADDR(const GNE_ADDR& GneAddr)
{
	if (IS_NORMAL_GNE_ADDR_SEGMENT(GneAddr.Type))			// ��ͨGNE_TYPE + ��ͨGNE_INST = ������ַ���Ϸ�
	{														// ��ͨGNE_TYPE + �㲥GNE_INST = �鲥��ַ���Ϸ�
		return true;								
	}
	else if (IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type))			// �㲥GNE_TYPE + �㲥GNE_INST = �㲥��ַ���Ϸ�
	{
		return IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
	}
	else													// ����������Ƿ�
		return false;
}

// �ж��Ƿ�Ϊһ��������ַ
// ǰ��������GneAddr��һ���Ϸ���GNE_ADDR
static inline bool IS_UNICAST_ADDR(const GNE_ADDR& GneAddr)
{
	return !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// �ж��Ƿ�Ϊһ���ಥ��ַ
// ǰ��������GneAddr��һ���Ϸ���GNE_ADDR
static inline bool IS_MULTICAST_ADDR(const GNE_ADDR& GneAddr)
{
	return !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// �ж��Ƿ�Ϊһ���㲥��ַ
// ǰ��������GneAddr��һ���Ϸ���GNE_ADDR
static inline bool IS_BROADCASE_ADDR(const GNE_ADDR& GneAddr)
{
	return IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// �ж�����GneAddr�Ƿ����
static inline bool IS_GNE_ADDR_EQUAL(const GNE_ADDR& Addr1, const GNE_ADDR& Addr2)
{
	return (IS_GNE_ADDR_SEGMENT_EQUAL(Addr1.Type, Addr2.Type) && IS_GNE_ADDR_SEGMENT_EQUAL(Addr1.Inst, Addr2.Inst));
}

// ��GNE_ADDRת��ΪGNE_PATH
static inline void GNE_ADDR_TO_GNE_PATH(const GNE_ADDR& Addr, GNE_PATH& Path)
{
	sprintf(Path, "%s/%s", Addr.Type, Addr.Inst);
}

// ��ȡ��ǰ·���Ķ���Ŀ¼
// ���������	szPath:		--	·���ַ���
// ���������	szTopDir	--	��ǰ·���Ķ���Ŀ¼����ȷ��szTopDir���㹻�Ŀռ䣬���飺char szTopDir[GNE_RES_GLOBAL_PATH_MAX_LEN + 1];
// ����ֵ��	ȥ������Ŀ¼�Լ����Ŀ¼��صķָ���'/'��ʣ���·���ַ���
//				NULL	--	˵���Ѿ�û����һ��Ŀ¼
//				��NULL	-- ˵��������һ��Ŀ¼
// ���ӣ�
/* 
	char szTopDir[GNE_SERVICE_PATH_GLOBAL_MAX_LEN + 1];
	const char* szPathLeft = "GMC/ForMoon/Control/AddGne";
	while(szPathLeft)
	{
		szPathLeft = GET_TOP_DIR(szPathLeft, szTopDir);
		printf("Current directory:%s\n", szTopDir);
	}
*/

static inline const char* GET_TOP_DIR(const char* szPath, char* szTopDir)
{
	assert(szPath && szPath[0] != '/');
	assert(szTopDir);

	while(!(*szPath == '/' || *szPath == '\0'))
		*szTopDir++ = *szPath++;
	*szTopDir = '\0';
	if (*szPath == '/')
		szPath++;
	if (*szPath == '\0')
		return NULL;
	else
		return szPath;
}

// �ж��Ƿ�Ϊ�Ϸ�����Ϣ����ģʽ
static inline bool IS_VALID_GNM_EXCHANGE_PATTERN(unsigned char GnmExchangePattern)
{
	return (GnmExchangePattern == GNM_EXCHANGE_PATTERN_REQUEST_REPLY) || (GnmExchangePattern = GNM_EXCHANGE_PATTERN_REQUEST_NO_REPLY);
}

// �ж��Ƿ�Ϊ�Ϸ���GNM_TYPE
static inline bool IS_VALID_GNM_TYPE(unsigned char GnmType)
{
	return (GnmType == GNM_TYPE_REQUEST ||  GnmType == GNM_TYPE_REPLY);
};

static inline bool IS_VALID_IP_ADDRESS(const char* szIPAddress)
{
	int nValue[4];
	int nRet = sscanf(szIPAddress, "%d.%d.%d.%d", &nValue[0], &nValue[1], &nValue[2], &nValue[3]);
	if (nRet == 4 &&
		nValue[0] >= 0 && nValue[0] < 256 &&
		nValue[1] >= 0 && nValue[1] < 256 &&
		nValue[2] >= 0 && nValue[2] < 256 &&
		nValue[3] >= 0 && nValue[3] < 256)
	{
		return true;
	}
	return false;
}

#endif // #ifndef __GMC_NETWORK_SYSTEM_DEF_H__
