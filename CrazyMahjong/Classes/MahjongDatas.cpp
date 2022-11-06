#include "MahjongDatas.h"

#include "cocos2d.h"
#include "MahjongAnim.h"

#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
USING_NS_CC;

MahjongDatas* MahjongDatas::instance = nullptr;

MahjongDatas::MahjongDatas()
{
}

int MahjongDatas::getCardNum()
{
	return cardsTong.size() + cardsWan.size();
}

void MahjongDatas::initGoodType()
{
	goodCard = 1 > random<float>(0, 1) ? TONG : WAN;
}

// 初始化所有 麻将牌面
void MahjongDatas::initData()
{
	CCLOG("MahjongDatas : initData");
	// 添加牌，36筒，36万，每样4张
	if (0 < cardsTong.size())
	{
		cardsTong.clear();
	}
	vector<int> cardsRes;
	for (int i = 0; i < 4; i++)
	{
		cardsRes.push_back(1);
		cardsRes.push_back(2);
		cardsRes.push_back(3);
		cardsRes.push_back(4);
		cardsRes.push_back(5);
		cardsRes.push_back(6);
		cardsRes.push_back(7);
		cardsRes.push_back(8);
		cardsRes.push_back(9);
	}
	for (int i = 0; i < 36; i++)
	{
		int size = cardsRes.size() - 1;
		int index = random<int>(0, size);
		int type = cardsRes.at(index);
		cardsTong.push_back(type);
		cardsRes.erase( find(cardsRes.begin(), cardsRes.end(), type) );
	} 
	// 添加牌，36万，每样4张
	if (0 < cardsTong.size())
	{
		cardsWan.clear();
	}
	for (int i = 0; i < 4; i++)
	{
		cardsRes.push_back(-1);
		cardsRes.push_back(-2);
		cardsRes.push_back(-3);
		cardsRes.push_back(-4);
		cardsRes.push_back(-5);
		cardsRes.push_back(-6);
		cardsRes.push_back(-7);
		cardsRes.push_back(-8);
		cardsRes.push_back(-9);
	}
	for (int i = 0; i < 36; i++)
	{
		int type = cardsRes.at(random<int>(0, cardsRes.size() - 1));
		cardsWan.push_back(type);
		cardsRes.erase(find(cardsRes.begin(), cardsRes.end(), type));
	}

	initGoodType();

	//return;
	////做牌
	

	std::string filename = "card.json";
	rapidjson::Document doc;
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		return;
	}
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	auto &arrary = doc["array"];
	std::vector<int> cardsArray;
	for (unsigned int i = 0; i < arrary.Size(); i++)
	{
		cardsArray.push_back(arrary[i].GetInt());
	}
	//int cardsArray[] = {
	//	4,-7,4,1,
	//	3,2,-1,-5,
	//	3,-8,-3, -2,
	//	3, -8, -4, 1,
	//	2, 3, 3, 3,			
	//	3, 6,6, 6,
	//	3, 3, -7, 3,
	//	-2, -5, -4, 8,
	//	1, -4, 9, 7,
	//	-2, -1, 6, -7,			// 36

	//	-9, 4, -9, 5,
	//	3, 9, 5, -8,
	//	-6, 5, 7, 1,
	//	1, -1, 5, -3,			// 52
	//	-8, -1, -3, 7,
	//	5, 4, -7, 3,
	//	-2, -5, -4, 8,
	//	1, -4, 9, 7,
	//	-2, -1, 6, -7,
	//};
	isFalseCard = true;
	for (int i = 0; i < cardsArray.size(); i++)
	{
		playedCards.push_back(cardsArray[cardsArray.size() - i - 1]);
	}
}

/// 抽取一张牌,
//@return num表示花色，0表示无牌
int MahjongDatas::popACard()
{
	if (isFalseCard)
	{
		int t = playedCards.at(playedCards.size() - 1);
		playedCards.pop_back();
		return t;
	}

	auto card = 0.5 > random<float>(0, 1) ? TONG : WAN;
	switch (card)
	{
	case TONG:
		if (cardsTong.empty())
		{
			return popWan();
		}
		return popTong();
		break;
	case WAN:
		if (cardsWan.empty())
		{
			return popTong();
		}
		return popWan();
		break;
	default:
		return 0;
		break;
	}
}
int MahjongDatas::popAGoodCard(vector<Card*> cardInHand)
{
	if (isFalseCard)
	{
		int t = playedCards.at(playedCards.size() - 1);
		playedCards.pop_back();
		return t;
	}

	switch (goodCard)
	{
	case TONG:
		return popTong();
		break;
	case WAN:
		return popWan();
		break;
	default:
		return 0;
		break;
	}
}

int MahjongDatas::popTong()
{
	if (0 == cardsTong.size())
	{
		return popWan();
	}
	int cardType = cardsTong.at(cardsTong.size() - 1);
	cardsTong.pop_back();
	return cardType;
}

int MahjongDatas::popWan()
{
	if (0 == cardsWan.size())
	{
		return popTong();
	}
	int cardType = cardsWan.at(cardsWan.size() - 1);
	cardsWan.pop_back();
	return cardType;
}

void MahjongDatas::reviewAllCards()
{
	if (NULL == MahjongAnim::getInstance())
	{
		return;
	}

	/*for (int type : cardsTong)				// 验证是否开局有18种牌，每种都有4个。
	{
		MahjongAnim::getInstance()->addRemever(type);
	}
	for (int type : cardsWan)
	{
		MahjongAnim::getInstance()->addRemever(type);
	}*/

}

