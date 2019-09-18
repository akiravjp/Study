// ***************************************************************
//  FileName	: $FILE_BASE$.h 
//  Creator 	: page(pk)  
//  Date		: $MONTH_02$/$DAY_02$/$YEAR$ $HOUR$:$MINUTE$:$SECOND$
//  Comment	: 
// ***************************************************************
#include <stdio.h>
#include <string.h>

char* strchr_trad(char *p, char c)
{
	if( NULL == p)
		return NULL;

	while( '\0' != *p)
	{
		if( (unsigned char)*p >= 0x81 && (unsigned char)*p <= 0xfe )/* big5 code */
		{
			p += 2;
			continue;
		}
		if( *p == c )
			return p;
		p++;
	}
}

int
is_gbk_chinese(unsigned char cFirst, unsigned char cSecond){
	if (cFirst >= 0xb0 && cFirst <= 0xf7 &&		
	    cSecond >= 0xa1 && cSecond <= 0xfe)
		return 1;
	return 0;
}

int main()
{
	char *str = "36	���ѵL��	<color=Blue2>���	<color=White>�W�[�ۤv�M�P��ͤ���I�� <color=Blue1>[=state_1]%+[=state_0] <color=White>�I	<color=White>���Ӥ��O <color=Red1>[=cost_stamina_percent]% <enter><color=White>�W�[�ۤv�M�P��ͤ���I�� <color=Blue1>[=state_1]%+[=state_0] <color=White>�I<enter><color=White>����ɶ� <color=Green1>[=skill_display_persist_time] <color=White>��<enter>		100			��������			�䵱\�����ķ�_a_p.3e	";
	char *p = strchr_trad(str, '[');
	printf("1: %s\n", p);
	p = NULL;
	p = strchr(str, '[');
	printf("2: %s\n", p);
}