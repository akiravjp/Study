/*****************************************************************************************
                    ������������������������������������������������������
                    �������������ⲿ���ʣУ�����Ľӿڡ���������������
                    ������������������������������������������������������
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-11
------------------------------------------------------------------------------------------
		Peeper�ڻ�ȡ�ⲿ����Ľӿ�ʵ��ʱ�ᴫ��IPeeperShellʵ����ָ��������
	�������˽ӿ�ָ�룬����ʱ����ͨ���˽ӿڵķ�����Peeper����Ϣ������Peeper
	���ָ���Ĳ�����
		ö�ٽṹKP_MESSAGE�г�������IPeeperShell���Խ��ܴ������Ϣ������
	��ϢPM_COMMAND������Peeper�ڲ������ģ��ⲿ��������Ϣ��Peeper��
*****************************************************************************************/
#ifndef __PEEPERSHELL_H__
#define __PEEPERSHELL_H__

//======================================
//		Peeper����ӿ�
//======================================
interface iKPeeperShell
{
	virtual int	SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) = 0;
	virtual int	PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) = 0;
	virtual IFunction* CreateFunctionInstance(LPSTR szFunctionName) = 0;	//�������ܰ�����
};

//----���õ�ǰĿ¼----
#define PEEPER_SET_CUR_PATH		0x04
//----���Ŀ¼----
#define PEEPER_RELATE_PATH		0x08

//======================================
//	Peeper����Ϣ
//======================================
enum	KP_MESSAGE
{
//----�������Խ��������----
	PM_COMMAND	= 1,
	//�������Խ�������������ᷢ�ʹ���Ϣ��Peeper
	//wParam  = �˵����ؼ������Ǽ��̿�ݼ���ID

	PM_SPECIAL_CMD,
	//
	//wParam = nCmdBase
	//lParam = nSpecialCmd

//----��ȡ��Ϣ������----

	PM_INSTANCE,
	//��ȡPeeper����ģ����
	//����   = Peeeper����ʵ�������HINSTANCE��

	PM_MAIN_WND,
	//��ȡPeeper�����ھ��
	//����   = Peeper�����ڵľ����HWND��

	PM_GET_WORK_PATH,
	//���Peeper���У�������Ŀ¼��
	//lParam = ָ��һ��Buffer�����ڽ��ܻ�ȡ����Ŀ¼�ַ������������Ĵ�СҪ��С��MAX_PATH��

	PM_GET_FPLUGIN_PATH,
	//���Peeper�Ĳ��Ŀ¼��
	//lParam = ָ��һ��Buffer�����ڽ��ܻ�ȡ����Ŀ¼�ַ������������Ĵ�СҪ��С��MAX_PATH��

	PM_GET_REF_PATH,
	//��ȡPeeper����Ŀ¼
	//wParam = �ڼ�������Ŀ¼
	//lParam = ָ��һ��Buffer��������Ŀ¼��Чʱ�����ڽ��ܻ�ȡ���Ĺ���Ŀ¼�ַ������������Ĵ�СҪ��С��MAX_PATH��
	//Return = �˹���Ŀ¼�Ƿ���Ч��

	PM_SET_REF_PATH,
	//����Peeper����Ŀ¼����ʹ����Ч
	//wParam = �ڼ�������Ŀ¼
	//lParam = ָ��һ���ַ���Buffer���ַ���ΪҪ���õ�Ŀ¼��

	PM_GET_PEEPER_CONFIG_FILE_NAME,
	//��ȡPeeper�����ļ����ļ���
	//lParam = ָ��һ��Buffer��������д�ļ���

//----��������----

	PM_EXIT,
	//�����˳�Peeper
	
	PM_RELOAD_FPLUGIN,
	//���¼��ع��ܲ��

	PM_REGISTER_SPECIAL_CMD,
	//ע�����⺯��
	//wParam = Plugin��ʼ��ʱ�յ���nCmdbase
	//lParam = ��ʾ����
	//����   = CMD id

	PM_UNREGISTER_SPECIAL_CMD,
	//ȡ��ע�����⺯��
	//lParam = ����id

//----���ڲ������----

