// MyMFC_PlayingCard.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyMFC_PlayingCard.h"
#include "StarDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFC_PlayingCardApp

BEGIN_MESSAGE_MAP(CMyMFC_PlayingCardApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyMFC_PlayingCardApp construction

CMyMFC_PlayingCardApp::CMyMFC_PlayingCardApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMyMFC_PlayingCardApp object

CMyMFC_PlayingCardApp theApp;


// CMyMFC_PlayingCardApp initialization

BOOL CMyMFC_PlayingCardApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CStarDlg dlg;
//	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		m_pMainWnd=new CMainFrm();
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateData();
		return TRUE;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
