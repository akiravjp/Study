/*****************************************************************************************
//	�Դ���ļ����и���ά�����������ɡ�չ�����޸ġ��ϲ��ȵȣ��Ĺ��߳���
//	Copyright : Kingsoft 2005
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2005-3-23
------------------------------------------------------------------------------------------
*****************************************************************************************/
#include "PackFile.h"

IPackFileShell*	g_PackFileShell = NULL;
char			g_StringTable[4][MAX_PATH] = { 0 };
int				g_nPackIndex = -1;

int Initialize()
{
	g_PackFileShell = CreatePackFileShell();
	return (g_PackFileShell != NULL);
}

void Unitialize()
{
	if (g_PackFileShell && g_nPackIndex >= 0)
		g_PackFileShell->ClosePack(g_nPackIndex);
	SAFE_RELEASE(g_PackFileShell);
}

//���ʹ�÷�����Ϣ
void OutputUsage()
{
	printf("-------------------------------------------------------------------------------\n");
	printf("                  Pack and Unpack (C) Kingsoft Season. 2005\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("Usage: PackFile P -P<PackName> -R<RootPath> -D<ElemFolder>\n");
//	printf("Usage: PackFile P -P<PackName> -R<RootPath> [-D<ElemFolder>] [-B<BatchFile>]\n");
	printf("Usage: PackFile E -P<PackName> -F<ElemFile> -O<OutputName>\n");
	printf("Usage: PackFile E -P<PackName> -R<RootPath>\n");
	printf("Usage: PackFile C -P<PackName> -A<AddPackFile>\n");
	printf("Usage: PackFile D -P<UpdatePak> -O<OldPackFile> -N<NewPackFile>\n");
	printf("Usage: PackFile U -P<UpdatePak> -O<OldPackList> -N<NewPackList>\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("Operation command : P Pack; E Extract; C Combin; U Diff\n");
	printf("-P : <PakName> is the file name of the output package, it can\n");
	printf("     be a fullname or a shorten name relate to <RootPath>.\n");
	printf("-R : specify the root path of the elem(s) to be pack(or unpack to),\n");
	printf("     <RootPath> is the full name of the root path.\n");
	printf("-D : special the folder to be pack to the package.\n");
	printf("     <ElemFolder> is a shorten name relate to <mRootPath> without leading-\'\\''.\n");
	//		printf("-B : not support yet.\n");
	printf("-U : unpack operation. <PackName> is the file name of the source package, it\n");
	printf("     must be a fullname.\n");
	printf("-F : specify the elem file to be unpack from the package.\n");
	printf("     <ElemFile> is a shorten name having leading-\'\\\'.\n");
	printf("-O : specify the dest file name of the unpack operation.,(E command)\n");
	printf("     <OutputName> is a full name.\n");
	//		printf("ATTENTION:when pack operation, ONLY one of '-D' or '-B' option can be exist, and must be exist.\n");
	printf("-------------------------------------------------------------------------------");
}

//�������
//����ļ�����
//-R<ElemFileRootPath>	�������ļ��ĸ�Ŀ¼(��Ҫ����)
//-D<ElemFolder>		�Ѵ�����Ŀ¼���ݶ��������ļ� (-D��-B�������߱�ȡ��һ)
//-B<BatchFileName>		�Ѵ��������ļ����г������ݶ��������ļ�
//-S                    ���û�����ò����ļ���С����8M���ش��󣬾ܾ�ѹ�����ļ�
//                      ������ò����ļ���С����8M�����ļ���ѹ��ԭ���������ļ���
PACK_OPER_INDEX AnalyseCmdLine(int argc, char* argv[])
{
	if (argc < 4 || argv[1][1] != 0)	// 
		return PACK_OPER_NONE;
	PACK_OPER_INDEX	eOper = PACK_OPER_NONE;
	switch(argv[1][0])
	{
	case 'P':
		eOper = PACK_OPER_PAK;
		break;
	case 'E':
		eOper = PACK_OPER_EXTRACT;
		break;
	case 'C':
		eOper = PACK_OPER_COMBIN;
		break;
	case 'D':
		eOper = PACK_OPER_DIFF;
		break;
	case 'U':
		eOper = PACK_OPER_UPDATE;
		break;
	default:
		return PACK_OPER_NONE;
	}

	char	szPakFile[256] = "";	/// ���û���ú�
	for (int i = 2; i < argc; i++)
	{
		if (argv[i][0] != '-')
			return PACK_OPER_NONE;
		switch(argv[i][1])
		{
		case 'P':
			strcpy(szPakFile, &argv[i][2]);	/// g_String[OPER_PACK_PACKFILE_NAME]������fullname Ҳ������shorten name
			break;
		case 'R':
			if (eOper == PACK_OPER_PAK)
				strcpy(g_StringTable[OPER_PACK_ELEM_ROOT_PATH], &argv[i][2]);
			else if (eOper == PACK_OPER_EXTRACT)
				strcpy(g_StringTable[OPER_EXTRACT_ELEM_ROOT_PATH], &argv[i][2]);
			break;
		case 'D':
			if (eOper == PACK_OPER_PAK)
				strcpy(g_StringTable[OPER_PACK_FOLDER_TO_ADD], &argv[i][2]);
			break;
		case 'B':
			if (eOper = PACK_OPER_PAK)
				strcpy(g_StringTable[OPER_PACK_BATCH_FILE], &argv[i][2]);
			break;
		case 'S':
			break;
		case 'F':
			if (eOper == PACK_OPER_EXTRACT)
				strcpy(g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT], &argv[i][2]);
			break;
		case 'O':
			if (eOper == PACK_OPER_EXTRACT)
				strcpy(g_StringTable[OPER_EXTRACT_DEST_FILE_NAME], &argv[i][2]);
			else if (eOper == PACK_OPER_DIFF)
				strcpy(g_StringTable[OPER_DIFF_OLD_PACK], &argv[i][2]);
			else if (eOper == PACK_OPER_UPDATE)
				strcpy(g_StringTable[OPER_UPDATE_OLD_PACK_LIST], &argv[i][2]);			
			break;
		case 'N':
			if (eOper == PACK_OPER_DIFF)
				strcpy(g_StringTable[OPER_DIFF_NEW_PACK], &argv[i][2]);
			else if (eOper == PACK_OPER_UPDATE)
				strcpy(g_StringTable[OPER_UPDATE_NEW_PACK_LIST],  &argv[i][2]);
			break;
		case 'A':
			if (eOper == PACK_OPER_COMBIN)
				strcpy(g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME], &argv[i][2]);
				break;
		default:
			return PACK_OPER_NONE;
		}
	}
	switch(eOper)
	{
	case PACK_OPER_PAK:
		if (!szPakFile[0] ||
			!g_StringTable[OPER_PACK_ELEM_ROOT_PATH][0] ||
			(!g_StringTable[OPER_PACK_FOLDER_TO_ADD][0] && !g_StringTable[OPER_PACK_BATCH_FILE][0]) ||
			(g_StringTable[OPER_PACK_FOLDER_TO_ADD][0] && g_StringTable[OPER_PACK_BATCH_FILE][0]))
		{
			eOper = PACK_OPER_NONE;
		}
		else
		{
			g_SetRootPath(g_StringTable[OPER_PACK_ELEM_ROOT_PATH]);
			g_GetFullPath(g_StringTable[OPER_PACK_PACKFILE_NAME], szPakFile);
		}
		break;
	case PACK_OPER_EXTRACT:
		if (szPakFile[0] &&
			g_StringTable[OPER_EXTRACT_DEST_FILE_NAME][0] &&
			g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT][0])
		{
			strcpy(g_StringTable[OPER_EXTRACT_PACKFILE_NAME], szPakFile);
		}
		else if (szPakFile[0] &&
			g_StringTable[OPER_EXTRACT_ELEM_ROOT_PATH][0])
		{
			strcpy(g_StringTable[OPER_EXTRACT_PACKFILE_NAME], szPakFile);
		}
		else
		{
			eOper = PACK_OPER_NONE;
		}
		break;
	case PACK_OPER_DIFF:
		if (!szPakFile[0] ||
			!g_StringTable[OPER_DIFF_OLD_PACK][0] ||
			!g_StringTable[OPER_DIFF_NEW_PACK][0])
		{
			eOper = PACK_OPER_NONE;
		}
		else
		{
			strcpy(g_StringTable[OPER_DIFF_DIFF_PACK], szPakFile);
		}
		break;
	case PACK_OPER_UPDATE:
		if (!szPakFile[0] ||
			!g_StringTable[OPER_UPDATE_OLD_PACK_LIST][0] ||
			!g_StringTable[OPER_UPDATE_NEW_PACK_LIST][0])
		{
			eOper = PACK_OPER_NONE;
		}
		else
		{
			strcpy(g_StringTable[OPER_UPDATE_DIFF_PACK_FILE], szPakFile);
		}
		break;
	case PACK_OPER_COMBIN:
		if (!szPakFile[0] || !g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME][0])
		{
			eOper = PACK_OPER_NONE;
		}
		else
		{
			strcpy(g_StringTable[OPER_COMBIN_PACKFILE_NAME], szPakFile);
		}
		break;
	}
	return eOper;
}


