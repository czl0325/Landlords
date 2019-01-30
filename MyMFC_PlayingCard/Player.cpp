#include "StdAfx.h"
#include "Player.h"
#include "CardRule.h"
CPlayer::CPlayer(CCardMap* cardMap):CRole(cardMap)
{
}

CPlayer::~CPlayer(void)
{

}
BOOL CPlayer::DirectnessPlay(CardType& type)
{
	DeleteDisCard();
	m_nDisCardCount=0;
	for(int i=0;i<m_nCardCount;i++)
	{
		if(m_pCardMap->CenterRect[i].top==CCardMap::CENTER_Y0-CCardMap::UP_CARD)
		{
			m_cDisCard[m_nDisCardCount]=m_cCard[i];
			m_nDisCardCount++;
		}
	}
	ScanToDisCardTable();
	if(CheckRule())
	{
		type=m_MyType;
		UnDisplayCard();
		ScanToCardTable();
		return TRUE;
	}
	return FALSE;
}
BOOL CPlayer::SendCard(CardType &type)
{
	DeleteDisCard();
	m_nDisCardCount=0;
	for(int i=0;i<m_nCardCount;i++)
	{
		if(m_pCardMap->CenterRect[i].top==CCardMap::CENTER_Y0-CCardMap::UP_CARD)
		{
			m_cDisCard[m_nDisCardCount]=m_cCard[i];
			m_nDisCardCount++;
		}
	}
	ScanToDisCardTable();
	if(m_nDisCardCount==0)
	{
		if(!m_bPass)
		{
			m_bPass=TRUE;
		}
		return TRUE;
	}else if(CheckRule())
	{
		if(m_MyType.m_nType==CCardRule::BOMB &&
			type.m_nType!=CCardRule::BOMB)
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
			ScanToCardTable();
			return TRUE;
		}else if(m_MyType.m_nType ==type.m_nType)
		{
			if(m_MyType.m_nLong==type.m_nLong)
			{
				if(m_MyType.m_nValue>type.m_nValue)
				{	
					if(m_bPass)
					{
						m_bPass=FALSE;
					}
					type=m_MyType;
					UnDisplayCard();
					ScanToCardTable();
					return TRUE;
				}
			}
		}
	}
	m_nDisCardCount=0;
	return FALSE;
}

void CPlayer::GoBack()
{
	m_pCardMap->InitRect();
}

//判断是否符合出牌规则
BOOL CPlayer::CheckRule()
{
	//判断是否是出单根
	if(CCardRule::IsOneCard(this)==CCardRule::SINGLE)
	{
		
		m_MyType.m_nType=CCardRule::SINGLE;
		m_MyType.m_nLong=1;
		m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
		return TRUE;
	}//判断是否是出一对
	else if(CCardRule::IsTwoCard(this)==CCardRule::PAIR)
	{
		m_MyType.m_nType=CCardRule::PAIR;
		m_MyType.m_nLong=2;
		m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
		return TRUE;
	}//判断是否是出三张一样的
	else if(CCardRule::IsThreeCard(this)==CCardRule::THREE)
	{
		
		m_MyType.m_nType=CCardRule::THREE;
		m_MyType.m_nLong=3;
		for(int i=0;i<14;i++)
		{
			if(m_nDisCardTable[i]==3)
			{
				m_MyType.m_nValue=i+3;
			}
		}
	}//判断是否是出三带一
	else if(CCardRule::IsThreeWOne(this)==CCardRule::THREE_SINGLE)
	{
		
		m_MyType.m_nType=CCardRule::THREE_SINGLE;
		m_MyType.m_nLong=4;
		for(int i=0;i<14;i++)
		{
			if(m_nDisCardTable[i]==3)
			{
				m_MyType.m_nValue=i+3;
			}
		}
		return TRUE;
	}//判断是否是出三带对
	else if(CCardRule::IsThreeWTwo(this)==CCardRule::THREE_PAIR)
	{
		m_MyType.m_nType=CCardRule::THREE_PAIR;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=0;i<14;i++)
		{
			if(m_nDisCardTable[i]==3)
			{
				m_MyType.m_nValue=i+3;
			}
		}
		return TRUE;
	}//判断是否是炸弹
	else if(CCardRule::Isbomb(this)==CCardRule::BOMB)
	{
		m_MyType.m_nType=CCardRule::BOMB;
		m_MyType.m_nLong=m_nDisCardCount;
		m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
		return TRUE;
	}//判断是否是炸弹带单根的情况
	else if(CCardRule::IsFourWSingle(this)==CCardRule::FOUR_SINGLE)
	{
		m_MyType.m_nType=CCardRule::FOUR_SINGLE;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=0;i<14;i++)
		{
			if(m_nDisCardTable[i]==4)
			{
				m_MyType.m_nValue=i+3;
			}
		}
		return TRUE;
	}
	//判断是否是炸弹带两对的情况
	else if(CCardRule::IsFourWPair(this)==CCardRule::FOUR_PAIR)
	{
		m_MyType.m_nType=CCardRule::FOUR_PAIR;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=0;i<14;i++)
		{
			if(m_nDisCardTable[i]==4)
			{
				m_MyType.m_nValue=i+3;
			}
		}
		return TRUE;
	}
	//检查是否是顺子
	else if(CCardRule::IsSeries(this)==CCardRule::SERIES)
	{
		m_MyType.m_nType=CCardRule::SERIES;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==1)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}//检查是否是顺对
	else if(CCardRule::IsPairSeries(this)==CCardRule::PAIR_SERIES)
	{
		m_MyType.m_nType=CCardRule::PAIR_SERIES;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==2)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}//检查是否是三带一的顺对
	else if(CCardRule::IsThreeWOneSeries(this)==CCardRule::THREE_SINGLE_SERIES)
	{
		m_MyType.m_nType=CCardRule::THREE_SINGLE_SERIES;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==3)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}
	//检查是否是三带对的顺对 
	else if(CCardRule::IsThreeWTwoSeries(this)==CCardRule::THREE_PAIR_SERIES)
	{
		m_MyType.m_nType=CCardRule::THREE_PAIR_SERIES;
		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==3)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}//判断是否是炸弹带单根的顺子
	else if(CCardRule::IsFourWSingleSeries(this)==CCardRule::FOUR_SINGLE_SERIES)
	{
		m_MyType.m_nType=CCardRule::FOUR_SINGLE_SERIES;

		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==4)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}//判断是否是炸弹带对的顺子
	else if(CCardRule::IsFourWPairSeries(this)==CCardRule::FOUR_PAIR_SERIES)
	{
		m_MyType.m_nType=CCardRule::FOUR_PAIR_SERIES;

		m_MyType.m_nLong=m_nDisCardCount;
		for(int i=13;i>=0;i--)
		{
			if(m_nDisCardTable[i]==4)
			{
				m_MyType.m_nValue=i+3;
				break;
			}
		}
		return TRUE;
	}
	else
	{
		m_nDisCardCount=0;
		return FALSE;
	}
		m_nDisCardCount=0;
		return FALSE;
}