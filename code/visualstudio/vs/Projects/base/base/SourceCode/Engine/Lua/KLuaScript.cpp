//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2001-9-13 10:33:29
// Code:	Romandou
//---------------------------------------------------------------------------
#include "Precompile.h"

#ifndef LUA_V_5

#include "Debug.h"
#include "File.h"
#include "KLuaScript.h"
#include <stdarg.h>
#ifdef __linux
	#include <unistd.h>
#endif

char g_szRunningScript[256];
char g_szRunningFunction[256];

//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
//#include "KFilePath.h"
#define MAX_VARIABLE	256

//��������
typedef enum
{
	DBC_NONE = 0,			//����������ڰ�״̬����ʱ����ѭ���ȴ�����
	DBC_CONTINUE,			//����ִ����һ�нű�����
	DBC_GET_VAR,			//��ȡ�������ƺ���ֵ
	DBC_SET_LOCAL_VAR,		//�޸ľֲ�����
	DBC_SET_GLOBAL_VAR,		//�޸�ȫ�ֱ���
	DBC_RELOAD_SCRIPT,		//��������ű�

	DBC_INACTIVE = 0xFEDC	//δ��
}DEBUG_COMMAND;

//������Ϣ�ṹ	������->�ű������
typedef struct 
{
	char	szFlag[4];		//��ʱ�Ķ�λ��־"LDMS"
	DWORD	dwCommand;		//����ָ��
	DWORD	dwParam1;		//��������1
	DWORD	dwParam2;		
	DWORD	dwParam3;
	DWORD	dwParam4;
	char	szParam1[256];	//�ַ�������1
	char	szParam2[256];
}DEBUG_MESSAGE;

//������Ϣ�ṹ	�ű������->������
typedef struct 
{
	char	szFlag[4];		//��ʱ�Ķ�λ��־"LDIS"
	DWORD	dwThis;			//��ǰKLuaScript��thisָ��
	DWORD	dwLineCount;	//��ǰ�к�
	DWORD	dwBreakCount;	//�ص�����ִ�д���
	DWORD	dwErrorCount;	//�������
	char*	lpszScriptFileName;		//�ű��ļ���ָ��
	char*	lpszScriptFuncName;		//�ű�������ָ��
	DWORD	dwVarCount;		//������ѯ����
	DWORD	dwGlobalTotal;	//ȫ�ֱ�������
	DWORD	dwLocalTotal;	//�ֲ���������
	char	VarNames[MAX_VARIABLE][32];		//��������
	char	VarTypes[MAX_VARIABLE];			//��������
	DWORD	VarIntValues[MAX_VARIABLE];		//��������ֵ
	char	VarStrValues[MAX_VARIABLE][256];//�����ַ���ֵ
	char	szErrorMsg[256];
}DEBUG_INFO;

static DEBUG_MESSAGE DebugMessage = {'L', 'D', 'M', 'S', DBC_INACTIVE, 0, 0, 0, 0, ""};
static DEBUG_INFO DebugInfo = {'L', 'D', 'I', 'S', 0, 0, 0, 0, 0, 0, 0};

