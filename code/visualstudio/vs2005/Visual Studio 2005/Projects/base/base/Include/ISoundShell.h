
#ifndef   _ISOUND_H_HEADER_INCLUDED_
#define   _ISOUND_H_HEADER_INCLUDED_
 
struct ISoundShell
{
public:
	//## ���ٽӿڶ���
	virtual  void	Release() = 0;
	//## ��ʼ����Ч����
	virtual  BOOL	Init(HWND pWnd) = 0;

	//---------��Ч���Ų���---------------
	//## ��Ч���Žӿ�
	virtual  void	PlayASound(
		//## ��������Ч���ļ���
		LPSTR FileName,
		//## ��������Ч������
		INT nPan,
		//## ��������Ч������
		INT nVol, 
		//## ��������Ч�Ƿ�ѭ������
		BOOL bLoop) = 0;

	//## ֹͣ������Ч
	virtual  void	StopASound(
		//## ��Ҫֹͣ���ŵ���Ч���ļ���
		LPSTR FileName) = 0;

	//## ������Ч���ŵ�����
	virtual  void	SetSoundVolume(
		//## ��Ч���ļ���
		LPSTR FileName,
		//## ��Ч�Ĳ�������
		LONG lVolume) = 0;
	//## �ж��Ƿ����ڲ�����Ч
	virtual  BOOL    IsPlayingSound(LPSTR FileName) = 0;
	virtual void StopAllSound() = 0;

	//---------���ֲ��Ų���---------------
	//## ���ֲ��Žӿ�
	virtual  void	PlayMusic(
		//## ���������ֵ��ļ���
		LPSTR FileName,
		//## �Ƿ�ѭ����������
		BOOL bLoop) = 0;

	//## ֹͣ�������ֽӿ�
	virtual  void	StopMusic() = 0;

	//## �������ֲ��ŵ�������С
	virtual  void	SetMusicVolume(
		//## ������С
		LONG lVolume) = 0;
	//## �ж��Ƿ����ڲ�������
	virtual  BOOL   IsPlayingMusic() = 0;

	//����Log����ļ�
	virtual	void	SetLogFile(class KLogFile*	pLogFile) = 0;

	//ÿ֡��Ҫ������
	virtual void	Update() = 0;
};

//------ģ��Ľӿں�����ԭ�͵Ķ���------
typedef ISoundShell*					(*fnCreateSoundShell)();

//------�ӿں����ĺ������ַ���----------
#define	FN_CREATE_SOUND_SHELL			"CreateSoundShell"


#endif //_ISOUND_H_HEADER_INCLUDED_
