//-------------------------------------------------------------------------
//	��Ӱ��˵�����	GMC_SDK
//	��Ȩ����:			2010 ��ɽ���(Kingsoft)
//	��������������:	2010-1 Golton Gao
//-------------------------------------------------------------------------
#ifndef __I_GMC_CLIENT_H__
#define __I_GMC_CLIENT_H__

// ��Ϸ����Ӧ��ʵ�ֵĽӿ�
struct IGameSpaceLogicForGmc
{
	//
	// ��������
	// �������	szNotice -- ��������
	//				szOption -- ����ѡ���ǰȡֵ��Χ��
	//						 ""			 -- ���ַ�������ʾһ�㹫��
	//						 "IMPORTANT" -- ��ʾ��Ҫ����
	//						 "NEWS"		 -- ��ʾ���Ź���
	// ���ز���	true	-- ��������ɹ�
	//				false	-- ��������ʧ��
	virtual bool BroadcastNotice(const char* szNotice, const char* szOption) = 0;

	//
	// ���Ľ�ɫ
	// �������	szRole	-- ��ҽ�ɫ��
	//				szMsg	-- ���ĵ���Ϣ����
	// ���ز���	true	-- ���ĳɹ� 
	//				false	-- ����ʧ��
	virtual bool ChatToPlayerByRole(const char* szRole, const char* szMsg) = 0;

	//
	// �����˺�
	// �������	szAcc	-- ����˻���
	//				szMsg	-- ���ĵ���Ϣ����
	// ���ز���	true	-- ���ĳɹ�
	//				false	-- ����ʧ��
	virtual bool ChatToPlayerByAccount(const char* szAcc, const char* szMsg) = 0;

	// 
	// �߳���ң����ݽ�ɫ��
	// �������	szRole	-- ��ҽ�ɫ��
	// ���ز���	true	-- �߳��ɹ�
	//				false	-- �߳�ʧ��
	virtual bool KickPlayerByRole(const char* szRole) = 0;

	// 
	// �߳���ң������˺ţ�
	// �������	szAcc	-- ����˺���
	// ���ز���	true	-- �߳��ɹ�
	//				false	-- �߳�ʧ��
	virtual bool KickPlayerByAccount(const char* szAccount) = 0;

	//
	// ˲�����
	// �������	szRole	-- ��ҽ�ɫ��
	//				nMapId	-- Ŀ�ĵصĵ�ͼID
	//				nX		-- Ŀ�ĵص�X����
	//				nY		-- Ŀ�ĵص�Y����
	//				nZ		-- Ŀ�ĵص�Z����
	// ���ز���	true	-- ˲�Ƴɹ�
	//				false	-- ˲��ʧ��
	virtual bool MovePlayerToLocationByRole(const char* szRole, int nMapId, int nX, int nY, int nZ) = 0;

	//
	// ˲����ҵ�Ŀ���ɫ���
	// �������	szRole			-- ��ҽ�ɫ��
	//				szTargetRole	-- Ŀ�Ľ�ɫ
	// ���ز���	true			-- ˲�Ƴɹ�
	//				false			-- ˲��ʧ��
	virtual bool MovePlayerToPlayerByRole(const char* szRole, const char* szTargetRole) = 0;

	//
	// ������ҷ�����Ϊ
	// �������	szRole	-- ��ҽ�ɫ��
	//				bAllow	-- true��������ҷ���; false���ֹ��ҷ���
	// ���ز���	true	-- ���Ƴɹ�
	//				false	-- ����ʧ��
	virtual bool ControlTalkBehaviorByRole(const char* szRole, bool bAllow) = 0;
};

struct IGmcClient
{
	virtual void Release() = 0;

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;
	virtual void Tick() = 0;

	//
	// ������GM��������Ϣ
	// �������	szAcc		--	����˺�
	//				szRole		--	��ҽ�ɫ��
	//				szChatType	--	�������ͣ����ڷ��࣬�����Ǿ�������ͬ����Ϸ��������չ
	//								"Accuse-trick"	������Ϣ
	//								"Accuse-treat"	���
	//								"Chock-none"	����
	//								"Helpme-none"	�˹������ظ�
	//				szMsg		--	����ľ�������
	virtual bool SendChatMsg(const char* szAcc, const char* szRole, const char* szChatType, const char* szMsg) = 0;

	virtual void SetGameSpaceLogicForGmc(IGameSpaceLogicForGmc* pGameSpaceLogic) = 0;
};

//=== �ⲿ���ø�ͷ�ļ�ʱ�������ӿ����� ===//
#ifndef  GMC_CLIENT_INTERNAL_SIGNATURE 

extern "C" IGmcClient*	GmcClientCreate();
#define FUNC_NAME_GMC_CLIENT_CREATE "GmcClientCreate"
typedef IGmcClient* (*FUNC_GMC_CLIENT_CREATE)();

#endif // #ifndef  GMC_CLIENT_INTERNAL_SIGNATURE 

#endif
