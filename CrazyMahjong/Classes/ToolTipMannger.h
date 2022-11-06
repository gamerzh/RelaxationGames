#pragma once
#include "TwiceSureDialog.h"
class ToolTipMannger
{
public:
	enum TipType
	{
		Tip_LackingCoinToEnterRoom =1,
		Tip_LackingCoinOther,
		Tip_PaySucceed,
		Tip_PayFailed,
		Tip_BeingVip,
		Tip_ShowExitGame
	};
public:
	static TwiceSureDialog* showDioag(Node*parents, TipType type, const char*arg1 = "", ...);
private:

	static TwiceSureDialog* showLackingCoin(const char*arg1, const char*arg2);

	static TwiceSureDialog* showLackingCoinOther();

	static TwiceSureDialog* showExitGame();
};

