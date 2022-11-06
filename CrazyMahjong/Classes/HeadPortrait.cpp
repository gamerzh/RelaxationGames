#include "HeadPortrait.h"
#include "Room.h"
#include "ChineseWorld.h"
#include "User.h"
using namespace std;

void HeadPortrait::setHeadProtrait(int dir, std::string name, int photo, int coins)
{
	this->setName("Head");
	_dir = dir;
	// 位置
	switch (dir)
	{
	case 0://43
		this->setPosition(65, 75);		// 下
		break;
	case 1:
		this->setPosition(1180, 443);		// 右
		break;
	case 2:
		this->setPosition(920, 650);		// 上
		break;
	case 3:
		this->setPosition(65, 443);		// 左
		break;
	}
	
	// 头像
	string str = "head_" + String::createWithFormat("%d", Room::getInstance()->getPlayerHead(dir))->_string + ".png";
	Sprite* headPhoto = Sprite::create("head_image_1.png");
	Vec2 center = headPhoto->getContentSize() / 2;
	this->addChild(headPhoto);

	// 姓名
	string strN = Room::getInstance()->getName(dir);
	nameLabel = LabelTTF::create(strN, "arial", 18.0f);
	nameLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	nameLabel->setPosition(center.x, center.y + 60.0f);
	headPhoto->addChild(nameLabel);

	// 金币数
	string coinStr = String::createWithFormat("%d", coins)->_string;
	coinsLabel = Label::createWithCharMap("coins_num.png", 11, 14, '0');
	coinsLabel->setString(coinStr);
	coinsLabel->setScale(1.5);
	coinsLabel->setAdditionalKerning(-3.0f);
	coinsLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	coinsLabel->setPosition(center.x + 3.0f, center.y - 60.0f);
	headPhoto->addChild(coinsLabel);

	auto sp = (Sprite*)getChildByName("headPortrait_bkg_vip");
	bool isVip = Room::getInstance()->isVip(dir);
	if (0)
	{
		sp->setVisible(true);
	}
}

void HeadPortrait::updateName()
{
	if (_dir == 0)
	{
		auto strN = User::getInstance()->getMyName();
		nameLabel->setString(strN);
	}
	else
	{
		
	}
}
void HeadPortrait::updateCoin()
{
	int coin = Room::getInstance()->getCoins(_dir);
	coinsLabel->setString(Value(coin).asString());

}


// 初始化头像：【底框，背景色】，【头像，姓名，金币】
bool HeadPortrait::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 背景色
	Sprite* bkgColor = Sprite::create("headPortrait_bkg.png");
	this->addChild(bkgColor,0,"bkgcolor");
	
	Sprite*vip = Sprite::create("headPortrait_bkg_vip.png");
	this->addChild(vip, 6, "headPortrait_bkg_vip");
	vip->setVisible(false);
	// 金币
	Sprite* coinIcon = Sprite::create("coinIcon.png");
	coinIcon->setPosition(-25, -39);
	this->addChild(coinIcon);

	// 倒计时蒙版
	//Sprite* mask = Sprite::create("mask.png");
	//progress = ProgressTimer::create(mask);
	//this->addChild(progress);
	//progress->setType(ProgressTimerType::RADIAL);
	scheduleUpdate();
	return true;
}

void HeadPortrait::update(float delta)
{
	
}

void HeadPortrait::setTimes(int times)
{
	if (times==1)
	{
		return;
	}
	auto path = String::createWithFormat("System_UI/multiple_%d.png",times);
	auto sp = Sprite::create(path->getCString());
	sp->setPosition(53-26, 12-34);
	addChild(sp,7);
}