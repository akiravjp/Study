//--------------------------------------------------------------
//	��Ӱ��˵�����	DataExchangeMechanism(DEM)
//	��Ȩ����:			2010 ��ɽ���(Kingsoft)
//	��������������:	2010-4-2 Golton Gao
//--------------------------------------------------------------
#ifndef __I_DATA_EXCHANGE_MECHANISM_H__
#define __I_DATA_EXCHANGE_MECHANISM_H__
/*--------------------------------------------------------------
	[˵��]��
		1���˹��̲ο���JsonCpp����лBaptiste Lepilleur��
		2������Base64�㷨��������������ݺ��ı�֮��ı任��
	[����]��
		��ο�DemDemo����
	[����]��
		DO(DataObject)��		���ݶ�����ԭ�����͡�����(ARRAY�����ṹ(STRUCT)�����͵�����Ƕ����ɵĶ���
								���ݶ��������ִ�����ʽ:DVO��DSO��
		DVO(DataValueObject)��	����ֵ��������״�ṹ���ڣ���������ʱ����ֵ/�ֶ�/Ԫ�صĴ�ȡ
		DSO(DataS11nObj):		�������л��������ֽ�����ʽ���ڵģ��������紫����߳־û�
		ע��S11n = Serialization
---------------------------------------------------------------*/

// === DVO��� ===//

// == DVO������ ==//
enum DVO_TYPE
{
	// == ԭ������ ==//
	DVO_TYPE_NULL = 0,	// NULL����
	DVO_TYPE_BOOL,		// ��������
	DVO_TYPE_LONGLONG,	// ��������(ͳһΪ64λ)
	DVO_TYPE_DOUBLE,	// ��������(ͳһΪ64λ)

	// == �������� ==//
	DVO_TYPE_STRING,	// �ַ�������
	DVO_TYPE_ARRAY,		// ��������
	DVO_TYPE_STRUCT,	// �ṹ����
};

// �ж��Ƿ�Ϊ�Ϸ���DO����
static inline bool IS_VALID_DVO_TYPE(int nType)
{
	return (nType >= DVO_TYPE_NULL && nType <= DVO_TYPE_STRUCT);
}

// == DVO�ֶ��� ==//
#define DVO_FIELD_NAME_MAX_LEN	32							// �ֶ�������󳤶�Ϊ32���ַ���������'\0')
typedef	char DVO_FIELD_NAME[DVO_FIELD_NAME_MAX_LEN + 1];	// �ֶ������Ͷ���


// == ����ֵ���� ==//
// ����ֵ������һ�֡�Ԫ���󡱣��������Ƕ������ͣ��μ�DEM_DO_TYPE���ģ���������ֻ��������ʱ����
// ��Բ�ͬ�����ͣ��в�ͬ�Ľӿڣ���ʹ��ʱ��ض�������������������
struct IDataValueObject
{
	// === �����ڹ��� ===//

	// ��������ֵ����
	// DataValueObjectCreate
	// DataValueObjectCreate��������DVO��NULL���͵�


	// === ����������͵Ľӿ� ===//

	// ��ȡObject������
	// ����ֵ��DVO�����ͣ��μ�DEM_DO_TYPE
	virtual int	 GetType() = 0;



	// === ���NULL���͵Ľӿ� ===//
	// DataValueObjectCreateֻ�ܴ�����NULL���͵�DVO���������͵�DVOֻ��ͨ��NULL���͵�ת���ӿ�ʵ��


	// ������ת��ΪBOOL����
	// ǰ����������������ΪNULL
	virtual bool ToBool(bool bBool) = 0;	

	// ������ת��ΪLONGLONG����
	// ǰ����������������ΪNULL
	virtual bool ToLongLong(long long llLongLong) = 0;

	// ������ת��ΪDOUBLE����
	// ǰ����������������ΪNULL
	virtual bool ToDouble(double dDouble) = 0;

	// ������ת��ΪSTRING����
	// ǰ����������������ΪNULL
	virtual bool ToString(const char* szStr) = 0;

	// ������ת��ΪARRAY����
	// ǰ����������������ΪNULL
	virtual bool ToArray() = 0;

	// ������ת��ΪSTRUCT����
	// ǰ����������������ΪNULL
	virtual bool ToStruct() = 0;



	// === ���BOOL���͵Ľӿ� ===//

	// ��ȡboolֵ
	// ǰ����������������ΪBOOL
	virtual bool GetBool() = 0;

	// ����boolֵ
	// ǰ����������������ΪBOOL
	virtual bool SetBool(bool bBool) = 0;



