// G2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "G2.h"
#include <stdio.h>
 
 

#define MAX_LOADSTRING 100
#define PLAYER1_STARTX 200
#define PLAYER1_STARTY 300
#define PLAYER2_STARTX 500
#define PLAYER2_STARTY 400
#define BONUS_CX	   42	
#define BONUS_CY	   45
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
CGame *g_pGame;
HWND HWnd;
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
////////////////////////////////////////////////////////
//
//Dis:Control the game 
//CGame Class 
//

CGame::CGame()
{
	m_hInst = NULL;//ʵ��
	m_hWnd = NULL;//����
	m_bActive = FALSE;//�Ƿ���Ч
	m_bShowStats = true;//�Ƿ���ʾ֡��
	m_bSingle = TRUE;//�Ƿ���
	g_pGame = this;//ָ��ָ����
}

CGame::~CGame()
{

}	
/////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////

//���Max-Min
inline int random( int min, int max )
{
	return (min + rand() % (max - min + 1));
}
///////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( g_pGame )//����Ч�Ļ�
		return g_pGame->MsgProc( hWnd, uMsg, wParam, lParam );
	
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

////////////////////////////////////////////////////////
//ItSelf Message Messagement 
////////////////////////////////////////////////////////
LRESULT CGame::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc1;

	switch( uMsg )
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
			break;
		/*
	case WM_LBUTTONDOWN:
		Add(LOWORD (lParam),HIWORD (lParam));
			break;*/
//�������
	case WM_KEYDOWN:
			 switch(wParam)
			 {
		/*	 case VK_RIGHT:
			  	 MOVE=true;
				 break;
				 */
			 case VK_ESCAPE:
				 PostQuitMessage(0);
				 break;
			 case VK_F6:
				 m_player[0].Reborn();
				 break;
			 }
			 break;
	case WM_PAINT:
			hdc1 = BeginPaint(hWnd, &ps);
		//	BitBlt(hdc1,ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right-ps.rcPaint.left,ps.rcPaint.bottom-ps.rcPaint.top,hdcMem,ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
		  EndPaint(hWnd, &ps);
			break;
	case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );

}

