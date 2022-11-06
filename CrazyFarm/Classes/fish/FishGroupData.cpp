#include "FishGroupData.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
FishGroupData* FishGroupData::_pInstance = NULL;

FishGroupData* FishGroupData::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new FishGroupData();
	}
	return _pInstance;
}

void FishGroupData::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}
bool FishGroupData::loadConfig()
{
	std::string filename = "config_fishgroup.json";
	rapidjson::Document doc;
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		return false;
	}

	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");
		return false;
	}
	rapidjson::Value& fishGroupConfig = doc["fishGroupConfig"];
	if (!fishGroupConfig.IsArray())
	{
		log("The data is not json");
		return false;
	}
	
	for (unsigned int i = 0; i < fishGroupConfig.Size(); i++)
	{	
		rapidjson::Value &val = fishGroupConfig[i];
		auto ttag = val["tag"].GetInt();
		auto &fishSinglegroup = val["fishgroup"];
		FishGroup fishgroup;
		fishgroup.tag = ttag;
		for (unsigned int j = 0; j < fishSinglegroup.Size(); j++)
		{
			auto &dict = fishSinglegroup[j];
			singleTypefishGroup  p ;
			p.fishID = dict["fishID"].GetInt();
			p.fishCount = dict["fishCount"].GetInt();
			p.fishRoute = dict["fishRoute"].GetInt();
			p.IntervalCreateTime = dict["IntervalCreateTime"].GetDouble();
			p.startPos = Vec2(dict["startPosX"].GetInt(), dict["startPosY"].GetInt());
			fishgroup.singleTypefishGroups.push_back(p);
		}
		map_TagToFishGroup[ttag] = fishgroup;
	}
	return true;
}

FishGroup FishGroupData::getGroupBytag(int tag)
{
	return map_TagToFishGroup[tag];
}