bool PackOperation();
bool UnpackOperation();
bool CombinOperation();
bool DiffOperation(bool bUpdate);

int main(int argc, char* argv[])
{
	int nRet = 1;	//ʧ��
	//====��������====
	PACK_OPER_INDEX eOper = AnalyseCmdLine(argc, argv);
	if (eOper == PACK_OPER_NONE)
	{
		OutputUsage();
		return nRet;
	}

	//====��ʼ��====
	if (!Initialize())
	{
		printf("ERROR : PackFile Initialize failed!\n");
		return nRet;
	}

	switch(eOper)
	{
	case PACK_OPER_PAK:
		nRet = !PackOperation();
		break;
	case PACK_OPER_EXTRACT:
		nRet = !UnpackOperation();
		break;
	case PACK_OPER_COMBIN:
		nRet = !CombinOperation();
		break;
	case PACK_OPER_DIFF:
		nRet = !DiffOperation(false);
		break;
	case PACK_OPER_UPDATE:
		nRet = !DiffOperation(true);
		break;
	}

	Unitialize();
	return nRet;
}

#ifdef WIN32
//=========�ϲ����ļ�===============
//����:�ϲ��������ļ�  �ɹ�����1,ʧ�ܷ���0
extern "C" __declspec(dllexport)
int PackCombin(const char* pszPackToCombinTo, const char* pszPackToCombinIn, int bRetrenchAfterCombin)
{
	if (!g_IsFileExist(pszPackToCombinTo) || !g_IsFileExist(pszPackToCombinIn))
		return false;
	strcpy(g_StringTable[OPER_COMBIN_PACKFILE_NAME], pszPackToCombinTo);
	strcpy(g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME], pszPackToCombinIn);

	int nRet = true;
	if (Initialize())
	{
		g_PackFileShell->SetOption(IPackFileShell::IPACK_FILE_SHELL_OPTION_RETRENCH, bRetrenchAfterCombin);
		nRet = (CombinOperation() != false);
	}
	Unitialize();

	return nRet;
}
#endif