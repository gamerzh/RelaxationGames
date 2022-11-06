#include "ToolTipMannger.h"
#include "TwiceSureDialog.h"
#include "utill/Chinese.h"

void ToolTipMannger::ShowPayTimeoutTip()
{
	auto dialog = TwiceSureDialog::createDialog(ChineseWord("netTimeOut").c_str());
	dialog->setPosition(0, 0);
	Director::getInstance()->getRunningScene()->addChild(dialog, 40);
}
void ToolTipMannger::ShowPaySuccessTip()
{
	auto dialog = TwiceSureDialog::createDialog(ChineseWord("BuySuccess").c_str());
	dialog->setPosition(0, 0);
	Director::getInstance()->getRunningScene()->addChild(dialog, 40);
}


void ToolTipMannger::showDioag(std::string str)
{
	auto dialog = TwiceSureDialog::createDialog(str.c_str());
	dialog->setPosition(Point::ZERO);
	Director::getInstance()->getRunningScene()->addChild(dialog, 40);
}