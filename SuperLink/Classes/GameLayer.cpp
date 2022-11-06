#include "GameLayer.h"
#include "Matrix.h"
#include"GameData.h"
#include"Audio.h"
#include"math.h"
#include "GameGuiLayer.h"
#include "CallAndroidMethod.h"
#include "GameResultScene.h"
bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Ready;
	GAMEDATA::getInstance()->setLevel(1);
	GAMEDATA::getInstance()->setTimes(GAMEDATA::getInstance()->getTimes()+1);
	MARGIN_BOTTOM = 220;
	MARGIN_LEFT = 100;
	Matrix::getInstance()->ROW_NUM = 4;
	Matrix::getInstance()->COL_NUM = 4;
	clickitem[0] = -1;
	clickitem[1] = -1;
	tipPos.push_back(-1);
	tipPos.push_back(-1);
	removeCount = 0;
	GAMEDATA::getInstance()->needResetMap = false;
	GAMEDATA::getInstance()->needTipPos = false;

	 

	//����touch�¼�����
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::ccTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::ccTouchEnded, this);

	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* game_bg = Sprite::create("game_bg.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg);
	drawMapBg();

	Audio::getInstance()->playSound(GAME_START);

	//���̳�ʼ��
	Matrix::getInstance()->MAX_TYPE_NUM = 4;
	Matrix::getInstance()->initMatrix();
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();
	for (int i = 0; i < allCells.size(); i++){
	    //��ʼ�������ϻ������е�Ԫ��
		Vec2 pos = getPosByPostion(allCells.at(i)->getPosition());
		//int ת string
		string s = "item" + CCString::createWithFormat("%d", (allCells.at(i)->getCellType() - 1))->_string + ".png";
		element = Sprite::create(s);
		element->setScale(0.5);
		element->setPosition(pos);
		auto Act= Sequence::create(DelayTime::create(0.2), ScaleTo::create(0.5, 1), nullptr);
		element->runAction(Act);
		element->setTag(allCells.at(i)->getCellType());
		this->addChild(element);
		allElements.pushBack(element);
	}
	GAMEDATA::getInstance()->updateProcess = true;
	schedule(schedule_selector(GameLayer::showMatrix), 1.0f, 0, 0);
	scheduleUpdate();



	return true;
}
void  GameLayer::drawMapBg(){
	for (int i = 0; i < Matrix::getInstance()->ROW_NUM;i++){
		for (int j = 0; j <Matrix::getInstance()->COL_NUM; j++){
			Sprite* element = NULL;
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)){
				//bg_1
				element = Sprite::create("item_bg1.png");
			}
			else{
				//bg_2
				element = Sprite::create("item_bg2.png");
			}
			element->setPosition(getPosByPostion(Matrix::getInstance()->getPositionByXAndY(j, i)));
			this->addChild(element);
			allBgElements.pushBack(element);
		}
	}

}
void GameLayer::resetMap(){

	if (tipPos.size()>1 && tipPos[0] != tipPos[1]){
		//����ʾ
		lights.at(0)->removeFromParent();
		lights.at(1)->removeFromParent();
		lights.clear();
		tipPos[0] = tipPos[1] = -1;
	}
	for (int i = 0; i < Matrix::getInstance()->getMartixCells().size(); i++){
		if (Matrix::getInstance()->getMartixCells().at(i)->getCellType()!= NULL){
			allElements.at(i)->setScale(1);
			auto Act = Sequence::create(DelayTime::create(0), ScaleTo::create(0.5, 0.2), nullptr);
			allElements.at(i)->runAction(Act);
		}
	}

	schedule(schedule_selector(GameLayer::newMap), 0.5f, 0, 0);
}

void GameLayer:: newMap(float dt){
	Matrix::getInstance()->resetMap();
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();
	for (int i = 0; i < allCells.size(); i++){
		if (allCells.at(i)->getCellType() != NULL){
			//��ʼ�������ϻ������е�Ԫ��
			//int ת string
			string s = "item" + CCString::createWithFormat("%d", (allCells.at(i)->getCellType() - 1))->_string + ".png";
			element = Sprite::create(s);
			auto Act1 = Sequence::create(DelayTime::create(0), ScaleTo::create(0.5, 1), nullptr);
			allElements.at(i)->setTag(allCells.at(i)->getCellType());
			allElements.at(i)->setTexture(element->getTexture());
			allElements.at(i)->runAction(Act1);
		}
	}

}

