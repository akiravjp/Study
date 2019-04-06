#ifndef __SprConverter_h__
#define __SprConverter_h__

#include <Windows.h>
#include <stdio.h>
#include <io.h>
#include <assert.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

#ifndef SAFE_FREE
#define SAFE_FREE(a)	if (a) {free(a); (a)=NULL;}
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(a)	if (a) {(a)->Release(); (a)=NULL;}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(a)	if (a) {delete (a); (a)=NULL;}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(a)	if (a) {delete[] (a); (a)=NULL;}
#endif
#define	SPR_COMMENT_FLAG				0x525053	//'SPR'


extern IDirect3DDevice9*	g_pd3dDevice;


struct FSprHead
{
	BYTE	Comment[4];	// ע������(SPR\0)
	WORD	Width;		// ͼƬ���
	WORD	Height;		// ͼƬ�߶�
	WORD	CenterX;	// ���ĵ�ˮƽλ��
	WORD	CenterY;	// ���ĵĴ�ֱλ��
	WORD	Frames;		// ��֡��
	WORD	Colors;		// ��ɫ��
	WORD	Directions;	// ������
	WORD	Interval;	// ÿ֡���������Ϸ֡Ϊ��λ��
	WORD	FrameFormat;// ��ÿ֡���ݵ���������
	WORD	Reserved[5];// �����ֶΣ����Ժ�ʹ�ã�
};

struct FSprPal
{
	BYTE		Red;		// ��ɫ����
	BYTE		Green;		// ��ɫ����
	BYTE		Blue;		// ��ɫ����
};

struct FSprOffs
{
	DWORD	Offset;		// ÿһ֡��ƫ��
	DWORD	Length;		// ÿһ֡�ĳ���
};

struct FSprFrame
{
	WORD	Width;		// ֡��С���, ��Сʲô��˼��
	WORD	Height;		// ֡��С�߶�
	WORD	OffsetX;	// ˮƽλ�ƣ������ԭͼ���Ͻǣ�
	WORD	OffsetY;	// ��ֱλ�ƣ������ԭͼ���Ͻǣ�
	BYTE	Sprite[1];	// RLEѹ��ͼ�����ݣ�ʲô���ĸ��
};

enum EFrameFormat
{
	enumFF_Default = 0,

	enumFF_OffsPng = 1,
	enumFF_OffsTga,
	enumFF_OffsDds,

	enumFF_LinkPng = 11,
	enumFF_LinkTga,
	enumFF_LinkDds,
};

class SprConverter
{
public:
	SprConverter();
	SprConverter::SprConverter(IDirect3DDevice9*	g_pd3dDevice);
	~SprConverter();
	bool Converter(const char* pszFileName);
	
	bool CreateNewSprFile(const char* pszSprName, const unsigned nFrames);	
private:
	bool LoadSprFile(const char* pszFileName);
	bool ExportNewFormatFile(const char* pszFileName);
	bool SaveNewSprFile(const char* pszSprName);
	bool SaveDdsFile(const char* pszSprName, int nFrame, IDirect3DTexture9* pTexture);
	void Release();
	
	
private:
	IDirect3DDevice9*	g_pd3dDevice;
// Spr�ļ��ṹ  |FSprHead|FSprPal*nColors|FSprOffs*nFrame|(FSprFrame+(data))*nFrame|
	LPBYTE	m_pSprData;
	DWORD	m_uSprDataSize;

	FSprHead*	m_pSprHead;
	FSprPal*	m_pSprPaList;
	FSprOffs*	m_pSprOffsList;

	FSprFrame**	m_ppSprFrameList;
};





#endif /*__SprConverter_h__*/