//�ű�ִ��ÿ�д���ǰ�Ļص�����
void KLuaScript::LuaProcessDebugInfo(Lua_State* L, lua_Debug* ar)
{
	BOOL	bFinished = FALSE;

	//��ȡԴ�����к�
	DebugInfo.dwLineCount = ar->currentline;
	//�ص�������һ
	DebugInfo.dwBreakCount++;
	while (!bFinished)
	{
		switch (DebugMessage.dwCommand)
		{
		case DBC_NONE:
			{
				break;
			}
		case DBC_CONTINUE:
			{
				bFinished = TRUE;
				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_GET_VAR:
			{
				//LUA�ĵ�����Ϣ�ṹ
				lua_Debug	ld;

				DebugInfo.dwGlobalTotal = 0;
				DebugInfo.dwLocalTotal = 0;

				//ȡ��ջ��Ϣ�ͺ�����Ϣ
				if (lua_getstack(L, 0, &ld) && lua_getinfo(L, "flnSu", &ld))
				{
					int nIndex = 0;
					//ȡȫ�ֱ������ƺ�ֵ
					//ld._func->value.i->func->f.l ��Ϊ��ǰ���������Ϣ
					for (int i = 0; i < ld._func->value.i->func->f.l->nkstr; i++)					
					{
						lua_getglobal(L, (char*)&(ld._func->value.i->func->f.l->kstr[i]->str));
						//�ú����ķ���ֵ��ȫ�ֺ�����ֵ����LUA�Ķ�ջ��
						//�����趨ȡջ��Ԫ��
						int nStackPos = -1;
						switch (lua_type(L, nStackPos))
						{
						case LUA_TNONE:
							{
								break;
							}
						case LUA_TUSERDATA:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TUSERDATA;
								nIndex++;
								break;
							}
						case LUA_TNIL:
							{
								break;
							}
						case LUA_TNUMBER:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TNUMBER;
								DebugInfo.VarIntValues[nIndex] = (DWORD)lua_tonumber(L, nStackPos);
								nIndex++;
								break;
							}
						case LUA_TSTRING:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TSTRING;
								strncpy(DebugInfo.VarStrValues[nIndex], (char*)lua_tostring(L, nStackPos), 255);
								DebugInfo.VarStrValues[nIndex][255] = 0;
								nIndex++;
								break;
							}
						case LUA_TTABLE:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TTABLE;
								nIndex++;
								break;
							}
						case LUA_TFUNCTION:
							{
								break;
							}
						}

					}
					DebugInfo.dwGlobalTotal = nIndex;

					//��ȡ�ֲ����������ƺ���ֵ
					const char* lpszName = NULL;
					int nLocalIndex = 0;

					DebugInfo.dwLocalTotal = ld._func->value.i->func->f.l->nlocvars;
					//ȡ�ֲ���������
					for (nLocalIndex = 0; nLocalIndex < (int)DebugInfo.dwLocalTotal; nLocalIndex++)
					{
						strncpy(DebugInfo.VarNames[nIndex], 
							(char*)(&(ld._func->value.i->func->f.l->locvars[nLocalIndex].varname->str)), 
							31);
						DebugInfo.VarNames[nIndex][31] = 0;
						nIndex++;
					}
					//ȡ�ֲ���������Чֵ����
					//�ֲ�������δ���������ʹ�ù���ֵ�����ڶ�ջ�г���
					int nAvailLocalTotal = 0;
					lpszName = lua_getlocal(L, &ld, nAvailLocalTotal + 1);
					while (lpszName != NULL)
					{
						nAvailLocalTotal++;
						lpszName = lua_getlocal(L, &ld, nAvailLocalTotal + 1);
					}
					//�Ӷ�ջ��ȡֵ
					for (int i = 0; i < nAvailLocalTotal; i++)
					{
						//ȷ����ջ�е�λ��
						//��LUA�����Ķ�ջλ�ñ�ʾ��ջ����ջ������
						//���Ķ�ջλ�ñ�ʾ��ջ����ջ�׼���
						int nStackPos = i - nAvailLocalTotal;
						DebugInfo.VarTypes[DebugInfo.dwGlobalTotal + i] = lua_type(L, nStackPos);
						switch (lua_type(L, nStackPos))
						{
						case LUA_TNONE:
							{
								
								break;
							}
						case LUA_TUSERDATA:
							{

								break;
							}
						case LUA_TNIL:
							{

								break;
							}
						case LUA_TNUMBER:
							{
								DebugInfo.VarIntValues[DebugInfo.dwGlobalTotal + i] = (DWORD)lua_tonumber(L, nStackPos);
								break;
							}
						case LUA_TSTRING:
							{
								strncpy(DebugInfo.VarStrValues[DebugInfo.dwGlobalTotal + i], (char*)lua_tostring(L, nStackPos), 255);
								DebugInfo.VarStrValues[DebugInfo.dwGlobalTotal + i][255] = 0;
								break;
							}
						case LUA_TTABLE:
							{

								break;
							}
						case LUA_TFUNCTION:
							{

								break;
							}
						}
					}

					for (int i = nAvailLocalTotal; i < (int)DebugInfo.dwLocalTotal; i++)
					{
						DebugInfo.VarTypes[DebugInfo.dwGlobalTotal + i] = LUA_TNONE;
					}
				}


				DebugMessage.dwCommand = DBC_NONE;
				DebugInfo.dwVarCount++;
				break;
			}
		case DBC_SET_GLOBAL_VAR:
			{
				switch (DebugMessage.dwParam1)
				{
				case LUA_TNUMBER:
					{
						lua_pushnumber(L, DebugMessage.dwParam2);						
						break;
					}
				case LUA_TSTRING:
					{
						lua_pushstring(L, DebugMessage.szParam2);
						break;
					}
				}

				lua_setglobal(L, DebugMessage.szParam1);

				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_SET_LOCAL_VAR:
			{
				lua_Debug	ld;

				if (lua_getstack(L, 0, &ld) && lua_getinfo(L, "flnSu", &ld))
				{
					//����ֲ������ڶ�ջ�е�λ��
					int nLocalVarIndex = 0;
					while (strncmp(DebugMessage.szParam1, 
								   (char*)(&(ld._func->value.i->func->f.l->locvars[nLocalVarIndex].varname->str)), 
								   255) &&
						nLocalVarIndex < ld._func->value.i->func->f.l->nlocvars)
						nLocalVarIndex++;
					
					if (nLocalVarIndex < ld._func->value.i->func->f.l->nlocvars)
					{
						switch (DebugMessage.dwParam1)
						{
						case LUA_TNUMBER:
							{
								lua_pushnumber(L, DebugMessage.dwParam2);						
								break;
							}
						case LUA_TSTRING:
							{
								lua_pushstring(L, DebugMessage.szParam2);
								break;
							}
						}
						lua_setlocal(L, &ld, nLocalVarIndex);
					}
				}

				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_RELOAD_SCRIPT:
			{
				KLuaScript*	lpThis = (KLuaScript*)DebugInfo.dwThis;
				lpThis->Load(lpThis->m_szScriptName);
				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_INACTIVE:
			{
				bFinished = TRUE;
				break;
			}
		default:
			{
				DebugMessage.dwCommand = DBC_INACTIVE;
				break;
			}
		}
		if (!bFinished)
		{
#ifdef WIN32
			Sleep(10);
#elif __linux
			usleep(10000);
#endif
		}
	}

	return;
}
#endif //LUA_DEBUG
//End Added by AQ

