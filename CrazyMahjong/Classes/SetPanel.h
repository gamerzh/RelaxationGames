#ifndef __SETPANEL_H__
#define __SETPANEL_H__

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

class SetPanel : public Node
{
public:
	CREATE_FUNC(SetPanel);
	
	void showPanel();

	MenuItem* btn = nullptr;
private:
	void hidePanel(Ref* pSender);
	bool init();
	float time = 0.1f;
	void slderEvent(Ref* pSender, SliderEventType type);

	void boxEventS(Ref* pSender, SliderEventType type);	// ʡ��
	void boxEventB(Ref* pSender, SliderEventType type);	// ��������
	void boxEventY(Ref* pSender, SliderEventType type);	// ��Ч
	void boxEventZ(Ref* pSender, SliderEventType type);	// ��
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

};
#endif