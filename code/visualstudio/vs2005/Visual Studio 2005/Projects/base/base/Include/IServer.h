// -------------------------------------------------------------------------
//	�ļ���		��	IServer.h
//	������		��	lailigao
//	����ʱ��	��	2004-8-18 4:16:44
//	��������	��	
//
// -------------------------------------------------------------------------
#ifndef __INCLUDE_ENTER_ISERVER_H__
#define __INCLUDE_ENTER_ISERVER_H__

#ifdef WIN32
	#include "Net/Win32/IServer.h"
#elif __linux
	#include "Net/Linux/IServer.h"
#endif

#endif // __INCLUDE_ENTER_ISERVER_H__
