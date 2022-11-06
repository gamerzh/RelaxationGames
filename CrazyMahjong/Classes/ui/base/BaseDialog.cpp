#include "BaseDialog.h"

bool BaseDialog::init(){
	if (!Layer::init()){
		return false;
	}
	drawDialog();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(BaseDialog::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	return true;
}

void BaseDialog::drawDialog(){

}

void BaseDialog::closeView(){
	this->removeFromParent();
}

bool BaseDialog::onTouchBegan(Touch *touch, Event  *event){
	return true;
}
