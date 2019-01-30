#pragma once


// CMainFrm frame
#include "Game.h"
class CMainFrm : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrm)
private:
	static CGame* m_pGame;
	
	DWORD dwThreadID;
public:
	static void GamePain();
public:
	CMainFrm();           // protected constructor used by dynamic creation
	virtual ~CMainFrm();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC );

	DECLARE_MESSAGE_MAP()

	
};


