// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <iostream>


// function list
void check_endian();

void FnTestAPI();

//////////////////////////////////////////////////////////////////////////
/// ����ģ�����ƥ������
//template<typename TSTR, typename LAMBDA>
//__forceinline void EnqueueUniqueRenderCommand(LAMBDA&& Lambda)
//{
//	//if (Lambda)
//	{
//		Lambda();
//	}
//}
//
//#define ENQUEUE_RENDER_COMMAND(Type) \
//	struct Type##Name \
//	{  \
//		static const char* CStr() { return #Type; } \
//		static const TCHAR* TStr() { return TEXT(#Type); } \
//	}; \
//	EnqueueUniqueRenderCommand<Type##Name>
//
//template<typename LAMBDA>
//__forceinline void EnqueueUniqueRenderCommand(LAMBDA& Lambda)
//{
//	static_assert(sizeof(LAMBDA) == 0, "EnqueueUniqueRenderCommand enforces use of rvalue and therefore move to avoid an extra copy of the Lambda");
//}