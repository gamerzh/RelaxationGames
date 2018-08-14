#include "TeamInfoFactory.h"
#include "json/document.h"
#include "json/rapidjson.h"

USING_NS_CC;
using namespace std;

#define RETURN_IF(cond)    if((cond)) return

TeamInfoFactory * TeamInfoFactory::m_instance = new TeamInfoFactory();

TeamInfoFactory* TeamInfoFactory::getInstance()
{
	return m_instance;
}


std::vector<FootManTeamProperty> TeamInfoFactory::getFootManTeamPropertyVector() {
	if (footManTeamPropertyVec.size() == 0) {
		string data = FileUtils::getInstance()->getStringFromFile("team.json");
		if (NULL != data.c_str() && data.compare("")) {
			rapidjson::Document _mDoc;
			_mDoc.Parse<0>(data.c_str());
			if (!_mDoc.HasParseError() && _mDoc.IsObject()) {
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
                        if (tempteam.HasMember("energyRate")) {
                            property.energyRate = tempteam["energyRate"].GetFloat();
                        }
						if (tempteam.HasMember("footManVec")) {
							const rapidjson::Value &footVec = tempteam["footManVec"];
							for (int j = 0; j < footVec.Capacity(); j++)
							{
								const rapidjson::Value &tempfoot = footVec[j];
								FootManProperty manProperty;
								manProperty.goalkeeper = tempfoot["goalkeeper"].GetBool();
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
		}
	}
	return footManTeamPropertyVec;
}

FootManTeamProperty TeamInfoFactory::getTeamPropertyById(int teamId) {
	for (auto var : getFootManTeamPropertyVector()) {
		if (var.teamId == teamId) {
			return var;
		}
	}
	log("TeamFactory->getTeamPropertyById : can't find this teamId");
	FootManTeamProperty property;
	return property;
}
