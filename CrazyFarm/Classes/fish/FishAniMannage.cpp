#include "FishAniMannage.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
FishAniMannage* FishAniMannage::_pInstance = NULL;

FishAniMannage* FishAniMannage::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new FishAniMannage();
	}
	return _pInstance;
}

void FishAniMannage::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}
bool FishAniMannage::loadAniByJsonAndPlist(const char* jsonName, const char* plistName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName);
	rapidjson::Document doc;
	if (!FileUtils::getInstance()->isFileExist(jsonName))
	{
		return false;
	}

	std::string data = FileUtils::getInstance()->getStringFromFile(jsonName);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError())
	{
		return false;
	}

	rapidjson::Value& ani_list = doc["ani_list"];
	if (!ani_list.IsArray())
	{
		return false;
	}
	std::vector<std::string> anis;
	for (unsigned int i = 0; i < ani_list.Size(); ++i)
	{
		rapidjson::Value &ani = ani_list[i];
		rapidjson::Value &imgs = ani["ani_img"];
		Animation* animation = Animation::create();
		int numOfpng = imgs.Size();
		for (int i = 0; i < numOfpng; i++){
			auto spath = imgs[i].GetString();
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spath);
			animation->addSpriteFrame(frame);
		}
		animation->setDelayPerUnit((ani["ani_time"].GetDouble()) / numOfpng);



		auto sFishID = doc["fishID"].GetInt();
		auto aniName = String::createWithFormat("%s_%d", ani["ani_name"].GetString(), sFishID);
		AnimationCache::getInstance()->addAnimation(animation, aniName->getCString());
		anis.push_back(aniName->getCString());

	}
	map_FishidToAnis[doc["fishID"].GetInt()] = anis;
	return true;
}

Animate* FishAniMannage::getAnimate(const char *animatname){
	Animation* animation = AnimationCache::getInstance()->getAnimation(animatname);
	if (animation)
	{
		Animate* animate = Animate::create(animation);
		return animate;
	}
	return nullptr;
	
}

SpriteFrame* FishAniMannage::getSpriteById(int fishid)
{
	auto path = String::createWithFormat("%d_%d.png", fishid, 1);
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path->getCString());
	return frame;
}