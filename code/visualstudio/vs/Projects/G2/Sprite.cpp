// Sprite.cpp: implementation of the Sprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sprite.h"
#include <Windows.h>
#include "Input.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////
 
//
//
#define	MAX_X		700
#define MAX_Y		500
#define BULLET_H	13
#define BULLET_W	13
#define TILE_H		10	
#define TILE_W		10
/////////////////////////////////////////////////
//CSprite 
//
///////////////////////////////////////////////////
////////////////////////////////////////////////
CSprite::CSprite()
{

}

///++++++++++++++++��ײ���
BOOL CSprite::HitTest( CSprite& sprite )
{
	if( !m_active || !sprite.m_active )
		return FALSE;//�������һ��Ϊ��Ч����������
	
	RECT rc1, rc2, temp;
	//rc1 ��Sprite1 �ľ���
	rc1.left = (int)m_x;
	rc1.right = rc1.left + m_width;
	rc1.top = (int)m_y;
	rc1.bottom = rc1.top + m_height;
	//rc2 ��Sprite2 �ľ���
	rc2.left = (int)sprite.m_x;
	rc2.right = rc2.left + sprite.m_width;
	rc2.top = (int)sprite.m_y;
	rc2.bottom = rc2.top + sprite.m_height;
//IntersectRect�������жϾ������޽�����return bool�ͣ�
	return IntersectRect( &temp, &rc1, &rc2 );
}

//++++++++++++++++��ͼ
void CSprite::Draw(HDC *TMemDC,HDC *hTemp)
{
	if( !m_active )
		return;//�������Ч��
	::BitBlt(*TMemDC,0,0,m_width,m_height,*hTemp,0,0,SRCCOPY);
}
//////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////
void CExlpode::Draw(HDC *TMemDC,HDC *hTemp)
	{
	int left=m_frame*m_width;
SelectObject(*hTemp,*m_bmp);
::TransparentBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left,0,m_width,m_height,RGB(255,0,255));
//0.15��Ķ���
 if( timeGetTime() - m_flickerTime > 200 )
		{
		m_flickerTime = timeGetTime();
		if(++m_frame>2)
			m_frame=0;
		}

	}
////////////////////////////////////////////////
//
BOOL CExlpode::Exploding()
{//ˮ��ʱ�����
if( timeGetTime() - m_lastTime> 5000)
	{
//	m_flickerTime = timeGetTime();
	m_explode=true;
	 return true;
	}
	 return false;//�������Ч��
}
void CExlpode::Boom(HDC *TMemDC,HDC *hTemp)
{
SelectObject(*hTemp,*m_explosion);
	{
		::TransparentBlt(*TMemDC,m_x,m_y,ExplosionWidth,ExplosionHeight,*hTemp,m_frame*ExplosionWidth,4*ExplosionHeight,ExplosionWidth,ExplosionHeight,RGB(255,0,255));
		::TransparentBlt(*TMemDC,m_x,m_y-ExplosionHeight,ExplosionWidth,ExplosionHeight,*hTemp,m_frame*ExplosionWidth,0,ExplosionWidth,ExplosionHeight,RGB(255,0,255));
		::TransparentBlt(*TMemDC,m_x,m_y+ExplosionHeight,ExplosionWidth,ExplosionHeight,*hTemp,m_frame*ExplosionWidth,1*ExplosionHeight,ExplosionWidth,ExplosionHeight,RGB(255,0,255));
		::TransparentBlt(*TMemDC,m_x-ExplosionWidth,m_y,ExplosionWidth,ExplosionHeight,*hTemp,m_frame*ExplosionWidth,2*ExplosionHeight,ExplosionWidth,ExplosionHeight,RGB(255,0,255));
		::TransparentBlt(*TMemDC,m_x+ExplosionWidth,m_y,ExplosionWidth,ExplosionHeight,*hTemp,m_frame*ExplosionWidth,3*ExplosionHeight,ExplosionWidth,ExplosionHeight,RGB(255,0,255));
	}
if( timeGetTime() - m_flickerTime > 100 )
		{
		m_flickerTime = timeGetTime();
		if(++m_frame>14)
			{
				PlaySound("sound\\explode.wav",NULL,SND_FILENAME|SND_ASYNC);
				m_explode=false;
				m_active=false;
			}
		}
}
//////////////////////////////////////////////////////
//BOOL HitTest( CSprite& sprite )
//OverLoaded -----------------------
///////////////////////////////////////////////////
BOOL CExlpode::HitTest( CSprite& sprite )
{
	if( !m_active || !sprite.m_active )
		return FALSE;//�������һ��Ϊ��Ч����������
	
	  RECT rc1,rc2,rc3;
	  rc1.left=m_x-ExplosionWidth;
	  rc1.top=m_y;
	  rc1.right=m_x+ExplosionWidth*2;
	  rc1.bottom=m_y+ExplosionHeight;
									
	  rc2.left=m_x;
	  rc2.top=m_y-ExplosionHeight;
	  rc2.right=m_x+ExplosionWidth;
	  rc2.bottom=m_y+ExplosionHeight*2;
									 
	 rc3.left=sprite.m_x;
	 rc3.top=sprite.m_y;
	 rc3.right=sprite.m_x+sprite.m_width;
	 rc3.bottom=sprite.m_y+sprite.m_height;
	return (IntersectRect(&rc1,&rc1,&rc3)||IntersectRect(&rc2,&rc2,&rc3));
		 
}