void GameLayer::startGame(float dt){
	//������Ϸ��ʼǰ�Ʒѵ㵯���¼�
	if (GAMEDATA::getInstance()->getFirstPay()){
		//��ʾ�û�û�и���
		if (GAMEDATA::getInstance()->getTimes() == 1){
			CallAndroidMethod::getInstance()->requestEvent(1);
		}
		else if (GAMEDATA::getInstance()->getTimes() == 2){
			CallAndroidMethod::getInstance()->requestEvent(2);
		}
		else if (GAMEDATA::getInstance()->getTimes() == 3){
			CallAndroidMethod::getInstance()->requestEvent(3);
		}
		else if (GAMEDATA::getInstance()->getTimes() == 4){
			CallAndroidMethod::getInstance()->requestEvent(5);
		}
		else if (GAMEDATA::getInstance()->getTimes() == 8){
			CallAndroidMethod::getInstance()->requestEvent(6);
		}
		else if (GAMEDATA::getInstance()->getTimes() == 12){
			CallAndroidMethod::getInstance()->requestEvent(7);
		}else if (GAMEDATA::getInstance()->getTimes() >= 16 && GAMEDATA::getInstance()->getTimes() % 4 == 0){
			//���¼���25��26��27
			int num = (GAMEDATA::getInstance()->getTimes()/4) % 3 + 25;
			CallAndroidMethod::getInstance()->requestEvent(num);
		}
		else{
			CallAndroidMethod::getInstance()->requestEvent(18);
		}
	}
	else{
		if (GAMEDATA::getInstance()->getTimes() == 10){
			CallAndroidMethod::getInstance()->requestEvent(28);
		}else if (GAMEDATA::getInstance()->getTimes() >= 20 && GAMEDATA::getInstance()->getTimes() % 10 == 0){
			//�����¼���29��30��31
			int num = (GAMEDATA::getInstance()->getTimes()/10) % 3 + 29;
			CallAndroidMethod::getInstance()->requestEvent(num);
		}else{
			//Start game
			CallAndroidMethod::getInstance()->requestEvent(18);
		}
	}
}

void GameLayer::showMatrix(float dt){
	Sprite* sprite = Sprite::create("GO.png");
	sprite->setPosition(240, 400);
	auto action = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 0)), FadeOut::create(0),
		nullptr);
	addChild(sprite, 1);
	sprite->runAction(action);
	Audio::getInstance()->playSound(readyGo);
	if (GAMEDATA::getInstance()->getLevel()==1){
		GAMEDATA::getInstance()->settime(20);
		schedule(schedule_selector(GameLayer::startGame), 1.0f, 0, 0);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 2){
		GAMEDATA::getInstance()->settime(20);
		CallAndroidMethod::getInstance()->requestEvent(19);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 3){
		GAMEDATA::getInstance()->settime(20);
		CallAndroidMethod::getInstance()->requestEvent(12);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 4){
		GAMEDATA::getInstance()->settime(20);
		CallAndroidMethod::getInstance()->requestEvent(20);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 5){
		GAMEDATA::getInstance()->settime(25);
		CallAndroidMethod::getInstance()->requestEvent(21);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 6){
		GAMEDATA::getInstance()->settime(30);
		CallAndroidMethod::getInstance()->requestEvent(13);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 7){
		GAMEDATA::getInstance()->settime(30);
		CallAndroidMethod::getInstance()->requestEvent(22);
	}
	else if (GAMEDATA::getInstance()->getLevel() == 8){
		GAMEDATA::getInstance()->settime(30);
		CallAndroidMethod::getInstance()->requestEvent(23);
	}
	else {
		GAMEDATA::getInstance()->settime(25);
		CallAndroidMethod::getInstance()->requestEvent(24);
	}

	
}
Vec2 GameLayer::getPosByPostion(int postion){
	int x = Matrix::getInstance()->getXByCellPosition(postion);
	int y = Matrix::getInstance()->getYByCellPosition(postion);
	float pos_x = x * ELEMENT_WIDTH + MARGIN_LEFT + ELEMENT_WIDTH/2;
	float pos_y = y * ELEMENT_WIDTH + MARGIN_BOTTOM + ELEMENT_WIDTH / 2;
	return ccp(pos_x, pos_y);
	
}

