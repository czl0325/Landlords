// StarDlg.h : header file
//

#pragma once


// CStarDlg dialog
class CStarDlg : public CDialog
{
private: 
	
	CRgn   m_MainRgn;
	int m_nStarButton_X;//开始按键的X坐标
	int m_nStarButton_Y;//开始按键的Y坐标
	int m_nExitButton_X;//退出按键的X坐标
	int m_nExitButton_Y;//退出按键的Y坐标
	BOOL m_bInStar;//是否在开始按键的矩阵内
	BOOL m_bInExit;//是否在退出按键的矩阵内
	RECT m_rStarGame;//开始按键的矩阵
	RECT m_rExitGame;//退出按键的矩阵
	RECT m_rWindow;//窗口的矩阵
	HDC m_hStarDC_1;
	HDC m_hStarDC_2;
	HDC m_hExitDC_1;
	HDC m_hExitDC_2;
	HDC m_hGameBack;//背景
	HDC m_hFrontDC;//前DC
	HDC m_hBackDC;//后DC
private:
	BOOL BitmapToDC(HDC DestDC,char* FileName,int Bitmap_Width,int Bitmap_Height);
// Construction
public:
	CStarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYMFC_PLAYINGCARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
   
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
