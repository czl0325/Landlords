#pragma once
#include "Card.h"
#include "Role.h"
class CPlayCard
{
public:
	CCard m_cCard[54];//54张牌
public:
	void initCard();
	void Shuffle();//洗牌
	void ToDeal(CRole* play_1,CRole* play_2,CRole* play_3);//分牌
	void ToDealLord(CRole* play);//分地主牌

	void MoveCard();//分牌时牌的移动
public:
	CPlayCard(void);
	~CPlayCard(void);
};
