#include "DreamSecond.h"
#include "Dream.h"
#include "DreamEvent.h"
#include "GameStatus.h"
#include "GameLayer.h"

DreamSecond* DreamSecond::create(int dreamId) {
    DreamSecond* ret = new DreamSecond();
    if (ret && ret->init(dreamId)) {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool DreamSecond::init(int dreamId) {
    if (!Node::init()) {
        return false;
    }
    auto visiblieSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("dream/dream_bg.png");
    bg->setPosition(visiblieSize.width / 2, visiblieSize.height / 2);
    addChild(bg);
    auto box = Sprite::create();
    if (dreamId == 7) {
        box->setTexture("dream/second/dream_second_7_2.png");
    }
    else {
        box->setTexture("dream/second/dream_second_6_2.png");
    }
    box->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 + 40);
    addChild(box);
    
    auto confirm = MenuItemImage::create("dream/second/dream_confirm_second.png", "dream/second/dream_confirm_second.png",
                                         CC_CALLBACK_1(DreamSecond::confirmDream, this));
    confirm->setTag(dreamId);
    auto close = MenuItemImage::create("dream/second/dream_close_second.png", "dream/second/dream_close_second.png",
                                       CC_CALLBACK_1(DreamSecond::closeView, this));
    close->setTag(dreamId);
    auto secondMenu = Menu::create(confirm, close, NULL);
    secondMenu->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 -100);
    secondMenu->alignItemsHorizontallyWithPadding(100);
    addChild(secondMenu);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
        return true;
    };
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void DreamSecond::confirmDream(Ref* ref) {
    MenuItem* tem = (MenuItem*)ref;
    int id = tem->getTag();
    Dream::getInstance()->requestEvent(id);
    //加速道具加1
    Director::getInstance()->resume();//重新启动游戏
    getParent()->removeFromParent();
    
}

void DreamSecond::closeView(Ref* ref) {
    Director::getInstance()->resume();//重新启动游戏
    getParent()->removeFromParent();
}
