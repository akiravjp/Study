//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_H_
#define _KG_INTERLOCKSINGLELIST_H_  1

#include <stdlib.h>
#include "KG_InterlockSingleList_DEF.h"

//========================= ����ԭ�� ==========================================

//��ʼ���������ͷ�ṹ
void KG_InitializeSListHead(PKG_SLIST_HEADER ListHead);
//��յ������
PKG_SLIST_ENTRY KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead);

//pushһ�����ListEntry��Ҫpush�Ľ���е�nextָ������ĵ�ַ������ֵ��push֮ǰ��ͷָ��
PKG_SLIST_ENTRY KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, PKG_SLIST_ENTRY ListEntry);
//popһ����㣬��Ȼ�����ص�ָ�벢��ֱ����pop���Ľڵ�ĵ�ַ����Ҫͨ��һ����CONTAINING_RECORDת��һ��
PKG_SLIST_ENTRY KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead);


//========================= ʵ�ֲ��� ==========================================

#if (defined(_MSC_VER) || defined(__ICL))
#include "KG_InterlockSingleList_MSC_x86.h"
#elif defined(__GNUC__)
#include "KG_InterlockSingleList_GNUC_x86.h"
#endif


inline void KG_InitializeSListHead(PKG_SLIST_HEADER ListHead)
{
    if (!ListHead)
        return;

    ListHead->Next.Next = NULL;
    ListHead->Depth = 0;
    ListHead->Sequence = 0;        
}



#endif
