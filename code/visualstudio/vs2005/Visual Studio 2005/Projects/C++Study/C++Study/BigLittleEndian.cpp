/* test big or little endian?
 *
 */
#include <stdio.h>

int CheckCPU()
{
	{
		union w
		{
			int a;
			char b;
		}c;
		c.a = 1;
		return (c.b == 1);
	}
}


enum IPACK_FILE_SHELL_PARAM
{
	PACK_FILE_SHELL_MAX_SUPPORT_PAK_NUM = 24,			//���ͬʱ֧�ֵĴ���ļ�����Ŀ
	PACK_FILE_SHELL_MAX_SUPPORT_ELEM_FILE_NUM = 200000,	//һ������ļ��������԰������ļ��ĸ���
	IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_MIN = 100,
	IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_MAX = 1000,
	IPACK_FILE_SIGNATURE_FLAG = 0x4b434150,				//'PACK'������ļ�����
	IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_DEF = 131072,		//128K��Ĭ��Ϊspr�ļ�����128K���֡ѹ��
								//ͨ��SetOption(IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE..)�������趨
		
};

/*
int main()
{
	if(CheckCPU())
		printf("Little Endian\n");
	else
		printf("Big Endian\n");

	char pack[4];
	*(int*)pack = IPACK_FILE_SIGNATURE_FLAG;
	getchar();
}
*/
