//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList_MSC_x86.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   Microsoft Visual C++ Implement for x86 CPU
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_MSC_X86_H_
#define _KG_INTERLOCKSINGLELIST_MSC_X86_H_  1

#include "KG_InterlockSingleList_DEF.h"


__declspec(naked) 
inline void *__fastcall __KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead) 
{
    __asm push    ebx
    __asm push    ebp
    __asm mov     ebp, ecx                    //__fastcall��ʽ�£���ڲ�������ecx(edx...)�еģ�
    __asm mov     edx, [ebp] + 4               //KG_SLIST_HEADER�ṹ�еĺ�������WORD����һ��ŵ�edx����
    __asm mov     eax, [ebp] + 0               //�����KG_SLIST_HEADER�ṹ�е�Nextָ��
Epop10: 
    __asm or      eax, eax         
    __asm jz      short Epop20                //�������Ϊ�գ��ͷ��ؿ�
    __asm mov     ecx, edx
    __asm add     ecx, 0FFFFH                 //�൱�ڽ���16λ��1����16λ��1����Ϊǰ��Ľ�λ��
    __asm mov     ebx, [eax] 
    __asm lock cmpxchg8b qword ptr [ebp]     
    //lockָ����ס���ߣ���֤���ָ����������иõ�ַ���ᱻ�޸�
    //ebp��ָ���64λ��������Ҳ�������ǵ�ͷ�ṹ��ַ����EDX:EAX���ɵ���ֵ��ʵҲ������ṹ������һ�����Ƕ�����ȵģ�
    //������ȣ���˵������ļ���ָ���ִ�й����У�ͷ�ṹ�����ݱ��������߳��޸��ˣ�����ָ��Ὣͷ�ṹ���¶���edx:eax
    //�����ȣ��Ὣecx:ebx���ɵ�64λ����������ʵ����pop����µ�ͷ�ṹ���ݣ����ݷŵ����ǵ�ͷ�ṹ�У��Ӷ�ʵ����ͷ��
    //�����ݵĸ���
    __asm jnz     short Epop10    
Epop20: 
    __asm pop     ebp               
    __asm pop     ebx 

    __asm ret
}

__declspec(naked)
inline void *__fastcall __KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, void* ListEntry)
{
    __asm push    ebx   
    __asm push    ebp   
    __asm mov     ebp, ecx            //__fastcall��ʽ�£���ڲ���ListHead����ecx�е�,ListEntry����edx�е�
    __asm mov     ebx, edx    
    __asm mov     edx, [ebp] + 4
    __asm mov     eax, [ebp] + 0
Epsh10: 
    __asm mov     [ebx], eax
    __asm mov     ecx, edx  
    __asm add     ecx, 010001H

    __asm lock cmpxchg8b qword ptr [ebp]      

    __asm jnz     short Epsh10 

    __asm pop     ebp                
    __asm pop     ebx                
    __asm ret
}

__declspec(naked) 
inline void *__fastcall __KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead) 
{
    __asm push    ebx
    __asm push    ebp
    __asm mov     ebp, ecx                    //__fastcall��ʽ�£���ڲ�������ecx(edx...)�еģ�
    __asm xor     ebx, ebx
    __asm mov     edx, [ebp] + 4               //KG_SLIST_HEADER�ṹ�еĺ�������WORD����һ��ŵ�edx����
    __asm mov     eax, [ebp] + 0               //�����KG_SLIST_HEADER�ṹ�е�Nextָ��
Epop10: 
    __asm or      eax, eax         
    __asm jz      short Epop20                //�������Ϊ�գ��ͷ��ؿ�
    __asm mov     ecx, edx
    __asm mov     cx,  bx
    __asm lock cmpxchg8b qword ptr [ebp]     
    __asm jnz     short Epop10    
Epop20: 
    __asm pop     ebp               
    __asm pop     ebx 

    __asm ret
}

inline PKG_SLIST_ENTRY KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead)
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedFlushSList(ListHead);
}

inline PKG_SLIST_ENTRY KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead) 
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedPopEntrySList(ListHead);
}

inline PKG_SLIST_ENTRY KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, PKG_SLIST_ENTRY ListEntry)
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedPushEntrySList(ListHead, (void *)ListEntry);
}


#endif
