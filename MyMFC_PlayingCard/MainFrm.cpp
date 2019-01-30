// MainFrm.cpp : implementation file
//

#include "stdafx.h"
#include "MyMFC_PlayingCard.h"
#include "MainFrm.h"


// CMainFrm
IMPLEMENT_DYNCREATE(CMainFrm, CFrameWnd)
CGame* CMainFrm::m_pGame=NULL;
CMainFrm::CMainFrm()
{
	
	RECT rc={112,84,912,720};
	Create(NULL,_T("¶·µØÖ÷"),WS_OVERLAPPED|WS_MINIMIZEBOX,rc);
	
}

CMainFrm::~CMainFrm()
{
	if(m_pGame!=NULL)
	{
		delete(m_pGame);
		m_pGame=NULL;
	}
}

int CMainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pGame=new CGame(::GetDC(this->m_hWnd),this->m_hWnd);
	::SetTimer(this->m_hWnd,0,10,NULL);

	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GamePain,0,NULL,&dwThreadID);
	return 1;
}
void CMainFrm::GamePain()
{

	if(m_pGame!=NULL)
	{
		m_pGame->GamePaint();
	}
	
}
void CMainFrm::OnPaint()
{
	
}

void CMainFrm::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pGame->MouseLButtonDown(point);
}
void CMainFrm::OnRButtonDown(UINT nFlags,CPoint point)
{
	m_pGame->MouseRButtonDown(point);
}
BOOL CMainFrm::OnEraseBkgnd(CDC* pDC )
{
	return TRUE;
}
void CMainFrm::OnTimer(UINT_PTR nIDEvent)
{}

BEGIN_MESSAGE_MAP(CMainFrm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMainFrm message handlers
