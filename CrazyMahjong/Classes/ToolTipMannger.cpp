#include "ToolTipMannger.h"
#include "PxPayMannger.h"
#include "ChineseWorld.h"
#include "cocos2d.h"
USING_NS_CC;

#define kZorderTipDialog 30;


TwiceSureDialog* ToolTipMannger::showDioag(Node*parents, TipType type, const char*arg1, ...)
{
	TwiceSureDialog*dg;
	std::vector<std::string> args;
	if (arg1 != "")
	{
		va_list arg_ptr;
		args.push_back(arg1);
		va_start(arg_ptr, type);
		do
		{
			std::string param = va_arg(arg_ptr, char*);
			args.push_back(param);
		} while (arg1 == "");
		va_end(arg_ptr);
	}
	//FileUtils;

	switch (type)
	{
	case ToolTipMannger::Tip_LackingCoinToEnterRoom:
		dg = showLackingCoin(args.at(0).c_str(), args.at(1).c_str());
		break;
	case ToolTipMannger::Tip_LackingCoinOther:
		dg = showLackingCoinOther();
		break;
	case ToolTipMannger::Tip_ShowExitGame:
		dg = showExitGame();
		break;
	default:
		auto str = String::createWithFormat("ToolTiptext_%d", (int)type);
		dg = TwiceSureDialog::createDialog(ChineseWord(str->getCString()).c_str());
		break;
	}
	dg->setPosition(0, 0);
	parents->addChild(dg, 30);
	return dg;

}

TwiceSureDialog* ToolTipMannger::showLackingCoin(const char*arg1, const char*arg2)
{
	auto callback = [=](Ref*psend)
	{
		auto dg = ((Node*)psend)->getParent()->getParent()->getParent();
		PxPayMannger::getInstance()->LaughCoinPayLayer(dg->getParent());
		dg->removeFromParentAndCleanup(1);
	};
	auto str = String::createWithFormat(ChineseWord("ToolTiptext_1").c_str(), arg1, arg2);
	TwiceSureDialog* dialog = TwiceSureDialog::createDialog(str->getCString(), callback);
	dialog->setCloseButtonCallback(callback);
	return dialog;
}

TwiceSureDialog* ToolTipMannger::showLackingCoinOther()
{
	auto callback = [=](Ref*psend)
	{
		auto dg = ((Node*)psend)->getParent()->getParent()->getParent();
		PxPayMannger::getInstance()->LaughCoinPayLayer(dg->getParent());
		dg->removeFromParentAndCleanup(1);
	};
	TwiceSureDialog* dialog = TwiceSureDialog::createDialog(ChineseWord("ToolTiptext_2").c_str(), callback);
	dialog->setCloseButtonCallback(callback);
	return dialog;
}

TwiceSureDialog* ToolTipMannger::showExitGame()
{
	auto callback = [=](Ref*psend)
	{
		Director::getInstance()->end();
	};
	TwiceSureDialog* dialog = TwiceSureDialog::createDialog(ChineseWord("ToolTiptext_6").c_str(), callback);
	return dialog;
}