#include "MenuScenePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"
#include "GameGuiLayer.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}

void  MenuScenePayHandler::dealRewardProp(int propId, int propNum){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventSuccess propId=%d,propNum=%d", propId,propNum);
#endif
	switch (propId)
	{
	case 1://�������?
		GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() + propNum);
		break;
	case 2://���ŵ���
		GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() + propNum);
		GAMEDATA::getInstance()->updateBtnInfo = true;
		break;
	case 3://��ʱ����
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() + propNum);
		GAMEDATA::getInstance()->updateBtnInfo = true;
		break;
	case 4://��ʾ����
		GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + propNum);
		GAMEDATA::getInstance()->updateBtnInfo = true;
		break;
	case 7:
		//�����¿�
		GAMEDATA::getInstance()->setMonthCard(true);
		GAMEDATA::getInstance()->setFirstPay(false);
		break;
	default:
		break;
	}
}
void  MenuScenePayHandler::dealEventClose(int eventId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventClose eventId=%d", eventId);
#endif
	if (eventId == 1 || eventId == 2 || eventId == 3 || eventId == 5 || eventId == 6 || eventId == 7 ||
		eventId == 25 || eventId == 26 || eventId == 27 || eventId == 28 || eventId == 29 || eventId == 30 || eventId == 31){
		CallAndroidMethod::getInstance()->requestEvent(18);
	}else if (eventId == 4 || eventId == 14 || eventId == 15 || eventId == 16 || eventId == 17){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Over;
	}
	else if (eventId == 11){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
	}
	else  if (eventId == 32){

	}
	else{
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
	}
}
void MenuScenePayHandler::dealEventSuccess(int eventId, int propIds[], int propNums[], int count){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventSuccess eventId=%d", eventId);
#endif
	CCLOG("dealEventSuccess eventId=" + eventId);
	for (int i = 0; i < count; i++){
		dealRewardProp(propIds[i], propNums[i]);
	}

	if (eventId == 1 || eventId == 2){
		
		CallAndroidMethod::getInstance()->requestEvent(18);
	}else if( eventId == 3 || eventId == 5 || eventId == 6 || eventId == 7 ||
		eventId == 25 || eventId == 26 || eventId == 27 || eventId == 28 || eventId == 29|| eventId ==30|| eventId == 31){

		GAMEDATA::getInstance()->setFirstPay(false);
		CallAndroidMethod::getInstance()->requestEvent(18);
	}
	else if (eventId == 4 || eventId == 14 || eventId == 15 || eventId == 16 || eventId == 17){
		GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() - 1);
		//�ָ���Ϸʱ��
		if (GAMEDATA::getInstance()->getLevel() == 1){
			GAMEDATA::getInstance()->settime(10);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 2){
			GAMEDATA::getInstance()->settime(15);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 3){
			GAMEDATA::getInstance()->settime(20);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 4){
			GAMEDATA::getInstance()->settime(20);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 5){
			GAMEDATA::getInstance()->settime(25);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 6){
			GAMEDATA::getInstance()->settime(20);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 7){
			GAMEDATA::getInstance()->settime(30);
		}
		else if (GAMEDATA::getInstance()->getLevel() == 8){
			GAMEDATA::getInstance()->settime(25);
		}
		else{
			GAMEDATA::getInstance()->settime(20);
		}

		//������Ϸ
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
		GAMEDATA::getInstance()->updateTimeInfo = true;
		GAMEDATA::getInstance()->updateProcess = true;
	}
	else if (eventId == 12 || eventId == 13|| eventId == 18 || eventId == 19 || eventId == 20 ||
		eventId == 21 || eventId == 22 || eventId == 23 || eventId == 24){
		if (eventId == 12 || eventId == 13){
			//����ʹ��һ�μ�ʱ��,���ѼƷѵ�
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime()+20);
			GAMEDATA::getInstance()->updateBtnInfo = true;
			GAMEDATA::getInstance()->updateProcess = true;
		}
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
	}else  if (eventId == 8 ){//������ʾ,����ʹ��һ��
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
		GAMEDATA::getInstance()->useTipProp = true;
	}else  if (eventId == 9){//��������,����ʹ��һ��
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
		GAMEDATA::getInstance()->useResetProp = true;
	}else  if (eventId == 10){//������?����ʹ��һ��
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
		GAMEDATA::getInstance()->useAddProps = true;
	}
	else  if (eventId == 11){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
		GAMEDATA::getInstance()->updateBtnInfo = true;
	}
	else  if (eventId == 32){
	 
	}
	else{
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
	}

	Audio::getInstance()->playSound(PAY_RESULT_SUCCESS);
}

void MenuScenePayHandler::dealEventFail(int eventId){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLog("dealEventFail eventId=%d",eventId);
#endif
	if (eventId == 1 || eventId == 2 || eventId == 3 || eventId == 5 || eventId == 6 || eventId == 7 ||
		eventId == 25 || eventId == 26 || eventId == 27 || eventId == 28 || eventId == 29 || eventId == 30 || eventId == 31){
		CallAndroidMethod::getInstance()->requestEvent(18);
	}else if (eventId == 4 || eventId == 14 || eventId == 15 || eventId == 16 || eventId == 17){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Over;
	}
	else if (eventId == 11){
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
	}
	else  if (eventId == 32){

	}
	else{
		if (eventId == 12 || eventId == 13){
			//����ʹ��һ�μ�ʱ��
			GAMEDATA::getInstance()->updateProcess = true;
		}
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
	}
	Audio::getInstance()->playSound(PAY_RESULT_FAIL);
}

void MenuScenePayHandler::setMoreGameState(bool isOpen){
	GAMEDATA::getInstance()->openMoreGame = isOpen;
}


void MenuScenePayHandler::setTehuiState(bool isOpen){
	GAMEDATA::getInstance()->openTehui = isOpen;
}
