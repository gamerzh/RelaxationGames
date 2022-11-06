#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct PayItem
{
	int ItemID;  //1���2��ʯ3����
	int ItemNum;
};
struct PayPointInfo {
	int paypoint_id;
	int price;
	std::vector<PayItem> items;
	std::string pay_point_desc;
};


class PayPointConfig {

public:
	PayPointConfig();
	static PayPointConfig* getInstance();

	bool LoadConfig();
	PayPointInfo getPayPointInfoById(int paypointId);
	int getVersion(){ return payversion; };
private:
	static PayPointConfig* _instance;
	std::vector<PayPointInfo> payPointInfos;
	int payversion;

};

