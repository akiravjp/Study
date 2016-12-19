/**********************************************************************
* Դ��������: futu_message_interface.h
* �������Ȩ: �������ӹɷ����޹�˾
* ϵͳ����  : 06�汾�ڻ�ϵͳ
* ģ������  : �����ڻ��ܱ߽ӿ�
* ����˵��  : �ܱ߽ӿ����ݲ�������
* ��    ��  : xdx
* ��������  : 20110315
* ��    ע  : �������Ͷ���   
* �޸���Ա  ��
* �޸�����  ��
* �޸�˵��  ��20110315 ����
**********************************************************************/
#ifndef _FUTU_MESSAGE_INTERFACE_H_
#define _FUTU_MESSAGE_INTERFACE_H_

#include "futu_data_types.h"

#ifdef _WIN32
#  ifdef HSAPI
#  undef HSAPI  
#  endif
#  define HSAPI __stdcall
#else
#    define HSAPI 
#endif

//����ӿ�ͳһ�Ĳ�ѯ�����ýӿ� (����COM��׼)
struct IHSKnown
{
	/**
	 * ��ѯ�뵱ǰ�ӿ���ص������ӿ�(���汾�Ľӿ��ݲ�ʹ��)
	 *@param HS_SID  iid  �ӿ�ȫ��Ψһ��ʶ
	 *@param IKnown **ppv ����iid��Ӧ�Ľӿ�ָ��
	 *@return ERR_OK �ɹ�,ERR_FAIL δ�鵽iid ��Ӧ�ӿ�
	*/
	virtual unsigned long  HSAPI QueryInterface( const char * iid, IHSKnown **ppv ) = 0;

	/**
	 * ���ýӿڣ����ü�����һ
	 *@return ��ǰ���ü���
	*/
	virtual unsigned long  HSAPI AddRef() = 0;

	/** 
	 * �ͷŽӿڣ����ü�����һ������Ϊ0ʱ�ͷŽӿڵ�ʵ�ֶ���
	 *@param ERR_OK��ʾ�ɹ�,������ʾʧ��
	*/
	virtual unsigned long  HSAPI Release() =  0;
};

/*
  һ����Ϣ���ݼ�¼,�����˺ܶ��Field=Value,����Field���ظ�
  ���ظ�������ͬ��Field,�򸲸��ϴε�����
  Ϊ��ʹ�ӿڿ�����,��֧��������������:
    ���ַ���(char),��'A','1',
	����(int),��123,-2343
	������(float),��23.50,-34.34
	�ַ�����(C���Է��'\0'��β�Ĵ�)(char*),��"Hello World"
	ע����ӿڸ��𷽷����̰߳�ȫ
*/
struct IFuRecord:public IHSKnown
{
	///������ݵķ���,������field�򸲸���ֵ
	/**
	 * ���һ���ַ���ֵ
	 *@param sField   �ֶ�����
	 *@param cValue   һ���ַ�ֵ
	 *@return ERR_OK��ӳɹ�,������ʾʧ��
	 [���̰߳�ȫ]
    */
	virtual int HSAPI SetChar(const char* sField,char cValue) = 0;

	/**
	 * ���һ������ֵ
	 *@param sField  �ֶ�����
	 *@param iValue  һ������ֵ
	 *@return ERR_OK��ӳɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SetInt(const char* sField,int iValue) = 0;

	/**
	 * ���һ������ֵ
	 *@param sField �ֶ�����
	 *@param cValue һ������ֵ
	 *@return ERR_OK��ӳɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SetDouble(const char* sField,double dValue) = 0;

	/**
	 * ���һ���ַ���(C���Ը�ʽ'\0'��β���ַ���)
	 *@param sField �ֶ�����
	 *@param cValue һ���ַ���ֵ
	 *@return ERR_OK��ӳɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SetString(const char* sField,const char* strValue) = 0;


    ///�����ֶη������ݵķ���
	/**
	 * ��ȡһ���ַ���ֵ
	 *@param sField �ֶ�����
	 *@return ��Ч�ַ�ֵ;�ֶβ�������Ĭ��'\0'
	 [�̰߳�ȫ]
	*/
	virtual char HSAPI GetChar(const char* sField) = 0;

	/**
	 * ��ȡһ������ֵ
	 *@param sField �ֶ�����
	 *@return ����һ������ֵ;�ֶβ�������Ĭ�Ϸ���0
	 [�̰߳�ȫ]
	*/
	virtual int  HSAPI GetInt(const char* sField) = 0;

	/**
	 * ���һ������ֵ
	 *@param sField �ֶ�����
	 *@return ����һ������ֵ;�ֶβ�������Ĭ�Ϸ���0.0(ע�⸡���͵ľ�������)
	 [�̰߳�ȫ]
	*/
	virtual double HSAPI GetDouble(const char* sField)  = 0;

	/**
	 * ���һ���ַ���
	 *@param sField �ֶ�����
	 *@return ����һ���ַ���,�粻���ڸ��ֶ��򷵻ؿ��ַ���""(ע�ⲻ��NULL)
	 [�̰߳�ȫ]
	*/
	virtual const char* HSAPI GetString(const char* sField) = 0;

