#pragma once
#include "Role.h"
class CCardRule
{
public:
	//牌的类型
	static const int SINGLE=0;//单根
	static const int PAIR=1;//对
	static const int THREE=2;//三张
	static const int THREE_SINGLE=3;//三带一
	static const int THREE_PAIR=4;//三带对
	static const int FOUR_SINGLE=5;//四带一
	static const int FOUR_PAIR=6;//四带对
	static const int SERIES=7;//顺子
	static const int PAIR_SERIES=8;//顺对
	static const int THREE_SINGLE_SERIES=9;//三带一的顺子
	static const int THREE_PAIR_SERIES=10;//三带对的顺子
	static const int FOUR_SINGLE_SERIES=11;//四带单根的顺子
	static const int FOUR_PAIR_SERIES=12;//四带对的顺子
	static const int BOMB=13;//炸弹

public:
	static int IsOneCard(CRole* player);//判断是否是单张牌
	static int IsTwoCard(CRole* player);//判断是否是一对
	static int IsThreeCard(CRole* player);//判断是否是三张
	static int Isbomb(CRole* player);//判断是否是炸弹
	
	static int IsThreeWOne(CRole* player);//判断是否是三带一
	static int IsThreeWTwo(CRole* player);//判断是否是三带二
	static int IsFourWSingle(CRole* player);//判断是否是炸弹带两根的组合
	static int IsFourWPair(CRole* player);//判断是否是炸弹带两对的组合
	
	static int IsSeries(CRole* player);//判断是否是顺子
	static int IsPairSeries(CRole* player);//判断是否是顺对
	static int IsThreeWOneSeries(CRole* player);//判断是否是三带一的顺子
	static int IsThreeWTwoSeries(CRole* player);//判断是否是三带对的顺子
	static int IsFourWSingleSeries(CRole* player);//判断是否是炸弹带单根的顺子
	static int IsFourWPairSeries(CRole* player);//判断是否是炸弹带对的顺子 
public:
	CCardRule(void);
	~CCardRule(void);
};
