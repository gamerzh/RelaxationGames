#include "FishRouteData.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
FishRouteData* FishRouteData::_pInstance = NULL;

FishRouteData* FishRouteData::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new FishRouteData();
	}
	return _pInstance;
}

void FishRouteData::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}
bool FishRouteData::loadConfig()
{
	std::string filename = "config_route.json";
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
	rapidjson::Value& MotionConfig = doc["MotionConfig"];
	if (!MotionConfig.IsArray())
	{
		log("The data is not json");
		return false;
	}
	
	for (unsigned int i = 0; i < MotionConfig.Size(); i++)
	{	
		Route newroute;
		rapidjson::Value &val = MotionConfig[i];
		auto tag = val["tag"].GetInt();
		auto &pointArray = val["routePoint"];
		RoutePoint* t = nullptr;
		newroute.head = nullptr;
		for (unsigned int j = 0; j < pointArray.Size(); j++)
		{
			auto &dict = pointArray[j];
			RoutePoint* p = new RoutePoint();
			p->moveState = dict["moveState"].GetInt();
			p->next = nullptr;
			switch (p->moveState)
			{
			case 1:
			{
				p->isRepeat = dict["isRepet"].GetInt();
				p->time = dict["time"].GetDouble();
				p->delay = dict["delay"].GetDouble();
				
				p->MoveByPos = Vec2(dict["MoveByPos"]["x"].GetDouble(), dict["MoveByPos"]["y"].GetDouble());
				/*auto &arraypoints = dict["ArrayPos"];
				auto size = arraypoints.Size();*/
				/*	p->pointarray = PointArray::create(30);
					p->pointarray->retain();
					for (unsigned int k = 0; k < arraypoints.Size();k++)
					{
					p->pointarray->addControlPoint(Vec2(arraypoints[k]["x"].GetDouble(), arraypoints[k]["y"].GetDouble()));
					}*/
				
			}
				break;
			case 2:
			{
				p->isRepeat = dict["isRepet"].GetInt();
				p->time = dict["time"].GetDouble();
				p->delay = dict["delay"].GetDouble();
				p->circleAngle = dict["circleAngle"].GetInt();
				p->ScaleDiff = dict["ScaleDiff"].GetInt();
				p->centrePos = Vec2(dict["circleX"].GetInt(), dict["circleY"].GetInt());
				p->isClockwise = dict["isClockwise"].GetBool();
			}
			break;
			case 3:
				p->isRepeat = dict["isRepet"].GetInt();
				p->delay = dict["delay"].GetDouble();
				p->aniName = dict["aniName"].GetString();
				break;

			default:
				break;
			}
			if (newroute.head == nullptr)
			{
				newroute.head = p;
			}
			else
			{
				t->next = p;
			}
			t = p;
		}
		map_TagToRoute[tag] = newroute;
	}
	return true;
}

Route FishRouteData::getRouteBytag(int tag)
{
	return map_TagToRoute[tag];
}