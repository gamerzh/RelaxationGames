#include "LobbyLayer.h"
#include "TeamAbility.h"
#include "UserData.h"
#include "GameStatus.h"
#include "GameScene.h"
#include "StartLayer.h"
#include "Audio.h"

USING_NS_CC;

bool LobbyLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    auto visibileSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("lobby_bg.png");
    bg->setPosition(visibileSize.width / 2, visibileSize.height / 2);
    addChild(bg);
    
    auto box1 = Sprite::create("box_1.png");
    box1->setPosition(visibileSize.width / 2 - 480, visibileSize.height / 2 - 50);
    addChild(box1);
    
    auto box2 = Sprite::create("box_2.png");
    box2->setPosition(visibileSize.width / 2 + 100, visibileSize.height / 2 - 50);
    addChild(box2);
    
    auto soundSelected = MenuItemImage::create("white_sound_on.png", "white_sound_on.png");
    auto soundNormal = MenuItemImage::create("white_sound_off.png", "white_sound_off.png");
    auto sound = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::controlSound, this),
                                                    soundSelected, soundNormal, NULL);
    if(UserData::getInstance()->getMusicStatus() == 0){
        sound->setSelectedIndex(1);
    }
    auto menu = Menu::create(sound,NULL);
    menu->setPosition(1240, 690);
    addChild(menu);
    
    auto number = LabelAtlas::create(StringUtils::format("%d",UserData::getInstance()->getPlayerGoldNum()),"sz2.png",16,24,'0');
    number->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    number->setPosition(330,690);
    addChild(number);
    
    loadButtonView();
    loadMasterVupView();
    loadWorldCupView();
    loadTeamView();
    
    GameStatus::getInstance()->setCurrentGameType(GameStatus::GameType::worldCup);
    GameStatus::getInstance()->setCurrentSelectedLevel(UserData::getInstance()->getWorldCupLevel());
    
    Audio::getInstance()->playLobbyBackgroundMusic();
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e) {
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK: {
                auto start = StartLayer::create();
                addChild(start,1000);
                break;
            }
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void LobbyLayer::controlSound(cocos2d::Ref* ref) {
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    UserData::getInstance()->setMusicStatus((temp->getSelectedIndex()+1)%2);
}


void LobbyLayer::loadButtonView() {
    auto visibileSize = Director::getInstance()->getVisibleSize();
    
    auto worldSpr1 = Sprite::create("world_cup_1.png");
    auto worldSpr2 = Sprite::create("world_cup_2.png");
    auto worldSelected = MenuItemSprite::create(worldSpr1, worldSpr1);
    auto worldNormal = MenuItemSprite::create(worldSpr2, worldSpr2);
    worldItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::worldMenuCallBack, this),
                                                         worldSelected, worldNormal, NULL);
    worldItemToggle->setSelectedIndex(0);
    worldItemToggle->setPosition(visibileSize.width / 2 - 480, visibileSize.height / 2 + 120);
    
    auto masterSpr1 = Sprite::create("master_cup_1.png");
    auto masterSpr2 = Sprite::create("master_cup_2.png");
    auto masterSelected = MenuItemSprite::create(masterSpr1, masterSpr1);
    auto masterNormal = MenuItemSprite::create(masterSpr2, masterSpr2);
    masterItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::masterMenuCallBack, this),
                                                          masterSelected, masterNormal, NULL);
    masterItemToggle->setSelectedIndex(1);
    masterItemToggle->setPosition(visibileSize.width / 2 - 480, visibileSize.height / 2 - 40);
    
    auto teamSpr1 = Sprite::create("my_team_1.png");
    auto teamSpr2 = Sprite::create("my_team_2.png");
    auto teamSelected = MenuItemSprite::create(teamSpr1, teamSpr1);
    auto teamNormal = MenuItemSprite::create(teamSpr2, teamSpr2);
    teamItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::teamMenuCallBack, this),
                                                        teamSelected, teamNormal, NULL);
    teamItemToggle->setSelectedIndex(1);
    teamItemToggle->setPosition(visibileSize.width / 2 - 480, visibileSize.height / 2 - 220);
    
    auto menu = Menu::create(worldItemToggle, masterItemToggle, teamItemToggle, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
}

void LobbyLayer::worldMenuCallBack(cocos2d::Ref* ref) {
    worldItemToggle->setSelectedIndex(0);
    masterItemToggle->setSelectedIndex(1);
    teamItemToggle->setSelectedIndex(1);
    worldLayer->setVisible(true);
    masterLayer->setVisible(false);
    teamLayer->setVisible(false);
    GameStatus::getInstance()->setCurrentGameType(GameStatus::GameType::worldCup);
    GameStatus::getInstance()->setCurrentSelectedLevel(UserData::getInstance()->getWorldCupLevel());
}

