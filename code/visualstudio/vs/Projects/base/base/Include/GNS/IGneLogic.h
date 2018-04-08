//---------------------------------------------------------------------------
// ��Ӱ��˵�����     GneLauncher(GL)
// ��Ȩ����           2010 ��ɽ���(Kingsoft)
// ��������������     2010-7-29 Golton Gao
//---------------------------------------------------------------------------
#ifndef __I_GNE_LOGIC_H__
#define __I_GNE_LOGIC_H__
/*---------------------------------------------------------------------------
   [˵��]: GneLogic��Ӧ��ʵ�ֵĽӿ�
---------------------------------------------------------------------------*/

// === ����� ===//
struct IGneMonitorStream
{
	// == ��������д�������Ϣ ==//
	virtual void		WriteError(const char* pFormat, ...) = 0;

	// == ��������д�볣����Ϣ ==//
	virtual void		WriteInfo(const char* pFormat, ...) = 0;
	
	// == ��������д�������Ϣ ==//
	virtual void		WriteDebug(const char* pFormat, ...) = 0;
};

// === ������ ===//
struct IGneCommandStream
{
	// === ����������д������ִ�н�� ===//
	virtual void		Write(const char* pFormat, ...) = 0;
};

struct IGneLogic
{
	// == Life Cycle ==//
	virtual void		Release() = 0;
	virtual bool		Initialize() = 0;
	virtual void		Terminate() = 0;

	// == Dependency Injection ==//
	virtual void		SetMonitorStream(IGneMonitorStream* pMonitorStream) = 0;
	virtual void		SetCommandStream(IGneCommandStream* pCommandStream) = 0;

	// == Schedule ==//
	virtual void		Tick() = 0;

	// == Data Access ==//
	virtual const char* GetVersion() = 0;
	virtual const char* GetStatus() = 0;

	// == Manipulation ==//
	virtual void		ExecCommand(const char* szCommand) = 0;
};

// == GneLogic�Ķ���ӿ� ==//

// == ��GNE_LOGIC�����ڲ� ==//
// (1)Ԥ����GNE_LOGIC_INTER_FLAG��
// (2)ʵ��GneLogicCreate()�ӿ�

#ifndef GNE_LOGIC_INTER_FLAG

extern "C" IGneLogic* GneLogicCreate();
#define FUNC_NAME_GNE_LOGIC_CREATE "GneLogicCreate"
typedef IGneLogic* (*FUNC_GNE_LOGIC_CREATE)();

#endif // #ifndef GNE_LOGIC_INTER_FLAG

#endif // #ifndef __I_GNE_APP_H__