////////////////////////////////////////////////////////
//������Ϸ
////////////////////////////////////////////////////////
int CGame::Run()
{
	MSG	msg;

    while( TRUE )
    {//�������Ϣ�ڶ���
        if (PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage( &msg, NULL, 0, 0))
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else if( m_bActive )
        {
			UpdateFrame();
        }
        else
            WaitMessage();
    }
	
	DDTerm();
	return msg.wParam;
}
///////////////////////////////////////////////////////
//DrawWorld()++++++++++++++++++++++++++++++++++++++++
//������
///////////////////////////////////////////////////////
void CGame::DrawWorld()
{
	CExlpode* explode;
SelectObject(hdcBuff,m_pBmpList[0]);//m_pBmpList[0]
::StretchBlt(hdcMem,0,0,800,600,hdcBuff,0,0,40,40,SRCCOPY);
//ը��

	//-----------
	//ը������

				for(int j = 0; j < 2; j ++ )
		{
				
					explode=&m_player[0].m_explode[j];
		 
						if( !(explode->m_active) )
						{	
							continue;
						}
		//ǰ����explode->m_active ��Ч
		 //���û�й�5�루ˮ�ݻ��ڣ��ͻ�ˮ��
				 if(!explode->m_explode)			
					explode->Draw(&hdcMem,&hdcBuff);
				else //�����ʾˮ��Ҫ����������
//		//Ҫ��ը��
				    explode->Boom(&hdcMem,&hdcBuff);
			}
 
//-------------
//������
	for( int i = 0; i < m_nMaxEnemys; i ++ )
	{
		m_enemy[i].Draw(&hdcMem,&hdcBuff);
	}
	
//�����
	m_player[0].Draw(&hdcMem,&hdcBuff);
	
	m_bonus.Draw(&hdcMem,&hdcBuff);
}
////////////////////////////////////////////////////////
//Update ! It is soul of this class (CGame Class)
////////////////////////////////////////////////////////
void CGame::UpdateFrame()
{
	//Update ʱ��
	static DWORD lastTick = timeGetTime();
	static int frameCount;
	static float fps;
if(m_gameState==GS_OVER)
	{
	char buffer2[40]="You Lose ! Ha Ha >_< ";
	TextOut(hdc,200, 50, buffer2,strlen(buffer2) );

MessageBox(NULL,"","ȷ��",MB_OK);
	ResetGame();
	return;
	}
	ProcessInput();
//

	DrawWorld();

//

	//֡�ļ���
	frameCount ++;
	DWORD thisTick = timeGetTime();
	if( thisTick - lastTick > 1000 )
	{
		fps = (float)frameCount / (thisTick - lastTick) * 1000;
		frameCount = 0;
		lastTick = thisTick;
	}
	if( m_bShowStats )
	{
		// Show FPS
		char buf[255];
		char buf3[255]="SHIFT ���Ϊ��ˮ�� �ո��Ϊ����";
		sprintf( buf, "FPS: %.2f /Sec Emenys Left: %d", fps,m_nEnemysLeft);
		TextOut(hdcMem,0, 0, buf,strlen(buf) );
		TextOut(hdcMem,300, 0, buf3,strlen(buf3) );	
	}
SelectObject(hdcBuff,m_pBmpList[7]);
for(int j=0;j<m_player[0].m_nLife;j++)
::TransparentBlt(hdcMem,j*23,20,19,19,hdcBuff,0,0,19,19,RGB(0,0,255));
	::BitBlt(hdc,0,0,700,500,hdcMem,0,0,SRCCOPY);
}
//////////////////////////////////////////////////////
//BoreEnemy() �������˻��趨λ�ã���û�д���ĵ���when enemyleft>0�� 
//
//
//////////////////////////////////////////////////////

