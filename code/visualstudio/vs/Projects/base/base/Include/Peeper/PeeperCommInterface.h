/*****************************************************************************************
                    ������������������������������������������������������
                    �������������У������ýӿ��붨�塡��������������
                    ������������������������������������������������������
Copyright : Kingsoft 2002
Author	:   Wooy(Wu yue)
CreateTime:	2002-3-6
------------------------------------------------------------------------------------------
*****************************************************************************************/
#ifndef __PEEPER_COMMINTERFACE_H__
#define __PEEPER_COMMINTERFACE_H__

//======================================
//	peeper�ɲ������ȵĹ��ܲ����Ľӿ�
//======================================
interface IFunction
{
	virtual void Release() = 0;		//�ͷŽӿ�
	virtual int  GetVersion() = 0;	//ȡ�ð汾��
};

//======================================
//	�۲���
//======================================
interface iKDetector
{
	virtual void	Notify(interface iKTargetObject* pObj) = 0;	//���ܱ��۲�������˱仯��֪ͨ
};

//======================================
//	���۲�Ŀ�����
//======================================
interface iKTargetObject
{
	virtual BOOL	Attach(iKDetector* pDetector) = 0;			//����۲���
	virtual void	Detach(iKDetector* pDetector) = 0;			//����۲��ߵ�����
	virtual BOOL	GetStatus(void* pData1, void* pData2) = 0;	//��ȡ����״̬
};

//======================================
//	��Դ������
//======================================
interface iKResHolder
{
	virtual BOOL	OpenResource(struct KResource* pResource) = 0;//����Դ
	virtual void	SaveResource() = 0;							//�洢�����򿪵���Դ
	virtual BOOL	CloseResource(int nFlag) = 0;				//�ر������򿪵���Դ
	virtual interface iKWndHolder* WndHolder() { return NULL; }	//�����Դ��������������Ĵ��ڰ���������Ľӿ�ָ�룬������򷵻�NULL��
	virtual void	Release() = 0;								//�ͷŽӿڶ���
};

//======================================
//	���ڰ�����
//======================================
interface iKWndHolder
{
	virtual BOOL	Create(HWND hParentWnd, RECT* prc) = 0;		//�������ڽ���
	virtual void	OnCmd(int nCmd) = 0;						//��Ӧ�����������
	virtual void	OnWndMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) {}; //��Ӧ������Ϣ
	virtual HWND	Wnd() = 0;									//��ô��ڵ�win32���
	virtual UINT	GetWndType() { return 0; }					//��ô��ڰ���������
	virtual iKResHolder* ResHolder() { return NULL;}		//��ô��ڶ����������Դ�������Ľӿ�ָ�룬������򷵻�NULL��
	virtual void	Release() = 0;								//�ͷŽӿڶ���
};

//======================================
//	���������Ϊ
//======================================
enum UI_OPERATION
{
	UIO_NONE		=	0,		//�޲���
	UIO_SELECT		=	1,		//ѡ��
	UIO_ACTIVE		=	2,		//����س���˫����
	UIO_DRAG_BEGIN	=	3,		//��ʼ�϶�
	UIO_DRAG_END	=	4,		//�϶�����
};

