// KCDlgSynSpr.cpp : implementation file
//

#include "stdafx.h"
#include "SprReader.h"
#include "KCDlgSynSpr.h"
#include "KCDialogRename.h"

KStrcutSynSpr g_KSSynSpr;
// KCDlgSynSpr dialog

IMPLEMENT_DYNAMIC(KCDlgSynSpr, CDialog)

KCDlgSynSpr::KCDlgSynSpr(CWnd* pParent /*=NULL*/)
	: CDialog(KCDlgSynSpr::IDD, pParent)
	, m_nFrame(0)
	, m_Interval(_T(""))
{
	g_KSSynSpr.nFrame = 0;
	m_nFrame = 0;
	memset(&m_SprHead, 0, sizeof(m_SprHead)); 
}

KCDlgSynSpr::~KCDlgSynSpr()
{
}

void KCDlgSynSpr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);

	//Style
	DWORD dwStyle;
	dwStyle = m_ListCtrl.GetStyle();
	m_ListCtrl.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);
	//
	m_ListCtrl.InsertColumn(0, "���", LVCFMT_LEFT, 40);
	m_ListCtrl.InsertColumn(1, "�ļ���", LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(2, "��Դλ��", LVCFMT_LEFT, 350);
	DDX_Text(pDX, IDC_EDITINTERVAL, m_Interval);
}


BEGIN_MESSAGE_MAP(KCDlgSynSpr, CDialog)
	ON_BN_CLICKED(IDC_BUTTONADD, &KCDlgSynSpr::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTONSYN, &KCDlgSynSpr::OnBnClickedButtonsyn)
	ON_BN_CLICKED(IDC_BUTLEAVE, &KCDlgSynSpr::OnBnClickedButleave)
	ON_BN_CLICKED(IDC_BUTTONDELETE, &KCDlgSynSpr::OnBnClickedButtonDeleteAll)
	ON_BN_CLICKED(IDC_BUTTONMove, &KCDlgSynSpr::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTONUP, &KCDlgSynSpr::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTONSOWN, &KCDlgSynSpr::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTONRENAME, &KCDlgSynSpr::OnBnClickedButtonRename)
END_MESSAGE_MAP()


// KCDlgSynSpr message handlers


void KCDlgSynSpr::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("png (*.png)|*.png|�����ļ�(*.*)|*.*||"), this);

	dlg.m_ofn.nMaxFile = MAXFILENUM;
	char *pc = new char[MAXFILENUM];
	dlg.m_ofn.lpstrFile = pc;
	dlg.m_ofn.lpstrFile[0] = NULL;
	CString strFilePath;
//	MessageBox(m_FileName.GetBuffer(), "ERROR", MB_OK);
	CString strFileName = m_FileName;	//��ֹ������ȴû��ѡ�ļ������
	CString strFirstName = m_FileName;
	int len = 0; // for string handle

	if(dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		while( NULL != pos)
		{
//			g_KSSynSpr.nFrame++;
			
			strFilePath = dlg.GetNextPathName(pos);
			//�����ж��ļ������Ƿ��������

			//���ļ������б�� -- 
			int n = strFilePath.ReverseFind('\\');
			CString strPath = strFilePath.Left(n+1);	//�õ�·�����������һ��'\'
			CString strName = strFilePath.Right(strFilePath.GetAllocLength()- n-1);		// �õ�ȥ��·�����ļ�ȫ��
			/*test
//			int row = m_ListCtrl.InsertItem(m_nFrame, strPath.GetBuffer());
//			char str[4000];
//			itoa(row, str, 10);
//			MessageBox(str, "ERROR", MB_OK);
			*/
			char strTemp[32];
			itoa(m_nFrame+1, strTemp, 10);
			m_ListCtrl.InsertItem(m_nFrame, strTemp); 
			m_ListCtrl.SetItemText(m_nFrame, 1, strName.GetBuffer());
			m_ListCtrl.SetItemText(m_nFrame, 2, strPath.GetBuffer());

			m_nFrame++;									//ͳ���ļ�������֡������
			if(m_nFrame == 1)
			{
				strFirstName = strFilePath;
//				MessageBox(strFirstName, "strFirstName", MB_OK);
			}
		}
//		char temp[32];
//		itoa(g_KSSynSpr.nFrame, temp, 10);
//		MessageBox(temp, "ERROR", MB_OK);


		/**
		 * ��2012-09-12��Ϊ��ʹ�õ�һ������ΪĬ�ϵ��޸����֣������´�����ֵ�strFilePath��ΪstrFirstName������û��
		 */
		if(strFirstName.IsEmpty())
			return;

		 // �õ��ļ�����ǰ׺,eg: xxx.0.png �õ�.0֮ǰ��λ��
		/**
		 * ��2012-09-04���������·���а�����'.'�Ļ�������ĳ�����Ϊ����
		 */
//		int len = strFilePath.Find('.');	//�õ�'.'֮ǰ�ĳ���
//		strFileName = strFilePath.Left(len);

		len = strFirstName.ReverseFind('.');	// �õ�xxx.n.png�ĵ�һ��'.'
		strFirstName = strFirstName.Left(len);
		while(strFirstName.ReverseFind('.') > strFirstName.ReverseFind('\\'))	//·�����л���'.'
		{
			len = strFirstName.ReverseFind('.');
			strFirstName = strFirstName.Left(len);
		}

		/**/
//		strFileName += ".spr";
//		MessageBox(strFileName.GetBuffer(), "ERROR", MB_OK);
	}

	//��ֵ��ȫ�ֱ���
	m_FileName = strFirstName;
	MessageBox(m_FileName, "m_FileName", MB_OK);
	//�õ������ļ�������
	len = m_FileName.ReverseFind('\\');
	g_FileName = m_FileName.Right(m_FileName.GetAllocLength() - len -1);
