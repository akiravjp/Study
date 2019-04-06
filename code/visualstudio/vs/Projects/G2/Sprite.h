// Sprite.h: interface for the Sprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__E81E9131_EE3F_4106_BA18_2311413BFA2E__INCLUDED_)
#define AFX_SPRITE_H__E81E9131_EE3F_4106_BA18_2311413BFA2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////
//����ͼ�ĳ��Ϳ�
#define boreWidth 56
#define boreHeight 71
#define boreWidth2 48
#define boreHeight2 64
#define ExplodeWidth 12
#define ExplodeHeight 12
#define PopoWidth	44
#define PopoHeight	41
#define ExplosionWidth 40
#define ExplosionHeight 40
//ö�ٷ���
enum DIRECTION
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
};
////////////////////////////////////////////////
//************************************
///CSprite Class 
///Comm: Base class
//////////////////////////////////////////////////
class CSprite  
{
public:
	 
	CSprite();
	 //Set m_width ,m_height and m_active 
	void Create( int w, int h, BOOL active )
	{
		m_width = w;
		m_height = h; 
		m_active = active;
	}
	 
	 //����Ƿ���ײ
	BOOL HitTest( CSprite& sprite );	
	 //��ͼ
	void Draw(HDC *TMemDC,HDC *hTemp);
	//����ͼƬ
	void BitBlt(HBITMAP *bmp){ m_bmp = bmp; }

public:
	//λͼ
	 HBITMAP *m_bmp;
	 //�Ƿ���
	BOOL m_active;
	 //λ��
	int	m_x;
	 
	int	m_y;
	 //��Ⱥ͸߶�
	int	m_width;
	 
	int	m_height;
};
///////////////////////////////////////////////////////
//��Ʒ �Ǻ� >_< 
//
enum BONUS
{
	BONUS_LIFE,
	BONUS_CLOCK,
	BONUS_SHOE,
	BONUS_FIRESPEED,
	BONUS_FastTurtle,
	BONUS_SlowTurtle,
};

/////////////////////////////////////////////////////////
//++++++++++++++++CBounds �� �̳��� CSprite ��
//�����
///////////////////////////////////////////////////
class CBonus : public CSprite
{
public:
	
 

void CBonus::Draw(HDC *TMemDC,HDC *hTemp)
{
	static BOOL bShow;//����ƫ��
	static m_frame=0; 
	
	if( !m_active )
		return;
	
	
	
int left = m_frame * m_width;
SelectObject(*hTemp,*m_bmp);
::TransparentBlt(*TMemDC,m_x,m_y+bShow*m_height/10,m_width,m_height,*hTemp,left,0,m_width,m_height,RGB(255,0,255));
	if( timeGetTime() - m_flickerTime > 200 )
	{
		m_flickerTime = timeGetTime();
		bShow = !bShow;
		if(++m_frame>2)
			m_frame=0;
	}
//��Ʒ��ʱ��
	if( timeGetTime() - m_lastTime > 15000 )
		m_active = FALSE;
}
















 //��������
	BONUS	m_type;
//��¼�ϴ�ʱ��	 
	DWORD	m_lastTime;
//��¼��˸ʱ�� 
	DWORD	m_flickerTime;
};
///////////////////////////////////
//
//
///////////////////////////////////
class CExlpode : public CBonus
{
public:
	void Draw(HDC *TMemDC,HDC *hTemp);

 //
	BOOL HitTest( CSprite& sprite );
	BOOL Exploding();
	void Boom(HDC *TMemDC,HDC *hTemp);
	void BitBlt(HBITMAP *bmp,HBITMAP *bmp_explosion)
	{
		m_explosion=bmp_explosion;
		CSprite::BitBlt(bmp);
	}
	void SetExplode(int x,int y)
	{	
		m_frame=0;
		m_x=x-PopoWidth/2;
		m_y=y-PopoHeight/2;
		m_flickerTime=m_lastTime=timeGetTime();
		m_width=PopoWidth;
		m_height=PopoHeight;
		m_active=TRUE;
		m_explode=FALSE;
	}
	HBITMAP *m_explosion;
	int m_frame;
	BOOL m_explode;
};
////////////////////////////////////
//******************************
/////���� CBore �̳��� CSprite.
/////////////////////////////
class CBore : public CSprite
{
public:
	 
