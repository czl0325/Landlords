#include "StdAfx.h"
#include "Game.h"
#include "CardMap.h"

CGame::CGame(HDC hdc,HWND hwnd)
{


	this->m_hDestDC=hdc;
	this->m_bLive=TRUE;
	this->m_bChooseLord=FALSE;
	
	m_hWnd=hwnd;

	RECT rc_Exit={CCardMap::EXIT_X,CCardMap::EXIT_Y,CCardMap::EXIT_X+100,CCardMap::EXIT_Y+30};
	m_rExit=rc_Exit;
	
	RECT rc_Send={CCardMap::OK_X,CCardMap::OK_Y,CCardMap::OK_X+80,CCardMap::OK_Y+30};
	m_rSend=rc_Send;
	
	RECT rc_Yes={CCardMap::CHOOSE_X+14,CCardMap::CHOOSE_Y+40,CCardMap::CHOOSE_X+14+80,CCardMap::CHOOSE_Y+40+30};
	m_rYes=rc_Yes;
	
	RECT rc_No={CCardMap::CHOOSE_X+105,CCardMap::CHOOSE_Y+40,CCardMap::CHOOSE_X+105+80,CCardMap::CHOOSE_Y+40+30};
	m_rNo=rc_No;
	
	m_pDrawCard=new CDrawCard();
	if(m_pDrawCard!=NULL)
	{
		m_pDrawCard->initDrawCard();
	}
	m_pCardMap=new CCardMap();
	if(m_pCardMap!=NULL)
	{
		m_pCardMap->InitRect();
	}
	m_pPlayCard=new CPlayCard();
	if(m_pPlayCard!=NULL)
	{
		m_pPlayCard->initCard();
	}
	
	m_pDrawItem=new CDrawItem();
	if(m_pDrawItem!=NULL)
	{
		m_pDrawItem->initDrawItem();
	}
	m_pCenter=new CPlayer(m_pCardMap);
	m_pLeft=new CComputer(m_pCardMap);
	m_pRight=new CComputer(m_pCardMap);
	/************************************************************/
	NewGame();
	/***********************************************************/
	m_hBackDC=::CreateCompatibleDC(m_hDestDC);
	HBITMAP bitmap = ::CreateCompatibleBitmap(m_hDestDC,800,600);
	::SelectObject(m_hBackDC,bitmap);

	

}
CGame::~CGame(void)
{
	if(m_pDrawCard!=NULL)
	{
		delete(m_pDrawCard);
		m_pDrawCard=NULL;
	}
	if(m_pDrawItem!=NULL)
	{
		delete(m_pDrawItem);
		m_pDrawItem=NULL;
	}
	if(m_pCenter!=NULL)
	{
		delete(m_pCenter);
		m_pCenter=NULL;
	}
	if(m_pLeft!=NULL)
	{
		delete(m_pLeft);
		m_pLeft=NULL;
	}
	if(m_pRight!=NULL)
	{
		delete(m_pRight);
		m_pRight=NULL;
	}
	if(m_pCardMap!=NULL)
	{
		delete(m_pCardMap);
		m_pCardMap=NULL;
	}
	if(m_pPlayCard!=NULL)
	{
		delete(m_pPlayCard);
		m_pPlayCard=NULL;
	}
}
//游戏绘画
int CGame::GamePaint()
{
	while(m_bLive)
	{
		/***********************画游戏背景和游戏按钮*********************/
		if(m_pDrawItem!=NULL)
		{
			m_pDrawItem->DrawGameItem(m_hBackDC,0,0,CDrawItem::GAMEBACK);
			m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::EXIT_X,
				CCardMap::EXIT_Y,CDrawItem::GAMEEXIT);
			m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::OK_X,CCardMap::OK_Y,
				CDrawItem::GAMEPASS);
		}
		/***/
		PainPoint();
		/***/
		for(int i=0;i<m_pCenter->m_nCardCount;i++)
		{
			if(m_pCardMap!=NULL)
			{
				if(m_pCardMap->CenterRect[i].top==CCardMap::CENTER_Y0-CCardMap::UP_CARD)
				{
					if(m_pDrawItem!=NULL)
					{
						m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::OK_X,CCardMap::OK_Y,
							CDrawItem::GAMEOK);
					}
					break;
				}
			}
		}
		
		if(!m_bStarPlay)
		{
			if(m_pDrawCard!=NULL)
			{
				m_pDrawCard->DrawCard(m_hBackDC,CCardMap::X,CCardMap::Y);
				if(m_nToDealNumber>=1)
				{
					m_pDrawCard->DrawCard(m_hBackDC,CCardMap::LEFT_X0,CCardMap::LEFT_Y0);
					m_pDrawCard->DrawCard(m_hBackDC,CCardMap::CENTER_X0,CCardMap::CENTER_Y0);
					m_pDrawCard->DrawCard(m_hBackDC,CCardMap::RIGHT_X0,CCardMap::RIGHT_Y0);
				}
			}
			if(this->m_nToDealNumber==17)
			{
				m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::CHOOSE_X,CCardMap::CHOOSE_Y,CDrawItem::CHOOSE);
				/***/
				m_pDrawCard->DrawLordCard(m_hBackDC,1,m_pPlayCard->m_cCard[51].m_nColor,
					m_pPlayCard->m_cCard[51].m_nNumber,FALSE);
				m_pDrawCard->DrawLordCard(m_hBackDC,2,m_pPlayCard->m_cCard[52].m_nColor,
					m_pPlayCard->m_cCard[52].m_nNumber,FALSE);
				m_pDrawCard->DrawLordCard(m_hBackDC,3,m_pPlayCard->m_cCard[53].m_nColor,
					m_pPlayCard->m_cCard[53].m_nNumber,FALSE);
				/***/
				for(int i=0;i<m_pCenter->m_nCardCount;i++)
				{
					m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->CenterRect[i].left,m_pCardMap->CenterRect[i].top,
						m_pCenter->m_cCard[i].m_nColor,m_pCenter->m_cCard[i].m_nNumber);
				}
				for(int i=0;i<m_pLeft->m_nCardCount;i++)
				{
					m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->LeftRect[i].left,m_pCardMap->LeftRect[i].top);
				}
				for(int i=0;i<m_pRight->m_nCardCount;i++)
				{	
					m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->RightRect[i].left,m_pCardMap->RightRect[i].top);
				}
				/***/
				m_bStar=TRUE;
				if(m_nLord!=CENTER)
				{
					m_bStarPlay=TRUE;
					m_bChooseLord=TRUE;
					ToDealLordCard(m_nLord);
				}
				/***/
			}else 
			{
				MoveCard();
				if(m_nMoveNumber==5)
				{
					m_nToDealNumber++;
				}
			}
		}else 
		{
			if(m_bChooseLord)
			{
				switch(m_nLord)
				{
				case LEFT:
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::LEFT_NAME_X,CCardMap::LEFT_NAME_Y,CDrawItem::LORD_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::CENTER_NAME_X,CCardMap::CENTER_NAME_Y,CDrawItem::FARMER_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::RIGHT_NAME_X,CCardMap::RIGHT_NAME_Y,CDrawItem::FARMER_FACE);
					break;
				case CENTER:
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::LEFT_NAME_X,CCardMap::LEFT_NAME_Y,CDrawItem::FARMER_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::CENTER_NAME_X,CCardMap::CENTER_NAME_Y,CDrawItem::LORD_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::RIGHT_NAME_X,CCardMap::RIGHT_NAME_Y,CDrawItem::FARMER_FACE);			
					break;
				case RIGHT:
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::LEFT_NAME_X,CCardMap::LEFT_NAME_Y,CDrawItem::FARMER_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::CENTER_NAME_X,CCardMap::CENTER_NAME_Y,CDrawItem::FARMER_FACE);
					m_pDrawItem->DrawGameItem(m_hBackDC,CCardMap::RIGHT_NAME_X,CCardMap::RIGHT_NAME_Y,CDrawItem::LORD_FACE);
					break;
				}
			}
			//绘制过牌的文字
			/**********************************************************/
			if(m_pLeft->m_bPass)
			{
				m_pDrawItem->DrawGameItem(m_hBackDC,200,100,CDrawItem::PASS);
				//m_pDrawItem->DrawMapText("PASS",200,100,RGB(255,0,0),30,m_hBackDC);
			}
			if(m_pRight->m_bPass)
			{
				m_pDrawItem->DrawGameItem(m_hBackDC,550,100,CDrawItem::PASS);
				//m_pDrawItem->DrawMapText("PASS",550,100,RGB(255,0,0),30,m_hBackDC);
			}
			if(m_pCenter->m_bPass)
			{
				m_pDrawItem->DrawGameItem(m_hBackDC,370,240,CDrawItem::PASS);
				//m_pDrawItem->DrawMapText("PASS",300,300,RGB(255,0,0),30,m_hBackDC);
			}
			/**********************画地主牌******************************/
			PainLordCard();
			/***************************************************************/
			for(int i=0;i<m_pCenter->m_nDisCardCount;i++)
			{
				m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->CenterDisCardRect[i].left,
					m_pCardMap->CenterDisCardRect[i].top,m_pCenter->m_cDisCard[i].m_nColor,
					m_pCenter->m_cDisCard[i].m_nNumber);
			}
			for(int i=0;i<m_pLeft->m_nDisCardCount;i++)
			{
				m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->LeftDisCardRect[i].left,
					m_pCardMap->LeftDisCardRect[i].top,m_pLeft->m_cDisCard[i].m_nColor,
					m_pLeft->m_cDisCard[i].m_nNumber);
			}
			for(int i=0;i<m_pRight->m_nDisCardCount;i++)
			{
				m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->RightDisCardRect[i].left,
					m_pCardMap->RightDisCardRect[i].top,m_pRight->m_cDisCard[i].m_nColor,
					m_pRight->m_cDisCard[i].m_nNumber);
			}
			/**************************************************************/
			for(int i=0;i<m_pCenter->m_nCardCount;i++)
			{
				m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->CenterRect[i].left,m_pCardMap->CenterRect[i].top,
					m_pCenter->m_cCard[i].m_nColor,m_pCenter->m_cCard[i].m_nNumber);
			}
			for(int i=0;i<m_pLeft->m_nCardCount;i++)
				{
					m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->LeftRect[i].left,m_pCardMap->LeftRect[i].top);
				}
				for(int i=0;i<m_pRight->m_nCardCount;i++)
				{	
					m_pDrawCard->DrawCard(m_hBackDC,m_pCardMap->RightRect[i].left,m_pCardMap->RightRect[i].top);
				}
		}
		::BitBlt(m_hDestDC,0,0,800,600,m_hBackDC,0,0,SRCCOPY);
		Sleep(25);
}
	
	return 1;
}
//游戏逻辑更新
int CGame::GameUpdate()
{
	return 1;
}
int CGame::MouseLButtonDown(POINT point)
{
	if(point.x>m_rExit.left && point.x<m_rExit.right &&
		point.y>m_rExit.top && point.y<m_rExit.bottom)
	{
		m_bLive=FALSE;
		::PostMessage(m_hWnd,WM_CLOSE,NULL,NULL);
	}
	if(!m_bStarPlay && m_bStar)
	{
		if(point.x>m_rYes.left && point.x<m_rYes.right &&
			point.y>m_rYes.top && point.y<m_rYes.bottom)
		{
			ToDealLordCard(m_nLord);
			m_bStarPlay=TRUE;
			m_bChooseLord=TRUE;
		}else if(point.x>m_rNo.left && point.y<m_rNo.right &&
			point.y>m_rNo.top && point.y<m_rNo.bottom)
		{
			m_nLord=RIGHT;
			ToDealLordCard(m_nLord);
			m_bStarPlay=TRUE;
			m_bChooseLord=TRUE;
		}
	}
	if(m_bStarPlay)
	{
		SendCard(point);
		UpCard(point);
	}
	return 1;
}
int CGame::MouseRButtonDown(POINT point)
{
	for(int i=0;i<m_pCenter->m_nCardCount;i++)
	{
		if(i<m_pCenter->m_nCardCount-1)
		{
		if(point.x>m_pCardMap->CenterRect[i].left &&
			point.x<m_pCardMap->CenterRect[i].left+CDrawCard::g_CARDWIDTH/4 &&
			point.y>m_pCardMap->CenterRect[i].top &&
			point.y<m_pCardMap->CenterRect[i].bottom &&
			m_pCardMap->CenterRect[i].top<CCardMap::CENTER_Y0)
		{
			m_pCardMap->CenterRect[i].top+=CCardMap::UP_CARD;
		}
		}else
		{
		if(point.x>m_pCardMap->CenterRect[i].left &&
			point.x<m_pCardMap->CenterRect[i].right &&
			point.y>m_pCardMap->CenterRect[i].top &&
			point.y<m_pCardMap->CenterRect[i].bottom &&
			m_pCardMap->CenterRect[i].top<CCardMap::CENTER_Y0)
		{
			m_pCardMap->CenterRect[i].top+=CCardMap::UP_CARD;
		}
		}
	}
	return 1;
}
//游戏运行主体
int CGame::GameLoop()
{
	return 1;
}

