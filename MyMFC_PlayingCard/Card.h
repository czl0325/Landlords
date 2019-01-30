#pragma once
//牌类
class CCard
{
public:
    static const int SPADE=0;//黑桃
	static const int HEART=1;//红心
	static const int CLUB=2;//梅花
	static const int DIAMOND=3;//方块 
	static const int SMALLBOSS=0;//小王
	static const int BIGBOSS=1;//大王
public:
	int m_nColor;
	int m_nNumber;
public:
	CCard(void);
	~CCard(void);
};
