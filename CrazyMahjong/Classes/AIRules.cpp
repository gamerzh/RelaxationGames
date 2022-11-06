#include "AIRules.h"
#include "Rules.h"
AIRules* AIRules::instance = nullptr;

AIRules* AIRules::getInstance()
{
	if (nullptr == instance)
	{
		instance = new AIRules();
	}
	return instance;
}

AIRules::AIRules()
{
	init();
}

bool AIRules::init()
{
	return true;
}


Card* AIRules::getCardToPlay(MahjongDrawer & drawer)
{
	bool isNoDianBao = random<int>(1, 100) < noDianPao;
	RuleType type = Rules::getInstance()->get_ruleType();
	int index=0; 
	if (2 == drawer.cardInHand.size())
	{
		if (type == Rule_Normal)
		{
			index = random<int>(0, 1);
		}
		else
		{
			for (int i = 0; i < 2;i++)
			{
				if (drawer[i]*(drawer.cardInSide[0]->get_type())<0)
				{
					index = i;
					break;
				}
			}
		}
		if (isNoDianBao)
		{
			bool hu = Rules::getInstance()->testCanHu(*_playerdrawer, drawer[index]);
			if (hu)
			{
				for (int i = 0; i < 2;i++)
				{
					if (index!=i)
					{
						index = i;
						break;
					}
				}
			}
		}
	}
	else  
	{
		if (Rules::getInstance()->get_ruleType()==Rule_Normal)
		{
			index = getCardToPlayIndex(drawer);
		}
		else
		{
			index = getCardToPlayIndexForQingYiSe(drawer);
		}
		if (isNoDianBao)
		{
			bool hu = Rules::getInstance()->testCanHu(*_playerdrawer, drawer[index]);
			if (hu)
			{
				for (int i = 0; i < 4; i++)
				{
					if (index != i)
					{
						index = i;
						break;
					}
				}
			}
		}
	}

	return drawer.cardInHand.at(index);
}

//获得牌多的牌的花色
int getMoreCardTypeByCards(MahjongDrawer&drawer)
{
	int WanCount = 0;
	int TongCount = 0;
	for (int i = 0; i < 5;i++)
	{
		if (drawer[i]>0)
		{
			WanCount++;
		}
		else
		{
			TongCount++;
		}
	}
	return WanCount > TongCount ? 1 : -1;
}

int AIRules::getCardToPlayIndexForQingYiSe(MahjongDrawer & drawer)
{
	int mostCard = getMoreCardTypeByCards(drawer);
	std::vector<int> otherCards;
	for (int i = 0; i < 5;i++)
	{
		if (drawer[i] * mostCard < 0)
		{
			otherCards.push_back(i);
		}
	}
	if (otherCards.size()>0)
	{
		return otherCards[otherCards.size() - 1];
	}
	else
	{
		return getCardToPlayIndex(drawer);
	}
}
int AIRules::getCardToPlayIndex(MahjongDrawer & drawer)
{
	// ----------------------------------------------------------------------
	if (drawer[0] == drawer[1])	// aa * * *
	{
		if (drawer[1] == drawer[2])
		{
			return random<int>(3, 4);	// aaa xy
		}
		
		if (drawer[3] == drawer[4])	// aa x yy
		{
			return 2;
		}

		if (drawer[2] == drawer[3]) // aa yy x
		{
			return 4;
		}

		if (2 >= drawer[2] - drawer[1]) // aab xy
		{
			if (2 >= drawer[3] - drawer[2])	// aabc x
			{
				return 4;
			}
			else
			{
				return random<int>(3, 4);
			}
		}

		if (2 >= drawer[3] - drawer[2]) // aa de x
		{
			return 4;
		}

		if (2 >= drawer[4] - drawer[3])
		{
			return 2;
		}
		for (int i = 2; i < 5;i++)//先打出不同花色
		{
			if (drawer[i]*drawer[0]<0)
			{
				return i;
			}
		}
		return random<int>(2, 4);
	}
	if (drawer[1] == drawer[2])	// a dd xy
	{
		if (drawer[2] == drawer[3])	// a ddd y 
		{
			if (2 >= drawer[1] - drawer[0]) // c ddd y
			{
				if (2 >= drawer[4] - drawer[3]) // c ddd e
				{
					return (0.5 < random<float>(.0f, 1.0f) ? 0 : 4);
				}
				return 4;
			}
			if (2 >= drawer[4] - drawer[3]) // x ddd e
			{
		
				return 0;
			}
			if (drawer[0]*drawer[1]<0)// x ddd y
			{
				return  0;
			}
			else
			{
				return 4;
			}
		}

		if (drawer[3] == drawer[4])	// x dd yy 
		{
			return 0;
		}
		return (0.5 < random<float>(.0f, 1.0f) ? 3 : 4);
	}

	// ----------------------------------------------------------------------
	if (drawer[2] == drawer[3])	// xy aa z
	{
		if (drawer[3]==drawer[4]) //xy aaa
		{
			return random<int>(0, 1);
		}
		if (2 >= drawer[1] - drawer[0]) // ab dd e
		{
			return 4;
		}

		if (2 >= drawer[2] - drawer[1]) // *cdd*
		{
			if (2 >= drawer[4] - drawer[3]) // a cdde
			{
				return 0;
			}
			return (0.5 < random<float>(.0f, 1.0f) ? 0 : 4);	// a cdd e
		}

		if (2 >= drawer[4] - drawer[3]) // a c dde
		{
			return (0.5 < random<float>(.0f, 1.0f) ? 0 : 1);	
		}
		return 4;
	}
	// ----------------------------------------------------------------------
	if (drawer[3] == drawer[4])	// x y z aa
	{
		if (2 >= drawer[1] - drawer[0]) // ab x dd
		{
			if (2 >= drawer[2] - drawer[1]) // abc dd
			{
				int diff1 = abs(drawer[1] - drawer[0]);
				int diff2 = abs(drawer[2] - drawer[1]);
				return diff1<diff2 ? 2 : 0;
			}
			return 2; // ab e dd
		}
		if (2 >= drawer[2] - drawer[1]) // x ab dd
		{
			return 0;
		}
		if (2 >= drawer[3] - drawer[2]) // x ab dd
		{
			return 0;
		}
		return random<int>(0, 2);
	}
	//判断是否有ABC牌型 不拆
	int startindex = getABCCardStartIndex(drawer);
	if (startindex)
	{
		for (int i = 0; i < 5;i++)
		{
			if (i<startindex&&i>startindex+2)
			{
				return i;
			}
		}
	}
	int WanOrTong = getMoreCardTypeByCards(drawer);
	if (WanOrTong)
	{
		return 0;
	}
	else
	{
		return 4;
	}

	// ----------------------------------------------------------------------
	return 4;
	return random<int>(0, 4);
}


int AIRules::getABCCardStartIndex(MahjongDrawer& drawer)
{
	if (drawer.cardInHand.size()<5)
	{
		return -1;
	}
	for (int i = 0; i < 3;i++)
	{
		if (Rules::isThreeBehind(drawer[i], drawer[i + 1], drawer[i + 2]))
		{
			return i;
		}
	}
	return -1;
}