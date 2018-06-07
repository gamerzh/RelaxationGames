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


std::vector<FootManTeam*> TeamFactory::getFootManTeamVector() {
	if (footTeamVec.size == 0) {
		for (int i = 0; i < getFootManTeamPropertyVector().size(); i++) {
			auto team = new  FootManTeam();
			footTeamVec.push_back(team);
		}
	}
	return footTeamVec;
}

std::vector<FootManTeamProperty> TeamFactory::getFootManTeamPropertyVector() {
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
	//解析json,获取战队数据
	string data = FileUtils::getInstance()->getStringFromFile("team.json");
	RETURN_IF(NULL == data.c_str() || !data.compare(""));
	rapidjson::Document _mDoc;
	_mDoc.Parse<0>(data.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	if (_mDoc.HasMember("team")) {
		const rapidjson::Value &team = _mDoc["team"];
		for (int i = 0; i < team.Capacity(); i++) {
			const rapidjson::Value &tempteam = team[i];
			FootManTeamProperty property;
			if (tempteam.HasMember("teamId")) {
				property.teamId = tempteam["teamId"].GetInt();
			}
			if (tempteam.HasMember("teamName")) {
				property.teamName = tempteam["teamName"].GetString();
			}
			if (tempteam.HasMember("teamBanner")) {
				property.teamBanner = tempteam["teamBanner"].GetString();
			}
			if (tempteam.HasMember("footManVec")) {
				const rapidjson::Value &footVec = tempteam["footManVec"];
				for (int j = 0; j < footVec.Capacity(); j++)
				{
					const rapidjson::Value &tempfoot = footVec[i];
					FootManProperty manProperty;
					manProperty.name = tempfoot["name"].GetString();
					manProperty.footImage = tempfoot["footImage"].GetString();
					manProperty.runSpeed = tempfoot["runSpeed"].GetInt();
					manProperty.skillType = tempfoot["skillType"].GetInt();
					property.footManVec.push_back(manProperty);
				}
			}
			footManTeamPropertyVec.push_back(property);
		}
	}
	
} 