void GameLayer::doItemSelectAnima(Vec2 pos){
	auto sp = Sprite::create("select_bg_1.png");
	sp->setPosition(pos);
	this->addChild(sp);
	auto animation = Animation::create();
	for (int i = 1; i<6; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "select_bg_%1d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(2.0f / 5);
	animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(animation);
	sp->runAction(RepeatForever::create(animate));
	lights.pushBack(sp);
}


void GameLayer::clearClickState(){
	lights.at(0)->removeFromParent();
	lights.at(1)->removeFromParent();
	items.at(0)->removeFromParent();
	items.at(1)->removeFromParent();
	lights.popBack();
	items.popBack();
	lights.popBack();
	items.popBack();
	clickitem[0] = -1;
	clickitem[1] = -1;
}

bool GameLayer::onTouchBegan(Touch*touch, Event*event){
	if (clickitem[0] == -1){
		Audio::getInstance()->playSound(CLICK);
	}
	if (GAMEDATA::getInstance()->gameState != GAMEDATA::GameState::Playing){
		return false;
	}
	//TODO:��������¼�
	auto point = touch->getLocation();
	return true;
}

void GameLayer::update(float dt){
	if (GAMEDATA::getInstance()->gameState == GAMEDATA::GameState::Playing){
		if (GAMEDATA::getInstance()->needResetMap){
			GAMEDATA::getInstance()->needResetMap = false;
			resetMap();
		}

		if (GAMEDATA::getInstance()->needTipPos){
			GAMEDATA::getInstance()->needTipPos = false;
			showTipPos();
		}

		// goto result scene
		if (GAMEDATA::getInstance()->gettime() < 0){
			GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::End;
			Audio::getInstance()->playSound(TIMEOVER);
			//������Ϸ����ʱ�¼���
			if (GAMEDATA::getInstance()->getReviveNum() == 0){
				CallAndroidMethod::getInstance()->requestEvent(4);
			}
			else if (GAMEDATA::getInstance()->getReviveNum() == 1){
				CallAndroidMethod::getInstance()->requestEvent(17);
			}
			else if (GAMEDATA::getInstance()->getReviveNum() == 2){
				CallAndroidMethod::getInstance()->requestEvent(16);
			}
			else if (GAMEDATA::getInstance()->getReviveNum() == 3){
				CallAndroidMethod::getInstance()->requestEvent(15);
			}
			else if(GAMEDATA::getInstance()->getReviveNum() == 4){
				CallAndroidMethod::getInstance()->requestEvent(14);
			}
			else{
				GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Ready;
				this->unscheduleAllCallbacks();
				Director::getInstance()->replaceScene(TransitionFade::create(1, GameResultScene::create()));
			}
		}
	}else if (GAMEDATA::getInstance()->gameState == GAMEDATA::GameState::Over){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Ready;
		this->unscheduleAllCallbacks();
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameResultScene::create()));
	}
}