//新游戏
BOOL CGame::NewGame()
{
	
	if(m_pLeft->m_nCardCount==0 || m_pCenter->m_nCardCount==0 ||
		m_pRight->m_nCardCount==0)
	{
		if(m_pLeft->m_nCardCount==0)
		{
			if(m_pLeft->m_nPeople==CRole::LORD)
			{
				m_pLeft->m_nSource+=2;
				m_pCenter->m_nSource--;
				m_pRight->m_nSource--;
				m_pLeft->m_nWin++;
				m_pCenter->m_nFail++;
				m_pRight->m_nFail++;
			}else
			{
				if(m_pCenter->m_nPeople==CRole::LORD)
				{
					m_pLeft->m_nSource++;
					m_pCenter->m_nSource-=2;
					m_pRight->m_nSource++;
					m_pLeft->m_nWin++;
					m_pCenter->m_nFail++;
					m_pRight->m_nWin++;
				}else if(m_pRight->m_nPeople==CRole::LORD)
				{
					m_pLeft->m_nSource++;
					m_pCenter->m_nSource++;
					m_pRight->m_nSource-=2;
					m_pLeft->m_nWin++;
					m_pCenter->m_nWin++;
					m_pRight->m_nFail++;
				}
			}
		}else if(m_pCenter->m_nCardCount==0)
		{
			if(m_pCenter->m_nPeople==CRole::LORD)
			{
				m_pLeft->m_nSource--;
				m_pCenter->m_nSource+=2;
				m_pRight->m_nSource--;
				m_pLeft->m_nFail++;
				m_pCenter->m_nWin++;
				m_pRight->m_nFail++;
			}else 
			{
				if(m_pLeft->m_nPeople==CRole::LORD)
				{
					m_pLeft->m_nSource-=2;
					m_pCenter->m_nSource++;
					m_pRight->m_nSource++;
					m_pLeft->m_nFail++;
					m_pCenter->m_nWin++;
					m_pRight->m_nWin++;
				}else if(m_pRight->m_nPeople==CRole::LORD)
				{
					m_pLeft->m_nSource++;
					m_pCenter->m_nSource++;
					m_pRight->m_nSource-=2;
					m_pLeft->m_nWin++;
					m_pCenter->m_nWin++;
					m_pRight->m_nFail++;
				}
			}
		}else if(m_pRight->m_nCardCount==0)
		{
			if(m_pRight->m_nPeople==CRole::LORD)
			{
				m_pLeft->m_nSource--;
				m_pCenter->m_nSource--;
				m_pRight->m_nSource+=2;
				m_pLeft->m_nFail++;
				m_pCenter->m_nFail++;
				m_pRight->m_nWin++;
			}else
			{
				if(m_pLeft->m_nPeople==CRole::LORD)
				{	
					m_pLeft->m_nSource-=2;
					m_pCenter->m_nSource++;
					m_pRight->m_nSource++;
					m_pLeft->m_nFail--;
					m_pCenter->m_nWin++;
					m_pRight->m_nWin++;
				}else if(m_pCenter->m_nPeople==CRole::LORD)
				{
					m_pLeft->m_nSource++;
					m_pCenter->m_nSource-=2;
					m_pRight->m_nSource++;
					m_pLeft->m_nWin++;
					m_pCenter->m_nFail++;
					m_pRight->m_nWin++;
				}
			}

		}
		m_pCenter->m_nDisCardCount=0;
		m_pLeft->m_nDisCardCount=0;
		m_pRight->m_nDisCardCount=0;
		
		m_pCenter->m_nCardCount=0 ;
		m_pLeft->m_nCardCount=0;
		m_pRight->m_nCardCount=0;
		
		m_pLeft->m_bPass=FALSE;
		m_pCenter->m_bPass=FALSE;
		m_pRight->m_bPass=FALSE;

		m_pPlayCard->Shuffle();
		m_pPlayCard->ToDeal(m_pCenter,m_pRight,m_pLeft);
		m_pCenter->CleanUp();
		m_pLeft->CleanUp();
		m_pRight->CleanUp();
		/***/
		this->m_bStarPlay=FALSE;
		this->m_bStar=FALSE;
		this->m_bChooseLord=FALSE;
		InitNumberCount();
		/***/
		produceLord();
		
		return TRUE;
		
	}
	return FALSE;

}
//新的一轮
BOOL CGame::NewRound()
{
	//左右
	if(m_pLeft->m_bPass==TRUE && m_pRight->m_bPass==TRUE)
	{
		m_pLeft->m_bPass=FALSE;
		m_pCenter->m_bPass=FALSE;
		m_pRight->m_bPass=FALSE;
		
		m_nStar=CENTER;
		return TRUE;

	}//中右
	else if(m_pCenter->m_bPass==TRUE && m_pRight->m_bPass==TRUE)
	{
		m_pLeft->m_bPass=FALSE;
		m_pCenter->m_bPass=FALSE;
		m_pRight->m_bPass=FALSE;

		m_nStar=LEFT;
		m_pLeft->DirectnessPlay(m_tRoleCardType);
		return TRUE;
	}//中左
	else if(m_pCenter->m_bPass==TRUE && m_pLeft->m_bPass==TRUE)
	{
		m_pLeft->m_bPass=FALSE;
		m_pCenter->m_bPass=FALSE;
		m_pRight->m_bPass=FALSE;

		m_nStar=RIGHT;
		m_pRight->DirectnessPlay(m_tRoleCardType);
		m_pLeft->SendCard(m_tRoleCardType,m_pRight,m_pCenter);
		return TRUE;
	}
	return FALSE;
	
}
//产生地主
BOOL CGame::produceLord()
{
	srand(time(NULL));
	int i=rand()%3;
	m_nLord=i;
	m_nCurrentPlay=m_nStar;
	return TRUE;
}
BOOL CGame::ToDealLordCard(int who)
{
	m_nStar=who;
	switch(who)
	{
		//左边玩家当地主
	case LEFT:
		m_pLeft->m_nPeople=CRole::LORD;
		m_pCenter->m_nPeople=CRole::ALLY;
		m_pRight->m_nPeople=CRole::ALLY;
		m_pPlayCard->ToDealLord(m_pLeft);
		break;
		//中间玩家当地主
	case CENTER:
		m_pLeft->m_nPeople=CRole::ALLY;
		m_pCenter->m_nPeople=CRole::LORD;
		m_pRight->m_nPeople=CRole::ALLY;
		m_pPlayCard->ToDealLord(m_pCenter);
		break;
		//右边玩家当地主
	case RIGHT:
		m_pLeft->m_nPeople=CRole::ALLY;
		m_pCenter->m_nPeople=CRole::ALLY;
		m_pRight->m_nPeople=CRole::LORD;
		m_pPlayCard->ToDealLord(m_pRight);
		break;
	}
	m_pCenter->CleanUp();
	m_pLeft->CleanUp();
	m_pRight->CleanUp();
	m_pCenter->ScanToCardTable();
	m_pLeft->ScanToCardTable();
	m_pRight->ScanToCardTable();
	//看谁先开始出牌
	switch(who)
	{
	case LEFT:
		m_pLeft->DirectnessPlay(m_tRoleCardType);
		m_nCurrentPlay=CENTER;
		break;
	case CENTER:
		break;
	case RIGHT:
		m_pRight->DirectnessPlay(m_tRoleCardType);
		m_pLeft->SendCard(m_tRoleCardType,m_pRight,m_pCenter);
		m_nCurrentPlay=CENTER;
		break;
	}
	return TRUE;
}
void CGame::PainLordCard()
{
	m_pDrawCard->DrawLordCard(m_hBackDC,1,m_pPlayCard->m_cCard[51].m_nColor,
			m_pPlayCard->m_cCard[51].m_nNumber,TRUE);
	m_pDrawCard->DrawLordCard(m_hBackDC,2,m_pPlayCard->m_cCard[52].m_nColor,
			m_pPlayCard->m_cCard[52].m_nNumber,TRUE);
	m_pDrawCard->DrawLordCard(m_hBackDC,3,m_pPlayCard->m_cCard[53].m_nColor,
			m_pPlayCard->m_cCard[53].m_nNumber,TRUE);
}
//绘制分数表
void CGame::PainPoint()
{
    char data_Source[20];
	char data_Win[20];
	char data_Fail[20];
	sprintf(data_Source,"%d",m_pLeft->m_nSource);
	sprintf(data_Win,"%d",m_pLeft->m_nWin);
	sprintf(data_Fail,"%d",m_pLeft->m_nFail);
	/***/
	m_pDrawItem->DrawMapText("电脑",CCardMap::LEFT_POINT_NAME_X,CCardMap::LEFT_POINT_NAME_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Source,CCardMap::LEFT_POINT_SOURCE_X,CCardMap::LEFT_POINT_SOURCE_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Win,CCardMap::LEFT_POINT_WIN_X,CCardMap::LEFT_POINT_WIN_Y,RGB(255,0,0),13,m_hBackDC);
	
	/***/
	sprintf(data_Source,"%d",m_pCenter->m_nSource);
	sprintf(data_Win,"%d",m_pCenter->m_nWin);
	sprintf(data_Fail,"%d",m_pCenter->m_nFail);
	/***/
	m_pDrawItem->DrawMapText("玩家",CCardMap::PLAY_POINT_NAME_X,CCardMap::PLAY_POINT_NAME_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Source,CCardMap::PLAY_POINT_SOURCE_X,CCardMap::PLAY_POINT_SOURCE_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Win,CCardMap::PLAY_POINT_WIN_X,CCardMap::PLAY_POINT_WIN_Y,RGB(255,0,0),13,m_hBackDC);
	
	/***/
	sprintf(data_Source,"%d",m_pRight->m_nSource);
	sprintf(data_Win,"%d",m_pRight->m_nWin);
	sprintf(data_Fail,"%d",m_pRight->m_nFail);
	/***/
	m_pDrawItem->DrawMapText("电脑",CCardMap::RIGHT_POINT_NAME_X,CCardMap::RIGHT_POINT_NAME_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Source,CCardMap::RIGHT_POINT_SOURCE_X,CCardMap::RIGHT_POINT_SOURCE_Y,RGB(255,0,0),13,m_hBackDC);
	m_pDrawItem->DrawMapText(data_Win,CCardMap::RIGHT_POINT_WIN_X,CCardMap::RIGHT_POINT_WIN_Y,RGB(255,0,0),13,m_hBackDC);
	
}
void CGame::UpCard(POINT point)
{
	for(int i=0;i<m_pCenter->m_nCardCount;i++)
	{
		if(i<m_pCenter->m_nCardCount-1)
		{
			if(point.x>this->m_pCardMap->CenterRect[i].left &&
			point.x<m_pCardMap->CenterRect[i].left+CDrawCard::g_CARDWIDTH/4 &&
			point.y>m_pCardMap->CenterRect[i].top &&
			point.y<m_pCardMap->CenterRect[i].bottom &&
			m_pCardMap->CenterRect[i].top>=CCardMap::CENTER_Y0)
			{
				m_pCardMap->CenterRect[i].top-=CCardMap::UP_CARD;
			}else if(point.x>m_pCardMap->CenterRect[i].left &&
			point.x<m_pCardMap->CenterRect[i].left+CDrawCard::g_CARDWIDTH/4 &&
			point.y>m_pCardMap->CenterRect[i].top &&
			point.y<m_pCardMap->CenterRect[i].bottom &&
			m_pCardMap->CenterRect[i].top<CCardMap::CENTER_Y0)
			{
				m_pCardMap->CenterRect[i].top+=CCardMap::UP_CARD;
			}
		}else
		{
			if(point.x>m_pCardMap->CenterRect[i].left &&
				point.x<m_pCardMap->CenterRect[i].right &&
				point.y>m_pCardMap->CenterRect[i].top &&
				point.y<m_pCardMap->CenterRect[i].bottom &&
				m_pCardMap->CenterRect[i].top>=CCardMap::CENTER_Y0)
			{
				m_pCardMap->CenterRect[i].top-=CCardMap::UP_CARD;
			}else if(point.x>m_pCardMap->CenterRect[i].left &&
			point.x<m_pCardMap->CenterRect[i].right &&
			point.y>m_pCardMap->CenterRect[i].top &&
			point.y<m_pCardMap->CenterRect[i].bottom &&
			m_pCardMap->CenterRect[i].top<CCardMap::CENTER_Y0)
			{
				m_pCardMap->CenterRect[i].top+=CCardMap::UP_CARD;
			}

		}
		
	}

}
void CGame::SendCard(POINT point)
{
	if(point.x>m_rSend.left && point.x<m_rSend.right &&
		point.y>m_rSend.top && point.y<m_rSend.bottom)
	{
		if(m_nStar==CENTER)
		{
			if(m_pCenter->DirectnessPlay(m_tRoleCardType))
			{
				if(!NewGame())
				{
					m_pRight->SendCard(m_tRoleCardType,m_pLeft,m_pCenter);
				}
				if(!NewGame())
				{
					if(!NewRound())
					{
						m_pLeft->SendCard(m_tRoleCardType,m_pRight,m_pCenter);
						m_nStar=-1;
					}
				}
				
				if(!NewGame())
				{
					if(!NewRound())
					{
						m_nStar=-1;
					}
				}
			}
		}else
		{
			if(!NewGame())
			{
				if(!NewRound())
				{
					if(m_pCenter->SendCard(m_tRoleCardType))
					{
						if(!NewGame())
						{
							if(!NewRound())
							{
								m_pRight->SendCard(m_tRoleCardType,m_pLeft,m_pCenter);
							}
						}
						if(!NewGame())
						{
							if(!NewRound())
							{
								m_pLeft->SendCard(m_tRoleCardType,m_pRight,m_pCenter);
								//NewRound();
							}
						}
					}
				}
			}
		}
		m_pCardMap->InitRect();
	}
}