//	MessageBox(g_FileName, "g_FileName", MB_OK);
//	g_KSSynSpr.nFrame  = ;
}

void KCDlgSynSpr::OnBnClickedButtonsyn()
{
	// TODO: Add your control notification handler code here
	SprConverter spr;
	CString strInfo;	//MessageBox��ʾ����Ϣ
	CString strInt;		//��ʱ���� -- ����ʵ��int to char

	// ��Ϣ׼��
	strInfo = "���ֻ��߳��ȴ������⣺\n";
	strInfo +=  "�ļ�����" + m_FileName;	
	strInt.Format("\n֡������%d\n", m_nFrame);
	strInfo += strInt;

	// ������� �� ���� 
	if( m_FileName.IsEmpty() || m_nFrame == 0){
		MessageBox(strInfo.GetBuffer(), "ERROR", MB_OK);
		return;
	}

	//��Ϣ��ʾ
	strInfo.Empty();
	strInt.Empty();
	strInfo = "�ϳ��ļ����� ";
	strInfo += m_FileName + ".spr";
	strInt.Format("\n֡������%d\n", m_nFrame);
	strInfo += strInt;

	/// ������Ϣ������
	UpdateData(true);		// ���´����ϵ�ֵ������
//	MessageBox(m_Interval.GetBuffer(), "xxx", MB_OK);
	m_SprHead.Interval = atoi(m_Interval.GetBuffer());
	
	int n = MessageBox(strInfo.GetBuffer(), "��ʾ", MB_OKCANCEL);
	if(n == IDOK){
		//��ʼ�ϳ�
		if(spr.CreateNewSprFile(m_FileName.GetBuffer(), m_nFrame, m_SprHead))
			MessageBox("�ϳɳɹ���", "ERROR", MB_OK);
		else
			MessageBox("�ϳ�ʧ�ܣ�", "ERROR", MB_OK);

		//����
		m_nFrame = 0;
		m_FileName.Empty();
		m_ListCtrl.DeleteAllItems();
	}
//	CDialog::OnOK();
}

void KCDlgSynSpr::OnBnClickedButleave()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void KCDlgSynSpr::OnBnClickedButtonDeleteAll()
{
	// TODO: Add your control notification handler code here
	m_nFrame = 0;
	m_FileName.Empty();
	m_ListCtrl.DeleteAllItems();
}

void KCDlgSynSpr::OnBnClickedButtonMove()
{
	// TODO: Add your control notification handler code here
	//�õ�ѡ�е��кţ��ĸ�item
	for( int i = 0; i < m_ListCtrl.GetItemCount(); )
	{
		if( m_ListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_ListCtrl.DeleteItem(i);
			m_nFrame--;

			//����һ��ɾ�����ѡ�е����
			i = 0;
			continue;
		}
		CString strTemp;
		strTemp.Format("%d", i+1);
		m_ListCtrl.SetItemText(i, 0, strTemp);
		i++;
	}
}