void GameLayer::showTipPos(){
	if (tipPos[0] != -1 || tipPos[1] != -1){
		return;
	}

	if (clickitem[0] != -1){
		lights.at(0)->removeFromParent();
		items.at(0)->setScale(1);
		items.at(0)->cleanup();
		lights.popBack();
		items.popBack();
		clickitem[0] = -1;
	}
	tipPos = Matrix::getInstance()->getTipPOsition();
	if (tipPos[0] == -1){
		//û�п�����Ԫ��
	}
	else{
		doItemSelectAnima(getPosByPostion(tipPos[0]));
		doItemSelectAnima(getPosByPostion(tipPos[1]));
		
	}
}
void GameLayer::bombAnim(){
	//1:���ű�ը����
	auto boom = Sprite::create("bomb_1.png");
	boom->setPosition( getPosByPostion(clickitem[0]));
	this->addChild(boom);
	auto animation1 = Animation::create();
	for (int i = 1; i<7; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "bomb_%1d.png", i);
		animation1->addSpriteFrameWithFile(szName);
	}
	animation1->setDelayPerUnit(0.2f / 6);
	animation1->setRestoreOriginalFrame(true);

	auto am1 = Animate::create(animation1);
	auto act1 = Sequence::create(am1, FadeOut::create(0), nullptr);
	boom->runAction(act1);
	//2:�������ӽ��㶯��
	auto circle = Sprite::create("conn_circle_1.png");
	circle->setPosition(getPosByPostion(clickitem[0]));
	this->addChild(circle);
	auto animation2 = Animation::create();
	for (int i = 1; i<4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "conn_circle_%1d.png", i);
		animation2->addSpriteFrameWithFile(szName);
	}
	animation2->setDelayPerUnit(0.2f / 3);
	animation2->setRestoreOriginalFrame(true);

	auto am2 = Animate::create(animation2);
	auto act2 = Sequence::create(am2, FadeOut::create(0), nullptr);
	circle->runAction(act2);
	
	//3:���ű�ը����
	auto boom1 = Sprite::create("bomb_1.png");
	boom1->setPosition(getPosByPostion(clickitem[1]));
	this->addChild(boom1);
	auto animation3 = Animation::create();
	for (int i = 1; i<7; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "bomb_%1d.png", i);
		animation3->addSpriteFrameWithFile(szName);
	}
	animation3->setDelayPerUnit(0.2f / 6);
	animation3->setRestoreOriginalFrame(true);

	auto am3 = Animate::create(animation3);
	auto act3 = Sequence::create(am3, FadeOut::create(0), nullptr);
	boom1->runAction(act3);
	//4:�������ӽ��㶯��
	auto circle1 = Sprite::create("conn_circle_1.png");
	circle1->setPosition(getPosByPostion(clickitem[1]));
	this->addChild(circle1);
	auto animation4 = Animation::create();
	for (int i = 1; i<4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "conn_circle_%1d.png", i);
		animation4->addSpriteFrameWithFile(szName);
	}
	animation4->setDelayPerUnit(0.2f / 3);
	animation4->setRestoreOriginalFrame(true);

	auto am4 = Animate::create(animation4);
	auto act4 = Sequence::create(am4, FadeOut::create(0), nullptr);
	circle1->runAction(act4);

	clean.pushBack(boom);
	clean.pushBack(circle);
	clean.pushBack(boom1);
	clean.pushBack(circle1);
}
void GameLayer::onTouchEnded(Touch*touch, Event*event){
	if (GAMEDATA::getInstance()->gameState != GAMEDATA::GameState::Playing){
		return;
	}
	if (GAMEDATA::getInstance()->gettime() <=0){
		return;
	}
	int  x = touch->getLocation().x;
	int y = touch->getLocation().y;
	if (screentoIndex(x, y).at(0)<0 || screentoIndex(x, y).at(1)<0){
		return;
	}
	int pos2 = Matrix::getInstance()->getPositionByXAndY(screentoIndex(x, y).at(0), screentoIndex(x, y).at(1));
	Vec2 scenePos = getPosByPostion(pos2);
	
	if (pos2<0 || pos2 >= Matrix::getInstance()->ROW_NUM*Matrix::getInstance()->COL_NUM){
		//CCLOG("onTouchEnded pos2=%d over", pos2);
		return;
	}
	if (Matrix::getInstance()->getMartixCells().at(pos2)->getCellType() == NULL){
		//CCLOG("onTouchEnded pos2=%d is null", pos2);
		return;
	}

	if (clickitem[0] != -1 && clickitem[0] == pos2){
		//CCLOG("onTouchEnded pos2=%d touch already", pos2);
		return;
	}

	
	if (tipPos.size()>1 && tipPos[0] != tipPos[1]){
		//����ʾ
		lights.at(0)->removeFromParent();
		lights.at(1)->removeFromParent();
		lights.clear();
		tipPos[0] = tipPos[1] = -1;
	}
	
	//deal touch item animation
	auto slectedIcon = allElements.at(pos2);
	auto actionUp1 = Sequence::create(ScaleTo::create(0.25, 1.1, 1),
		ScaleTo::create(0.25, 0.9, 1), ScaleTo::create(0.25, 1, 1.01), ScaleTo::create(0.25, 1, 0.9), nullptr);
	slectedIcon->runAction(RepeatForever::create(actionUp1->clone()));
	
	if (clickitem[0] == -1){
		clickitem[0] = pos2;
		doItemSelectAnima(scenePos);
		items.pushBack(slectedIcon);
	}
	else
	{
		clickitem[1] = pos2;
		doItemSelectAnima(scenePos);
		items.pushBack(slectedIcon);
	}


	if (clickitem[0] != -1 && clickitem[1] != -1){
		if (Matrix::getInstance()->canRemoveElement(clickitem[0], clickitem[1])){
			//CCLOG("can remove");
			//����������߼�
			//1:��������,����������ʾ����
			dealConnectANim();
			bombAnim();
			//3:��������״̬�����������Ϣ
			clearClickState();
			//4:����ͳ����Ϣ
			removeCount += 2;
			
			//�ж��Ƿ��п�����Ԫ��
			if (removeCount == Matrix::getInstance()->COL_NUM*Matrix::getInstance()->ROW_NUM){
				//ȫ������
				//TODO:next map
				GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
				Audio::getInstance()->playSound(GAME_SUCCESS);
				schedule(schedule_selector(GameLayer::nextMap),0.5f, 0, 0);
				
			}
			else{
				if (!Matrix::getInstance()->hasRemoveElement()){
					resetMap();
				}
			}
			

		}
		else{
			//CCLOG("can not remove pos1=%d&pos2=%d", clickitem[0], clickitem[1]);
			lights.at(0)->removeFromParent();
			items.at(0)->setScale(1);
			items.at(0)->cleanup();
			Sprite *temp = lights.at(1);
			Sprite *temp1 = items.at(1);
			lights.popBack();
			items.popBack();
			lights.popBack();
			items.popBack();
			lights.pushBack(temp);
			items.pushBack(temp1);
			clickitem[0] = clickitem[1];
			clickitem[1] = -1;
		}
	}

}

