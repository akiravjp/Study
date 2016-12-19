#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__
//======================================================
//====				���ػ�������					====
//======================================================


enum LOCALIZATION_CHARACTER_SET
{
	LOCALIZATION_CHARACTER_SET_GBK		= 0,	//GBK����
	LOCALIZATION_CHARACTER_SET_BIG5		= 1,	//BIG5����
	LOCALIZATION_CHARACTER_SET_ENGLISH	= 2,	//Ӣ�ı���
	LOCALIZATION_CHARACTER_SET_VIETNAM	= 3,	//Խ���ı���
};

#ifndef LOCALIZATION_INTERNAL_SIGNAL
//------�ӿں�����ԭ�Ͷ���----------
typedef int (*fnLOC_IsCharacterNotAllowAtLineHead)(const char* pCharacter);
typedef int (*fnLOC_GetCharacterWide)(const char* pCharacter);
//------�ӿں����ĺ������ַ���----------
#define	FN_IS_CHARACTER_NOT_ALLOW_AT_LINE_END		"LOC_IsCharacterNotAllowAtLineHead"
#define FN_GET_CHARACTER_WIDE						"LOC_GetCharacterWide"

extern "C"
{
	//��ȡ�ñ��ػ��汾�����Լ�
	LOCALIZATION_CHARACTER_SET LOC_GetLocalizationCharacterSet(LOCALIZATION_CHARACTER_SET);
	//���ĳ���ַ��Ƿ�Ϊ����������׵��ַ������������ַ��򷵻�0�����򷵻��ַ�ռ���ӽ���
	int LOC_IsCharacterNotAllowAtLineHead(const char* pCharacter);
	//�õ�һ���ַ��Ŀ�ȣ�ռ�����ֽڣ�
	int LOC_GetCharacterWide(const char* pCharacter);
}

#endif //LOCALIZATION_INTERNAL_SIGNAL

#endif //__LOCALIZATION_H__

