// -------------------------------------------------------------------------
//	�ļ���		��	IClient.h
//	������		��	lailigao
//	����ʱ��	��	2004-8-18 4:17:11
//	��������	��	
//
// -------------------------------------------------------------------------
#ifndef __INCLUDE_ENTER_ICLIENT_H__
#define __INCLUDE_ENTER_ICLIENT_H__

#ifdef WIN32
	#include "Net/Win32/IClient.h"
#elif __linux
	#include "Net/Linux/IClient.h"
#endif

#endif // __INCLUDE_ENTER_ICLIENT_H__