void GameLayer::nextMap(float dt){
	
	GAMEDATA::getInstance()->setLevel(GAMEDATA::getInstance()->getLevel() + 1);
	if (GAMEDATA::getInstance()->getLevel() == 2){
		MARGIN_BOTTOM = 150;
		MARGIN_LEFT = 65;
		Matrix::getInstance()->ROW_NUM = 6;
		Matrix::getInstance()->COL_NUM = 5;
		
	}
	else{
		MARGIN_BOTTOM = 150;
		MARGIN_LEFT = 30;
		Matrix::getInstance()->ROW_NUM = 6;
		Matrix::getInstance()->COL_NUM = 6;
	}
	clickitem[0] = -1;
	clickitem[1] = -1;
	removeCount = 0;
	GAMEDATA::getInstance()->needResetMap = false;
	GAMEDATA::getInstance()->needTipPos = false;
	
	//���̳�ʼ��
	Matrix::getInstance()->initMatrix();
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();

	
	for (int i = 0; i < allBgElements.size();i++){
		allBgElements.at(i)->removeFromParent();
	}
	allBgElements.clear();
	allElements.clear();
	drawMapBg();
	for (int i = 0; i < allCells.size(); i++){
		//��ʼ�������ϻ������е�Ԫ��
		Vec2 pos = getPosByPostion(allCells.at(i)->getPosition());
		//int ת string
		string s = "item" + CCString::createWithFormat("%d", (allCells.at(i)->getCellType()-1))->_string + ".png";
		element = Sprite::create(s);
		element->setPosition(pos);
		element->setTag(allCells.at(i)->getCellType());
		this->addChild(element);
		allElements.pushBack(element);
	}
	schedule(schedule_selector(GameLayer::showMatrix),0, 0, 0);
	GAMEDATA::getInstance()->updateProcess = true;
}

