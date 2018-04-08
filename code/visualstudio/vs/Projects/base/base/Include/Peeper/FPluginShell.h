/*****************************************************************************************
                    ������������������������������������������������������
                    ���������У�����༭������ģ�����Ĺ淶����������
                    ������������������������������������������������������
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-9
------------------------------------------------------------------------------------------
	���ļ�������Peeper�༭������ģ�����Ĺ淶��

	Peeper�༭���༭(ģ��)���

		�༭ģ�����Ĳ��������Ϊ�༭��(Peeper)��
		���������뵼����������������
		FPluginQuerryInfo
			���ڲ�ѯ�������Ϣ������ԭ�ͼ������fnFPluginQuerryInfo��
		FPluginGetShell
			���ڻ�ȡ�����Shell�ӿڶ��󣬺���ԭ�ͼ������fnFPluginGetShell��
			����Ķ�������ӿ�ΪKPluginShell�����ͨ��FPluginGetShell��ͻ��ṩ�˽ӿڶ���
			���ô˺���ʱ�ᴫ��IPeeperShell�ӿ�ʵ����ָ�룬�������˽ӿ�ָ�룬����ʱ����ͨ��
			�˽ӿڵķ�����Peeper����Ϣ������Peeper���ָ���Ĳ�����

		IFPluginShell�ӿ�
			IFPluginShellΪPeeper���ݲ���Ľӿڣ�Peeperͨ������ĺ���FPluginGetShell
		��ô˽ӿ�ʵ����ָ�롣
			IFPluginShell�ṩ�����в���������
		CreateResourceHolder
			����һ����Դ�����ӿڡ���Դ�����ӿڿ�������ִ����Դ�Ĵ򿪡���ʾ���༭���洢��
			������
		OnCmd
			��Ӧ�Դ˲���Զ��Ĳ˵����������Ƚ���Ĳ�����
			�ڲ���Ҫ��ʹ��IFPluginShell�ӿڵ�ʱ�򣬵���Release�����ͷ�����
*****************************************************************************************/
#pragma once

struct KFuncInfo
{
	char			Name[64];	//��������
	int				Version;	//���ܰ汾Ҫ��
};

//======================================
//	����ģ������Ϣ�ṹ
//======================================
struct KFPluginInfo
{
	int		Size;					//�ṹ��С
	char	Title[STRING_SHORT];	//�������
	char	Intro[1024];			//���˵��
	int		NumResType;				//�ɴ����������Դ���͵ĸ���
	KResTypeInfo*	pResTypeInfo;	//�ɴ����������Դ���͵���Ϣ
	int		NumFunc;				//�ɴ����������Դ���͵ĸ���
	KFuncInfo*		pFuncInfo;		//��ִ�еĹ��ܵ���Ϣ
};

enum PEEPER_PLUGIN_MSG
{
	PEEPER_ACTIVE = 1,
	//wparam = bActive
	PEEPER_CONFIGURABLE = 2,
	//return = bCofigurable

	PEEPER_CONFIG = 3,
};

//======================================
//	���ģ��ӿ�
//======================================
interface iKFPluginShell
{
	virtual int		   PeeperMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	//����һ����Դ�����ӿڶ���
	virtual void*	   CreateResourceHolder(HWND hParentWnd, RECT* prc, int nResType) = 0;
	//����һ�����ܵ��ýӿ�
	virtual IFunction*  CreateFunctionInstance(int nFuncIndex) = 0;
	virtual void	   OnCmd(int nCmd) = 0;					//��Ӧ��������
	virtual void	   Release() = 0;						//�ͷŽӿ�
};

//--------------------------------------------------------------------------
//	FPluginQuerryInfo����ԭ�ͣ����ڻ�ȡ�������Ϣ��
//	������pInfo ָ��һ�������Ϣ�ṹ��ָ�룬����д�����Ϣ�󷵻ء�
//--------------------------------------------------------------------------
//******************************************************************************
typedef void (*fnFPluginQuerryInfo)(KFPluginInfo* pInfo);

//--------------------------------------------------------------------------
//	FPluginGetShell����ԭ�ͣ����ڻ�ȡ����Ľӿ�Shell����
//	������pInfo ָ��һ�������Ϣ�ṹ��ָ�룬����д�����Ϣ�󷵻ء�
//--------------------------------------------------------------------------
typedef iKFPluginShell* (*fnFPluginGetShell)(iKPeeperShell* pPeeper, int nUiCmdBase);

//======================================
//	����Ľ������Χ
//======================================
#define	FPLUGIN_COMMAND_RANGE	0x200
