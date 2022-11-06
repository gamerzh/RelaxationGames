#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MenuScenePayHandler
{       
public:
	MenuScenePayHandler() {};
	~MenuScenePayHandler() {};  
	void dealEventSuccess();
	void dealEventFail();
	void dealEventClose();

	static MenuScenePayHandler* getInstance();
	void setHotDioagOver();

};
#endif