	///�������ʷ���,ͨ���˷��ʿɱ���������¼
	/**
	 * �ƶ�����¼ͷ(��һ��Field=Value)
	 *@return ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI MoveFirst() = 0;

	/**
	 * ��һ����¼
	 *@return ERR_OK��ʾ�ɹ�,������ʾʧ�ܻ��Ѿ�����¼β
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI MoveNext() = 0;

	/**
	 * �ж��Ƿ��Ƶ��˼�¼β
	 *@return 0��ʾδ����¼β,1��ʾ�ѵ���¼β
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI IsEOF() = 0;

	/**
	 * ��ȡ��ǰ�ֶ���(ͨ���������Է��ʵ�ֵ)
	 *@return NULL��ʾ�ѵ���β��������,��NULL��ʾ�ֶ���
	 [�̰߳�ȫ]
	*/
	virtual const char* HSAPI GetFieldName() = 0;

	/** 
	 * ɾ��һ���ֶ�
	 *@param sField Ҫɾ�����ֶ���
	 *@return ERR_OK��ʾɾ���ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
    */
	virtual int HSAPI RemoveField(const char* sField) = 0;

	/**
	 * �Ƿ����ĳ���ֶ�
	 *@param sField �ֶ���
	 *@return 0��ʾ������,1��ʾ����
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI IsExist(const char* sField) = 0;

	/**
	 * ɾ�����е��ֶ�
	 *@return ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI Clear() = 0;

	/** 
	 * ��ȡ��¼����(Field=Value)
	 *@return ��ʾ��¼(Field=Value)������
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI GetCount() = 0;
};

//�ڻ���Ϣ�ӿ�,һ����Ϣ����������Ϣ������,����һ������IFuRecord���
//ע�������ӿڷ��̰߳�ȫ����˾�����Ҫ���߳�ͬʱ������Ϣ
struct IFuMessage:public IHSKnown
{
	/**
	 * ������Ϣ����
     *@param iType �μ�FUTU_MSG_TYPE�Ķ���
	 *@param iMode ��ʾ����Ϣ��������Ӧ��,0-����,1-Ӧ��
	 *@return ERR_OK��ʾ�ɹ�,������ʾ��Ч��֧�ֵ���Ϣ����
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI SetMsgType(int iType,int iMode) = 0;

	/** 
	 * ��ȡ��Ϣ����
	 *@param [out]lpMsgMode ��Ϣģʽ.�ο�FUTU_MSG_MODE�Ķ���
	 *@return  ��Ϣ����.�ο�FUTU_MSG_TYPE�Ķ���
	 [�̰߳�ȫ]
    */
	virtual int HSAPI GetMsgType(int* lpMsgMode = NULL) = 0;

	/**
	 * ��ȡ��¼����
	 *@param >=0��ʾ��¼����,������ʾ�����ʧ��
	 [�̰߳�ȫ]
	*/
	virtual int HSAPI GetCount() = 0;

	/** 
	 * ����һ����¼,�������ص�ָ���Բ�����ֵ
	 *@return ��NULL��ʾһ����Ч�ļ�¼,NULL��ʾ�����ڴ�ʧ��
	 [���̰߳�ȫ]
	*/
	virtual IFuRecord* HSAPI AddRecord() = 0;

	/**
	 * ��ȡһ����¼
	 *@param iIndex ��¼����λ��,��0��ʼ����
	 *@return ��NULL��ʾһ����Ч�ļ�¼,NULL��ʾ����Խ��
	 [���̰߳�ȫ]
	*/
	virtual IFuRecord* HSAPI GetRecord(int iIndex = 0) = 0;

	/**
	 * ɾ��һ����¼
	 *@param iIndex ��¼����λ��,��0��ʼ����
	 *@return ERR_OK��ʾɾ������,����ʧ��(����������Խ��)
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI DelRecord(int iIndex = 0) = 0;

	/**
	 * ɾ�����еļ�¼
	 *@return ERR_OK��ʾ�ɹ�,������ʾʧ��
	 [���̰߳�ȫ]
	*/
	virtual int HSAPI Clear() = 0;
};

//�����ӿ�
#ifdef __cplusplus
extern "C"
{
#endif

   /** 
    * ����һ���µ���Ϣ
	*@param iMsgType ��Ϣ����,��ο���ϢFUTU_MSG_TYPE���Ͷ���
	*@param iMsgMode ��Ϣģʽ,��ο���ϢFUTU_MSG_MODE���Ͷ���
	*return          ��NULL��ʾһ����Ч����Ϣ,NULL��ʾ�����ڴ�ʧ��
	[�̰߳�ȫ]
   */
   IFuMessage* HSAPI NewFuMessage(int iMsgType = MSG_TYPE_UNKNOWN,int iMsgMode = MSG_MODE_UNKNOWN);

#ifdef __cplusplus
}
#endif


#endif/*futu_msg_interface.h*/

