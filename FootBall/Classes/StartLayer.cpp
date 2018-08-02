#include "StartLayer.h"
#include "DreamLayer.h"
#include "Dream.h"
USING_NS_CC;

bool StartLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("start_bg.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(bg);
    
    auto logo = Sprite::create("logo.png");
    logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(logo);
    
    auto btn = MenuItemImage::create("start_btn.png", "start_btn.png",CC_CALLBACK_0(StartLayer::startGame,this));
    auto menu = Menu::create(btn,NULL);
    menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-260);
    addChild(menu);
    
    if(!Dream::getInstance()->getDreamTimes()){
        auto dream1 = DreamLayer::create(1);
        addChild(dream1);
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e) {
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK: {
                if (!Dream::getInstance()->getDreamTimes()) {
                    if (NULL == getChildByTag(1025)) {
                        DreamLayer* nod = DreamLayer::create(12);
                        nod->setTag(1025);
                        addChild(nod,10);
                    }
                }
                else {
                    Dream::getInstance()->quitGame();
                }
                break;
            }
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void StartLayer::startGame() {
    removeFromParent();
}