KLuaScript::KLuaScript()
{
	m_szScriptName[0]		= '\0';
	m_LuaState	= lua_open(100);

	if (m_LuaState == NULL)
	{
		ScriptError(LUA_CREATE_ERROR, "");
		m_IsRuning			= false;
	}
	else
	{
		m_IsRuning			= true;
	}
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::KLuaScript
//---------------------------------------------------------------------------
KLuaScript::KLuaScript(int StackSize/* = 0*/)
{
	m_szScriptName[0]		= '\0';
	m_LuaState				= lua_open(StackSize);

	if (m_LuaState == NULL )
	{
		ScriptError(LUA_CREATE_ERROR, "");
		m_IsRuning = false;
	}
	else
	{
		m_IsRuning	= true;
	}
}


//---------------------------------------------------------------------------
// ����:	KLuaScript::~KLuaScript
//---------------------------------------------------------------------------
KLuaScript::~KLuaScript()
{
	Exit();
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::LoadBuffer()
//---------------------------------------------------------------------------
bool KLuaScript::LoadBuffer(const char* pBuffer, unsigned int dwLen)
{
	if (lua_getgccount(m_LuaState) > 2000) 
	{
		lua_setgcthreshold(m_LuaState, 0) ;
		if (m_szScriptName[0])
			printf("lua gcc connect. %s \n", m_szScriptName);
		else
			printf("lua gcc connect.\n");
	}

	if (dwLen < 0)
	{
		ScriptError(LUA_SCRIPT_LEN_ERROR, "");
		return false;
	}
	
	if (Lua_CompileBuffer(m_LuaState,pBuffer, dwLen, NULL) != 0)
	{
		ScriptError(LUA_SCRIPT_COMPILE_ERROR, "");
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::Load
//---------------------------------------------------------------------------
bool KLuaScript::Load(const char * Filename)
{
	IFile*	pFile = NULL;
	char*	pBuffer = NULL;
	unsigned int	Size;

	if ((pFile = g_OpenFile(Filename)) == NULL)
		return false;

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
    strncpy(m_szScriptName, Filename, sizeof(m_szScriptName));
	m_szScriptName[sizeof(m_szScriptName) - 1] = '\0';
	
    g_GetFullPath(m_szFullScriptName, Filename);
	m_szFullScriptName[sizeof(m_szFullScriptName) - 1] = '\0';
#endif //LUA_DEBUG	  this
	//End Added by AQ

	int		nResult = false;

	Size = pFile->Size();
	pBuffer = (char*)malloc(Size + 4);
	if (pBuffer)
	{
		if (pFile->Read(pBuffer, Size) == Size)
		{
			pBuffer[Size] = 0;

			try
			{
				if (LoadBuffer(pBuffer, Size))
					nResult = true;
				else
					ScriptError(LUA_SCRIPT_COMPILE_ERROR, "");
			}
			catch(...)
			{
				printf("Load Script %s �����쳣������!!\n", Filename);
			}
		}
		free(pBuffer);
		pBuffer = NULL;
	}

	pFile->Release();
	pFile = NULL;

	if (!nResult)
		return false;

	return ExecuteCode();
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::Execute
//---------------------------------------------------------------------------
bool KLuaScript::ExecuteMain()
{
	if (m_IsRuning && m_LuaState)
	{
		strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
		strncpy(g_szRunningFunction, MAINFUNCTIONNAME, sizeof(g_szRunningFunction));
		return CallFunction(MAINFUNCTIONNAME, 0, "");
	}
	return false;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ExecuteCode
//---------------------------------------------------------------------------
bool KLuaScript::ExecuteCode()
{
	if (!(m_IsRuning && m_LuaState))
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, "");
		//if (!ExecuteCode()) return false; ZHANGPENG ������������д�
		return false;
	}

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
	if (DebugMessage.dwCommand != DBC_INACTIVE)
	{
		DebugInfo.lpszScriptFileName = m_szScriptName;
		DebugInfo.dwThis = (DWORD)this;
		DebugInfo.lpszScriptFuncName = NULL;
	}
#endif //LUA_DEBUG
	//End Added by AQ

	int state;
	strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
	g_szRunningFunction[0] = 0;
	if (state = Lua_Execute(m_LuaState) != 0)
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, state, "");
		return false;
	}

	return	true;
}


//---------------------------------------------------------------------------
// ����:	KLuaScript::CallFunction
// ����:	����Lua�ű��ڵĺ���
// ����:	char* cFuncName
// ����:	int nResults
// ����:	char* cFormat  ����ʱ�������������� 
//			n:������(double) d:����(int) s:�ַ����� f:C������  n:Nil v:Value p:Point
//        v��ΪLua֧�ֵģ�����Ϊ���ε���index��ָ����index��ָ��ջ�ı�����Ϊ
//			 �ú����ĵ��ò�����
//	ע�⣺���ڸú����в���������,�������֣�ϵͳ����ȷ��������double������int
//  ���ڣ����ֱ�����ʽ�ǲ�ͬ�ġ������Ҫע�⵱�������������ʱ����ʽ��Ӧ��d
//  ��������n,����ǿ�иı�Ϊdouble�Ρ��������ּ���Ĵ���
//   
// ����:	...
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
{
	double nNumber;
	char * cString	= NULL;
	void * pPoint	= NULL;
	Lua_CFunction CFunc;
	int i=0;
	int nArgnum = 0;
	int nIndex = 0;
	int nRetcode;		//���ýű�������ķ�����

	if (! (m_IsRuning && m_LuaState))
	{
		ScriptError(LUA_SCRIPT_STATES_IS_NULL, cFuncName);
		return false;
	}

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
	if (DebugMessage.dwCommand != DBC_INACTIVE)
	{
		DebugInfo.lpszScriptFileName = m_szScriptName;
		DebugInfo.lpszScriptFuncName = cFuncName;
		DebugInfo.dwThis = (DWORD)this;
	}
#endif //LUA_DEBUG
	//End Added by AQ
	
	{
		Lua_GetGlobal(m_LuaState, cFuncName); //�ڶ�ջ�м�����Ҫ���õĺ�����

		while (cFormat[i] != '\0')
		{
			switch(cFormat[i])
			{
			case 'n'://�����������double�� NUMBER��Lua��˵��Double��
				{ 
					nNumber = va_arg(vlist, double );
					Lua_PushNumber(m_LuaState, nNumber);
					nArgnum ++;							

				}
				break;
			
			case 'd'://���������Ϊ����
				{
					nNumber = (double)(va_arg(vlist, int));
					Lua_PushNumber(m_LuaState, (double) nNumber);
					nArgnum ++;
				}
				break;
				
			case 's'://�ַ�����
				{
					cString = va_arg(vlist, char *);
					Lua_PushString(m_LuaState, cString);
					nArgnum ++;							
				}
				break;
			case 'N'://NULL
				{
					Lua_PushNil(m_LuaState);
					nArgnum ++;
				}
				break;
			
			case 'f'://�������CFun�Σ����ڲ�������
				{
					CFunc = va_arg(vlist, Lua_CFunction);
					Lua_PushCFunction(m_LuaState, CFunc) ;
					nArgnum ++;
				}
				break;
			
			case 'v'://������Ƕ�ջ��IndexΪnIndex����������
				{
					nNumber = va_arg(vlist, int);
					int nIndex1 = (int) nNumber;
					Lua_PushValue(m_LuaState, nIndex1);
					nArgnum ++;
				}
				break;
			case 't'://����ΪһTable����
				{
					
					

				}
				break;
			
			case 'p':
				{
					pPoint = va_arg(vlist, void *);

					Lua_PushUserTag(m_LuaState, pPoint,m_UserTag);
					nArgnum ++;
				}
				break;
			}
				
			i++;	
		}
		
	}  
    		
	nRetcode = Lua_Call(m_LuaState, nArgnum, nResults);
	
	if (nRetcode != 0)
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, nRetcode, cFuncName);
		return false;
	}
	

	return	true;
}