void CGame::InitNumberCount()
{
	this->m_nCRemoveX=CCardMap::X;
	this->m_nCRemoveY=CCardMap::Y;
	this->m_nLRemoveX=CCardMap::X;
	this->m_nLRemoveY=CCardMap::Y;
	this->m_nRRemoveX=CCardMap::X;
	this->m_nRRemoveY=CCardMap::Y;
	this->m_nMoveNumber=0;
	this->m_nToDealNumber=0;
}
BOOL CGame::MoveCard()
{
	if(m_nCRemoveX>CCardMap::CENTER_X0)
	{
		m_nCRemoveX-=16;
	}else
	{
		this->m_nCRemoveX=CCardMap::X;
	}
	if(m_nCRemoveY<CCardMap::CENTER_Y0)
	{
		m_nCRemoveY+=56;
	}else
	{
		this->m_nCRemoveY=CCardMap::Y;
	}
	/***/
	if(m_nLRemoveX>CCardMap::LEFT_X0)
	{
		m_nLRemoveX-=68;
	}else
	{
		this->m_nLRemoveX=CCardMap::X;
	}
	if(m_nLRemoveY>CCardMap::LEFT_Y0)
	{
		m_nLRemoveY-=32;
	}else
	{
		this->m_nLRemoveY=CCardMap::Y;
	}
	/***/
	if(m_nRRemoveX<CCardMap::RIGHT_X0)
	{
		m_nRRemoveX+=70;
	}else
	{
		this->m_nRRemoveX=CCardMap::X;
	}
	if(m_nRRemoveY>CCardMap::RIGHT_Y0)
	{
		m_nRRemoveY-=32;
	}else
	{
		this->m_nRRemoveY=CCardMap::Y;
	}
	/***/
	m_pDrawCard->DrawCard(m_hBackDC,m_nCRemoveX,m_nCRemoveY);
	m_pDrawCard->DrawCard(m_hBackDC,m_nLRemoveX,m_nLRemoveY);
	m_pDrawCard->DrawCard(m_hBackDC,m_nRRemoveX,m_nRRemoveY);
	if(m_nMoveNumber<5)
	{
		m_nMoveNumber++;
	}else
	{
		m_nMoveNumber=0;
	}
	return TRUE;
}