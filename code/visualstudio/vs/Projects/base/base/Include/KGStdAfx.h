#ifndef KG_STDAFX_H
#define	KG_STDAFX_H

#ifdef WIN32

#ifndef _CRT_SECURE_NO_DEPRECATE
#define	_CRT_SECURE_NO_DEPRECATE
#endif

#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define	_CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef _USE_32BIT_TIME_T
#define	_USE_32BIT_TIME_T
#endif

//#define DECLSPEC_DEPRECATED
// �����������2005���ƺ��ᵼ���ڴ�������ͷŲ�һ�£���Ҿ�����_malloca�ض���ľ����
//#define	_CRTDBG_MAP_ALLOC	// ʹ��CrtMemoryDebug 

#ifndef ASSERT
#include <assert.h>
#define ASSERT(x)	assert(x)
#endif

#else

#endif
#endif