void LobbyLayer::masterMenuCallBack(cocos2d::Ref* ref) {
    worldItemToggle->setSelectedIndex(1);
    masterItemToggle->setSelectedIndex(0);
    teamItemToggle->setSelectedIndex(1);
    worldLayer->setVisible(false);
    masterLayer->setVisible(true);
    teamLayer->setVisible(false);
    GameStatus::getInstance()->setCurrentGameType(GameStatus::GameType::masterCup);
    GameStatus::getInstance()->setCurrentSelectedLevel(UserData::getInstance()->getMasterCupLevel());
}

void LobbyLayer::teamMenuCallBack(cocos2d::Ref* ref) {
    worldItemToggle->setSelectedIndex(1);
    masterItemToggle->setSelectedIndex(1);
    teamItemToggle->setSelectedIndex(0);
    worldLayer->setVisible(false);
    masterLayer->setVisible(false);
    teamLayer->setVisible(true);
}

void LobbyLayer::loadWorldCupView() {
    selectLayerIndex = 0;
    worldLayer = Layer::create();
    addChild(worldLayer);
    loadWorldPipeView(worldLayer,UserData::getInstance()->getWorldCupLevel());
   
}

void LobbyLayer::selectCupLevel(Ref* ref) {
    //选择关卡
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    int tag = temp->getTag();
    for(int i=101;i<108;i++){
        if(i == tag){
            ((MenuItemToggle*)temp->getParent()->getChildByTag(i))->setSelectedIndex(1);
        }else{
            ((MenuItemToggle*)temp->getParent()->getChildByTag(i))->setSelectedIndex(0);
        }
    }
    GameStatus::getInstance()->setCurrentSelectedLevel(tag-101);
}

void LobbyLayer::startGame(cocos2d::Ref* ref) {
    Audio::getInstance()->playEffect(START_GAME);
    Director::getInstance()->replaceScene(GameScene::create());
}


void LobbyLayer::loadMasterVupView() {
    selectLayerIndex = 1;
    masterLayer = Layer::create();
    masterLayer->setVisible(false);
    addChild(masterLayer);
    loadMasterPipeView(masterLayer,UserData::getInstance()->getMasterCupLevel());
}

void LobbyLayer::loadTeamView() {
    selectLayerIndex = 2;
    teamLayer = Layer::create();
    teamLayer->setVisible(false);
    addChild(teamLayer);
    auto box1 = TeamAbility::create(TeamAbilityType::speed);
    box1->setPosition(460 , 320);
    teamLayer->addChild(box1);
    auto box2 = TeamAbility::create(TeamAbilityType::shoot);
    box2->setPosition(460 + 280, 320);
    teamLayer->addChild(box2);
    auto box3 = TeamAbility::create(TeamAbilityType::energy);
    box3->setPosition(460 + 280 * 2, 320);
    teamLayer->addChild(box3);
}