//---------------------------------------------------------------------------
// ����:	KLuaScript::CallFunction
//---------------------------------------------------------------------------
bool KLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
{
	bool bResult  = false;
	strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
	strncpy(g_szRunningFunction, cFuncName, sizeof(g_szRunningFunction));
	va_list vlist;
	va_start(vlist, cFormat);
	// MikeDai[2004-12-14]
	// Potential function Invoking confusion between the following two functions:
	// bool KLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
	// bool KLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
	bResult = CallFunction((char*)cFuncName, nResults, cFormat, vlist);
	va_end(vlist);
	return bResult;
}


//---------------------------------------------------------------------------
// ����:	KLuaScript::GetValuesFromStack
// ����:	�Ӷ�ջ�л�ñ���
//---------------------------------------------------------------------------
bool KLuaScript::GetValuesFromStack(char * cFormat, ...)	
{
	va_list vlist;
	double* pNumber = NULL;
	const char **   pString ;
	int * pInt = NULL;
	int i = 0;
	int nTopIndex = 0;
	int nIndex = 0;
	int nValueNum = 0;//cFormat���ַ����ȣ���ʾ��Ҫȡ�Ĳ�������

	if (! m_LuaState)
		return false;

	nTopIndex = Lua_GetTopIndex(m_LuaState);	
	nValueNum = strlen(cFormat);
	
	if (nTopIndex == 0 || nValueNum == 0)//����ջ�������ݻ�ȡ�����Ƿ���false
		return false;

	if (nTopIndex < nValueNum)
		return false;

	nIndex = nTopIndex - nValueNum +1;
	
	{
		va_start(vlist, cFormat);     
		
		while (cFormat[i] != '\0')
		{
			
			switch(cFormat[i])
			{
			case 'n'://����ֵΪ��ֵ��,Number,��ʱLuaֻ����double�ε�ֵ
				{
					pNumber = va_arg(vlist, double *);
					
					if (pNumber == NULL)
						return false;

					if (Lua_IsNumber(m_LuaState, nIndex ))
					{
						* pNumber = Lua_ValueToNumber(m_LuaState, nIndex ++ );
												
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR, "");
						return false;
					}
					
					
				}
				break;
			case 'd':
				{
					pInt = va_arg(vlist, int *);
					if (pInt == NULL)
						return false;
					if ( Lua_IsNumber(m_LuaState, nIndex))
					{
						* pInt = (int ) Lua_ValueToNumber(m_LuaState, nIndex ++);
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR, "");
						return false;
					}

				}
				break;
			case 's'://�ַ�����
				{
					pString = va_arg(vlist, const char **);
					
					if (pString == NULL)
						return false;
					
					if (Lua_IsString(m_LuaState, nIndex))
					{
						(*pString) = (const char *)Lua_ValueToString(m_LuaState, nIndex++);
						
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_STRING_ERROR, "");
						return false;
					}
				}
				break;
			
			}
			
			
		i ++;	
		}
		va_end(vlist);     		/* Reset variable arguments.      */
		
	}
	return	true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::Init
