//---------------------------------------------------------------------------
// ������Ե�����2 TextParamAnalyse �ı���������
// ��Ȩ����:       2007 ��ɽ���(Kingsoft)
// ��������������: Խ��(wooy)
//---------------------------------------------------------------------------
#ifndef __TEXT_PARAM_ANALYSE_H__
#define __TEXT_PARAM_ANALYSE_H__

#ifndef WIN32     // linux
	#define		C_TPA_API extern "C"
#else               //WIN32
	#ifdef TEXT_PARAM_ANALYSE_INTERNAL
		#define C_TPA_API extern "C" __declspec(dllexport)
	#else
		#define C_TPA_API extern "C" __declspec(dllimport)
	#endif
#endif

//-----------------------------------------------------------------------
// ע�⣺��Щ�ӿں������Ը��ָ���ָ�봫�����������Щ������ʵ�ִ����У�ͳ
// һ�����Ƿ�Ϊ��ָ��ļ�飬����Ҳ�����õ�ģ����Ҫ���б�֤��ָ�벻Ϊ�գ�
// KTextParamAnalyseInfo::pStringҲ�����⡣������������������������������
//-----------------------------------------------------------------------
namespace KTextParamAnalyse
{
	struct KTextParamAnalyseInfo
	{
		const char*		pString;		//ָ������ı��������ݵĻ�����������Ҫ��0��β
		int				nStringMaxLen;	//�ı��������ݵĻ������е����ݵĳ��ȣ��ֽ�����
		int				nStartPos;		//��ǰ��������λ�ã���pString��ʼ���(�ֽڳ���)ƫ������
	};
	enum STANDARD_RESULT
	{
		SR_OK = 0,			//�㶨
		SR_FAIL,			//ʧ��
		SR_TIMEOUT,			//��ʱ
		SR_DISPATCH_FAIL,	//����ʧ��
		SR_CMD_ERR,			//�������
		SR_NOT_ALLOW,		//������������������Ȩ���
		SR_NONE,			//�޶�Ӧ���������ѯ�ģ�ָ�����󲻴���
		STANDARD_RESULT_COUNT, 
	};
	enum
	{
		MAX_FIELD_PREFIX_LEN = 15, //�ֶ�ǰ׺��������ȣ�����ð�ź��ַ�����β��0
	};
	//�ӿ�ʼ����λ�û�ȡһ���ַ�����nMaxLen��ʾ�ַ�������󳤶�(������β��)��
	//�������pString���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseString(KTextParamAnalyseInfo& info, char* pString, int nMaxLen);
	//�ӿ�ʼ����λ�û�ȡһ���ַ����ֶΣ�pFieldPrefixΪ�ֶ�ǰ׺��ʶ��nMaxLen��ʾ�ַ�������󳤶�(������β��)��
	//����ַ����������򷵻�ʧ�ܣ�����ַ�������Ϊ0��Ҳ���سɹ������سɹ�ʱpString���Ѵ��һ����0��β���ַ�����
	//�����pFieldPrefix�����ַ�������Ҫ��:�ָ�����bMatchΪ������������ʾ�����������Ƿ�Ϊָ�����ֶΣ��ֶ�ǰ׺�Ƿ���ƥ�����ˣ���
	//�������pString���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseFieldString(KTextParamAnalyseInfo& info, const char* pFieldPrefix, char* pString, int nMaxLen, bool& bMatch);
	//�ӿ�ʼ����λ�û�ȡһ�������ֶΣ�pFieldPrefixΪ�ֶ�ǰ׺��ʶ
	C_TPA_API bool	AnalyseFieldInteger(KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nValue, bool& bMatch);
	//�ӿ�ʼ����λ�û�ȡһ��16���������ֶΣ�pFieldPrefixΪ�ֶ�ǰ׺��ʶ
	C_TPA_API bool	AnalyseFieldInteger16(KTextParamAnalyseInfo& info, const char* pFieldPrefix, unsigned int& uValue, bool& bMatch);
	//�ж��Ƿ�Ϊָ�����ֶ�
	C_TPA_API bool	AnalyseIsField(const KTextParamAnalyseInfo& info, const char* pFieldPrefix);
	//�ж��Ƿ�Ϊָ�����ֶΣ��������жϽ���������Ƿ�Ҫ�������ֶΡ��ú���ִ��ÿһ��ֻ������ǰ���һ���ֶΣ�����������������
	//����˵����bJumpIfMath Ϊ��ֵʱ��ʾ���Ϊָ���ֶ���������Ϊ��ֵʱ��ʾ�������ָ���ֶ�������
	//����˵����bEncounterErr Ϊ������������ʾ����ʱ�Ƿ��������������������һ����������ֶΣ�����ֵһ����false��
	//����ֵ��ʾ���Ƿ���Ϊ������������������ǰ���һ���ֶ�
	C_TPA_API bool	AnalyseIsFieldThenJump(KTextParamAnalyseInfo& info, const char* pFieldPrefix, bool bJumpIfMatch, bool& bEncounterErr);
	//��ȡ�׸��ֶε�ǰ׺���ƣ�pFieldPrefixָ��Ļ��������Ȳ�С��MAX_FIELD_PREFIX_LEN+1���ֽڣ����ص��ֶ�ǰ׺����ð�ź��ַ�����β��0
	C_TPA_API bool	AnalyseGetFirstFieldPrefix(const KTextParamAnalyseInfo& info, char* pFieldPrefix);
//====���û����ֶη���������֮����������������ڵļ������=====
	//�������к��ֶ�
	C_TPA_API bool	AnalyseFieldSn(KTextParamAnalyseInfo& info, unsigned int& uSn0, unsigned int& uSn1);
	//�������������ֶΣ�����ֵ��ʾ�Ƿ�ɹ�ȡ��������Ҫ��ֵ����������bMatch��ʾ���ڷ������ֶ��Ƿ���GROUP�ֶ�
	C_TPA_API bool	AnalyseFieldGroup(KTextParamAnalyseInfo& info, int& nArea, int& nGroup, bool& bMatch);
	//�������������ֶΣ�����ֵ��ʾ�Ƿ�ɹ�ȡ��������Ҫ��ֵ����������bMatch��ʾ���ڷ������ֶ��Ƿ���GROUPN�ֶ�
	//�������pGroupName���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseFieldGroupN(KTextParamAnalyseInfo& info, char* pGroupName, int nMaxLen, bool& bMatch);
	//�����ʺ����ֶ�
	//�������pAccount���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseFieldAcc(KTextParamAnalyseInfo& info, char* pAccount, int nMaxLen, bool& bMatch);
	//������ɫ���ֶ�
	//�������pRole���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseFieldRole(KTextParamAnalyseInfo& info, char* pRole, int nMaxLen, bool& bMatch);
	//�����������ֶ�
	//�������pObj���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseFieldObj(KTextParamAnalyseInfo& info, char* pObj, int nMaxLen, bool& bMatch);
	//�����nSizeΪpData�ɽ��ܵ��ַ�������󳤶�(��������),������nSizeΪʵ��ȡ�õ��ַ����ĳ���(��������)
	//�������pData���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseSizeFieldText(KTextParamAnalyseInfo& info, const char* pFieldPrefix, char* pData, int& nSize, bool& bMatch);
	//�ж��Ƿ�ΪT_????�Σ�����������ݳ���Ϊ����
	C_TPA_API bool	AnalyseSizeFieldTextSize(const KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nSize, int& nDataOffset);
	//�����nSizeΪpData�ɽ��ܵ��ַ�������󳤶�,������nSizeΪʵ��ȡ�õ��ַ����ĳ���
	//�������pData���������㹻����ú�������false����ά�����ݴ���λ�ò��䡣
	C_TPA_API bool	AnalyseSizeFieldBin(KTextParamAnalyseInfo& info, const char* pFieldPrefix, void* pData, int& nSize, bool& bMatch);
	//�ж��Ƿ�ΪB_????�Σ�����������ݳ���Ϊ����
	C_TPA_API bool	AnalyseSizeFieldBinSize(const KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nSize, int& nDataOffset);

//====�����ֶι���=====
	//��ȡ'����Ĵ�����'�ֶεı�׼�ַ���
	C_TPA_API const char*	GetStandardResultFieldString(STANDARD_RESULT eResult);

