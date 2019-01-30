#include "StdAfx.h"
#include "CardMap.h"
#include "DrawCard.h"
CCardMap::CCardMap(void)
{
	this->m_nMoveX=this->X;
	this->m_nMoveY=this->Y;
}

CCardMap::~CCardMap(void)
{
}
void CCardMap::InitRect()
{
	//中间玩家的放牌位置
	for(int i=0;i<20;i++)
	{
		RECT temp={CENTER_X0+(CDrawCard::g_CARDWIDTH/4*i),CENTER_Y0,
			(CENTER_X0+CDrawCard::g_CARDWIDTH/4*i)+CDrawCard::g_CARDWIDTH,
			CENTER_Y0+CDrawCard::g_CARDHEIGHT};
		CenterRect[i]=temp;
	}
	//中间玩家的出牌位置
	for(int i=0;i<20;i++)
	{
		RECT temp={CENTER_X1+(CDrawCard::g_CARDWIDTH/4*i),CENTER_Y1,
			(CENTER_X1+CDrawCard::g_CARDWIDTH/4*i)+CDrawCard::g_CARDWIDTH,
			CENTER_Y1+CDrawCard::g_CARDHEIGHT};
		CenterDisCardRect[i]=temp;
	}
	
	
	
	//左边玩家的放牌位置
	for(int i=0;i<20;i++)
	{
		RECT temp={LEFT_X0,LEFT_Y0+(CDrawCard::g_CARDHEIGHT/5*i),
			LEFT_X0+CDrawCard::g_CARDWIDTH,
			LEFT_Y0+(CDrawCard::g_CARDHEIGHT/5*i)+CDrawCard::g_CARDHEIGHT
		};
		LeftRect[i]=temp;
	}
	//左边玩家的出牌位置
	for(int i=0;i<20;i++)
	{
		RECT temp={LEFT_X1,LEFT_Y1+(CDrawCard::g_CARDHEIGHT/5*i),
			LEFT_X1+CDrawCard::g_CARDWIDTH,
			LEFT_Y1+(CDrawCard::g_CARDHEIGHT/5*i)+CDrawCard::g_CARDHEIGHT};
		LeftDisCardRect[i]=temp;
	}
	
	
	//右边玩家的放牌
	for(int i=0;i<20;i++)
	{
		RECT temp={RIGHT_X0,RIGHT_Y0+(CDrawCard::g_CARDHEIGHT/5*i),
			RIGHT_X0+CDrawCard::g_CARDWIDTH,
			RIGHT_Y0+(CDrawCard::g_CARDHEIGHT/5*i)+CDrawCard::g_CARDHEIGHT};
		RightRect[i]=temp;
	}
	//右边玩家出牌的区域
	for(int i=0;i<20;i++)
	{
		RECT temp={RIGHT_X1,RIGHT_Y1+(CDrawCard::g_CARDHEIGHT/5*i),
			RIGHT_X1+CDrawCard::g_CARDWIDTH,
			RIGHT_Y1+(CDrawCard::g_CARDHEIGHT/5*i)+CDrawCard::g_CARDHEIGHT};
		RightDisCardRect[i]=temp;
	}
}