//////////////////////////////////////////////////
///���� ++CBore++ �̳��� CSprite.
///
///
////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++
//����ͼ�Ļ���
void CBore::Draw(HDC *TMemDC,HDC *hTemp)
{
	int left = m_frame * m_width;
SelectObject(*hTemp,*m_bmp);
::TransparentBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left,0,m_width,m_height,RGB(255,0,255));
//0.15��Ķ���
 if( timeGetTime() - m_time > 100 )
	{
		m_time = timeGetTime();
		if( m_bAdvance )
		{
			if( ++m_frame > 9 )
			{
				m_frame = 1;
				m_bAdvance = FALSE;
			}
		}
		else
		{
			if( --m_frame < 0 )
			{
				m_frame = 1;
				m_bAdvance = TRUE;
			}
		}
	}
}
//////////////////////////////////////////////////
//CBullet �̳���CSprite 
//
//
//////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++
CBullet::CBullet()
{
	m_dir = DIR_UP;
	m_speed = 0;
}
/////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++
//�ӵ����ƶ�
//���½���ӵ���Ϊ��Ч��del��
////////////////////////////////////////////////
BOOL CBullet::Move()
{
	if( !m_active )
		return FALSE;
	
	int offset = m_speed;
	switch( m_dir )
	{
	case DIR_UP:
		m_y -= offset;
		break;
	case DIR_DOWN:
		m_y += offset;
		break;
	case DIR_LEFT:
		m_x -= offset;
		break;
	case DIR_RIGHT:
		m_x += offset;
		break;
	}
	//���ûԽ���return true
	if( m_x >= 0 && m_x + m_width <= MAX_X &&
		m_y >= 0 && m_y + m_height <= MAX_Y )
		return TRUE;
//Խ��͵���
	if( m_x < 0 )
		m_x = 0;
	else if( m_x + m_width > MAX_X )
		m_x = MAX_X - m_width;
	if( m_y < 0 )
		m_y = 0;
	else if( m_y + m_height > MAX_Y )
		m_y = MAX_Y - m_height;

	return FALSE;
}
//�ӵ���Draw ++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++
void CBullet::Draw(HDC *TMemDC,HDC *hTemp)
{

	if( !m_active )
		return;
	SelectObject(*hTemp,*m_bmp);
::TransparentBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,0,0,m_width,m_height,RGB(0,0,255));

}



////////////////////////////////////////
//************************************
//CTank
///////////////////////////////////////
//+++++++++++++++++++++
CTank::CTank()
{
	m_bullet[0].Create( BULLET_W, BULLET_H, FALSE );
	m_bullet[1].Create( BULLET_W, BULLET_H, FALSE );	
	m_time = 0;
	m_frame = 0;
}
//////////�ı䷽��+++++++++++
/////////////++++++++++++�ȴ��޸�����
void CTank::ChangeDirection( DIRECTION dir )
{
	if( m_dir != dir )//�����ͬ����
	{
		m_dir = dir;
		int row = (int)m_y / TILE_H;
		int col = (int)m_x / TILE_W;
		int xoffset = (int)m_x % TILE_W;
		int yoffset = (int)m_y % TILE_H;
		 
		if( xoffset <= 10 )//���ƫ��С��10
			m_x = (col * TILE_W + 2);
		else if( xoffset < TILE_W - 6 )//���ƫ��С��30����10
			m_x = (col * TILE_W + 18);
		else //ƫ�ƴ���30С��36
			m_x = (col * TILE_W + 34);

		if( yoffset <= 10 )
			m_y = (row * TILE_H + 2);
		else if( yoffset < TILE_H - 6 )
			m_y = (row * TILE_H + 18);
		else
 
			m_y = (row * TILE_H + 34);
	}
}
///////