//======================================
//	�ļ��б���ͼ����
//======================================
//�ļ��б���ͼ���ڻص�����ԭ�Ͷ���
typedef int (*fnFlvCallback)(char* pFile, void* pData, int nParam);
interface iKFileListView : public iKWndHolder, iKDetector, iKTargetObject
{
	//���ý��沼�������nLayoutȡֵ��Ϊ÷��FLV_LAYOUT������ֵ�����
	virtual void SetLayout(UINT nLayout) = 0;
	//���ûص�������nCallback��ȡֵΪ÷��FLV_CALLBACK_IDX������һֵ
	virtual void SetCallback(UINT nCallback, fnFlvCallback pCallback, int nParam) = 0;
	//�г������ļ��е�����
	virtual void Browse(char* pFolder) = 0;
	//��ȡ��ǰѡ����ļ�������ѡģʽ��
	virtual BOOL GetFile(char* pFile) = 0;
	//��ȡѡ�е��ļ�����ѡģʽ��
	virtual BOOL GetFile(char* pFile, int* pnPos) = 0;
	//��ȡѡ�е��ļ�����Ŀ
	virtual UINT GetSelectedCount() = 0;
	//ˢ��
	virtual void Refresh() = 0;
};
//�ļ��б���ͼ���ڲ���ѡ��
enum FLV_LAYOUT
{
	FLV_PATH_WND	= 0x0001,	//��ʾĿ¼����
	FLV_SINGLE_SEL	= 0x0002,	//�б���ֻ��ͬʱѡ��һ���ļ�/Ŀ¼
	FLV_FILE_INFO	= 0x0004,	//��ʾ�ļ��ض���Ϣ
	FLV_FILE_TIME	= 0x0008,	//��ʾ�ļ�����޸�ʱ��
	FLV_FILE_SIZE	= 0x0010,	//��ʾ�ļ���С
	FLV_INC_FOLDER	= 0x0100,	//�ļ��б�������ļ���
	FLV_INC_HIDDEN	= 0x0200,	//�ļ��б�����������ļ�(��)

};
//�ļ��б���ͼ���ڻص���������
enum FLV_CALLBACK_IDX
{
	FLV_CBI_FILTER	= 1,		//�ļ�����
	FLV_CBI_GETINFO	= 2,		//�ļ���Ϣ����
};

//======================================
//	�ļ�����ͼ����
//======================================
interface iKFolderView : public iKWndHolder, iKTargetObject
{
	virtual void	SelectFolder(char* pFolder) = 0;		//ѡ����Ŀ¼����ʾ���ļ���
	virtual void	SelectFolder(LPITEMIDLIST pFolder) = 0;	//ѡ����itemlist��ʾ���ļ���
	virtual void	Refresh() = 0;							//ˢ��
};

//======================================
//	ͼ����ʾ����
//======================================
interface iKImageView : public iKWndHolder, iKTargetObject
{
	virtual void	SetWnd(HWND hWnd) = 0;					//���û���ͼ�δ���Win32���
	virtual void	SetCanvasRect(RECT* prc) = 0;			//���ô��ڻ���������
	virtual void	SetInterval(int nInterval) = 0;			//���û�֡���
	virtual void*	SetImage(void* pImage) = 0;				//���ô���Ҫ��ʾ��ͼ��
	virtual void	OnPaint() = 0;							//�ڴ�������ɻ��Ʋ���
};

//======================================
//	�ļ�������ӿ�
//======================================
interface iFileBatchProcess : IFunction
{
	enum FileBatchProcessOption
	{
		FBP_PROCESS_CALLBACK = 1,
		FBP_PROCESS_END_CALLBACK,
		FBP_CALLBACK_PARAM,
		FBP_SEARCH_FILE_FILTER,
		FBP_ROCESS_BTN_LABEL,

		FBP_SEARCH_FILE					= 0x0100,
		FBP_SEARCH_FOLDER				= 0x0200,
		FBP_SEARCH_RECURSIVE			= 0x0400,
		FBP_HIDE_PROCESS_BTN			= 0x0800,
		FBP_HIDE_RESULT_COLUMN			= 0x1000,
		FBP_REMOVE_ITEM_AFTER_PROCESSED = 0x2000,
	};

	typedef bool (*fnProcessFun)(void* Param, const char* pPath, const char* pFile, char* pResult);
	typedef void (*fnProcessEndFun)(void* Param, bool bOkForAll);

	virtual void	SetOption(FileBatchProcessOption eOption, void* OptionValue) = 0;
	virtual void	Process() = 0;
	virtual void	Process(const char* pPath) = 0;
	virtual bool	CreateUi(HWND hParentWnd, RECT* pRc) = 0;
	virtual void	AdjustLayout(RECT* pRc) = 0;			//�������ڲ���
	virtual void	ShowUi(bool bShow) = 0;
	virtual void	DestroyUi() = 0;
	virtual void	ClearResult() = 0;
};

#endif //__PEEPER_COMMINTERFACE_H__
