#pragma once
#include "Card.h"
#include "CardMap.h"

//角色类
class CRole
{
public:
	//牌的类型结构
	struct CardType
	{
		int m_nType;
		int m_nValue;
		int m_nLong;
	};
public:
	static const int ALLY=0;//盟友
	static const int LORD=1;//地主
public:
	int m_nSource;
	int m_nWin;
	int m_nFail;
	
	
	int m_nPeople;//玩家的类型是敌人还是盟友 

	CCardMap* m_pCardMap;
    CardType m_MyType;

	BOOL m_bPass;//是否过牌
	

	//int m_nPeopleType;//任务人物类型
	int m_nCardType;//出牌的类型
	
	int m_nCardTable[15];//记录还未出牌的表
	int m_nCardCount;//还未出牌的牌数量
	CCard m_cCard[20];//未出的牌

	int m_nDisCardTable[15];//记录出牌的表
	int m_nDisCardCount;//记录出牌的数量
	CCard m_cDisCard[20];//记录所出的牌
public:
	virtual BOOL DirectnessPlay(CardType &type);//直接出牌
	virtual BOOL SendCard(CardType &type);//出牌
	virtual void UnDisplayCard();//消失牌
	void CleanUp();//整理牌
	void DeleteDisCard();//删除已出的牌
	void ScanToCardTable();//将牌整理到未出牌的表中 
	void ScanToDisCardTable();//将牌整理到出牌的表中
	
public:
	CRole(CCardMap* cardMap);
	virtual ~CRole(void);
};
