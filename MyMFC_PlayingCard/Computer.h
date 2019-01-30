#pragma once
#include "role.h"

class CComputer :public CRole
{
private:
	CRole* m_pRole[2];
public:
	BOOL DirectnessPlay(CardType &type);
	virtual BOOL SendCard(CardType &type,CRole* role_1,CRole* role_2);
	
	BOOL SearchSingle(int number);//搜索单根的牌来打
	BOOL AI_SearchSingle(int number);//主动搜索单根的牌来打
	
	BOOL SearchPair(int number);//搜索对来打
	BOOL AI_SearchPair(int number);//主动搜索对来打
	
	BOOL SearchThree(int number);//搜索三张的来打
	BOOL AI_SearchThree(int number);//主动搜索单根的牌来打

	BOOL SearchThreeWOne(int number);//搜索三带一的牌来打
	BOOL AI_SearchThreeWOne(int number);//主动搜索三带一的牌来打
	
	BOOL SearchThreeWTwo(int number);//搜索三带对的牌来打
	BOOL AI_SearchThreeWTwo(int number);//主动搜索三代对的牌来打
	
	BOOL SearchBomb(int number);//搜索炸弹来打
	BOOL AI_SearchBomb(int number);//主动搜索炸弹的牌来打

	BOOL SearchFourWSingle(int number);//搜索炸弹带单根的牌来打
	BOOL AI_SearchFourWSingle(int number);//主动搜索炸弹带单根的牌来打

	BOOL SearchFourWPair(int number);//搜索炸弹带对的牌来打
	BOOL AI_SearchFourWPair(int number);//主动搜索炸弹带对的牌来打
	
	BOOL SearchSeries(int number,int Long);//搜索顺子来打
	BOOL AI_SearchSeries(int number,int Long);//主动搜索顺子来打

	BOOL SearchPairSeries(int number,int Long);//搜索顺对来打
	BOOL AI_SearchPairSeries(int number,int Long);//主动搜索顺对来打

	BOOL SearchThreeWOneSeries(int number,int Long);//搜索三带一的顺子来打
	BOOL AI_SearchThreeWOneSeries(int number,int Long);//主动搜索三带一的顺子来打 
private:
	BOOL DirectnessAI();//电脑直接出牌的AI
	BOOL SendCardAI(CRole* role_1,CRole* role_2);//电脑跟牌的AI

public:
	CComputer(CCardMap* cardMap);
	virtual ~CComputer(void);

};
