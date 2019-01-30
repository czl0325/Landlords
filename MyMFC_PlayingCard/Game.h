#pragma once
#include "DrawCard.h"
#include "CardMap.h"
#include "PlayCard.h"
#include "Player.h"
#include "Computer.h"
#include "DrawItem.h"
class CGame
{
public:
	static const int GAME_RUN=50;//游戏心跳时间
public:
	static const int LEFT=0;//左边
	static const int CENTER=1;//中间
	static const int RIGHT=2;//右边
private:
    int m_nCRemoveX;//中间玩家
	int m_nCRemoveY;
	int m_nLRemoveX;//左边玩家
	int m_nLRemoveY;
	int m_nRRemoveX;//右边玩家
	int m_nRRemoveY;
	int m_nMoveNumber;//移动次数的时间计数器
	int m_nToDealNumber;//分牌次数的时间计数器

	HWND m_hWnd;
	RECT m_rExit; 
	RECT m_rSend;
	RECT m_rYes;
	RECT m_rNo;
	int m_nLord;//地主
	int m_nStar;//开始出牌的人
	int m_nCurrentPlay;//当前出牌的人
	BOOL m_bChooseLord;//是否在选择地主状态
	HDC m_hDestDC;//目标DC
	HDC m_hBackDC;//背后缓冲DC
	
	BOOL m_bLive;//游戏是否运行
	BOOL m_bStar;//游戏是否开始
	BOOL m_bStarPlay;//游戏是否开始玩
	
	CRole::CardType m_tRoleCardType;//
	CDrawCard* m_pDrawCard;
    CDrawItem* m_pDrawItem;
	CCardMap*  m_pCardMap;
    CPlayCard* m_pPlayCard;
	CPlayer* m_pCenter;//中间的玩家
	CComputer* m_pLeft;//左边的玩家
	CComputer* m_pRight;//右边的玩家
	
public:
	BOOL MoveCard();//卡的移动

	BOOL NewGame();//新的游戏
	BOOL NewRound();//新的一轮
	BOOL produceLord();//产生地主
	BOOL ToDealLordCard(int who);//分地主牌
	int GameLoop();//游戏运行主函数
	int GamePaint();//游戏绘制
	int GameUpdate();//游戏逻辑更新
	int MouseLButtonDown(POINT point);//鼠标左键事件
	int MouseRButtonDown(POINT point);//鼠标右键事件

	void InitNumberCount();//初始化时间计数器
	void PainLordCard();//绘制地主牌
	void PainPoint();//绘制分数表
	void UpCard(POINT point);//将牌提起来的方法
	void SendCard(POINT point);//出牌
	
public:
	CGame(HDC hdc,HWND hwnd);
	~CGame(void);
};
