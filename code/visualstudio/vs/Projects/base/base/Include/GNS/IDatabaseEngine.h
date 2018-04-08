//--------------------------------------------------------------
// ��Ӱ��˵�����  DatabaseEngine
// ��Ȩ����:        2010 ��ɽ���(Kingsoft)
// ��������������: 2010-4-28 Golton Gao
//--------------------------------------------------------------
#ifndef __I_DATABASE_ENGINE_H__
#define __I_DATABASE_ENGINE_H__

struct IDatabaseEngine;
struct IStatement;
struct IResultSet;

// ���ݿ�����������Ϣ
struct DATABASE_ENGINE_CONFIG
{
	char	DbIP[16];								// ���ݿ�IP
	int		DbPort;									// ���ݿ�˿�
	char	DbName[31];								// ���ݿ���
	char	DbUser[21];								// ���ݿ��û���
	char	DbPwd[21];								// ���ݿ�����
};

struct IDatabaseEngine
{
	// ���ٽӿڶ���
	virtual void Release() = 0;

	// ��ʼ�����ݿ����棨�������ݿ⣩
	virtual bool Initialize(const DATABASE_ENGINE_CONFIG& Config) = 0;

	// ����ʼ�����ݿ����棨�Ͽ����ݿ⣩
	virtual void Terminate() = 0;

	// === DDL�����ӿ� ===//
	// ���ӱ��
	virtual bool AddTable(
		const TABLE_NAME	TableName,				// ����
		const FIELD_TYPE	FieldType[],			// ����ֶ�������Ϣ
		unsigned int		uFieldNum,				// ����ֶ�����
		bool				bIfNotExists = false	// �Ƿ�ֻ�ڱ�񲻴���ʱ����
		) = 0;

	// ɾ�����
	virtual bool DelTable(
		const TABLE_NAME	TableName				// ����
		) = 0;
	
	// �����ֶ�
	virtual bool AddField(
		const TABLE_NAME	TableName,				// ����
		const FIELD_TYPE	FieldType[],			// �ֶ�������Ϣ
		unsigned int		uFieldNum				// �ֶ�����
		) = 0;
	
	// �����ֶ�
	virtual bool DelField(
		const TABLE_NAME	TableName,				// ����
		const FIELD_TYPE	FieldType[],			// �ֶ�������Ϣ
		unsigned int		uFieldNum				// �ֶ�����
		) = 0;

	// === DML�����ӿ���IStatement���ṩ ===//
	virtual IStatement*	CreateStatement() = 0;	// ����Statememt

	// ��ȡ������Ϣ
	virtual const char* GetErrorStr() = 0;

	// ��ȡ������
	virtual unsigned int GetErrorCode() = 0;
};

struct IStatement
{
	// ���ٽӿڶ���
	virtual void Release() = 0;

	// ׼��Insert����
	virtual bool PrepareInsert(
		const TABLE_NAME	TableName,			// ����
		const FIELD_TYPE	FieldType[],		// ��Ҫ������ֶε�������Ϣ
		unsigned int		uFieldNum			// ��Ҫ������ֶ�����
		) = 0;

	// ׼��Select����
	virtual bool PrepareSelect(
		const TABLE_NAME	TableName,			// ����
		const FIELD_TYPE	FieldType[],		// ��Ҫѡ����ֶε�������Ϣ 
		unsigned int		uFieldNum,			// ��Ҫѡ����ֶ�����
		const FIELD_FILTER	FieldFilter[],		// �ֶ�ֵ��������
		unsigned int		uFilterNum,			// �ֶ�ֵ����������
		unsigned int		uOffset,			// ��ʼƫ����
		int					nExpectNum			// ѡ��ļ�¼����
		) = 0;

	// ׼��Update����
	virtual bool PrepareUpdate(
		const char*			TableName,			// �����
		const FIELD_TYPE	FieldType[],		// ��Ҫ���µ�Ŀ���ֶε�������Ϣ
		unsigned int		uFieldNum,			// ��Ҫ���µ��ֶε�����
		const FIELD_FILTER	FieldFilter[],		// �ֶ�ֵ��������
		unsigned int		uFilterNum			// �ֶ�ֵ����������
		) = 0;

	// ׼��Delete����
	virtual bool PrepareDelete(
		const TABLE_NAME	TableName,			// ����
		const FIELD_FILTER	FieldFilter[],		// �ֶ�ֵ��������
		unsigned int		uFilterNum			// �ֶ�ֵ����������
		) = 0;