	//��һ���ַ�����������ͷ����ȡһ����16���Ʊ�ʾ����ֵ
	//����pStringΪ������ͷ���Ŀ�ʼָ�룬����nStringMaxLenΪ�������ĳ���
	//ת�������Դ�����������β���һ����'0~9'�ҷ�'A-F'���ַ�Ϊֹ������nConvertLen��������ת��������ַ�����Ŀ��
	//����ֵΪ��ȡ������ֵ�����δ��ȡ����ֵ���򷵻�0����ʱnConvertLenҲ����0��
	C_TPA_API bool ConvertString16ToInteger(const char* pString, int nStringMaxLen, int& nConvertedLen, unsigned int& uValue);

	//��һ���ַ�����������ͷ����ȡһ����10���Ʊ�ʾ����ֵ
	//����pStringΪ������ͷ���Ŀ�ʼָ�룬����nStringMaxLenΪ�������ĳ���
	//ת�������Դ�����������β���һ����'0~9'���ַ�Ϊֹ������nConvertLen��������ת��������ַ�����Ŀ��
	//����ֵΪ��ȡ������ֵ�����δ��ȡ����ֵ���򷵻�0����ʱnConvertLenҲ����0��
	//���Դ�������
	C_TPA_API bool ConvertString10ToInteger(const char* pString, int nStringMaxLen, int& nConvertedLen, int& nValue);
};

#endif //__TEXT_PARAM_ANALYSE_H__