// ����:	��ʼ���ű�����ע��ϵͳ��׼������
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Init()
{
	Exit();
	if (! m_LuaState)
	{
		m_LuaState	= Lua_Create(0);
		if (m_LuaState == NULL)
		{
			ScriptError(LUA_CREATE_ERROR, "");
			m_IsRuning	= false;
			return false;
		}
		//Added by AQ for Debugger, 2004.11.15
		//�����лص�����
#ifdef	LUA_DEBUG
		m_LuaState->linehook = LuaProcessDebugInfo;
#endif //LUA_DEBUG
		//End Added by AQ

		m_IsRuning	= true;
		m_UserTag = lua_newtag(m_LuaState)	;
	}

	RegisterStandardFunctions();
	return	true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ReleaseScript
// ����:	�ͷŸýű���Դ��
//---------------------------------------------------------------------------
void KLuaScript::Exit()
{
	m_szScriptName[0] = '\0';
	m_IsRuning = false;
	if (m_LuaState)
	{
		Lua_Release(m_LuaState);
		m_LuaState = NULL;
	}
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::RegisterFunction
// ����:	ע��ĳ�ڲ�C�������ű���
// ����:	char* FuncName  �ڽű���ʹ�õĺ�����
// ����:	void* Func    ʵ����Ӧ��C����ָ��
// ����:	int Args = 0 //��KScript�ӿ����ݣ�����
// ����:	int Flag = 0 //��KScript�ӿ�����, ����
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::RegisterFunction(const char* FuncName , void* Func)
{
	if (! m_LuaState)
		return false;
	Lua_Register(m_LuaState, FuncName, (Lua_CFunction)Func);
	return true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::RegisterFunctions
// ����:	����ע��Lua���ڲ�C������������������Ϣ������TLua_Funcs��������
// ����:	TLua_Funcs *Funcs �����ָ��
// ����:	int n ��������������Ϊ�㣬��ϵͳ����õ���
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::RegisterFunctions(TLua_Funcs Funcs[], int n)
{
	if (! m_LuaState)
		return false;
	if (n == 0)
		n = sizeof(Funcs) / sizeof(Funcs[0]);
	for (int i = 0; i < n; i ++)
		Lua_Register(m_LuaState, Funcs[i].name, Funcs[i].func);
	return true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::RegisterStandardFunctions
// ����:	ע��Luaϵͳ��׼�ĺ�����
// ����:	void 
//---------------------------------------------------------------------------
void KLuaScript::RegisterStandardFunctions()
{
	if (! m_LuaState)
		return ;
	Lua_OpenBaseLib(m_LuaState);//Lua������
	Lua_OpenIOLib(m_LuaState);//���������
	Lua_OpenStrLib(m_LuaState);//�ַ��������
	Lua_OpenMathLib(m_LuaState);//��ֵ�����
	//Lua_OpenDBLib(m_LuaState);//���Կ�
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ScriptError
//---------------------------------------------------------------------------
void KLuaScript::ScriptError(int Error, char *szExtendInfo)
{
//Modified by AQ for debugger, 2004.11.18
//Original code:
//	char lszErrMsg[200];
//	sprintf(lszErrMsg, "ScriptError %d. (%s) \n", Error, m_szScriptName);
//	lua_outerrmsg(lszErrMsg);
//New code:
#ifdef LUA_DEBUG
	sprintf(DebugInfo.szErrorMsg, "ScriptError %d. (%s:%s) \n", Error, m_szScriptName, (szExtendInfo && szExtendInfo[0]) ? szExtendInfo : "");
	//KGLogPrintf(LOG_WARNING, DebugInfo.szErrorMsg);
	lua_outerrmsg(DebugInfo.szErrorMsg);
	DebugInfo.dwErrorCount++;
#endif	//LUA_DEBUG
//End Modified by AQ
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ScriptError
//---------------------------------------------------------------------------
void KLuaScript::ScriptError(int Error1 ,int Error2, char *szExtendInfo)
{
//Modified by AQ for debugger, 2004.11.18
//Original code:
//	char lszErrMsg[200];
//	sprintf(lszErrMsg, "ScriptError %d:[%d] (%s) \n", Error1, Error2, m_szScriptName);
//	lua_outerrmsg(lszErrMsg);
//New code:
#ifdef LUA_DEBUG
	sprintf(DebugInfo.szErrorMsg, "ScriptError %d:[%d] (%s:%s) \n", Error1, Error2, m_szScriptName, (szExtendInfo && szExtendInfo[0]) ? szExtendInfo : "");
	//KGLogPrintf(LOG_WARNING, DebugInfo.szErrorMsg);
	lua_outerrmsg(DebugInfo.szErrorMsg);
	DebugInfo.dwErrorCount++;
#endif	//LUA_DEBUG
//End Modified by AQ
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::SafeCallBegin
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SafeCallBegin��SafeCallEnd������Ӧ����ʹ�ã��Է�ֹ�ڵ���Lua���ⲿ����֮��
//�ж��������ڶ�ջ��δ��������ﵽ����ǰ����ú��ջ��ռ�ô�С���䡣
//�������ֻ�����ڵ����ⲿ����ʱ���ڲ�����������˴���
//																	Romandou
//---------------------------------------------------------------------------
void KLuaScript::SafeCallBegin(int * pIndex)
{
	if (! m_LuaState)
		return ;
	Lua_SafeBegin(m_LuaState, pIndex);
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::SafeCallEnd
// ����:	
// ����:	int nIndex
// ����:	void 
//---------------------------------------------------------------------------
void KLuaScript::SafeCallEnd(int nIndex)
{
	if (! m_LuaState)
		return;
	Lua_SafeEnd(m_LuaState, nIndex);
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::StopScript
// ����:	��ֹ�ű�
// ����:	void
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Stop()
{
	if (!m_IsRuning)
		return true;
	if (!m_LuaState)
		return false;
	m_IsRuning =  false;
	return true;
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ResumeScript
// ����:	�ָ�����ֹ�Ľű�
// ����:	void
// ����:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Resume()
{
	if ((! m_IsRuning) && (m_LuaState))
	{
		m_IsRuning = true;
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------
// ����:	KLuaScript::CreateTable
// ����:	����һ��Lua��Table���ڵ��øú���������Table������Ա֮�󣬱������
//			SetGlobalName()�������Tableָ��һ�����֡�
// ����:	unsigned int 
//---------------------------------------------------------------------------
unsigned int KLuaScript::CreateTable()
{
	 int nIndex = 0;
	
	nIndex = Lua_GetTopIndex(m_LuaState) ;
	Lua_NewTable(m_LuaState);
	if (Lua_GetTopIndex(m_LuaState) != ++nIndex ) 
		return (unsigned int)(-1);

	return nIndex;
}

void KLuaScript::PushNumber(double number)
{
	if (m_LuaState)
		Lua_PushNumber(m_LuaState, number);
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::SetGlobalName
// ����:	����Lua��ջ����������һ������
// ����:	char* szName
// ����:	void 
//---------------------------------------------------------------------------
void KLuaScript::SetGlobalName(char* szName)
{
	if (!szName)
		return ;
	Lua_SetGlobal(m_LuaState, szName);
}

//---------------------------------------------------------------------------
// ����:	KLuaScript::ModifyTable
// ����:	��ָ�����Ƶ�LuaTable�ö�ջ���ˣ������ض���Index
// ����:	char* szTableName
// ����:	unsigned int ��Lua�в����ڸ�Table�򷵻�-1
//---------------------------------------------------------------------------
unsigned int KLuaScript::ModifyTable(const char* szTableName) 
{
	if (! szTableName[0])
		return (unsigned int)(-1);
	
	int nIndex = Lua_GetTopIndex(m_LuaState);
	
	Lua_GetGlobal(m_LuaState, szTableName);

	if (Lua_GetTopIndex(m_LuaState) != ++nIndex)
		return (unsigned int)(-1);
	
	return nIndex;
}

void KLuaScript::SetScriptName(const char* scpname)
{
	strncpy(m_szScriptName, scpname, sizeof(m_szScriptName));
	m_szScriptName[sizeof(m_szScriptName) - 1] = 0;
}


void g_GetExecutingScript(char *pszScriptBuffer, int nScriptBufferLen, char *pszFunctionBuffer, int nFunctionBufferLen)
{
	if (pszScriptBuffer)
	{
		strncpy(pszScriptBuffer, g_szRunningScript, nScriptBufferLen);
		pszScriptBuffer[nScriptBufferLen - 1] = 0;
	}
	if (pszFunctionBuffer)
	{
		strncpy(pszFunctionBuffer, g_szRunningFunction, nFunctionBufferLen);
		pszFunctionBuffer[nFunctionBufferLen - 1] = 0;
	}
}

#endif	//not LUA_V_5