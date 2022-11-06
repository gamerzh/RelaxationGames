#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpClientUtill.h"
#include "lobby/LobbyScene.h"
USING_NS_CC;

struct SignItem
{
	int itemId;
	int num;
	SignItem(){};
	SignItem(int _itemid, int _num){ itemId = _itemid, num = _num; };
}; 

class SignMannger {
    
public:
	static SignMannger* getInstance();
	void sendRequest();
	std::vector<SignItem> getSignItems(){ return _signItems; };
	void clearSignItem(){ _signItems.clear(); };
	void setLobbyLayer(LobbyScene*layer){ _layer = layer; };
private:
	SignMannger();
	void HttpToPostRequestSign();
	void onHttpRequestCompletedForSign(HttpClient *sender, HttpResponse *response);
	static SignMannger* _instance;
	std::vector<SignItem> _signItems;
	LobbyScene*_layer;
};

