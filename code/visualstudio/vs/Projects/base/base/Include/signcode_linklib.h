/* -------------------------------------------------------------------------
//	�ļ���		��	kgc/signcode_linklib.h
//	������		��	lailigao
//	����ʱ��	��	2004-10-11 0:11:03
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_SIGNCODE_LINKLIB_H__
#define __KGC_SIGNCODE_LINKLIB_H__

// -------------------------------------------------------------------------
#define LINKLIB "SignCodeScan.lib"

#if !defined(__Linked_kgcsigncode)
#define __Linked_kgcsigncode
#pragma message("\t�����Զ�����ģ�� - " LINKLIB)
#pragma linklib(LINKLIB)
#endif

#undef LINKLIB
// -------------------------------------------------------------------------

#endif /* __KGC_SIGNCODE_LINKLIB_H__ */