	PM_CREATE_CHILD_WND,
	//Ҫ�󴴽��Ӵ���
	//wParam = ָ���Ӵ��������Ƶ��ַ��������Դ���NULL����Peeper����Ĭ�����͵Ĵ��ڡ�(char*)
	//lParam = ָ���������½����ڵ�iKWndHolder�ӿ�ʵ����ָ��(iKWndHolder)
	//����   = �´������Ӵ��ڵľ����HWND��

	PM_DESTROY_CHILD_WND,
	//Ҫ��ر��Ӵ���
	//wParam = Ҫ�رյ��ִ��ڵľ��(HWND)

	PM_CREATE_FILELIST_VIEW,
	//Ҫ�󴴽��ļ��б���
	//wParam = �����ھ��(HWND)
	//lParam = ���ھ�������(RECT*)
	//����   = �´����Ĵ��ڵİ�������ָ��(HWND)

	PM_CREATE_FOLDER_VIEW,
	//Ҫ�󴴽��ļ����������
	//wParam = �����ھ��(HWND)
	//lParam = ���ھ�������(RECT*)
	//����   = �´����Ĵ��ڵİ�������ָ��(HWND)

	PM_CREATE_IMG_VIEW,
	//����ͼ����ʾ����
	//����   = ��������ͼ����ʾ���ڵĽӿ�ָ�루KImageView*��

//----�϶����----

	PM_DRAG_BEGIN,
	//�����϶���Դ״̬
	//lParam = ���϶�����Դ�ṹָ�루KResource*��

	PM_QUERY_DRAG,
	//��ѯ�϶�����Դ����Ϣ
	//lParam = ���ձ��϶���Դ����Ϣ�Ľṹ��ָ�루KResource*��
	//����   = �Ƿ�ɹ�ȡ���϶���Դ����Ϣ��bool��

//----�������----
	PM_INSERT_MENU,
	//����˵���
	//lParam = �˵��ľ��(HMENU)
	//wParam = �˵�����id�ĵ��ڻ�ֵ(int)

	PM_REMOVE_MENU,
	//�Ƴ�һ���˵���
	//lParam = �˵��ľ��(HMENU)

	PM_GET_REBAR,
	//���rebar�Ĵ��ھ��
	//����   = rebar�Ĵ��ھ����HWND��

	PM_INSERT_TOOLBAR,
	//����µĹ�����
	//lParam = �������Ĵ��ھ��(HWND)

	PM_SHOW_TOOLBAR,
	//��ʾ��������һ��������
	//lParam = �������Ĵ��ھ��(HWND)
	//wParam = (bool) true --> ��ʾ, false --> ����

	PM_DOCK_WND,
	//ͣ��һ�������������ڵĲ����
	//lParam = Ҫͣ���Ĵ��ڵľ��
	//wParam = ͣ����λ��(0-3)

	PM_UNDOCK_WND,
	//ȡ�������������ڵĲ���ڵ�ͣ��
	//lParam = ȡ��ͣ�����ڵľ��
	//wParam = ԭ��ͣ����λ��(0-3)

	PM_REMOVE_TOOLBAR,
	//ɾ��һ��������
	//lParam = �������Ĵ��ھ��(HWND)

//----��Դ����----
	PM_RESOURCE_OPEN,
	//wParam = lParam��ָ����Դ�ṹ��Ҫ���Ƿ��ͷ�(BOOL)
	//lParam = ��Դ�ṹָ��(KResource*)
};

//======================================
//Peeper�Ľ��淢������Ļ�ֵ���䷶ΧΪ��ֵ��0xFFFF
//======================================
#define	PEEPER_COMMAND_BASE		0xF000
#define PEEPER_SPECIAL_CMD_BASE (PEEPER_COMMAND_BASE - 0x200)

//======================================
//	����λ��
//======================================
enum POSITION_RELATE
{
	POSITION_LEFT	= 0,
	POSITION_TOP	= 1,
	POSITION_RIGHT	= 2,
	POSITION_BOTTOM	= 3,
};

//======================================
//	Peeper���ڵ���Ϣ
//======================================
enum	KPW_MESSAGE
{
	PWM_DROP_ITEM		= WM_USER + 1,
	PWM_OPEN_RESOURCE,
};

#endif //__PEEPERSHELL_H__