	// === ���longlong���͵Ľӿ� ===//
	// ��ȡlonglongֵ
	// ǰ����������������ΪLONGLONG
	virtual long long GetLongLong() = 0;

	// ����longlongֵ
	// ǰ����������������ΪLONGLONG
	virtual bool SetLongLong(long long llLongLong) = 0;



	// === ���DOUBLE���͵Ľӿ� ===//

	// ��ȡdoubleֵ
	// ǰ����������������ΪDOUBLE
	virtual double GetDouble() = 0;

	// ����doubleֵ
	// ǰ����������������ΪDOUBLE
	virtual bool SetDouble(double dDouble) = 0;



	// === ���STRING���͵Ľӿ� ===//

	// ��ȡstringֵ
	// ǰ����������������ΪSTRING
	virtual const char* GetString() = 0;

	// ����stringֵ
	// ǰ����������������ΪSTRING
	virtual bool SetString(const char* szStr) = 0;



	// === ���ARRAY���͵Ľӿ� ===//
	// ARRAY���Ϳ��Կ�����ͬ�����͵Ķ��DVOԪ��(Element)�ļ���
	// ARRAY���͵Ľӿھ������Element����CRUD(��ɾ�Ĳ�)�Ĳ���


	// == ARRAY���Ӳ���(Add����)�Ľӿ� ==//

	// ����һ��NULL���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemNull() = 0;

	// ����һ��BOOL���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemBool(bool bBool) = 0;

	// ����һ��LONGLONG���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemLongLong(long long llLongLong) = 0;

	// ����һ��DOUBLE���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemDouble(double dDouble) = 0;

	// ����һ��STRING���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemString(const char* szStr) = 0;

	// ����һ�������κ�Ԫ�ص�ARRAY���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemArray() = 0;

	// ����һ�������κ��ֶε�STRUCT���͵�Ԫ��
	// ����ֵ��	NULL	--	����Ԫ��ʧ��
	//				��NULL	--	����Ԫ�سɹ������ص�Ϊ����Ԫ�صĶ����ָ��
	// ǰ����������������ΪARRAY
	virtual IDataValueObject* AddElemStruct() = 0;


	// == ARRAYɾ������(Del����)�Ľӿ� ==//

	// ɾ��ARRAY�е�һ��Ԫ��
	// ǰ����������������ΪARRAY��Ԫ�������Ϸ�
	virtual void DelElem(unsigned int uElemIndex) = 0;


	// == ARRAY�޸Ĳ���(Set����)�Ľӿ� ==//

	// ����BOOL���͵�Ԫ�ص�ֵ
	// ǰ����������������ΪARRAY��Ԫ�������Ϸ���Ԫ������ΪBOOL
	virtual bool SetElemBool(unsigned int uElemIndex, bool bBool) = 0;

	// ����LONGLONG���͵�Ԫ�ص�ֵ
	// ǰ����������������ΪARRAY��uIndex�Ϸ���Ԫ������ΪLONGLONG
	virtual bool SetElemLongLong(unsigned int uIndex, long long llLongLong) = 0;

	// ����DOUBLE���͵�Ԫ�ص�ֵ
	// ǰ����������������ΪARRAY��uIndex�Ϸ���Ԫ������ΪDOUBLE
	virtual bool SetElemDouble(unsigned int uIndex, double dDouble) = 0;

	// ����STRING���͵�Ԫ�ص�ֵ
	// ǰ����������������ΪARRAY��uIndex�Ϸ���Ԫ������ΪSTRING
	virtual bool SetElemString(unsigned int uIndex, const char* szStr) = 0;


	// == ARRAY��ѯ����(Get����)�Ľӿ� ==//

	// ����ARRAY
	/*
		���ӣ�
		IDataValueObject* pArray;
		unsigned int uElemNum = pArray->GetElemNum();
		for (unsigned int i = 0; i < uElemNum; i++)
		{
			switch(pElem->GetElemType(i))
			{
				case DVO_TYPE_STRING:
					printf("FieldValue:%s\n", pArray->GetElemValue(i)->GetString());
				break;
				//...
			}
		}
	*/

	// ��ȡARRAY��Ԫ�ص�����
	// ǰ����������������ΪARRAY
	virtual unsigned int GetElemNum() = 0;

	// ��ȡԪ������
	// ǰ����������������ΪARRAY��Ԫ������ֵ�Ϸ�
	virtual int GetElemType(unsigned int uElemIndex) = 0;

