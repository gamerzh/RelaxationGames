#include "ScrollTextMannger.h"
#include "ChineseWorld.h"
#include "NameMannger.h"
ScrollTextMannger* ScrollTextMannger::_instance = NULL;

ScrollTextMannger::ScrollTextMannger(){

}
ScrollTextMannger* ScrollTextMannger::getInstance(){
	if (_instance == NULL){
		_instance = new ScrollTextMannger();
	}
	return _instance;
}
int price[] = { 18, 28, 58, 88 };
std::string ScrollTextMannger::getScrollTextInfo()
{
	int index= rand() % 3;
	auto key = SCROLLTEXT_HEAD+Value(index).asString();
	auto str = ChineseWord(key.c_str());
	switch (index)
	{
	case 0:
		str = String::createWithFormat(str.c_str(), NameMannger::getName().c_str(),price[rand()%4])->getCString();
		break;
	case 1:
		str = String::createWithFormat(str.c_str(), NameMannger::getName().c_str(), (rand()%5+2)*5000)->getCString();
		break;
	case 2:
		str = String::createWithFormat(str.c_str(), NameMannger::getName().c_str())->getCString();
		break;
	default:
		str = "";
		break;
	}
	return str;
}