	// ��FieldValue����
	virtual bool BindFieldPara(
		const FIELD_TYPE	FieldType[],		// �ֶ�������Ϣ
		const FIELD_VALUE	FieldValue[],		// �ֶ�ֵ
		unsigned int		uFieldNum			// �ֶ�����
		) = 0;

	// ��FieldFilter����
	virtual bool BindFilterPara(
		const FIELD_FILTER	FieldFilter[],		// �ֶ�ֵ��������
		unsigned int		uFilterNum			// �ֶ�ֵ����������
		) = 0;

	// ��FieldValue��FieldFilter����
	virtual bool BindFieldAndFilterPara(
		const FIELD_TYPE	FieldType[],		// �ֶ�������Ϣ		
		const FIELD_VALUE	FieldValue[],		// �ֶ�ֵ
		unsigned int		uFieldNum,			// �ֶ�����
		const FIELD_FILTER	FieldFilter[],		// �ֶ�ֵ��������
		unsigned int		uFilterNum			// �ֶ�ֵ����������
		) = 0;

	// ִ��
	virtual bool Execute() = 0;

	// �ύ
	virtual bool Commit() = 0;

	// �ع�
	virtual bool Rollback() = 0;

	// ��ȡDQL����(SELECT)�Ľ����
	// ����ֵ��NULL	-- ��ȡʧ��
	//			��NULL	-- ��ȡ�ɹ������ؽ������ָ��
	// ע�⣺ʹ��������������ͷ�֮
	virtual IResultSet* GetResultSet() = 0;

	// ��ȡDML����(INSERT, UPDATE, DELETE)��Ӱ��ļ�¼��
	// ����ֵ��-1	-- ��ȡʧ��
	//			>=0	-- ��ȡ�ɹ������ز�����Ӱ��ļ�¼��
	virtual int	GetAffectedRows() = 0;

	// ��ȡ������Ϣ
	virtual const char* GetErrorStr() = 0;

	// ��ȡ������
	virtual unsigned int GetErrorCode() = 0;
};

struct IResultSet
{
	// ���ٽӿڶ���
	virtual void Release() = 0;

	// ��ȡ��һ����¼
	// ����ֵ��true	-- ��ȡ��һ����¼�ɹ�
	//			false	-- ��ȡ��һ����¼ʧ�ܻ��߲�������һ����¼
	virtual bool Next() = 0;

	// ��ȡ��¼���ֶ�����
	virtual unsigned int GetFieldCount() = 0;

	// ��ȡ��ǰ��¼���ֶ�����
	// ����ֵ���ֶ����ͣ��μ�FIELD_DATA_TYPE
	virtual int GetFieldType(
		unsigned int	uColumnIndex	// ����ţ���0��ʼ
		) = 0;

	// �жϵ�ǰ��¼���ֶ��Ƿ�ΪNULLֵ
	virtual bool IsNull(
		unsigned int uColumnIndex		// ���кţ���0��ʼ
		)= 0;

	// ��ȡ��ǰ��¼���ֶ�ֵ
	// ����ֵ��true	-- ��ȡ�ֶ�ֵ�ɹ�
	//			false	-- ��ȡ�ֶ�ֵʧ�ܣ������С
	virtual bool GetFieldValue(
		unsigned int	uColumnIndex,	// ����ţ���0��ʼ 
		void*			pValueBuffer,	// ֵ����
		unsigned int	uBufferLen,		// ���泤��
		unsigned int&	uRealLen		// ���������ʵ��ֵռ�л��泤��
		) = 0;

	// ��ȡ������Ϣ
	virtual const char* GetErrorStr() = 0;

	// ��ȡ������
	virtual unsigned int GetErrorCode() = 0;
};

//=== �ⲿ���ø�ͷ�ļ�ʱ�������ӿ����� ===//
#ifndef  DATABASE_ENGINE_INTERNAL_SIGNATURE 

extern "C" IDatabaseEngine* DatabaseEngineCreate();
#define FUNC_NAME_DATABASE_ENGINE_CREATE "DatabaseEngineCreate"
typedef IDatabaseEngine* (*FUNC_DATABASE_ENGINE_CREATE)();

#endif // #ifndef  DATABASE_ENGINE_INTERNAL_SIGNATURE 

#endif // #ifndef __DATABASE_ENGINE_H__
