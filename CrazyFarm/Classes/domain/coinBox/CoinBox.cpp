#include "domain/coinBox//CoinBox.h"
#include "utill/JniFunUtill.h"

CoinBox *CoinBox::_instance = NULL;

CoinBox::CoinBox(){
    this->init();
}

void CoinBox::init(){
}

CoinBox* CoinBox::getInstance(){
    if(_instance == NULL){
		_instance = new CoinBox();
    }
    return _instance;
}

void CoinBox::addCoinBox(int money)
{
	CoinBoxs.push_back(money);
}
int CoinBox::getPerCoinBox()
{
	auto endCoin = CoinBoxs.at(CoinBoxs.size()-1);
	CoinBoxs.pop_back();
	return endCoin;
}

BoxConfigInfo CoinBox::getBoxConfigInfoByItemID(int itemid)
{
	return ConfigBox::getInstance()->getBoxConfigInfoByItemId(itemid);
}


float CoinBox::getCatchPer(int userboxlevel)
{
	float catchper[4] = { 1.0, 1.1, 1.2, 1.3 };
	return catchper[userboxlevel];
}