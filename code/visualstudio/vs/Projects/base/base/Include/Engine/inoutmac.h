// -------------------------------------------------------------------------
//	�ļ���		��	inoutmac.h
//	������		��	лï�� (Hsie)
//	����ʱ��	��	2003-07-20 14:47:18
//	��������	��	
//
// -------------------------------------------------------------------------
#ifndef __INOUTMAC_H__
#define __INOUTMAC_H__
#include "EngineBase.h"
//�˺�����ȷ��������ַ����
//����ֵΪ��������
ENGINE_API int gGetMacAndIPAddress(
    unsigned char *pMacAddressIn,   unsigned long *pIPAddressIn, 
    unsigned char  *pMacAddressOut, unsigned long *pIPAddressOut, 
    unsigned uMask = 0x0000a8c0, 
    int nMacLength = 6
);

#endif // __INOUTMAC_H__
