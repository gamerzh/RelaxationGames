#include "NameMannger.h"
#include "ChineseWorld.h"
#include "User.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

std::vector < std::string> NameMannger::nameCache;
const std::string head = "NPC_NAME_%d";
void NameMannger::loadName()
{
	nameCache.clear();
	std::string  filename = "fonts/npcName.json";
	rapidjson::Document doc;
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	rapidjson::Value& itemList = doc["npcNameConfig"];
	for (unsigned int i = 0; i < itemList.Size();i++)
	{
		nameCache.push_back(itemList[i].GetString());
	}
}
std::string NameMannger::getName()
{
	static bool isInit = false;
	if (!isInit)
	{
		isInit = true;
		loadName();
	}
	int size = nameCache.size();
	if (size<=2)
	{
		loadName();
		size = nameCache.size();
	}
	while (true)
	{
		int num = rand()%(size-1);
		auto iter = nameCache.begin();
		std::advance(iter, num);
		std::string name = *iter;
		nameCache.erase(iter);
		if (name != User::getInstance()->getMyName())
		{
			return name;
		}
	}
}