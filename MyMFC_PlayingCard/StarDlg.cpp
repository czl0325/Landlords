// StarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMFC_PlayingCard.h"
#include "StarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStarDlg dialog




CStarDlg::CStarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStarDlg::IDD, pParent)
{
	this->m_nStarButton_X=40;
	this->m_nStarButton_Y=50;
	this->m_nExitButton_X=130;
	this->m_nExitButton_Y=50;
	RECT tempStar={m_nStarButton_X,m_nStarButton_Y,m_nStarButton_X+81,m_nStarButton_Y+45};
	this->m_rStarGame=tempStar;
	RECT tempExit={m_nExitButton_X,m_nExitButton_Y,m_nExitButton_X+81,m_nExitButton_Y+45};
	this->m_rExitGame=tempExit;
	
	this->m_hStarDC_1=::CreateCompatibleDC(NULL);
	this->m_hStarDC_2=::CreateCompatibleDC(NULL);
	this->m_hExitDC_1=::CreateCompatibleDC(NULL);
	this->m_hExitDC_2=::CreateCompatibleDC(NULL);
	this->m_hGameBack=::CreateCompatibleDC(NULL);

	this->m_bInStar=FALSE;
	this->m_bInExit=FALSE;
	BitmapToDC(m_hStarDC_1,"bmp\\StarGameButton.bmp",81,45);
	BitmapToDC(m_hStarDC_2,"bmp\\StarGameButton2.bmp",81,45);
	BitmapToDC(m_hExitDC_1,"bmp\\ExitButton.bmp",81,45);
	BitmapToDC(m_hExitDC_2,"bmp\\ExitButton2.bmp",81,45);
	BitmapToDC(m_hGameBack,"bmp\\FInfor_Middle.bmp",248,140);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LORD);
}

void CStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
void CStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.x>m_rStarGame.left && point.x<m_rStarGame.right &&
		point.y>m_rStarGame.top && point.y<m_rStarGame.bottom)
	{
		CDialog::OnOK();
	}else if(point.x>m_rExitGame.left && point.x<m_rExitGame.right &&
		point.y>m_rExitGame.top && point.y<m_rExitGame.bottom)
	{
		::PostMessage(m_hWnd,WM_CLOSE,NULL,NULL);
	}
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));     

}
void CStarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(point.x>m_rStarGame.left && point.x<m_rStarGame.right &&
		point.y>m_rStarGame.top && point.y<m_rStarGame.bottom)
	{
		m_bInStar=TRUE;
	}else
	{
		m_bInStar=FALSE;
	}
}

BOOL CStarDlg::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}
BEGIN_MESSAGE_MAP(CStarDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



//初始化窗口的函数
BOOL CStarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CRect   m_Rect; 
	GetClientRect(&m_Rect);
	m_MainRgn.CreateRoundRectRgn(0,0,m_Rect.Width(),m_Rect.Height(),40,40);
	SetWindowRgn(m_MainRgn,TRUE);   

	//获取窗口矩阵

	GetClientRect(&m_rWindow);
	m_hFrontDC=::GetDC(this->m_hWnd);
	m_hBackDC=::CreateCompatibleDC(m_hFrontDC);
	HBITMAP bitmap=::CreateCompatibleBitmap(m_hFrontDC,m_rWindow.right,m_rWindow.bottom);
	::SelectObject(m_hBackDC,bitmap);
	
	

	
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	
	return TRUE;  
}

void CStarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//BOOL b=::BitBlt(m_hBackDC,0,0,m_rWindow.right,m_rWindow.bottom,m_hGameBack,0,0,SRCCOPY);
		BOOL b=::TransparentBlt(m_hBackDC,0,0,248,140,m_hGameBack,0,0,248,140,RGB(255,255,255));
		if(!m_bInStar)
		{
			::TransparentBlt(m_hBackDC,m_nStarButton_X,m_nStarButton_Y,81,45,m_hStarDC_1,0,0,81,45,RGB(0,0,0));
		}else if(m_bInStar)
		{
			::TransparentBlt(m_hBackDC,m_nStarButton_X,m_nStarButton_Y,81,45,m_hStarDC_2,0,0,81,45,RGB(0,0,0));
		}
		::TransparentBlt(m_hBackDC,m_nExitButton_X,m_nExitButton_Y,81,45,m_hExitDC_1,0,0,81,45,RGB(0,0,0));
		
		::TransparentBlt(m_hFrontDC,0,0,m_rWindow.right,m_rWindow.bottom,m_hBackDC,0,0,m_rWindow.right,m_rWindow.bottom,RGB(0,0,0));
		CDialog::OnPaint();
	}
}

HCURSOR CStarDlg::OnQueryDragIcon()
{
	
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CStarDlg::BitmapToDC(HDC DestDC, char *FileName, int Bitmap_Width,int Bitmap_Height)
{
	CString str;
	HBITMAP hBitmap=(HBITMAP)::LoadImage(NULL,FileName,IMAGE_BITMAP,Bitmap_Width,Bitmap_Height,
		LR_LOADFROMFILE);
	if(hBitmap==NULL)
	{
		str.Format("无法导入位图:%s",FileName);
		AfxMessageBox(str);
		return FALSE;
	}
	if(FAILED(SelectObject(DestDC,hBitmap)))
	{
		return FALSE;
	}
	return TRUE;
}