#include "CTurntable.h"

#include "TurntableCell.h"
#include "TurnTableDialog.h"
#include "domain/logevent/LogEventTurnTable.h"

#define MAX_COUNT 6 
bool CTurntable::init()
{

    if ( !Sprite::initWithFile("turntable_frame.png") )
    {
        return false;
    }
	

	
	result = BonusPoolManager::getInstance()->getBonuspoolResult();
	auto pool = result.reward_list;
	reward = pool.at(result.reward_position);
	curPos = result.reward_position;
	Size visibleSize = getContentSize();
	pSprite_circle = CCSprite::create("turntable_rarota.png");
    pSprite_circle->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2));
    addChild(pSprite_circle, 0);
    
	auto splight1 = Sprite::create("turntablelight_1.png");
	splight1->setPosition(pSprite_circle->getContentSize() / 2);
	pSprite_circle->addChild(splight1, 1);
	splight1->runAction(RepeatForever::create(Blink::create(0.8f, 1)));

	auto splight2 = Sprite::create("turntablelight_2.png");
	splight2->setPosition(pSprite_circle->getContentSize() / 2);
	pSprite_circle->addChild(splight2, 1);
	splight2->runAction(Sequence::create(DelayTime::create(0.4f), CallFunc::create([=]{splight2->runAction(RepeatForever::create(Blink::create(0.8f, 1))); }), nullptr));


    Sprite* pSprite_point = Sprite::create("bg_point.png");
    pSprite_point->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(pSprite_point, 1);
    
	int size = pool.size();

	int tempCoin = 3;
	int tempDm = 2;
	 for (int i = 0; i < size; i++) 
	{
		String *path;
	  auto item = pool[i];
	  int id = item.item_id;
	  int num = item.num;
	  if (id != 1001 && id != 1002)
	  {
		  path = String::createWithFormat("sign_%d.png", id);
	  }
	  else if (id == 1001)
	  {
		  path = String::createWithFormat("coin_%d.png", tempCoin++);
	  }
	  else if (id == 1002)
	  {
		  path = String::createWithFormat("zuanshi_%d.png", tempDm++);
	  }/*path = String::createWithFormat("sign_%d.png", id);*/

	 
		auto cell = TurntableCell::create(path->getCString(), num);
		cell->setTag(i);
		cell->setPosition(pSprite_circle->getContentSize()/2);
		cell->setRotation(i*60);
		(id != 1001 && id != 1002) ? cell->setAnchorPoint(ccp(0.5, -1.0)) : cell->setAnchorPoint(ccp(0.5, -1.2));
		pSprite_circle->addChild(cell);   
    }
    return true;
}


void CTurntable::menuButtonCallbackStop()
{
	static int count = 0;


    
    pSprite_circle->stopAllActions();
	float curangle = (360-360 * (curPos+ CCRANDOM_MINUS1_1()*0.5) / MAX_COUNT); //改变里面的数字 更改停的位置
	CCLOG("curAngle = %f", curangle);
	pSprite_circle->setRotation(curangle); 
    
	CCActionInterval* actionTo_1 = CCRotateBy::create(0.375, 360 * 2);
	CCActionInterval* actionTo_2 = CCRotateBy::create(0.125, 144);
	CCActionInterval* actionTo_3 = CCRotateBy::create(0.1625, 108);
	CCActionInterval* actionTo_4 = CCRotateBy::create(0.2125, 72);
	CCActionInterval* actionTo_5 = CCRotateBy::create(0.25, 36);



	pSprite_circle->runAction(Sequence::create(actionTo_1, actionTo_2, actionTo_3, actionTo_4, actionTo_5, DelayTime::create(1.0f), CallFunc::create([&]{
		auto parent = (TurnTableDialog*)getParent();
		parent->onGetRewards(reward); }),nullptr));

 


}

void CTurntable::menuButtonCallback(Ref* pSend) {
    


	LogEventTurnTable::getInstance()->sendDataToServer(result.bouns_position + 1, result.reward_position + 1);
    static bool need_rotation = false;


    
    
    
    if (!need_rotation) {
        need_rotation = true;

		CCActionInterval* actionTo_5 = CCRotateBy::create(0.25, 36);
		CCActionInterval* actionTo_4 = CCRotateBy::create(0.2125, 72);
		CCActionInterval* actionTo_3 = CCRotateBy::create(0.1625, 108);
		CCActionInterval* actionTo_2 = CCRotateBy::create(0.2, 144);
		CCActionInterval* actionTo_1 = CCRotateBy::create(1, 360 * 5);

		pSprite_circle->runAction(Sequence::create(actionTo_5, actionTo_4, actionTo_3, actionTo_2, actionTo_1, CallFunc::create(CC_CALLBACK_0(CTurntable::menuButtonCallbackStop, this)), nullptr));
  
    
        need_rotation = false;
    }
}