	// ��ȡԪ��ֵ
	// ǰ����������������ΪARRAY��Ԫ������ֵ�Ϸ�
	virtual IDataValueObject* GetElemValue(unsigned int uElemIndex) = 0;



	// === ���STRUCT���͵Ľӿ� ===//
	// STRUCT���Ϳ��Կ����ǲ������͵Ķ��DVO�ֶ�(Field)�ļ���
	// ÿ���ֶ�(Field)�����ֶ���(FieldName)���ֶ�ֵ(FieldValue)
	// �ֶ����ĳ���(������'\0')����<=DVO_FIELD_NAME_MAX_LEN
	// STRUCT���͵Ľӿھ������Field����CRUD(��ɾ�Ĳ�)�Ĳ���


	// == STRUCT���Ӳ���(Add����)�Ľӿ� ==//

	// ����һ��NULL���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldNull(const DVO_FIELD_NAME FieldName) = 0;

	// ����һ��BOOL���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldBool(const DVO_FIELD_NAME FieldName, bool bBool) = 0;

	// ����һ��LONGLONG���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldLongLong(const DVO_FIELD_NAME FieldName, long long llLongLong) = 0;

	// ����һ��DOUBLE���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldDouble(const DVO_FIELD_NAME FieldName, double dDouble) = 0;

	// ����һ��STRING���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldString(const DVO_FIELD_NAME FieldName, const char* szStr) = 0;

	// ����һ�������κ�Ԫ�ص�ARRAY���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldArray(const DVO_FIELD_NAME FieldName) = 0;

	// ����һ�������κ��ֶε�STRUCT���͵��ֶ�
	// ����ֵ��	NULL	--	�����ֶ�ʧ��
	//				��NULL	--	�����ֶγɹ������ص�Ϊ�����ֶεĶ����ָ��
	// ǰ����������������ΪSTRUCT
	virtual IDataValueObject* AddFieldStruct(const DVO_FIELD_NAME FieldName) = 0;


	// == STRUCTɾ�������Ľӿ� ==//

	// ɾ���ֶ�
	// ǰ����������������ΪSTRUCT���ֶ����Ϸ�(�ֶ�����ָ���ֶδ��ڣ�
	virtual void DelField(const DVO_FIELD_NAME FieldName) = 0;


	// == STRUCT�޸Ĳ���(Set����)�Ľӿ� ==//

	// ����BOOL���͵��ֶε�ֵ
	// ǰ����������������ΪSTRUCT���ֶ�����ָ���ֶδ������ֶ�����ΪBOOL
	virtual bool SetFieldBool(const DVO_FIELD_NAME FieldName, bool bBool) = 0;

	// ����LONGLONG���͵��ֶε�ֵ
	// ǰ����������������ΪSTRUCT���ֶ�����ָ���ֶδ������ֶ�����ΪLONGLONG
	virtual bool SetFieldLongLong(const DVO_FIELD_NAME FieldName, long long llLongLong) = 0;

	// ����DOUBLE���͵��ֶε�ֵ
	// ǰ����������������ΪSTRUCT���ֶ�����ָ���ֶδ������ֶ�����ΪDOUBLE
	virtual bool SetFieldDouble(const DVO_FIELD_NAME FieldName, double dDouble) = 0;

	// ����STRING���͵��ֶε�ֵ
	// ǰ����������������ΪSTRUCT���ֶ�����ָ���ֶδ������ֶ�����ΪSTRING
	virtual bool SetFieldString(const DVO_FIELD_NAME FieldName, const char* szStr) = 0;


	// == STRUCT��ѯ����(Get����)�Ľӿ� ==//

	// = ����STRUCT���ֶ� =//
	/*
		���ӣ�
		IDataValueObject* pStruct;
		unsigned int uFieldNum = pStruct->GetFieldNum();
		for (unsigned int i = 0; i < uFieldNum; i++)
		{
			printf("FieldName:%s\n", pStruct->GetFieldName());
			switch(pStruct->GetFieldType(i))
			{
				case DVO_TYPE_STRING:
					printf("FieldValue:%s\n", pStruct->GetFieldValue(i)->GetString());
				break;
				//...
			}
		}
	*/

	// �ж��Ƿ�Ϊ�ṹ��һ���Ϸ����ֶ���
	// �ڲ���һ���ֶ�֮ǰ����Ҫȷ�����ֶ��Ǵ��ڵģ��ر��ǵ������Ѿ��������紫����ߴ���IO��
	// ǰ����������������ΪSTRUCT
	virtual bool IsValidFieldName(const DVO_FIELD_NAME FieldName) = 0;

