// MyMFC_PlayingCard.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyMFC_PlayingCardApp:
// See MyMFC_PlayingCard.cpp for the implementation of this class
//

class CMyMFC_PlayingCardApp : public CWinApp
{
public:
	CMyMFC_PlayingCardApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyMFC_PlayingCardApp theApp;