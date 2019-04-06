/* -------------------------------------------------------------------------
//	�ļ���		��	kgc/SignCode_i.h
//	������		��	lailigao
//	����ʱ��	��	2004-10-10 23:33:04
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_SIGNCODE_I_H__
#define __KGC_SIGNCODE_I_H__

// -------------------------------------------------------------------------
namespace SignCodeScan
{
	BOOL InitScan();
	BOOL UnInitScan();
	int  RunOnce();

	BOOL AddSignCode(void* pBuffer, int nCount);
	BOOL ClearSignCode();
	int GetSignFlag();
	
	int CheckBuffer(unsigned uSignPos, unsigned uSignLen);
	
	int CheckBufferPure(unsigned uSignPos, unsigned uSignLen);
};

// -------------------------------------------------------------------------

#endif /* __KGC_SIGNCODE_I_H__ */
