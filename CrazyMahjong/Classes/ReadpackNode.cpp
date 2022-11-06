#include "ReadpackNode.h"
#include "RedpackPanel.h"
#include "Room.h"

bool ReadpackNode::init()
{
	if (!Button::init("hb.png"))
	{
		return false;
	}


	//auto light = Sprite::create("redPackLight.png");
	//light->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
	//light->setPosition(getContentSize() / 2);
	//addChild(light, -1);
	/*setScale(1.3f);
	setOpacity(0);
	setEnabled(false);
	setCascadeOpacityEnabled(true);*/
	/*runAction(Sequence::create(Spawn::createWithTwoActions(FadeIn::create(0.5f), MoveTo::create(0.5f, Vec2(400, 240))), ScaleTo::create(0.2f, 1.0f), MoveTo::create(0.5f, Vec2(126, 110)), CallFunc::create([=]{setEnabled(true); }), nullptr));*/

	std::function<void(Ref*, Widget::TouchEventType)> callback = [=](Ref*, Widget::TouchEventType){
		showResult(0);
	};
	addTouchEventListener(callback);
	schedule(schedule_selector(ReadpackNode::updateBySecond), 2.0f,CC_REPEAT_FOREVER,0.0f);
}
void ReadpackNode::updateBySecond(float delta)
{
	int num = rand() % 3;
	if (num == 0)
	{
		showResult(rand() % 2 + 1);
	}
}
void ReadpackNode::showResult(int index)
{
	//1 3 5  70 15 15
	int score = Room::getInstance()->getRoomScore();
	int num = rand() % 100+1;
	if (num >= 70)
	{
		score *= 1;
	}
	else if (num>=85)
	{
		score *= 3;
	}
	else
	{
		score *= 5;
	}
	auto readpack = RedpackPanel::create(index, score);
	readpack->setPosition(0, 0);
	getParent()->addChild(readpack, 50);
	removeFromParentAndCleanup(1);
}