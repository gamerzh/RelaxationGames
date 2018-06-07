#include "TeamFactory.h"
#include "json/document.h"
#include "json/rapidjson.h"

USING_NS_CC;
using namespace std;

#define RETURN_IF(cond)           if((cond)) return

TeamFactory* TeamFactory::m_instance = new TeamFactory();

TeamFactory* TeamFactory::getInstance()
{
	return m_instance;
}

std::vector<FootManTeam> TeamFactory::getFootManTeamVector() {

}

std::vector<FootManTeamProperty> TeamFactory::getFootManTeamPropertyVector() {
	//解析json,获取战队数据
	string data = FileUtils::getInstance()->getStringFromFile("team.json");
	RETURN_IF(NULL == data.c_str() || !data.compare(""));
	rapidjson::Document _mDoc;
	_mDoc.Parse<0>(data.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &code = _mDoc["team"];
}