///////////////////////////////////////////////////////////////
//	
//  FileName		:   KLibrary.h
//  Composer		:	wangbin
//	latest Modify	:	2006-01-12
//  Comment			:   ��̬��Ŀ�ƽ̨��װ
//	
///////////////////////////////////////////////////////////////

#ifndef __KLIBRARY_H__
#define __KLIBRARY_H__

#ifdef __linux
#include "./KLibrary_linux.h"
#else
#include "./KLibrary_win32.h"
#endif

#endif //__KLIBRARY_H__