	// �ж��Ƿ�Ϊ�ṹ��һ���Ϸ���Field(�ֶ�����ָ���ֶδ���������ƥ��)
	// �ڲ���һ���ֶ�֮ǰ����Ҫȷ�����ֶ��Ǵ��ڵģ��ر��ǵ������Ѿ��������紫����ߴ���IO��
	// ǰ����������������ΪSTRUCT
	virtual bool IsValidField(const DVO_FIELD_NAME FieldName, int nType) = 0;

	// ��ȡ�ֶ���
	// ǰ����������������ΪSTRUCT
	virtual unsigned int GetFieldNum() = 0;

	// ��ȡ�ֶ�����
	// ǰ����������������ΪSTRUCT���ֶ�����ֵ�Ϸ�
	virtual int	GetFieldType(unsigned int uFieldIndex) = 0;
	
	// ��ȡ�ֶ���
	// ǰ����������������ΪSTRUCT���ֶ�����ֵ�Ϸ�
	virtual const char* GetFieldName(unsigned int uFieldIndex) = 0;

	// ��ȡ�ֶ�ֵ
	// ǰ����������������ΪSTRUCT���ֶ�����ֵ�Ϸ�
	virtual IDataValueObject* GetFieldValue(unsigned int uFieldIndex) = 0;

	// ��ȡ�ֶ�����
	// ǰ����������������ΪSTRUCT���ֶ����Ϸ�
	virtual int	GetFieldType(const DVO_FIELD_NAME FieldName) = 0;

	// ��ȡ�ֶ�ֵ
	// ǰ����������������ΪSTRUCT���ֶ����Ϸ�
	virtual IDataValueObject* GetFieldValue(const DVO_FIELD_NAME FieldName) = 0;
};


// == DVO����������֧����� ==//
// DVO��ֱ��֧�ֶ������������ͣ����ǿ���ͨ�������������ݱ����C�ַ��������֧��
// IBinaryEncoderDecoder����������������ַ���֮��ı����

// ���ݶ����ƿ鳤�ȼ��������ַ�������󳤶ȣ�������'\0')
// ������ǰԤ����Ҫ���ı��뻺��
// ���ӣ�
/*
	#define BIN_DATA_MAX_LEN				20
	#define BIN_DATA_ENCODED_MAX_LEN		(BIN_ENCODED_MAX_LEN(BIN_DATA_MAX_LEN))
	char BinEncodeBuffer[BIN_DATA_ENCODED_MAX_LEN + 1];
*/
#define BIN_ENCODED_MAX_LEN(nBinLen)	(((nBinLen) + 2) / 3 * 4)

// �����ַ������ȣ�������'\0'����������Ķ����ƿ����󳤶�
// ������ǰԤ����Ҫ���Ľ��뻺��
// ���ӣ�
/*
	#define STR_DATA_MAX_LEN				20
	#define STR_DATA_DECODED_MAX_LEN		(STR_DECODED_MAX_LEN(STR_DATA_MAX_LEN))
	char StrDecodeBuffer[STR_DATA_DECODED_MAX_LEN];
*/
#define STR_DECODED_MAX_LEN(nStrLen)	((((nStrLen) + 3) / 4) * 3)


// === DSO��� ===//

// == DSO�ĸ�ʽ ==//
enum DSO_FORMAT
{
	DSO_FORMAT_JSON = 0,	// JSON�ı���Ŀǰֻ֧�ָ���ʽ
};

// === �ڴ������ ===//
struct IDemAllocator
{
	virtual void* Malloc(size_t size)  = 0;
	virtual void  Free(void* memblock) = 0;
};

struct IDem
{
	// == Life Cycle  ==//
	virtual void Release() = 0;

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;

	// == Dependency Injection ==//
	// �����������ڴ������
	// DEMĬ�ϲ���CRT���ڴ������
	// ��������˸ýӿڣ���DEMʹ�������õ��ڴ������
	// �ýӿ�����Initialize֮ǰ����
	virtual void SetAllocator(IDemAllocator* pAllocator) = 0;

	// == Data Access ==//
	// ��ȡ������Ϣ
	virtual const char*	GetError() = 0;

	// == Manipulation ==//
	
	// ����һ��NULL���͵�DVO����
	// ����ֵ��	��NULL		--	��������ɹ������ص��Ƕ���ָ��
	//				NULL		--	��������ʧ��
	virtual IDataValueObject* CreateDVO() = 0;

	// ����DVO����
	virtual void DestroyDVO(IDataValueObject* pDvo) = 0;

