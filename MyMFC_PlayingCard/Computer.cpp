#include "StdAfx.h"
#include "Computer.h"
#include "CardRule.h"
CComputer::CComputer(CCardMap* cardMap):CRole(cardMap)
{
}

CComputer::~CComputer(void)
{
}
BOOL CComputer::DirectnessPlay(CardType &type)
{
	DeleteDisCard();
	m_nDisCardCount=0;
	if(m_nCardCount>0)
	{
		DirectnessAI();
		type=m_MyType;
		m_bPass=FALSE;
		UnDisplayCard();
		ScanToCardTable();
	}
	return TRUE;
}
BOOL CComputer::SendCard(CardType &type,CRole* role_1,CRole* role_2)
{
	DeleteDisCard();
	m_nDisCardCount=0;
	if(!SendCardAI(role_1,role_2))
	{
		if(!m_bPass)
		{
			m_bPass=TRUE;
		}
		return TRUE;
	}
	switch(type.m_nType)
	{
	case CCardRule::SINGLE:
		if(SearchSingle(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
	case CCardRule::PAIR:
		if(SearchPair(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
	case CCardRule::THREE:
		if(SearchThree(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
	case CCardRule::THREE_SINGLE:
		if(SearchThreeWOne(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
	case CCardRule::THREE_PAIR:
		if(SearchThreeWTwo(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
	case CCardRule::BOMB:
		if(SearchBomb(type.m_nValue))
		{
			if(m_bPass)
			{
				m_bPass=FALSE;
			}
			type=m_MyType;
			UnDisplayCard();
		}else
		{
			m_bPass=TRUE;
		}
		break;
		case CCardRule::FOUR_SINGLE:
			if(SearchFourWSingle(type.m_nValue))
			{
				if(m_bPass)
				{
					m_bPass=FALSE;
				}
				type=m_MyType;
				UnDisplayCard();
			}else
			{
				m_bPass=TRUE;
			}
		break;
		case CCardRule::FOUR_PAIR:
			if(SearchFourWPair(type.m_nValue))
			{
				if(m_bPass)
				{
					m_bPass=FALSE;
				}
				type=m_MyType;
				UnDisplayCard();
			}else
			{
				m_bPass=TRUE;
			}
			break;
		case CCardRule::SERIES:
			if(SearchSeries(type.m_nValue,type.m_nLong))
			{
				if(m_bPass)
				{
					m_bPass=FALSE;
				}
				type=m_MyType;
				UnDisplayCard();
			}else
			{
				m_bPass=TRUE;
			}
			break;
		case CCardRule::PAIR_SERIES:
			if(SearchPairSeries(type.m_nValue,type.m_nLong))
			{
				if(m_bPass)
				{
					m_bPass=FALSE;
				}
				type=m_MyType;
				UnDisplayCard();
			}else
			{
				m_bPass=TRUE;
			}
			break;
		case CCardRule::THREE_SINGLE_SERIES:
			if(SearchThreeWOneSeries(type.m_nValue,type.m_nLong))
			{
				if(m_bPass)
				{
					m_bPass=FALSE;
				}
				type=m_MyType;
				UnDisplayCard();
			}else
			{
				m_bPass=TRUE;
			}
			break;
		case CCardRule::THREE_PAIR_SERIES:
			m_bPass=TRUE;
			break;
		case CCardRule::FOUR_SINGLE_SERIES:
			m_bPass=TRUE;
			break;
		case CCardRule::FOUR_PAIR_SERIES:
			m_bPass=TRUE;
			break;
	}
	ScanToCardTable();
	return TRUE;
}



//搜索单根的牌来打
BOOL CComputer::SearchSingle(int number)
{
	for(int i=0;i<m_nCardCount;i++)
	{
		if(m_cCard[i].m_nNumber>number)
		{
			m_cDisCard[0]=m_cCard[i];
			m_nDisCardCount++;
			m_MyType.m_nType=CCardRule::SINGLE;
			m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
			m_MyType.m_nLong=m_nDisCardCount;
			return TRUE;
		}
	}
	if(m_nDisCardCount==0)
	{
		return FALSE;
	}
	return FALSE;
}
//主动搜索单根的牌来打
BOOL CComputer::AI_SearchSingle(int number)
{	
	for(int i=0;i<m_nCardCount;i++)
	{
		if(m_cCard[i].m_nNumber==number)
		{
			m_cDisCard[0]=m_cCard[i];
			m_nDisCardCount++;
			m_MyType.m_nType=CCardRule::SINGLE;
			m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
			m_MyType.m_nLong=m_nDisCardCount;
			return TRUE;
		}
	}
	if(m_nDisCardCount==0)
	{
		return FALSE;
	}
	return FALSE;

}



//搜索对来打
BOOL CComputer::SearchPair(int number)
{
	if(m_nCardCount>1)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==2 && i+3>number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_nDisCardCount=2;//因为对只有两张牌
						m_MyType.m_nType=CCardRule::PAIR;
						m_MyType.m_nLong=m_nDisCardCount;
						m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
//主动搜索对来打
BOOL CComputer::AI_SearchPair(int number)
{
	if(m_nCardCount>1)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==2 && i+3==number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_nDisCardCount=2;//因为对只有两张牌
						m_MyType.m_nType=CCardRule::PAIR;
						m_MyType.m_nLong=m_nDisCardCount;
						m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}


//搜索三张的牌来打 
BOOL CComputer::SearchThree(int number)
{
	if(m_nCardCount>2)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i+3>number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						m_nDisCardCount=3;
						m_MyType.m_nType=CCardRule::THREE;
						m_MyType.m_nLong=m_nDisCardCount;
						m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
						return TRUE;
					}
				}
			}

		}
	}
	return FALSE;
}
//主动搜索三张的牌来打
BOOL CComputer::AI_SearchThree(int number)
{
	if(m_nCardCount>2)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i+3==number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						m_nDisCardCount=3;
						m_MyType.m_nType=CCardRule::THREE;
						m_MyType.m_nLong=m_nDisCardCount;
						m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
						return TRUE;
					}
				}
			}

		}
	}
	return FALSE;
}
//搜索三带一的牌来打
BOOL CComputer::SearchThreeWOne(int number)
{
	if(m_nCardCount>3)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i>=number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						for(int a=0;a<14;a++)
						{
							if(m_nCardTable[a]==1)
							{
								for(int j=0;j<m_nCardCount;j++)
								{
									if(m_cCard[j].m_nNumber==j+3)
									{
										m_cDisCard[3]=m_cCard[j];
										m_nDisCardCount=4;
										m_MyType.m_nType=CCardRule::THREE_SINGLE;
										m_MyType.m_nLong=m_nDisCardCount;
										m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//主动搜索三带一的牌来打
BOOL CComputer::AI_SearchThreeWOne(int number)
{
		if(m_nCardCount>3)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i==number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						for(int a=0;a<14;a++)
						{
							if(m_nCardTable[a]==1)
							{
								for(int j=0;j<m_nCardCount;j++)
								{
									if(m_cCard[j].m_nNumber==j+3)
									{
										m_cDisCard[3]=m_cCard[j];
										m_nDisCardCount=4;
										m_MyType.m_nType=CCardRule::THREE_SINGLE;
										m_MyType.m_nLong=m_nDisCardCount;
										m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//搜索三带对的牌来打
BOOL CComputer::SearchThreeWTwo(int number)
{
	if(m_nCardCount>4)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i+3>number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						for(int a=0;a<14;a++)
						{
							if(m_nCardTable[a]==2)
							{
								for(int j=0;j<m_nCardCount;j++)
								{
									if(m_cCard[j].m_nNumber==a+3)
									{
										m_cDisCard[3]=m_cCard[j];
										m_cDisCard[4]=m_cCard[j+1];
										m_nDisCardCount=5;
										m_MyType.m_nType=CCardRule::THREE_PAIR;
										m_MyType.m_nLong=m_nDisCardCount;
										m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
	
	
}
//主动搜索三带对的牌来打
BOOL CComputer::AI_SearchThreeWTwo(int number)
{
	if(m_nCardCount>4)
	{
		for(int i=0;i<14;i++)
		{
			if(m_nCardTable[i]==3 && i+3==number)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==i+3)
					{
						m_cDisCard[0]=m_cCard[k];
						m_cDisCard[1]=m_cCard[k+1];
						m_cDisCard[2]=m_cCard[k+2];
						for(int a=0;a<14;a++)
						{
							if(m_nCardTable[a]==2)
							{
								for(int j=0;j<m_nCardCount;j++)
								{
									if(m_cCard[j].m_nNumber==a+3)
									{
										m_cDisCard[3]=m_cCard[j];
										m_cDisCard[4]=m_cCard[j+1];
										m_nDisCardCount=5;
										m_MyType.m_nType=CCardRule::THREE_PAIR;
										m_MyType.m_nLong=m_nDisCardCount;
										m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//搜索炸弹来打
BOOL CComputer::SearchBomb(int number)
{
	if(m_nCardCount>1)
	{
		if(m_cCard[0].m_nNumber==16 && m_cCard[1].m_nNumber==17)
		{
			m_cDisCard[0]=m_cCard[1];
			m_cDisCard[1]=m_cCard[1];
			
			m_nDisCardCount=2;
			m_MyType.m_nType=CCardRule::BOMB;
			m_MyType.m_nLong=m_nDisCardCount;
			m_MyType.m_nValue=m_cDisCard[1].m_nNumber;
			return TRUE;

		}
	}
	if(m_nCardCount>3)
	{
		if(number>15)
		{
			return FALSE;
		}
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber>number && m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				m_cDisCard[0]=m_cCard[i];
				m_cDisCard[1]=m_cCard[i+1];
				m_cDisCard[2]=m_cCard[i+2];
				m_cDisCard[3]=m_cCard[i+3];
				m_nDisCardCount=4;
				m_MyType.m_nType=CCardRule::BOMB;
				m_MyType.m_nLong=m_nDisCardCount;
				m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//主动搜索炸弹的牌来打
BOOL CComputer::AI_SearchBomb(int number)
{
	if(m_nCardCount>3)
	{
		if(number>15)
		{
			return FALSE;
		}
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber==number && m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				m_cDisCard[0]=m_cCard[i];
				m_cDisCard[1]=m_cCard[i+1];
				m_cDisCard[2]=m_cCard[i+2];
				m_cDisCard[3]=m_cCard[i+3];
				m_nDisCardCount=4;
				m_MyType.m_nType=CCardRule::BOMB;
				m_MyType.m_nLong=m_nDisCardCount;
				m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//搜索炸弹带单根的牌来打
BOOL CComputer::SearchFourWSingle(int number)
{
	if(m_nCardCount>5)
	{
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber>number && m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==m_cCard[i].m_nNumber)
					{
						continue;
					}else
				{
					for(int j=0;j<m_nCardCount;j++)
					{
						if(m_cCard[j].m_nNumber!= m_cCard[k].m_nNumber &&
							m_cCard[j].m_nNumber!=m_cCard[i].m_nNumber)
						{
							m_cDisCard[0]=m_cCard[i];
							m_cDisCard[1]=m_cCard[i+1];
							m_cDisCard[2]=m_cCard[i+2];
							m_cDisCard[3]=m_cCard[i+3];
							m_cDisCard[4]=m_cCard[k];
							m_cDisCard[5]=m_cCard[j];

							m_nDisCardCount=6;
							m_MyType.m_nType=CCardRule::FOUR_SINGLE;
							m_MyType.m_nLong=m_nDisCardCount;
							m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
							return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//主动搜索炸弹带单根的牌来打
BOOL CComputer::AI_SearchFourWSingle(int number)
{
	if(m_nCardCount>5)
	{
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber==number && m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber==m_cCard[i].m_nNumber)
					{
						continue;
					}else
				{
					for(int j=0;j<m_nCardCount;j++)
					{
						if(m_cCard[j].m_nNumber!= m_cCard[k].m_nNumber &&
							m_cCard[j].m_nNumber!=m_cCard[i].m_nNumber)
						{
							m_cDisCard[0]=m_cCard[i];
							m_cDisCard[1]=m_cCard[i+1];
							m_cDisCard[2]=m_cCard[i+2];
							m_cDisCard[3]=m_cCard[i+3];
							m_cDisCard[4]=m_cCard[k];
							m_cDisCard[5]=m_cCard[j];

							m_nDisCardCount=6;
							m_MyType.m_nType=CCardRule::FOUR_SINGLE;
							m_MyType.m_nLong=m_nDisCardCount;
							m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
							return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//搜索炸弹带对的牌来打
BOOL CComputer::SearchFourWPair(int number)
{
	if(m_nCardCount>7)
	{
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber>number &&
				m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber!=m_cCard[i].m_nNumber &&
						m_cCard[k].m_nNumber==m_cCard[k+1].m_nNumber)
					{
						for(int j=0;j<m_nCardCount;j++)
						{	
							if(m_cCard[j].m_nNumber!=m_cCard[i].m_nNumber &&
								m_cCard[j].m_nNumber!=m_cCard[k].m_nNumber &&
								m_cCard[j].m_nNumber==m_cCard[j+1].m_nNumber)
							{
								m_cDisCard[0]=m_cCard[i];
								m_cDisCard[1]=m_cCard[i+1];
								m_cDisCard[2]=m_cCard[i+2];
								m_cDisCard[3]=m_cCard[i+3];
								m_cDisCard[4]=m_cCard[k];
								m_cDisCard[5]=m_cCard[k+1];
								m_cDisCard[6]=m_cCard[j];
								m_cDisCard[7]=m_cCard[j+1];

								m_MyType.m_nType=CCardRule::FOUR_PAIR;
								m_nDisCardCount=8;
								m_MyType.m_nLong=m_nDisCardCount;
								m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//主动搜索炸弹带对的牌来打
BOOL CComputer::AI_SearchFourWPair(int number)
{
	if(m_nCardCount>7)
	{
		for(int i=0;i<m_nCardCount;i++)
		{
			if(m_cCard[i].m_nNumber==number &&
				m_cCard[i].m_nNumber==m_cCard[i+1].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+2].m_nNumber &&
				m_cCard[i].m_nNumber==m_cCard[i+3].m_nNumber)
			{
				for(int k=0;k<m_nCardCount;k++)
				{
					if(m_cCard[k].m_nNumber!=m_cCard[i].m_nNumber &&
						m_cCard[k].m_nNumber==m_cCard[k+1].m_nNumber)
					{
						for(int j=0;j<m_nCardCount;j++)
						{	
							if(m_cCard[j].m_nNumber!=m_cCard[i].m_nNumber &&
								m_cCard[j].m_nNumber!=m_cCard[k].m_nNumber &&
								m_cCard[j].m_nNumber==m_cCard[j+1].m_nNumber)
							{
								m_cDisCard[0]=m_cCard[i];
								m_cDisCard[1]=m_cCard[i+1];
								m_cDisCard[2]=m_cCard[i+2];
								m_cDisCard[3]=m_cCard[i+3];
								m_cDisCard[4]=m_cCard[k];
								m_cDisCard[5]=m_cCard[k+1];
								m_cDisCard[6]=m_cCard[j];
								m_cDisCard[7]=m_cCard[j+1];

								m_MyType.m_nType=CCardRule::FOUR_PAIR;
								m_nDisCardCount=8;
								m_MyType.m_nLong=m_nDisCardCount;
								m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}
//搜索顺子来打
BOOL CComputer::SearchSeries(int number,int Long)
{
	int count=0;
	
	for(int i=0;i<12;i++)
	{
		if(i+3>number && m_nCardTable[i]>0)
		{
			for(int k=i;k>i-Long;k--)
			{
				if(k<0)
				{
					count=0;
					break;
				}else
				{
					if(m_nCardTable[k]>0)
					{
						count++;
					}else
					{
						count=0;
						break;
					}
				}
			}
			if(count==Long)
			{
				for(int a=0;a<m_nCardCount;a++)
				{
					if(m_cCard[a].m_nNumber==i+3)
					{
                      for(int b=0;b<count;)
					  {
						  for(int c=a;c>0;c--)
						  {
							  if(c==m_nCardCount)
							  {
								  continue;
							  }else if(m_cCard[c].m_nNumber!=m_cCard[c+1].m_nNumber)
							  {
									m_cDisCard[b]=m_cCard[c];
									b++;
							  }
						  }
					  }
					}
				}
				
				m_nDisCardCount=Long;
				m_MyType.m_nType=CCardRule::SERIES;
				m_MyType.m_nLong=m_nDisCardCount;
				m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//搜索顺对来打
BOOL CComputer::SearchPairSeries(int number, int Long)
{
	int count=0;
	int disCard=0;
	for(int i=0;i<12;i++)
	{
		if(i+3>number && m_nCardTable[i]>1)
		{
			for(int k=i;k>i-(Long/2);k--)
			{
				if(k<0)
				{
					count=0;
					break;
				}else
				{
					if(m_nCardTable[k]>1)
					{
						count+=2;
					}else
					{
						count=0;
						break;
					}
				}
			}
			if(count==Long)
			{
				for(int a=i;a>i-(Long/2);a--)
				{
					for(int b=0;b<m_nCardCount;b++)
					{
						if(m_cCard[b].m_nNumber==a+3 && m_cCard[b-1].m_nNumber==a+3)
						{
							m_cDisCard[disCard]=m_cCard[b];
							disCard++;
							m_cDisCard[disCard]=m_cCard[b-1];
							disCard++;
							break;
						}
					}
				}
				m_nDisCardCount=disCard;
				m_MyType.m_nType=CCardRule::PAIR_SERIES;
				m_MyType.m_nLong=count;
				m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
				return TRUE;
			}

		}
		
	}
	return FALSE;

}

//搜索三带一的顺子
BOOL CComputer::SearchThreeWOneSeries(int number, int Long)
{
	
	int count=0;//计数
	int disCard=0;//主根数
	int carry=0;//带的根数
	if(m_nCardCount<8)
	{
		return FALSE;
	}
	for(int i=0;i<12;i++)
	{
		if(i+3>number && m_nCardTable[i]>=3)
		{
			for(int k=i;k>i-(Long-Long/4)/3;k--)
			{
				if(m_nCardTable[k]>=3)
				{
					count+=3;
				}else
				{
					count=0;
					break;
				}
			}
		}
		if(count==(Long-Long/4))
		{
			for(int b=i;b>i-(Long-Long/4)/3;b--)
			{
				for(int a=0;a<m_nCardCount;a++)
				{
					if(m_cCard[a].m_nNumber==b+3)
					{
						m_cDisCard[disCard]=m_cCard[a++];
						disCard++;
						m_cDisCard[disCard]=m_cCard[a++];
						disCard++;
						m_cDisCard[disCard]=m_cCard[a];
						disCard++;
						break;
					}
				}
			}
			/********************************************/
			for(int c=0;c<m_nCardCount;c++)
			{
				int tag=0;
				for(int d=0;d<disCard+carry;d++)
				{
					if(m_cCard[c].m_nNumber==m_cDisCard[d].m_nNumber)
					{
						tag=1;
						break;
					}
				}
				if(tag!=1)
				{
					m_cDisCard[disCard+carry]=m_cCard[c];
					carry++;
				}
				if(carry==2)
				{
					m_nDisCardCount=disCard+carry;
					m_MyType.m_nType=CCardRule::THREE_SINGLE_SERIES;
					m_MyType.m_nLong=disCard+carry;
					m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//主动搜索三带一的顺子
BOOL CComputer::AI_SearchThreeWOneSeries(int number, int Long)
{
	int count=0;//计数
	int disCard=0;//主根数
	int carry=0;//带的根数
	if(m_nCardCount<8)
	{
		return FALSE;
	}
	for(int i=0;i<12;i++)
	{
		if(i+3==number && m_nCardTable[i]>=3)
		{
			for(int k=i;k>i-(Long-Long/4)/3;k--)
			{
				if(m_nCardTable[k]>=3)
				{
					count+=3;
				}else
				{
					count=0;
					break;
				}
			}
		}
		if(count==(Long-Long/4))
		{
			for(int b=i;b>i-(Long-Long/4)/3;b--)
			{
				for(int a=0;a<m_nCardCount;a++)
				{
					if(m_cCard[a].m_nNumber==b+3)
					{
						m_cDisCard[disCard]=m_cCard[a++];
						disCard++;
						m_cDisCard[disCard]=m_cCard[a++];
						disCard++;
						m_cDisCard[disCard]=m_cCard[a];
						disCard++;
						break;
					}
				}
			}
			/********************************************/
			for(int c=0;c<m_nCardCount;c++)
			{
				int tag=0;
				for(int d=0;d<disCard+carry;d++)
				{
					if(m_cCard[c].m_nNumber==m_cDisCard[d].m_nNumber)
					{
						tag=1;
						break;
					}
				}
				if(tag!=1)
				{
					m_cDisCard[disCard+carry]=m_cCard[c];
					carry++;
				}
				if(carry==2)
				{
					m_nDisCardCount=disCard+carry;
					m_MyType.m_nType=CCardRule::THREE_SINGLE_SERIES;
					m_MyType.m_nLong=disCard+carry;
					m_MyType.m_nValue=m_cDisCard[0].m_nNumber;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
//主动出牌的AI
BOOL CComputer::DirectnessAI()
{
	/***************************************************************/
	for(int i=0;i<15;i++)
	{
		if(m_nCardTable[i]==4)
		{
			if(!AI_SearchFourWPair(i+3))
			{
				if(!AI_SearchFourWSingle(i+3))
				{
					AI_SearchBomb(i+3);
					return TRUE;
				}else
				{
					return TRUE;
				}

			}else
			{
				return TRUE;
			}
		}
	}
	/***************************************************************/
	for(int i=0;i<15;i++)
	{
		if(i<12)
		{
			if(m_nCardTable[i]==3 && m_nCardTable[i+1]==3)
			{
				if(!AI_SearchThreeWOneSeries(i+1+3,8))
				{
					if(!this->AI_SearchThreeWTwo(i+3))
					{
						if(!this->AI_SearchThreeWOne(i+3))
						{
							if(this->AI_SearchThree(i+3))
							{
								return TRUE;
							}
						}else
						{
							return TRUE;
						}
					}else
					{
						return TRUE;
					}
				}else
				{
					return TRUE;
				}
			}
		}
		if(!this->AI_SearchThreeWTwo(i+3))
		{
			if(!this->AI_SearchThreeWOne(i+3))
			{
				if(this->AI_SearchThree(i+3))
				{
					return TRUE;
				}
			}else
			{
				return TRUE;
			}
		}else
		{
			return TRUE;
		}
	}

	/****************************************************************/
	for(int i=0;i<15;i++)
	{
		if(m_nCardTable[i]==2)
		{
			if(AI_SearchPair(i+3))
			{
				return TRUE;
			}
		}
	}
	/***************************************************************/
	for(int i=0;i<15;i++)
	{
		if(m_nCardTable[i]!=0)
		{
			if(this->AI_SearchSingle(i+3))
			{
				return TRUE;
			}
		}
	}
	return TRUE;
}
//被动出牌的AI
BOOL CComputer::SendCardAI(CRole *role_1, CRole *role_2)
{
	if(this->m_nPeople!=LORD)
	{
		if(role_1->m_nPeople==ALLY )
		{
			if(role_2->m_bPass==TRUE)
			{
				return FALSE;
			}
		}else if(role_2->m_nPeople==ALLY)
		{
			if(role_1->m_bPass==TRUE)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
	
}