void KCDlgSynSpr::OnBnClickedButtonUp()
{
	// TODO: Add your control notification handler code here
	TCHAR szBuf[MAXFILENUM];
	LVITEM lvi;
	lvi.iSubItem = 0;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = szBuf;
	lvi.cchTextMax = MAXFILENUM;
	//�õ�ѡ�е��кţ��ĸ�item
	for( int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		if( m_ListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			// 
			if(i> 0){
				/* //����������
				lvi.iItem = i;
				m_ListCtrl.GetItem(&lvi);
				m_ListCtrl.DeleteItem(i);
				lvi.iItem = i-1;
				m_ListCtrl.InsertItem(&lvi);
				*/
				CString str1, str2, str3;
				//����
				str1 = m_ListCtrl.GetItemText(i, 0);
				str2 = m_ListCtrl.GetItemText(i, 1);
				str3 = m_ListCtrl.GetItemText(i, 2);
				//ɾ��
				m_ListCtrl.DeleteItem(i);
				//���²���
				str1.Format("%d", i);
				m_ListCtrl.InsertItem(i-1, str1);
				m_ListCtrl.SetItemText(i-1, 1, str2);
				m_ListCtrl.SetItemText(i-1, 2, str3);

				str1.Format("%d", i+1);
				m_ListCtrl.SetItemText(i, 0, str1);

				//��Ȼѡ����һ��
//				m_ListCtrl.SetItemState(i-1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			}
		} 
	}
}

void KCDlgSynSpr::OnBnClickedButtonDown()
{
	// TODO: Add your control notification handler code here
	for( int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		if( m_ListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			// 
			if(i>= 0){
				/* //����������
				lvi.iItem = i;
				m_ListCtrl.GetItem(&lvi);
				m_ListCtrl.DeleteItem(i);
				lvi.iItem = i-1;
				m_ListCtrl.InsertItem(&lvi);
				*/
				CString str1, str2, str3;
				//����
				str1 = m_ListCtrl.GetItemText(i, 0);
				str2 = m_ListCtrl.GetItemText(i, 1);
				str3 = m_ListCtrl.GetItemText(i, 2);
				//ɾ��
				m_ListCtrl.DeleteItem(i);
				//���²���
				str1.Format("%d", i+2);
				m_ListCtrl.InsertItem(i+1, str1);
				m_ListCtrl.SetItemText(i+1, 1, str2);
				m_ListCtrl.SetItemText(i+1, 2, str3);

				str1.Format("%d", i+1);
				m_ListCtrl.SetItemText(i, 0,  str1);
				//��Ȼѡ����һ��
//				m_ListCtrl.SetItemState(i-1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);


				//����
				return;
			}
		}
	}
}

void KCDlgSynSpr::OnBnClickedButtonRename()
{
	// TODO: Add your control notification handler code here
	/* for test
	string OldName, NewName, StrCmd;
	OldName = "xxx.spr";
	NewName = "yyy.spr";
	StrCmd = "rename ";
	StrCmd += OldName;
	StrCmd += " ";
	StrCmd += NewName;
//	MessageBox(StrCmd.c_str(), "CMD", MB_OK);
	
	system(StrCmd.c_str());
	*/
	m_pKCDlgRename = new KCDialogRename;
	m_pKCDlgRename->m_pParent = this;
	m_pKCDlgRename->Create(KCDialogRename::IDD);

	m_pKCDlgRename->ShowWindow(SW_SHOW);
}

void KCDlgSynSpr::RenameUpdate(void)
{
		/**/
	CString NewFileName;
	string StrCmd, PreName, OldName, NewName;
	PreName = g_FileName.GetBuffer();
	int SigRename = 0;			// �洢�����Ƿ�ɹ�
	int result = 1;
//	MessageBox(PreName.c_str(), "PreName", MB_OK);

	// �޸ĺϳɵ��ļ���
	m_FileName = m_FileName.Left(m_FileName.ReverseFind('\\'));
	m_FileName += "\\";
	m_FileName += PreName.c_str();

	for(int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		/*
		CString str1, str2, str3;
		//����
		str1 = m_ListCtrl.GetItemText(i, 0);
		str2 = m_ListCtrl.GetItemText(i, 1);
		str3 = m_ListCtrl.GetItemText(i, 2);
		*/

		// old name
		OldName = m_ListCtrl.GetItemText(i, 1);

		//new name
		NewFileName.Format("%s.%d.png", PreName.c_str(), i);
		NewName = NewFileName.GetBuffer();
//		MessageBox(NewFileName.GetBuffer(), "SHOW", MB_OK);
		StrCmd = "rename ";
		StrCmd += OldName;
		StrCmd += " ";
		StrCmd += NewName;

//		MessageBox(StrCmd.c_str(), "CMD", MB_OK);
		result = system(StrCmd.c_str());
		SigRename = (SigRename | result);
		if(result !=0)
		{
			MessageBox("����ʧ�ܣ�", "��ʾ", MB_OK);
			return;
		}

		m_ListCtrl.SetItemText(i, 1, NewName.c_str());	
	}

	MessageBox("�����ɹ���", "��ʾ", MB_OK);

	//�޸ĺϳɵ��ļ���
	/*
	MessageBox(m_FileName, "FileName1", MB_OK);
	int tlen = m_FileName.GetAllocLength();
	int len = m_FileName.ReverseFind('\\');
	CString StrTest;
	StrTest.Format("%d, %d", tlen, len);
	MessageBox(StrTest, "LEN", MB_OK);
	*/
}