//+++++++++++++++�����Ƿ�����������ײ��
BOOL CTank::HitTest( CTank& sprite, int oldx, int oldy )
{
	if( !m_active || !sprite.m_active ||
		m_bBoring || sprite.m_bBoring )
		return FALSE;
	
	int x1 = (int)sprite.m_x;
	int y1 = (int)sprite.m_y;
	int x2 = x1 + sprite.m_width;
	int y2 = y1 + sprite.m_height;
	int newx = (int)m_x;
	int newy = (int)m_y;
	switch( m_dir )
	{
	case DIR_UP:
//(newx <= x2 && newx + m_width >= x1 )
//�ж�����ֱ�����н��� 
//oldy ��P1(����)ǰһ�������Ͻ� ����ͬ��
		if( newx <= x2 && newx + m_width >= x1 &&
			oldy >= y2 && newy <= y2 )
			return TRUE;
		break;
	case DIR_DOWN:
		if( newx <= x2 && newx + m_width >= x1 &&
			oldy + m_height <= y1 && newy + m_height >= y1 )
			return TRUE;
		break;
	case DIR_RIGHT:
		if( newy <= y2 && newy + m_height >= y1 &&
			oldx + m_width <= x1 && newx + m_width >= x1 )
			return TRUE;
		break;
	case DIR_LEFT:
		if( newy <= y2 && newy + m_height >= y1 &&
			oldx >= x2 && newx <= x2 )
			return TRUE;
		break;
	}

	return FALSE;
}
///////
///////////////////////////////////////////
//********************************
//Ememys �� �̳��� CTank�ࣨCBullte��(Sprite)
//////////////////////////////////////////////


////+++++++���˾���������߰�
void CEnemy::ChangeDirection()
{
	CTank::ChangeDirection( (DIRECTION)(rand() % 4) );
}
//++++++++�е���������//����Ҫ��һ��
BOOL CEnemy::Fire()
{

//�����һ���ӵ����ڣ��������ϴη���ʱ���150mm���Ͳ�������
	if( m_bullet[0].m_active ||
		timeGetTime() - m_time < 150 )
		return FALSE;
//�����ˡ�����
	m_time = timeGetTime();
	m_bullet[0].m_active = TRUE;//��һ�ŵ���ʼ��
	m_bullet[0].m_speed = 6;
	m_bullet[0].m_dir = m_dir;//�������򻹲��Ǹ��ƶ�����һ����
//	m_bullet[0].m_width CTank()���캯���ѳ�ʼ�ˣ���bullet->CTank->CEnemy
//��CEnemy �� CGame ����һ�� CEnemy m_enemy[] ;����������
	//�����ӵ�λ��
	switch( m_dir )
	{ 
	case DIR_UP:
		m_bullet[0].m_x = m_x + m_width/2 - BULLET_W/2;
		m_bullet[0].m_y = m_y;
		break;
	case DIR_DOWN:
		m_bullet[0].m_x = m_x + m_width/2 - BULLET_W/2;
		m_bullet[0].m_y = m_y + m_height - BULLET_H;
		break;
	case DIR_LEFT:
		m_bullet[0].m_x = m_x;
		m_bullet[0].m_y = m_y + m_height/2 - BULLET_H/2;
		break;
	case DIR_RIGHT:
		m_bullet[0].m_x = m_x + m_width - BULLET_W;
		m_bullet[0].m_y = m_y + m_height/2 - BULLET_H/2;
	}
	return TRUE;
}
////++++++++++++++++++
//��������
void CEnemy::Reborn()
{ 
	m_active = TRUE;
//�ٲ���
	m_bBoring = TRUE;
//������
	m_bore.m_x = m_x - 2;
	m_bore.m_y = m_y - 2;
	m_bore.Bore();
	m_shieldTime = timeGetTime();
}

