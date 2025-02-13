//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KMemStack.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Memory Stack Class
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "KMemBase.h"
#include "KMemStack.h"
#include "Debug.h"

//---------------------------------------------------------------------------
// 函数:	KMemStack
// 功能:	购造函数
//---------------------------------------------------------------------------
KMemStack::KMemStack()
{
	g_MemZero(m_pStack, sizeof(m_pStack));
	m_nStackTop  = 0;
	m_nStackEnd  = 0;
	m_nChunkTop  = 0;
	m_nChunkSize = 65536;
}
//---------------------------------------------------------------------------
// 函数:	~KMemStack
// 功能:	析购函数
//---------------------------------------------------------------------------
KMemStack::~KMemStack()
{
	FreeAllChunks();
}
//---------------------------------------------------------------------------
// 函数:	Init
// 功能:	初始化
// 参数:	nChunkSize	Chunk尺寸大小
//---------------------------------------------------------------------------
void KMemStack::Init(int nChunkSize)
{
	FreeAllChunks();
	m_nChunkSize = nChunkSize;
}
//---------------------------------------------------------------------------
// 函数:	Push
// 功能:	分配内存
// 参数:	nSize	内存大小
// 返回:	void*	内存指针，= NULL 表示分配失败
//---------------------------------------------------------------------------
void* KMemStack::Push(int nSize)
{
	unsigned char* pResult;

	if (m_nChunkSize < nSize)
		m_nChunkSize = nSize;

	if (m_nStackTop + nSize > m_nStackEnd)
	{
		if (!AllocNewChunk())
			return NULL;
	}

	pResult = m_pStack[m_nChunkTop - 1];
	pResult += m_nStackTop;
	m_nStackTop += nSize;
	return pResult;
}
//---------------------------------------------------------------------------
// 函数:	Free
// 功能:	释放内存块
// 参数:	pMem	内存块指针
//---------------------------------------------------------------------------
void KMemStack::Free(void* pMem)
{
	return;
}
//---------------------------------------------------------------------------
// 函数:	AllocNewChunk
// 功能:	分配新的内存块，并且填充为0
// 返回:	true	成功 
//			false	失败
//---------------------------------------------------------------------------
int KMemStack::AllocNewChunk()
{
	if (m_nChunkTop >= MAX_CHUNK)
	{
		g_MessageBox("KMemStack : Chunk over flow");
		return false;
	}

	m_pStack[m_nChunkTop] = (unsigned char*)g_MemAlloc(m_nChunkSize);
	if (m_pStack[m_nChunkTop] == NULL)
		return false;

	m_nChunkTop++;
	m_nStackTop = 0;
	m_nStackEnd = m_nChunkSize;
	return true;
}
//---------------------------------------------------------------------------
// 函数:	FreeAllChunks
// 功能:	释放所有的内存块
//---------------------------------------------------------------------------
void KMemStack::FreeAllChunks()
{
	for (int i = 0; i < m_nChunkTop; i++)
	{
		g_MemFree(m_pStack[i]);
		m_pStack[i] = NULL;
	}
	m_nStackTop = 0;
	m_nStackEnd = 0;
	m_nChunkTop = 0;
}
//---------------------------------------------------------------------------
// 函数:	GetChunkSize
// 功能:	取得堆栈Chunk的大小
// 返回:	Chunk 的大小 in bytes
//---------------------------------------------------------------------------
int KMemStack::GetChunkSize()
{
	return m_nChunkSize;
}
//---------------------------------------------------------------------------
// 函数:	GetStackSize
// 功能:	取得内存堆栈的大小
// 参数:	void
// 返回:	内存堆栈的大小 in bytes
//---------------------------------------------------------------------------
int KMemStack::GetStackSize()
{
	return (m_nStackTop + (m_nChunkTop - 1) * m_nChunkSize);
}

