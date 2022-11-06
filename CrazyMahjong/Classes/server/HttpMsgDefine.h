#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define TIMEOUT 404
struct RewardValue 
{
	int _itemid;
	int _num;
	RewardValue(int itemid, int num){ _itemid = itemid, _num = num; };
	RewardValue(){};
};
struct CDkeyValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> _rewards;

};
struct LoginValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;
	std::string _downurl;

};
struct RegisterValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;
	std::vector<RewardValue> rewards;
	std::string _downurl;
};

struct FirstRegisterValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	std::string _sesssionid;
	std::vector<RewardValue> rewards;
	std::string username;
	std::string _downurl;
};
struct SetNameValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
};
struct OpenBoxValue :public Ref
{
	int _errorcode;
	std::string _errormsg;
	int  _reward_coins;
	int _chestLevel;
};

struct MissionListItem
{
	int mission_id;
	std::string task_content;
	std::string tast_content_url_pic;
	std::vector<RewardValue> rewards;
	int to_page;
	int require_nums;
	int current_nums;
	bool isReceive;
};
struct AchieveListItem
{
	int tag = 1;
	int mission_id;
	std::string task_content;
	std::string tast_content_url_pic;
	std::string tast_icon_url_pic;
	std::vector<RewardValue> rewards;
	int max_level;//任务最大等级
	int current_level;//任务当前级别

	int to_page;
	int require_nums;
	int current_nums;
	bool isReceive;
};



struct MissionListValue 
{
	int _errorcode;
	std::string _errormsg;
	std::vector<MissionListItem> MissionItems;
};

struct MissionRewardValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> rewards;
};

struct AchieveRewardValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> rewards;
	AchieveListItem _new_task_item;
};

struct AchieveListValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<AchieveListItem> AchieveItems;
};


struct ActivedValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<std::string> imgUrls;

};



struct GuizuRewardValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> rewards;
};


struct UserInfoValue
{
	int _errorcode;
	std::string _errormsg;
	unsigned long _coins;
	int _exps;
	unsigned long _diamonds;
	int _maxTurrentLv;
	int _chargemoney;
	int _chestLevel;
	//首冲相关
	int mo_coins;
	int mo_first;
};



////-----------------------------pay--------------------------
struct OverBookValue 
{
	int _errorcode;
	std::string _errormsg;
	std::string orderID;
	/////微信支付
	std::string wx_prepayid ;
	std::string wx_sign;
	std::string wx_timestamp ;
	std::string wx_nonceStr;
};

struct DemandOrderValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> rewards;
	int realprice;
};
////-----------------------------pay--------------------------

struct BagItemValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> itemLists;
};

struct BuyBagItemValue
{
	int _errorcode;
	std::string _errormsg;
	int costDmNum;
	int buyItemNum;
};


struct RoomItem
{
	int roomid;
	int playerNum;
	int requireTurrentLv;

};
struct RoomInfoValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RoomItem> _roomitems;

};


struct GetVipCoinValue
{
	int _errorcode;
	std::string _errormsg;
	long coins;
};


struct changGiftValue
{
	int _errorcode;
	std::string _errormsg;
}; 
struct RecordGiftItem
{
	int _date;
	std::string reward_desc;
	std::string change_state;
};
struct RecordGiftValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RecordGiftItem> _items;
};


struct EmailListItem
{
	int mailbox_id;
	std::string email_title;
	std::string email_content;
	std::vector<RewardValue> email_rewards;
	int email_create_time;
	bool isRead ;
};


struct EmailListValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<EmailListItem> _emailListItems;
};

struct EmailRewardValue
{
	int _errorcode;
	std::string _errormsg;
	std::vector<RewardValue> rewards;
};

struct SendPresentValue
{
	int _errorcode;
	std::string _errormsg;
	RewardValue rewards;
};
struct WXShareInfoValue
{
	int _errorcode;
	int hongbao_key;
	std::string shareTitle;
	std::string shareContent;
	std::string shareUrl;
	std::string _errormsg;
	RewardValue rewards;
};