////++++++++++++++++++
//���˵Ļ��ƺ���
void CEnemy::Draw(HDC *TMemDC,HDC *hTemp)
{
	if( !m_active )
		return;//�������Ч��
//����ٲ� �ͻ��ٲ�һ����
	if( m_bBoring )
	{
		m_bore.Draw(TMemDC,hTemp);
		//2�������ʱ��� �������ˡ�
		if( timeGetTime() - m_shieldTime > 2000 )
			m_bBoring = FALSE;
		return;
	}

int top;
int left;
switch(m_dir)
	{
	case DIR_UP: 
		top=0;
		break;
	case DIR_DOWN:
		top=1;
		break;
	case DIR_LEFT:
		top=2;
		break;
	case DIR_RIGHT:
		top=3;
		break;
	}

left=m_frame%6;
if(m_frame==6)
	m_frame=0;


	SelectObject(*hTemp,*m_bmp);
//	::BitBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left*m_width,top*m_height,SRCCOPY);
::TransparentBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left*m_width,top*m_height,m_width,m_height,RGB(255,0,255));
m_bullet[0].Draw(TMemDC,hTemp);
}
/////////////////////////////////////////////////////
//CPlayer �� �����
//
//////////////////////////////////////////////////////
CPlayer::CPlayer()
{
m_nLife=3;
m_nScore=0;
}
////////////////////////////////////////////
//CPlayer::Fire()
//Func:�����ӵ������ݣ��Ϳ��Ʒ������
///////////////////////////////////////
BOOL CPlayer::Fire()
{
//�������200mm
	if( timeGetTime() - m_time < 200 )
		return FALSE;
//�ҵ�����һ�������ڵ��ӵ�	
	for( int i = 0; i < 2; i ++ )
		if( !m_bullet[i].m_active )
			break;
	if(i==2)
		return FALSE;
	m_time = timeGetTime();
	m_bullet[i].m_active = TRUE;
	m_bullet[i].m_speed = 6;
	m_bullet[i].m_dir = m_dir;
	switch( m_dir )
	{ 
	case DIR_UP:
		m_bullet[i].m_x = m_x + m_width/2 - BULLET_W/2;
		m_bullet[i].m_y = m_y;
		break;
	case DIR_DOWN:
		m_bullet[i].m_x = m_x + m_width/2 - BULLET_W/2;
		m_bullet[i].m_y = m_y + m_height - BULLET_H;
		break;
	case DIR_LEFT:
		m_bullet[i].m_x = m_x;
		m_bullet[i].m_y = m_y + m_height/2 - BULLET_H/2;
		break;
	case DIR_RIGHT:
		m_bullet[i].m_x = m_x + m_width - BULLET_W;
		m_bullet[i].m_y = m_y + m_height/2 - BULLET_H/2;
	}

	return TRUE;
}
/////////////////////////////////////////////////
//	BOOL ProcessInput( WORD input, DWORD time );
BOOL CPlayer::ProcessInput( WORD input, DWORD time )
{
		DIRECTION dir;
		if( input & KEY_UP )
			dir = DIR_UP;
		else if( input & KEY_DOWN )
			dir = DIR_DOWN;
		else if( input & KEY_LEFT )
			dir = DIR_LEFT;
		else if( input & KEY_RIGHT )
			dir = DIR_RIGHT;
	
		if( input & KEY_DIRECTION )
		{
			if( m_dir == dir )
				Move();
			else
				ChangeDirection( dir );
		}
	if( input & KEY_FIRE )
			Fire();
	if( input & KEY_SETEXPLODE )
			SetExplode();
	return TRUE;
}
///////////////////////////////////////
// ��ʱû�õ�
//
/////////////////////////////////////////
void CPlayer::Reborn()
{ 
	m_active = TRUE;
//	m_bShield = TRUE;
	m_bBoring = TRUE;
	m_bore.m_x = m_x - 2;
	m_bore.m_y = m_y - 2;
	m_bore.Bore();
	m_shieldTime = timeGetTime();
	m_dir = DIR_UP;
	m_speed = 4;
	m_nLife=3;
}
//////////////////////////////////////
//Darw ++++++++++++++++++++++++++
//��ҵĻ���
//
///////////////////////////////////////
void CPlayer::Draw(HDC *TMemDC,HDC *hTemp)
{
	if( !m_active )
		return;//�������Ч��
//����ٲ� �ͻ��ٲ�һ����
	if( m_bBoring )
	{
		m_bore.Draw(TMemDC,hTemp);
		//2�������ʱ��� �������ˡ�
		if( timeGetTime() - m_shieldTime > 2000 )
			m_bBoring = FALSE;
		return;
	}

int top;
int left;
switch(m_dir)
	{
	case DIR_UP: 
		top=0;
		break;
	case DIR_DOWN:
		top=1;
		break;
	case DIR_LEFT:
		top=2;
		break;
	case DIR_RIGHT:
		top=3;
		break;
	}

left=m_frame%6;
if(m_frame==6)
	m_frame=0;


	SelectObject(*hTemp,*m_bmp);
//	::BitBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left*m_width,top*m_height,SRCCOPY);
::TransparentBlt(*TMemDC,m_x,m_y,m_width,m_height,*hTemp,left*m_width,top*m_height,m_width,m_height,RGB(255,0,255));
for(int j=0;j<2;j++)
m_bullet[j].Draw(TMemDC,hTemp);
}
/////////////////////////////////////////////
//
//
/////////////////////////////////////////////
BOOL CPlayer::SetExplode()
{

		int i=0;
		while(m_explode[i].m_active)
			{
				i++;
				if(i==2)
					return false;
				
			}
		m_explode[i].SetExplode(m_x+m_width/2,m_y+m_height/2);
		return true;
	
}