void LobbyLayer::loadWorldPipeView(cocos2d::Node* node,int index){

    auto pipe_bg = Sprite::create("worldcup/luc.png");
    pipe_bg->setPosition(735,315);
    node->addChild(pipe_bg);
    
    auto team1 = Sprite::create("worldcup/z.png");
    team1->setPosition(380, 500);
    node->addChild(team1,2);
    
    auto team2 = Sprite::create("worldcup/x1.png");
    team2->setPosition(380, 370);
    node->addChild(team2,2);
    
    auto team3 = Sprite::create("worldcup/f1.png");
    team3->setPosition(380, 240);
    node->addChild(team3,2);
    
    auto team4 = Sprite::create("worldcup/b.png");
    team4->setPosition(380, 120);
    node->addChild(team4,2);
    
    auto team5 = Sprite::create("worldcup/p1.png");
    team5->setPosition(1100, 500);
    node->addChild(team5,2);
    
    auto team6 = Sprite::create("worldcup/h1.png");
    team6->setPosition(1100, 370);
    node->addChild(team6,2);
    
    auto team7 = Sprite::create("worldcup/d1.png");
    team7->setPosition(1100, 240);
    node->addChild(team7,2);
    
    auto team8 = Sprite::create("worldcup/a1.png");
    team8->setPosition(1100, 120);
    node->addChild(team8,2);
    
    auto four1 = Sprite::create("yuxuan_5_3.png");
    four1->setPosition(545,435);
    node->addChild(four1,2);
    
    auto four2 = Sprite::create("yuxuan_5_3.png");
    four2->setPosition(545,180);
    node->addChild(four2,2);
    
    auto four3 = Sprite::create("yuxuan_5_3.png");
    four3->setPosition(925,435);
    node->addChild(four3,2);
    
    auto four4 = Sprite::create("yuxuan_5_3.png");
    four4->setPosition(925,180);
    node->addChild(four4,2);
    
    auto finalCup = Sprite::create("worldcup/final_1.png");
    finalCup->setPosition(735,325);
    node->addChild(finalCup,2);
    
    auto pipe_1 = Sprite::create("worldcup/g2.png");
    pipe_1->setPosition(460, 475);
    node->addChild(pipe_1);
    pipe_1->setVisible(false);
    
    auto pipe_2 = Sprite::create("worldcup/g3.png");
    pipe_2->setPosition(458, 155);
    node->addChild(pipe_2);
    pipe_2->setVisible(false);
    
    auto pipe_3 = Sprite::create("worldcup/g5.png");
    pipe_3->setPosition(1010, 475);
    node->addChild(pipe_3);
    pipe_3->setVisible(false);
    
    auto pipe_4 = Sprite::create("worldcup/g6.png");
    pipe_4->setPosition(1022, 155);
    node->addChild(pipe_4);
    pipe_4->setVisible(false);
    
    auto pipe_5 = Sprite::create("worldcup/g1.png");
    pipe_5->setPosition(605, 315);
    node->addChild(pipe_5);
    pipe_5->setVisible(false);
    
    auto pipe_6 = Sprite::create("worldcup/g7.png");
    pipe_6->setPosition(865, 315);
    node->addChild(pipe_6);
    pipe_6->setVisible(false);
    
    auto pipe_7 = Sprite::create("worldcup/g4.png");
    pipe_7->setPosition(640, 375);
    node->addChild(pipe_7);
    pipe_7->setVisible(false);
    
    auto pipe_8 = Sprite::create("worldcup/g4.png");
    pipe_8->setPosition(857, 250);
    node->addChild(pipe_8);
    pipe_8->setVisible(false);
    
    if(index == 1){
        team2->setTexture("worldcup/x2.png");
        team3->setTexture("worldcup/f2.png");
        team6->setTexture("worldcup/h2.png");
        team7->setTexture("worldcup/d2.png");
        four1->setTexture("worldcup/z3.png");
        four2->setTexture("worldcup/b2.png");
        four3->setTexture("worldcup/p2.png");
        four4->setTexture("worldcup/a2.png");
        pipe_1->setVisible(true);
        pipe_2->setVisible(true);
        pipe_3->setVisible(true);
        pipe_4->setVisible(true);
        pipe_5->setVisible(true);
        pipe_6->setVisible(true);
    }else if(index >= 2){
        team2->setTexture("worldcup/x2.png");
        team3->setTexture("worldcup/f2.png");
        team6->setTexture("worldcup/h2.png");
        team7->setTexture("worldcup/d2.png");
        four1->setTexture("worldcup/z3.png");
        four2->setTexture("worldcup/b3.png");
        four3->setTexture("worldcup/p3.png");
        four4->setTexture("worldcup/a2.png");
        finalCup->setTexture("worldcup/final_2.png");
        pipe_1->setVisible(true);
        pipe_2->setVisible(true);
        pipe_3->setVisible(true);
        pipe_4->setVisible(true);
        pipe_7->setVisible(true);
        pipe_8->setVisible(true);
    }
    
    auto game = MenuItemImage::create("start_game_blue.png","start_game_blue.png", CC_CALLBACK_1(LobbyLayer::startGame,this));
    auto gm = Menu::create(game,NULL);
    gm->setPosition(730,95);
    node->addChild(gm);
}