vector<int> GameLayer::screentoIndex(float x, float y)
{

	int pos_x=-1;
	int pos_y=-1;

	for (int i = 0; i < Matrix::getInstance()->COL_NUM; i++){
		if ((x<=i* ELEMENT_WIDTH + ELEMENT_WIDTH + MARGIN_LEFT)&&
			(x>i* ELEMENT_WIDTH  + MARGIN_LEFT)){
			
			pos_x = i;
			break;
		}
	}

	for (int i = 0; i < Matrix::getInstance()->ROW_NUM; i++){
		if ((y <= i * ELEMENT_WIDTH + MARGIN_BOTTOM + ELEMENT_WIDTH)&&
			y > i* ELEMENT_WIDTH + MARGIN_BOTTOM){
			pos_y = i;
			break;
		}
	}
	vector<int> temp;
	temp.push_back(pos_x);
	temp.push_back(pos_y);

	if (pos_x != -1 && pos_y!=-1){
		if (pos_x < Matrix::getInstance()->COL_NUM && pos_y <  Matrix::getInstance()->ROW_NUM) {
			return temp;
		}
		else{
			return temp;
		}
	}
	else{
		return temp;
	}

}

void  GameLayer::deawLine(int x1, int y1, int x2, int y2,bool line){
	if (x1 == x2){
		float pos_x1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1,y1)).x;
		float pos_y1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1,y1)).y;

		if (!line){
			if (x1 == Matrix::getInstance()->COL_NUM - 1){
				pos_x1 += 65;
				deawLine(x1, y1, x1 + 1, y1,true);
				deawLine(x2, y2, x2 + 1, y2,true);
			}
			else if (x1 == 0){
				pos_x1 -= 65;
				deawLine(x1, y1, x1 - 1, y1, true);
				deawLine(x2, y2, x2 - 1, y2, true);
			}
		}
		auto DL = Sprite::create("conn_line_v_1.png");
		DL->setPosition(pos_x1, pos_y1 + (y2 - y1) * 35);
		if (y2 < 0 || y2 == Matrix::getInstance()->ROW_NUM){

			DL->setScaleY(0.15*(abs(y2 - y1)));
		}
		else{
			DL->setScaleY(0.18*(abs(y2 - y1)));
		}


		this->addChild(DL);
		auto animation22 = Animation::create();
		for (int i = 1; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "conn_line_v_%1d.png", i);
			animation22->addSpriteFrameWithFile(szName);
		}
		animation22->setDelayPerUnit(0.2f / 3);
		animation22->setRestoreOriginalFrame(true);
		auto animate2 = Animate::create(animation22);
		auto act1 = Sequence::create(animate2, FadeOut::create(0), nullptr);
		DL->runAction(act1);
	}
	else if (y1 == y2){
		float pos_x1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1, y1)).x;
		float pos_y1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1, y1)).y;

		if ((!line)){
			if (y1 == Matrix::getInstance()->ROW_NUM - 1){
				pos_y1 += 65;
				deawLine(x1, y1, x1, y1 + 1, true);
				deawLine(x2, y2, x2, y2 + 1, true);
			}
			else if (y1 == 0){
				pos_y1 -= 65;
				deawLine(x1, y1, x1, y1 - 1, true);
				deawLine(x2, y2, x2, y2 - 1, true);
			}
		}
		
		auto DL = Sprite::create("conn_line_h_1.png");
		DL->setPosition(pos_x1 + (x2 - x1) * 35, pos_y1);
		if (x2< 0 || x2 == Matrix::getInstance()->COL_NUM){

			DL->setScaleX(0.15*(abs(x2 - x1)));
		}
		else{
			DL->setScaleX(0.19*(abs(x2 - x1)));
		}


		this->addChild(DL);
		auto animation22 = Animation::create();
		for (int i = 1; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "conn_line_h_%1d.png", i);
			animation22->addSpriteFrameWithFile(szName);
		}
		animation22->setDelayPerUnit(0.2f / 3);
		animation22->setRestoreOriginalFrame(true);
		auto animate2 = Animate::create(animation22);
		auto act1 = Sequence::create(animate2, FadeOut::create(0), nullptr);
		DL->runAction(act1);
		
	
		
	}
}
void  GameLayer::dealConnectANim(){

	Audio::getInstance()->playSound(ELECTRICITY);
	
	std::vector<int> changePos = Matrix::getInstance()->getRoadChangePos();
	int x1 = Matrix::getInstance()->getXByCellPosition(clickitem[0]);
	int x2 = Matrix::getInstance()->getXByCellPosition(clickitem[1]);
	int y1 = Matrix::getInstance()->getYByCellPosition(clickitem[0]);
	int y2 = Matrix::getInstance()->getYByCellPosition(clickitem[1]);
	//CCLOG("changePos.size()=%d" , changePos.size());
	if (changePos.size()==0){
		//pos1,pos2ֱ��
		deawLine(x1, y1, x2, y2, true);
	}
	else if (changePos.size()==1){
		int x3 = Matrix::getInstance()->getXByCellPosition(changePos[0]);
		int y3 = Matrix::getInstance()->getYByCellPosition(changePos[0]);
		deawLine(x1, y1, x3, y3, true);
		deawLine(x3, y3, x2, y2, true);
	}
	else if (changePos.size() == 2){
		int x3 = Matrix::getInstance()->getXByCellPosition(changePos[0]);
		int y3 = Matrix::getInstance()->getYByCellPosition(changePos[0]);
		int x4 = Matrix::getInstance()->getXByCellPosition(changePos[1]);
		int y4 = Matrix::getInstance()->getYByCellPosition(changePos[1]);
		//CCLOG("deawLine x1=%d,x2=%d,x3=%d,x4=%d,y1=%d,y2=%d,y3=%d,y4=%d",x1,x2,x3,x4,y1,y2,y3,y4);
		if (x1==x3){
			if (y1!=y3){
				deawLine(x3, y3, x1, y1, true);
			}
			if (y2!= y4){
				deawLine(x4, y4, x2, y2, true);
			}
		}else if (x1==x4){
			if (y1 != y4){
				deawLine(x4, y4, x1, y1, true);
			}
			if (y2 != y3){
				deawLine(x3, y3, x2, y2, true);
			}
		}
		else if (y1 == y3){
			if (x1 != x3){
				deawLine(x3, y3, x1, y1, true);
			}
			if (x2 != x4){
				deawLine(x4, y4, x2, y2, true);
			}
		}
		else if (y1 == y4){
			if (x1 != x4){
				deawLine(x4, y4, x1, y1, true);
			}
			if (x2 != x3){
				deawLine(x3, y3, x2, y2, true);
			}
		}

		if (Matrix::getInstance()->boardLine){
			deawLine(x4, y4, x3, y3, false);
		}
		else{
			deawLine(x4, y4, x3, y3, true);
		}
	}

	//��ʾ������
	doubleHitCount++;
	
	if (doubleHitCount==1){
		Audio::getInstance()->playSound(CONN_1);
	}
	else if (doubleHitCount == 2){
		Audio::getInstance()->playSound(CONN_2);
	}
	else if (doubleHitCount == 3){
		Audio::getInstance()->playSound(CONN_3);
	}
	else if (doubleHitCount == 4){
		Audio::getInstance()->playSound(CONN_4);
	}
	else{
		Audio::getInstance()->playSound(CONN_5);
	}
	
	auto sprite2 = Sprite::create("game_conn_icon.png");
	sprite2->setPosition(280, 400);
	auto action = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(0),
		nullptr);
	sprite2->runAction(action);
	//int ת string
	CCString* ns = CCString::createWithFormat("%d", doubleHitCount);
	string s = ns->_string;

	auto sprite_num = LabelAtlas::create(s, "game_conn_txt.png", 41, 47, '0');
	sprite_num->setPosition(280+49, 375);
	auto action2 = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(0),
		nullptr);
	sprite_num->runAction(action2);
	addChild(sprite_num,10);
	addChild(sprite2,10);
	//����÷�
	GAMEDATA::getInstance()->setAchievescore(GAMEDATA::getInstance()->getAchievescore() + 40 * GAMEDATA::getInstance()->getLevel()*doubleHitCount);
	GAMEDATA::getInstance()->updateScore = true;

	if (doubleHitCount==1){
		//дһ��1.5s�Ķ�ʱ��
		schedule(schedule_selector(GameLayer::dealDoubleHit), 2.0f, 0, 0);
	}
}
	
void GameLayer::dealDoubleHit(float dt){
	doubleHitCount = 0;
}