	// ������������ݿ�Ϊ�ַ���
	// ���������	pBinData	--	��Ҫ����Ķ��������ݿ�ָ��
	//				nDataLen	--	��Ҫ����Ķ��������ݿ鳤��
	//				pStrBuf		--	��ű�����ַ����Ļ���
	//				nBufLen		--	��ű�����ַ����Ļ���Ĵ�С
	// ���������	nCodedLen	--	ʵ�ʱ������ַ�������
	// ����ֵ��	true		--	����ɹ�
	//				false		--	����ʧ�ܣ���ű������Ļ����С
	virtual bool Code(void* pBinData, int nDataLen, char* pStrBuf, int nBufLen, int& nCodedLen) = 0;

	// �����ַ���Ϊ���������ݿ�
	// ���������	pStr		--	��Ҫ������ַ���ָ��
	//				nStrLen		--	�ַ�������
	//				pBinBuf		--	��Ž��������ƿ�Ļ���
	//				nBufLen		--	��Ž��������ƿ�Ļ���Ĵ�С
	// �������:	nDecodedLen	--	ʵ�ʽ����Ķ����ƿ�ĳ���
	// ����ֵ��	true		--	����ɹ�
	//				false		--	����ʧ�ܣ���Ž��������ƿ�Ļ���Ĵ�С��С�����зǷ��ַ�
	virtual bool Decode(const char* pStr, int nStrLen, void* pBinBuf, int nBufLen, int& nDecodedLen) = 0;
	// ��DVOת��ΪDSO
	// ���������	pDvo		--	��Ҫ��ת��DVO�����ָ��
	//				nDsoFormat	--	ת�����DSO�ĸ�ʽ���ο�DSO_FORMAT
	//				pDsoDataBuf	--	���ת�����DSO�Ļ���ָ��
	//				uDataBufLen	--	���ת�����DSO�Ļ����С
	// ���������	uRealLen	--	ת�����DSO��ʵ�ʴ�С
	// ����ֵ��	true		--	ת���ɹ�
	//				false		--	ת��ʧ�ܣ�����GetErrorString�鿴ʧ��ԭ��
	// ���ӣ�
	/*
		IDataObjectConvertor* pConvertor;
		char DsoBuffer[100];
		unsigned int uRealLen;
		if (pConvertor->DVO2DSO(pDvo, DSO_FORMAT_JSON, DsoBuffer, sizeof(DsoBuffer), uRealLen))
		{
			printf("DSO:%s\n", DsoBuffer);
		}
		else
		{
			printf("Failed for %s\n", pConvertor->GetErrorStr());
		}
	*/
	virtual bool DVO2DSO(IDataValueObject* pDvo, int nDsoFormat, char* pDsoDataBuf, unsigned int uDataBufLen, unsigned int& uRealLen) = 0;

	// ��DSOת��ΪDVO
	// ���������	nDsoFormat	--	DSO�ĸ�ʽ���ο�DSO_FORMAT
	//				pDsoData	--	DSO���ݿ�ָ��
	//				uDsoSize	--	DSO���ݿ��С
	// ���������	pDvo		--	ת����DVO��ָ��
	// ����ֵ��	true		--	ת���ɹ�
	//				false		--	ת��ʧ��
	// ע�⣺		pDvo��ָ�Ķ�����Convertor�ڲ�������ʹ�ú���Ҫ�ͷ�
	// ���ӣ�
	/*
		IDataValueObject* pDvo;
		IDataObjectConvertor* pConvertor;
		char DsoData[] = "{1234}";
		if (pConvertor->DSO2DVO(DDF_JSON, DsoData, (unsigned int)strlen(DsoData), pDvo)
		{
			printf("%d\n", pDvo->GetLongLong());
			pDvo->Release();
		}
		else
		{
			printf("Convert failed for %s\n", pConvertor->GetErrorStr());
		}
	*/
	virtual bool DSO2DVO(int nDsoFormat, const char* pDsoData, unsigned int uDsoSize, IDataValueObject*& pDvo) = 0;

	
};

//=== �ⲿ���ø�ͷ�ļ�ʱ�������ӿ����� ===//
#ifndef  DEM_INTERNAL_SIGNATURE 

extern "C" IDem*					DemCreate();
#define FUNC_NAME_DEM_CREATE		"DemCreate"
typedef IDem*						(*FUNC_DEM_CREATE)();

#endif // #ifndef  DEM_INTERNAL_SIGNATURE 

#endif // #ifndef __I_DATA_EXCHANGE_MECHANISM_H__
