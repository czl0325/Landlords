#pragma once
#include "role.h"

class CPlayer :public CRole
{
//私有方法
private:
     BOOL CheckRule();//判断出牌是否符合规则
public:
	 virtual BOOL SendCard(CardType &type);
	 virtual BOOL DirectnessPlay(CardType &type);
	 void GoBack();//牌退回原地
public:
	CPlayer(CCardMap* cardMap);
	virtual ~CPlayer(void);
};
