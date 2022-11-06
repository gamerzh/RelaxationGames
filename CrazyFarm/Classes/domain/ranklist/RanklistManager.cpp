#include "domain/ranklist//RanklistManager.h"
#include "server/HttpClientUtill.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#include "server/HttpMannger.h"

#define RANKLISTINCOIN "/player/rank/coin"
#define RANKLISTINEXP "/player/rank/exp"
RanklistManager* RanklistManager::_instance = NULL;

RanklistManager::RanklistManager(){

}
RanklistManager* RanklistManager::getInstance(){
    if(_instance == NULL){
		_instance = new RanklistManager();
    }
    return _instance;
}

void RanklistManager::loadCoin()
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, RANKLISTINCOIN);
	HttpClientUtill::getInstance()->onGetHttp(url->getCString(), CC_CALLBACK_2(RanklistManager::onHttpRequestCompletedForCoin, this));
}
void RanklistManager::loadExp()
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, RANKLISTINEXP);
	HttpClientUtill::getInstance()->onGetHttp(url->getCString(), CC_CALLBACK_2(RanklistManager::onHttpRequestCompletedForExp, this));
}

void RanklistManager::onHttpRequestCompletedForExp(HttpClient *sender, HttpResponse *response)
{

	RanklistValue* value = new RanklistValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = 404;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = 404;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back ranklist cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = 404;
			break;
		}

		int result = 0;
		value->_errorcode = result;
		if (result == 0)
		{
			auto &vec = doc["ranklist"];
			for (unsigned int i = 0; i < vec.Size(); i++)
			{
				rankListItem item;
				item.name = vec[i]["name"].GetString();
				item.vipLevel = vec[i]["vip"].GetInt();
				item.exp = vec[i]["exp"].GetDouble();
				item.coin = vec[i]["coins"].GetDouble();
				item.gender = vec[i]["gender"].GetInt();
				value->_rankItems.push_back(item);
			}
			vec = doc["rankrule"];
			for (unsigned int i = 0; i < vec.Size(); i++)
			{
				rankRange item;
				item.rank_start = vec[i]["rank_start"].GetDouble();
				item.rank_end = vec[i]["rank_end"].GetDouble();
				item.value_start = vec[i]["coin_start"].GetDouble();
				item.value_end = vec[i]["coin_end"].GetDouble();
				value->_rankRange.push_back(item);
			};
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_ranklist_exp_info");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void RanklistManager::onHttpRequestCompletedForCoin(HttpClient *sender, HttpResponse *response)
{

	RanklistValue* value = new RanklistValue();
	while (1)
	{
		if (!response)
		{
			value->_errorcode = 404;
			break;
		}
		if (!response->isSucceed())
		{
			value->_errorcode = 404;
			break;
		}
		long statusCode = response->getResponseCode();
		// dump data
		std::vector<char> *buffer = response->getResponseData();
		auto temp = std::string(buffer->begin(), buffer->end());
		log("http back ranklist cb  info: %s", temp.c_str());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			value->_errorcode = 404;
			break;
		}

		int result = 0;
		value->_errorcode = result;
		if (result == 0)
		{
			auto &vec = doc["ranklist"];
			for (unsigned int i = 0; i < vec.Size(); i++)
			{
				rankListItem item;
				item.name = vec[i]["name"].GetString();
				item.vipLevel = vec[i]["vip"].GetInt();
				item.exp = vec[i]["exp"].GetDouble();
				item.coin = vec[i]["coins"].GetDouble();
				item.gender = vec[i]["gender"].GetInt();
				value->_rankItems.push_back(item);
			}
			vec = doc["rankrule"];
			for (unsigned int i = 0; i < vec.Size(); i++)
			{
				rankRange item;
				item.rank_start = vec[i]["rank_start"].GetDouble();
				item.rank_end = vec[i]["rank_end"].GetDouble();
				item.value_start = vec[i]["coin_start"].GetDouble();
				item.value_end = vec[i]["coin_end"].GetDouble();
				value->_rankRange.push_back(item);
			};
		}
		else
		{
			value->_errormsg = doc["errormsg"].GetString();
		}
		break;
	}
	EventCustom event("get_ranklist_coin_info");
	event.setUserData(value);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
int RanklistManager::getRankByCoinForMyself(int coin)
{
	
	return getRankByCoin(coin);
}

int RanklistManager::getRankByCoin(int coin)
{
	///如果下达排行榜中有自己
	auto name = User::getInstance()->getUserName();
	for (int i = 0; i < rankItemsByCoin.size(); i++)
	{
		if (!rankItemsByCoin[i].name.compare(name))
		{
			return i+1;
		}
	}
	//没自己
	rankRange range;
    for (auto var:_rankCoinRange)
    {
		if (coin>=var.value_start&&coin<=var.value_end)
		{
			range = var;
			break;
		}
    }
	return getCurrencyRankByRange(range.rank_start, range.rank_end, range.value_start, range.value_end, coin);

}
int RanklistManager::getRankByExp(int exp)
{
	///如果下达排行榜中有自己
	auto name = User::getInstance()->getUserName();
	for (int i = 0; i < rankItemsByExp.size(); i++)
	{
		if (!rankItemsByExp[i].name.compare(name))
		{
			return i+1;
		}
	}
	///没自己
	rankRange range;
	for (auto var : _rankExpRange)
	{
		if (exp >= var.value_start&&exp <= var.value_end)
		{
			range = var;
			break;
		}
	}
	return getCurrencyRankByRange(range.rank_start, range.rank_end, range.value_start, range.value_end, exp);
}