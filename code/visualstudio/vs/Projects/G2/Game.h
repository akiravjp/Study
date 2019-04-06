#include "Sprite.h"
#define NUM_BITMAPS 2
#define NUM_EXPLODES 20 
#define NUM_ENEMYS 5
enum GAMESTATE
{
	GS_SPLASH,
	GS_ACTIVE,
	GS_WIN,
	GS_OVER,
};
class CGame  
{
public:
	 
	CGame();
	 
	virtual ~CGame();

	 //��ʼ��
	BOOL Initialize(HINSTANCE hInst);
	  //��ʼ��1
	BOOL	InitApplication();
	 //��ʼ����2��
	BOOL	DDInit();
	//����ʱ�ͷ��ڴ�
	void	DDTerm();
	//��ʼ����3��
	BOOL	InitGame();
	//���½���
	void	UpdateFrame();
	//������Ϸ
	int		Run();
	//���鱬ը
//	void	Explode( CSprite& sprite, BOOL bExplode=FALSE );
	//��ұ���
//	void	PlayerBeenHit( CPlayer& player );
	// ������
	BOOL	BoreBonus();
	//������
	BOOL	BoreEnemy();
	//��ҳԽ���
//	void	EatBonus( CPlayer& player );
	// ���˳Խ���
//	void	EatBonus( CEnemy& enemy );	
	// ���� 
	void	GameOver();
	//����ͼ
	BOOL	LoadBitmaps();
	//����
	void	OutputText( int x, int y, LPCTSTR string );
	//������ͼ
	void	DrawWorld();
	//��Ϣ����
	LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM, LPARAM );

private:
	//ʵ��
	HINSTANCE	m_hInst;
	//���ھ��
	HWND		m_hWnd;
	//�豸����
	HDC hdcMem,hdcBuff;
	HDC hdc;
	HDC hdcMem_Test;
	//�Ƿ�
	BOOL		m_bActive;
	//�Ƿ���֡��
	BOOL		m_bShowStats;
	//֡��
	int frame,fps;
	//����
	RECT		m_rcWindow;
	 
	// ͼƬ����
	HBITMAP		m_pBmpList[NUM_BITMAPS];
	HBITMAP     hbm;
	HBITMAP     hTest_bmp;
	//
	BITMAP bmp,Test_bmp;

	//���
//	CPlayer		m_player[2];
	//����
	BOOL m_bSingle;
	// 
//	CEnemy		m_enemy[NUM_ENEMYS];
	// 
	int			m_nMaxEnemys;
	// 
//	CExplode	m_explode[NUM_EXPLODES];
	// 
//	CBonus		m_bonus;
	// 
	GAMESTATE	m_gameState;
	// 
	DWORD		m_lastTime;
	// 
	int			m_nLevel;
	// 
	int			m_nEnemysLeft;
	// 
	int			m_nEnemys;
	// 
	BOOL		m_bEnemyLocked;
	// 
	DWORD		m_lockTime;
};