	void Draw(HDC *TMemDC,HDC *hTemp);
	 
	void Bore()
	{
		m_active = TRUE;
		m_bAdvance = TRUE;
		m_frame = 0;
		m_time = timeGetTime();
	}

	//ƫ��
	int	  m_frame;
	//ʱ��
	DWORD m_time;
	//�߼������ƶ���ѭ����
	BOOL  m_bAdvance;
};
/////////////////////////////////////
//************************************
//�ӵ��� �̳� CSprite
/////////////////////////////////////
class CBullet: public CSprite
{
public: 
	CBullet();
	 
	BOOL Move();
	 
	void Draw(HDC *TMemDC,HDC *hTemp);

	//����
	DIRECTION	m_dir;
	 //�ٶ�
	float		m_speed;
};

///////////////////////////////////////
//************************************
//̹���� �̳���CBullet���̳���CSprite��
/////////////////////////////////////////// 
class CTank: public CBullet
{
public:
	 
	CTank();
	 //����
	void Create( int w, int h, BOOL active )
	{
		CSprite::Create( w, h, active );
		//��Ϊ���������� (���Ϳ�)
		m_bore.Create( boreWidth, boreHeight, TRUE );
	}	
	 //���� ����ͼ -��̹�ˣ��ӵ�������
	void BitBlt( HBITMAP *tank, HBITMAP *bullet, HBITMAP *bore )
	{
		m_bmp = tank;
		m_bullet[0].BitBlt( bullet );
		m_bullet[1].BitBlt( bullet );
		m_bore.BitBlt( bore );
	}
	//�ı䷽��
	void ChangeDirection( DIRECTION dir );
	//�ƶ����жϣ�m_frame is ͼλ��-����Ч����
	BOOL Move(){ m_frame = m_frame++; return CBullet::Move(); }
	////�����Ƿ�����������ײ�ˣ��˶��У�
	BOOL HitTest( CTank& sprite, int oldx, int oldy );
	//����뾫����ײ
	BOOL HitTest( CSprite& sprite ){ return CSprite::HitTest(sprite); }
	//
	void Draw(HDC *TMemDC,HDC *hTemp);
	//�ӵ���������
	CBullet m_bullet[2];
	//ʱ��
	DWORD	m_time;
	//λͼƫ�ƣ���Ҫ��ͬ��������ͼ������ʹ���ж���Ч����
	int		m_frame;
	//�ʱ��
	DWORD	m_maxTime;
	//����ʱ��
	DWORD	m_shieldTime;
	//��˸ʱ��
	DWORD	m_flickerTime;
	//�Ƿ�������
	BOOL	m_bBoring;
	//����ʵ��
	CBore	m_bore;
};
//////////////////////////////////////////////
///
//������ �̳� CTank��
//
////////////////////////////////////////////////
class CEnemy : public CTank
{
public:
	 
	void ChangeDirection();
 
	BOOL Fire();
 
	void Reborn();
 
	void Draw(HDC *TMemDC,HDC *hTemp);


 
};

//�����
class CPlayer : public CTank
{
public:
	CPlayer();
	void Create( int w, int h, BOOL active )
	{
		CSprite::Create( w, h, active );
		//��Ϊ���������� (���Ϳ�)
		m_bore.Create( boreWidth2, boreHeight2, TRUE );
	}	

	//������ҵ�����
	BOOL ProcessInput( WORD input, DWORD time );
	BOOL Fire();
	BOOL SetExplode();
	
//	BOOL SetExplode();
	void Draw(HDC *TMemDC,HDC *hTemp);
	void Reborn();
	//����
	int		m_nLife;
	//����
	int		m_nScore;
	CExlpode m_explode[2];
};

#endif // !defined(AFX_SPRITE_H__E81E9131_EE3F_4106_BA18_2311413BFA2E__INCLUDED_)
