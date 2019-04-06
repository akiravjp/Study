#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

#include "KCFileFind.h"
#include "SprConverter.h"

using namespace std;

int ModifySpr(LPCTSTR lpFileName, const FSprHead &SprHead);
int main(int args, char **argv)
{
	/*
	WIN32_FIND_DATA FindFileData;
	HANDLE hFile;
	hFile = FindFirstFile(".\\*", &FindFileData);// Ϊʲôʹ��".\\"Ϊʲô���У�����Ҫ�Ӹ�*ͨ�����
	do
	{
		printf("%s\n", FindFileData.cFileName);
	}while(FindNextFile(hFile, &FindFileData));

	FindClose(hFile);
	*/
	WIN32_FIND_DATA FindData;
	KCFileFind cFileFind;
	string strFilter;	//�ܹ�ƥ��������ļ�����

	unsigned int count = 0;
	unsigned int nSuccess = 0;
	unsigned int nFailed = 0;
	FSprHead SprHead; 
	memset(&SprHead, 0, sizeof(SprHead));

	int sig = 0;
	while(1)
	{
		cout << "***************���߲˵�***************" << endl;
		cout << "1.�޸�֡���" << endl;
		cout << "2.����" << endl;
		cout << "3. �˳�" << endl;
		cin >> sig;
		getchar();
		switch(sig)
		{
			case 1:
				cout << "�������ļ�����*.spr����" << endl;
				cin >> strFilter;
				cout << "�������Ϊ��" << strFilter << endl;
				getchar();
				cout << "�������޸ĵļ��Ϊ��" << endl;
				cin >> SprHead.Interval;
				getchar();
				cout << "������ļ��Ϊ��" << SprHead.Interval << endl;
				cFileFind.First(strFilter.c_str());
				while(cFileFind.IsExist())
				{
					count++;
					printf("\n***%d***\n", count);
					FindData = cFileFind.GetCurrentFile();
					cout << FindData.cFileName << endl;
					if(ModifySpr(FindData.cFileName, SprHead))
					{
						printf("Failed\n");
						nFailed++;
					}
					else
					{
						printf("Ok\n");
						nSuccess++;
					}
					cFileFind.Next();
				}

				printf("\n���ļ�����%d\n", count);
				cout << "�ɹ�����" << nSuccess << " || ʧ������" << nFailed << endl;
				 break;
			case 2:
				 break;
			case 3:
				exit(1);
				break;
		}
	}

	getchar();
	getchar();
//	Sleep(10000);
}

/**
 * �޸��ļ���Ϊ��ƷFileName��ͷ��
 * ע����ʹ�øú���֮ǰ����ļ����������
 */
int ModifySpr(LPCTSTR lpFileName, const FSprHead &SprHead)
{
	//��ȡͷ�ļ���Ϣ
	FILE *pf = NULL;
	FSprHead *pSprHead;	// �洢��ȡ��Spr�ļ�ͷ
	pf = fopen(lpFileName, "rb+");
	if(NULL == pf)
	{
		printf("Read File error!\n");
		return -1;
	}
	

	// ��ȡspr�ļ�����
	DWORD uSprDataSize = filelength(fileno(pf));
	BYTE *pSprData = new BYTE[uSprDataSize];
	if (pSprData == NULL)
	{
		fclose(pf);
		printf("Malloc Failed!\n");
		return -1;
	}
	if (fread(pSprData, uSprDataSize, 1, pf) == 1)
	{
//		fclose(pf);
		pSprHead = (FSprHead*)pSprData;
		if ((LPBYTE)pSprHead + sizeof(FSprHead) > (LPBYTE)pSprData + uSprDataSize)
		{
			printf("Error\n");
			return -1;
		}
		if (*(int*)&pSprHead->Comment[0] != SPR_COMMENT_FLAG || !pSprHead->Frames || pSprHead->FrameFormat != enumFF_LinkPng)
		{
			return -1;
		}
	}
	// �����Ϣ
	printf("֡����%d, ֡�����%d\n", pSprHead->Frames, pSprHead->Interval);

	/**
	 * �޸���Ϣ
	 */
	/// �ļ�ָ�붨λ
	unsigned int offset = sizeof(SprHead.Comment)+sizeof(SprHead.Height)+sizeof(SprHead.Width)+sizeof(SprHead.CenterX)+sizeof(SprHead.CenterY)+
		sizeof(SprHead.Colors)+sizeof(SprHead.Frames)+sizeof(SprHead.Directions);
	fseek(pf, offset, SEEK_SET);

	///д���µ���ֵ
	fwrite(&SprHead.Interval, sizeof(SprHead.Interval), 1, pf);
	rewind(pf);

	return 0;// �ɹ�
}