BOOL CGame::BoreEnemy()
{
	if( m_nEnemysLeft <= 0 )//m_nEnemysLeft �ܹ�Ҫ����ĵ�����Ҫ���ֵĵ�����
		return FALSE;
	
	int which = random( 0, 4 );//ȡ0-4
	int x, y;
//����m_nMaxEnemys ������ λ�ó�ʼ��
	//ÿ��ֻ��һ���޻�ĵ��˳�ʼ������Ϸһ��ʼ����Ϊ�����޻��
	for( int i = 0; i < m_nMaxEnemys; i ++ )
		if( !m_enemy[i].m_active )
		{
			switch( which )//�ĸ�λ��
			{
			case 0:
				x = 2; y = 2;
				break;
			case 1:
				x = 194; y = 2;
				break;
			case 2:
				x = 386; y = 2;
				break;
			case 3:
				x = 2; y = 160;
				break;
			case 4:
				x = 386; y = 160;
				break;
			}
			int temp = rand() % 100;
			if( temp < 50 )//50%���� �������ͺ��ٶ�
			{
			//	m_enemy[i].m_type = 0;
				m_enemy[i].m_speed = 3;
			}
			else if( temp < 80 )
			{
			//	m_enemy[i].m_type = 1;
				m_enemy[i].m_speed = 4;
			}
			else
			{
			//	m_enemy[i].m_type = 2;
				m_enemy[i].m_speed = 5;
			}
//��������
			m_enemy[i].m_x = x;
			m_enemy[i].m_y = y;
			m_enemy[i].m_dir = DIR_DOWN;
/*
//���ʣ��4��8��11 �ͳ��ֱ���ͺ�ʱ
			if( m_nEnemysLeft == 4 ||
				m_nEnemysLeft == 11 ||
				m_nEnemysLeft == 18 )
			{
				m_enemy[i].m_bBonus = TRUE;
				m_enemy[i].m_redTime = 0;
			}
			else
				m_enemy[i].m_bBonus = FALSE;


			if( m_enemy[i].m_type == 2 )
				m_enemy[i].m_level = 2;
*/
			m_enemy[i].Reborn();

			m_nEnemysLeft --;
			if( ++which > 2 )
				which = 0;
			return TRUE;
		}
	return FALSE;
}
////////////////////////////////////////////////////
//BoreBonus +++++++++++++++++++++++++++++++++++++
// ��Ʒ�ĵ���
///////////////////////////////////////////////////
BOOL CGame::BoreBonus(int x,int y)
{
	
 
	int temp = rand() % 100;
	int offsize=0;
	if( temp < 50 )
		{m_bonus.m_type = BONUS_FIRESPEED;offsize=4;}
	else if( temp < 60 )
	{m_bonus.m_type = BONUS_CLOCK;offsize=2;}
	else if( temp < 70 )
	{m_bonus.m_type = BONUS_SHOE;offsize=3;}
	else if( temp < 80 )
		{m_bonus.m_type = BONUS_LIFE;offsize=1;}
	else if(temp<85)
	{m_bonus.m_type =BONUS_FastTurtle;offsize=5;}
	else {m_bonus.m_type = BONUS_SlowTurtle;offsize=6;}
	 
	if(offsize==0)
	{
	   m_bonus.m_active=false;
		return false;
	}
	if(offsize>4)
			offsize=5;
	m_bonus.BitBlt(&m_pBmpList[8+offsize]);
	m_bonus.m_x = x;
	m_bonus.m_y = y;
	m_bonus.m_lastTime = 
	m_bonus.m_flickerTime = timeGetTime();
	if(offsize>4) 
			m_bonus.Create(36,41,TRUE);
		else 
			m_bonus.Create(BONUS_CX,BONUS_CY,TRUE);
	return TRUE;
}
//////////////////////////////////////////////////////
//EatBonus -CPlayer ++++++++++++++++++++++++++++++++++
/////////////////////////////////////////////////////
void CGame::EatBonus( CPlayer& player )
{
//	m_DirectSound.Play( EFFECT_PICK );

	int i;
	PlaySound("sound\\get.wav",NULL,SND_FILENAME|SND_ASYNC);
	switch( m_bonus.m_type )
	{
	case BONUS_LIFE:
		player.m_nLife = player.m_nLife+3;
		break;
	case BONUS_CLOCK:
		m_bEnemyLocked = TRUE;
		m_lockTime = timeGetTime();
		break;
	case BONUS_SHOE:
		player.m_speed += 3;
		break;
	case BONUS_FIRESPEED:
		for(i=0;i<2;i++)
			player.m_bullet[i].m_speed+=6;
			break;
	case BONUS_FastTurtle:
			player.m_speed += 6;
		break;
	case BONUS_SlowTurtle:
		player.m_speed -= 6;
		break;
	}
	m_bonus.m_active = FALSE;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//������������-���룬������Ϊ��
//////////////////////////////////////////////////////
//��������

void CGame::ProcessInput()
{
	static DWORD lastTick = timeGetTime();
	DWORD time = timeGetTime() - lastTick;
	CBullet* bullet;
	CExlpode* explode;
	int x, y;
	DIRECTION dir;
	int surface;
	int i, j, k;
 //	// process player's input
	WORD input[2];

//+++++++++++++++++++++++++++++++
	//�������ͻ����
	if(timeGetTime() - lastTick>100)//�����ٶȿ���
{

	m_Input.GetKey(input[0],input[1]);
	for( k = 0; k < 2; k ++ )
	{
		if( !m_player[k].m_active )
			continue;

		x = m_player[k].m_x;
		y = m_player[k].m_y;
		dir = m_player[k].m_dir;
		if( !m_player[k].m_bBoring && m_gameState != GS_OVER )
		{
			 m_player[k].ProcessInput(input[k], time);
		//Play Sound	//if( m_player[k].ProcessInput(input[k], time) )
			
		}
//��
	
			if(m_player[k].HitTest(m_bonus))
				EatBonus(m_player[k]);
		
//-----------

		//ը������
		for( j = 0; j < 2; j ++ )
		{
			explode=&m_player[k].m_explode[j];
		if( !(explode->m_active) )
			{	
				continue;
			}
	
			if(explode->Exploding())
			{
				for( i = 0; i < m_nMaxEnemys; i ++ )
					{
					if( !m_enemy[i].m_bBoring&&explode->HitTest(m_enemy[i]))
						{	explode->m_active=FALSE;
							m_enemy[i].m_active = FALSE;
							BoreBonus(m_enemy[i].m_x,m_enemy[i].m_y);
							m_nEnemys --;
							m_player[k].m_nScore += 100;
						}
					}
			}
	
					 
		}
//-------------

	//�ӵ�����
//------------------------------------------------------
			for( j = 0; j < 2; j ++ )
	
		{
			bullet = &m_player[k].m_bullet[j];
			if( !bullet->m_active )
				continue;
			//�ӵ��ƶ�
			if( !bullet->Move() )
			{ //�ӵ�ʧЧʱ����
				bullet->m_active = FALSE;
				continue;
			}
	//�ӵ����е���
//-----------------------------------------------
		for( i = 0; i < m_nMaxEnemys; i ++ )
			{
				if( !m_enemy[i].m_bBoring &&
					bullet->HitTest( m_enemy[i] ) )
				{
					// our bullet hit the enemy
					bullet->m_active = FALSE;
				//��ը	
				////	Explode( *bullet );	
					m_enemy[i].m_active = FALSE;
			
					if( !m_enemy[i].m_active )
					{
						// the enemy is dead
					//	Explode( m_enemy[i], TRUE );
						//m_DirectSound.Play( EFFECT_EXPLODE );
						BoreBonus(m_enemy[i].m_x,m_enemy[i].m_y);
						m_nEnemys --;
						m_player[k].m_nScore += 100;
					}
					break;
				}
			}	//�ӵ����е��ˣ�END��
//-----------------------------------------------
		}//����ӵ�����END��
//------------------------------------------------------
	}//��Ҵ���END


//+++++++++++++++++++++++++++++++++
//		���˵Ĵ�����
//+++++++++++++++++++++++++++++++++
	if(m_bEnemyLocked) 
		if((timeGetTime()-m_lockTime)>5000) m_bEnemyLocked=false;
//��������
///-------
		for( i = 0; i < m_nMaxEnemys&&!m_bEnemyLocked; i ++ )
	{
//��ģ�û�����ģ��ƶ���ת��
//-----------
		if(!m_enemy[i].m_bBoring&&
			m_enemy[i].m_active )
		{
			x = m_enemy[i].m_x;
			y = m_enemy[i].m_y;
			dir = m_enemy[i].m_dir;
			//�߲����ĵı�ת�����߶�����0.5%����ת����
			if( rand() % 200 == 0 ||
				!m_enemy[i].Move() )
			{
				m_enemy[i].ChangeDirection();
			}
		}
//-----------	
		
///����Ƿ�з�������
//-------------------------
			for( int j = 0; j < m_nMaxEnemys; j ++ )
			{
				if( i != j &&
					m_enemy[i].HitTest( m_enemy[j], x, y ) )
				{
					// two enemys hit each other
					m_enemy[i].ChangeDirection();
				/*
					//�ı䷽��������ˣ��ͻ�ԭ��
			
					if( m_enemy[i].HitTest( m_enemy[j], x, y ) )
					{
						m_enemy[i].m_x = x;
						m_enemy[i].m_y = y;
						m_enemy[i].m_dir = dir;
					}
				*/
					break;
				}
			}///����Ƿ�з�������(END)
//-------------------------
		//��1%���ʿ���	
			if( rand() % 50 == 0 )
				m_enemy[i].Fire();
//���з��ӵ�������
//-----------
		bullet = &m_enemy[i].m_bullet[0];
		if( bullet->m_active )
		{
			if( !bullet->Move() )
				bullet->m_active = FALSE;
		}
		for(k=0;k<2;k++)
			if(bullet->HitTest(m_player[k]))
			{
				bullet->m_active = FALSE;
				m_player[k].m_nLife--;
				if(m_player[k].m_nLife<0)
				{
					m_player[k].m_active=FALSE;
					m_gameState=GS_OVER;
				}
			}
//-----------
	}	// process enemys(END)
		//(For ���)��ģ�û�����ģ��ƶ���ת�򣩣�END��
lastTick = timeGetTime();
}
	// produce some enemys...
	static DWORD lastTime=0;
	DWORD thisTime = timeGetTime();
//3 Sec�� �Ͳ�������
	if( thisTime - lastTime > 3000 )
	{
		lastTime = thisTime;
		BoreEnemy();
	}

}		
		//	surface = m_plane.GetSurface( m_enemy[i] );
	//		if( surface == OBJ_BRICK )
		//	{//�����ǽ��70%�ǿ���30%ת����
			/*	if( rand() % 100 < 30 )
				{
					m_enemy[i].ChangeDirection();
				//	surface = m_plane.GetSurface( m_enemy[i] );
				}
				else
					m_enemy[i].Fire();
			*/
		//	}
		//	else if( surface == OBJ_CONCRETE ||
		//			surface == OBJ_RIVER )
		//	{//����ˮ��������ת����
		//		m_enemy[i].ChangeDirection();
		//		surface = m_plane.GetSurface( m_enemy[i] );
		//	}
			//�����������ˣ�����
/*			if( m_enemy[i].HitTest( m_player[0], (int)x, (int)y ) ||
				m_enemy[i].HitTest( m_player[1], (int)x, (int)y ) )
			{
				m_enemy[i].m_x = x;
				m_enemy[i].m_y = y;
				m_enemy[i].m_dir = dir;
				m_enemy[i].Fire();
			}//�������ǰ��û·����ԭ
			else if( surface != OBJ_NULL && surface != OBJ_TREE )
			{
				m_enemy[i].m_x = x;
				m_enemy[i].m_y = y;
				m_enemy[i].m_dir = dir;
			}

  */

	

////////////////////////////////////////////////////////
//Load all the Bitmap or Create DC
////////////////////////////////////////////////////////
BOOL CGame::DDInit()
{
 m_hWnd=HWnd;
 hdc=GetDC(m_hWnd);
 hdcMem=CreateCompatibleDC(hdc);
 hdcBuff=CreateCompatibleDC(hdc);
 hdcMem_Test=CreateCompatibleDC(hdc);

hbm=CreateCompatibleBitmap(hdc,700,500);
hTest_bmp=CreateCompatibleBitmap(hdc,53,49);
	SelectObject(hdcMem,hbm);
	SelectObject(hdcMem_Test,hTest_bmp);
	//=h_pic
m_pBmpList[0]=(HBITMAP)LoadImage(NULL,"pic\\Sky.bmp",IMAGE_BITMAP,40,40,LR_LOADFROMFILE);
	
	//h_ball
m_pBmpList[1]=(HBITMAP)LoadImage(NULL,"pic\\λͼ_126.bmp",IMAGE_BITMAP,13,13,LR_LOADFROMFILE);
/*
	//h_Killer
//m_pBmpList[1]=(HBITMAP)LoadImage(NULL,"Killer.bmp",IMAGE_BITMAP,106,49,LR_LOADFROMFILE);

	//Enemy
	*/
m_pBmpList[2]=(HBITMAP)LoadImage(NULL,"pic\\Enemy.BMP",IMAGE_BITMAP,336,268,LR_LOADFROMFILE);
	//bore-Enemy
m_pBmpList[3]=(HBITMAP)LoadImage(NULL,"pic\\bore.bmp",IMAGE_BITMAP,560,71,LR_LOADFROMFILE);
	//player 1
m_pBmpList[4]=(HBITMAP)LoadImage(NULL,"pic\\Player1.BMP",IMAGE_BITMAP,288,256,LR_LOADFROMFILE);
	//bore-Player
m_pBmpList[5]=(HBITMAP)LoadImage(NULL,"pic\\Player1Bore.bmp",IMAGE_BITMAP,480,64,LR_LOADFROMFILE);
	//h_Popo
m_pBmpList[6]=(HBITMAP)LoadImage(NULL,"pic\\Popo.bmp",IMAGE_BITMAP,132,41,LR_LOADFROMFILE);	
	//h_heart
m_pBmpList[7]=(HBITMAP)LoadImage(NULL,"pic\\heart.bmp",IMAGE_BITMAP,19,19,LR_LOADFROMFILE);	
 
	//h_explode
m_pBmpList[8]=(HBITMAP)LoadImage(NULL,"pic\\Explosion.bmp",IMAGE_BITMAP,560,200,LR_LOADFROMFILE);	

	//h_bouns-list
m_pBmpList[9]=(HBITMAP)LoadImage(NULL,"pic\\Gift3.bmp",IMAGE_BITMAP,126,45,LR_LOADFROMFILE);	
m_pBmpList[10]=(HBITMAP)LoadImage(NULL,"pic\\Gift5.bmp",IMAGE_BITMAP,126,45,LR_LOADFROMFILE);	
m_pBmpList[11]=(HBITMAP)LoadImage(NULL,"pic\\Gift6.bmp",IMAGE_BITMAP,126,45,LR_LOADFROMFILE);	
m_pBmpList[12]=(HBITMAP)LoadImage(NULL,"pic\\Gift1.bmp",IMAGE_BITMAP,126,45,LR_LOADFROMFILE);	
m_pBmpList[13]=(HBITMAP)LoadImage(NULL,"pic\\GiftTurtle.bmp",IMAGE_BITMAP,108,41,LR_LOADFROMFILE);	
//m_pBmpList[14]=(HBITMAP)LoadImage(NULL,"GiftTurtle.bmp",IMAGE_BITMAP,126,45,LR_LOADFROMFILE);	




//m_pBmpList[3]=(HBITMAP)LoadImage(NULL,"explode.bmp",IMAGE_BITMAP,92,370,LR_LOADFROMFILE);

//m_pBmpList[5]=h_heart=(HBITMAP)LoadImage(NULL,"heart.bmp",IMAGE_BITMAP,19,19,LR_LOADFROMFILE);
//m_pBmpList[6]=h_Frame=(HBITMAP)LoadImage(NULL,"λͼ_296.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);

 // GetObject (h_pic, sizeof (BITMAP), &bitmap) ;
 
//		   cxSource=bitmap.bmWidth;


//		   cySource=bitmap.bmHeight;
//		   */
////////////////////////////////////////////////////
//����
	//player1.bmp bullet.bmp bore.bmp shield.bmp
m_player[0].BitBlt( &m_pBmpList[4], &m_pBmpList[1], &m_pBmpList[5]);
 for( int j = 0; j < 2; j ++ )
	m_player[0].m_explode[j].BitBlt(&m_pBmpList[6],&m_pBmpList[8]);

///����
for( int i = 0; i < NUM_ENEMYS; i ++ )
	m_enemy[i].BitBlt(&m_pBmpList[2], &m_pBmpList[1],&m_pBmpList[3]);
return true;
}
////////////////////////////////////////////////////////
//��Ϸ��ʼ��
////////////////////////////////////////////////////////
BOOL CGame::InitGame()
{
	srand( timeGetTime() );//��������
	/*
	// initialize input devices
	m_DirectInput.Create( m_hInst, m_hWnd );
	
	// initizlize sound effects
	m_DirectSound.Init( m_hWnd );
	*/
//����������ң�����
	m_player[0].Create( 48, 64, TRUE );
	m_player[1].Create( 28, 28, FALSE );
//for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
	m_player[0].m_explode[j].m_active=false;
//Create���� ������ʱ��Ч
	for( int i = 0; i < NUM_ENEMYS; i ++ )
		m_enemy[i].Create( 56, 67, FALSE );

//Create��ը ������ʱ��Ч
//	for( i = 0; i < NUM_EXPLODES;  i ++ )
//		m_explode[i].Create( 28, 28, FALSE );
	/*
//Create���� ������ʱ��Ч
	m_bonus.Create( 30, 28, FALSE );
	*/
//��ѡ�����
	m_gameState = GS_ACTIVE;

	return TRUE;
}




////////////////////////////////////////////////////////
//��ʼ�����ܿ��ƣ�
////////////////////////////////////////////////////////
BOOL CGame::Initialize( HINSTANCE hInst )
{
	m_hInst = hInst;

	if( !DDInit() || !InitGame() )
	{
		DDTerm();
		return FALSE;
	}
	//�����޸ı���û��
	ResetGame();
	return TRUE;
}
////////////////////////////////////////////////////////
//InitLevel�����ȼ���ʼ��
//
///////////////////////////////////////////////////////
BOOL CGame::InitLevel()
{
	for( int i = 0; i < NUM_ENEMYS; i ++ )
	{
		m_enemy[i].m_active = FALSE;
		m_enemy[i].m_bullet[0].m_active = FALSE;
	}
	m_bonus.m_active = FALSE;
	m_nEnemysLeft = m_nEnemys = 20;
	for(i=0;i<2;i++)
		for(int j=0;j<2;j++)
		{	m_player[i].m_explode[j].m_explode=false;
			m_player[i].m_explode[j].m_active = FALSE;
		}
	m_bEnemyLocked=false;
	return TRUE;
}
//////////////////////////////////////////////////
///RestGame ��Ϸ���濪ʼ�ĳ�ʼ��-m_nMaxEnemys��m_gameState��m_bActive
//Ҳ������ InitLevel();
////////////////////////////////////////////////
BOOL CGame::ResetGame()
{
		m_nMaxEnemys = 4;
		m_gameState = GS_ACTIVE;
		m_bActive=true;
		ResetPlayer(m_player[0]);
		return InitLevel();
}
//


void CGame::ResetPlayer( CPlayer& player )
{
	if( &player == &m_player[0] )
	{
		player.m_x = PLAYER1_STARTX;
		player.m_y = PLAYER1_STARTY;
	}
	else
	{
		player.m_x = PLAYER2_STARTX;
		player.m_y = PLAYER2_STARTY;
	}
	player.Reborn();
}


//
////////////////////////////////////////////////////////
//Relase memery.It is a VIP .
//
////////////////////////////////////////////////////////
void CGame::DDTerm()
{
/*	for( int i = 0; i < NUM_BITMAPS; i ++ )
		SAFE_RELEASE( m_pBmpList[i] );	
	if( !m_bFullScreen )
		SAFE_RELEASE( m_pddsBackBuffer );
	SAFE_RELEASE( m_pddsFrontBuffer );
	SAFE_RELEASE( m_pDD );*/
}
//
//
////////////////////////////////////////////////////////
//Enter of this Programe
////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
 
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_G2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
 
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}


	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_G2);

//////////////////////////////////////////////////
///��Ϸ�Ŀ�ʼ
CGame	game;
	
	game.Initialize( hInst );
	return game.Run();
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_G2);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_G2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
 // HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   HWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!HWnd)
   {
      return FALSE;
   }

   ShowWindow(HWnd, nCmdShow);
   UpdateWindow(HWnd);
MoveWindow(HWnd,50,15,800,600,true);
   return true;
}

//

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