void LobbyLayer::loadMasterPipeView(Node* node, int index) {
    
    auto pipe1 = Sprite::create("pipe_1_2.png");
    pipe1->setPosition(440,365);
    pipe1->setTag(201);
    node->addChild(pipe1);
    
    auto pipe2 = Sprite::create("pipe_2_2.png");
    pipe2->setPosition(570, 345);
    pipe2->setTag(202);
    node->addChild(pipe2);
    
    auto pipe3 = Sprite::create("pipe_3_2.png");
    pipe3->setPosition(670, 285);
    pipe3->setTag(203);
    node->addChild(pipe3);
    
    auto pipe4 = Sprite::create("pipe_4_2.png");
    pipe4->setPosition(770, 300);
    pipe4->setTag(204);
    node->addChild(pipe4);
    
    auto pipe5 = Sprite::create("pipe_5_2.png");
    pipe5->setPosition(900, 330);
    pipe5->setTag(205);
    node->addChild(pipe5);
    
    auto pipe6 = Sprite::create("pipe_6_2.png");
    pipe6->setPosition(1005, 315);
    pipe6->setTag(206);
    node->addChild(pipe6);
    
    auto level1Selected = MenuItemImage::create("yuxuan_1_1.png", "yuxuan_1_1.png");
    auto level1Normal = MenuItemImage::create("yuxuan_1_2.png", "yuxuan_1_2.png");
    auto level1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level1Selected, level1Normal, NULL);
    level1->setTag(101);
    level1->setPosition(400, 445);
    
    auto level2Selected = MenuItemImage::create("yuxuan_2_1.png", "yuxuan_2_1.png", "yuxuan_2_3.png");
    auto level2Normal = MenuItemImage::create("yuxuan_2_2.png", "yuxuan_2_2.png", "yuxuan_2_3.png");
    auto level2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level2Selected, level2Normal, NULL);
    level2->setTag(102);
    level2->setPosition(485, 285);
    level2->setEnabled(false);
    
    auto level3Selected = MenuItemImage::create("yuxuan_3_1.png", "yuxuan_3_1.png", "yuxuan_3_3.png");
    auto level3Normal = MenuItemImage::create("yuxuan_3_2.png", "yuxuan_3_2.png", "yuxuan_3_3.png");
    auto level3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level3Selected, level3Normal, NULL);
    level3->setTag(103);
    level3->setPosition(655, 385);
    level3->setEnabled(false);
    
    auto level4Selected = MenuItemImage::create("yuxuan_4_1.png", "yuxuan_4_1.png", "yuxuan_4_3.png");
    auto level4Normal = MenuItemImage::create("yuxuan_4_2.png", "yuxuan_4_2.png", "yuxuan_4_3.png");
    auto level4 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level4Selected, level4Normal, NULL);
    level4->setTag(104);
    level4->setPosition(690, 160);
    level4->setEnabled(false);
    
    auto level5Selected = MenuItemImage::create("yuxuan_5_1.png", "yuxuan_5_1.png", "yuxuan_5_3.png");
    auto level5Normal = MenuItemImage::create("yuxuan_5_2.png", "yuxuan_5_2.png", "yuxuan_5_3.png");
    auto level5 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level5Selected, level5Normal, NULL);
    level5->setTag(105);
    level5->setPosition(850, 430);
    level5->setEnabled(false);
    
    auto level6Selected = MenuItemImage::create("yuxuan_6_1.png", "yuxuan_6_1.png", "yuxuan_6_3.png");
    auto level6Normal = MenuItemImage::create("yuxuan_6_2.png", "yuxuan_6_2.png", "yuxuan_6_3.png");
    auto level6 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),
                                                     level6Selected, level6Normal, NULL);
    level6->setTag(106);
    level6->setPosition(955, 220);
    level6->setEnabled(false);
    
    auto level7Selected = MenuItemImage::create("yuxuan_7_1_b.png", "yuxuan_7_1_b.png", "yuxuan_7_3.png");
    auto level7Normal = MenuItemImage::create("yuxuan_7_2_b.png", "yuxuan_7_2_b.png", "yuxuan_7_3.png");
    auto level7 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyLayer::selectCupLevel, this),level7Selected, level7Normal, NULL);
    level7->setTag(107);
    
    if(index ==6){
        level7->setPosition(1050, 470);
    }else{
        level7->setPosition(1090, 470);
    }
    level7->setEnabled(false);
    
    
    auto menu = Menu::create(level1, level2, level3, level4, level5, level6, level7, NULL);
    menu->setPosition(0, 0);
    node->addChild(menu);
    
    auto game = MenuItemImage::create("start_game_blue.png","start_game_blue.png", CC_CALLBACK_1(LobbyLayer::startGame,this));
    auto gm = Menu::create(game,NULL);
    gm->setPosition(1100,85);
    node->addChild(gm);
    
    //通道的显示
    for (int i = 1; i <= index; i++){
        ((Sprite*)node->getChildByTag(200 + i))->setTexture(StringUtils::format("pipe_%d_1.png",i));
    }
    //按钮的显示
    for (int j = 0; j <= index; j++) {
        ((MenuItemToggle*)menu->getChildByTag(101 + j))->setEnabled(true);
        if(j == index){
            ((MenuItemToggle*)menu->getChildByTag(101 + j))->setSelectedIndex(1);
        }else{
            ((MenuItemToggle*)menu->getChildByTag(101 + j))->setSelectedIndex(0);
        }
    }
}

