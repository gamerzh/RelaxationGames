#include "MonmetEightRoute.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
MonmetEightRoutedata* MonmetEightRoutedata::_pInstance = NULL;

MonmetEightRoutedata* MonmetEightRoutedata::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new MonmetEightRoutedata();
	}
	return _pInstance;
}

void MonmetEightRoutedata::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}
bool MonmetEightRoutedata::loadConfig()
{
	std::string filename = "config_route2.json";
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
		MonmentEightRoute newroute;
		rapidjson::Value &val = MotionConfig[i];
		auto tag = val["tag"].GetInt();
		newroute.startPos = Point(val["startPos"]["x"].GetDouble(), val["startPos"]["y"].GetDouble());
		auto &pointArray = val["routePoint"];
		MonmentEightRoutePoint* t = nullptr;
		newroute.head = nullptr;
		
		for (unsigned int j = 0; j < pointArray.Size(); j++)
		{
			auto &dict = pointArray[j];
			MonmentEightRoutePoint* p = new MonmentEightRoutePoint();
			p->moveState = dict["moveState"].GetInt();
			p->next = nullptr;
			switch (p->moveState)
			{
			case 1:
			{
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
				p->time = dict["time"].GetDouble();
				p->delay = dict["delay"].GetDouble();
				p->circleAngle = dict["circleAngle"].GetInt();
				p->ScaleDiff = dict["ScaleDiff"].GetInt();
				p->centrePos = Vec2(dict["centrePos"]["x"].GetDouble(), dict["centrePos"]["y"].GetDouble());
				p->isClockwise = dict["isClockwise"].GetBool();
			}
			break;
			case 3:
				p->delay = dict["delay"].GetDouble();
				p->aniName = dict["aniName"].GetString();
				break;
			case 4:
				p->curPos = Vec2(dict["endPos"]["x"].GetDouble(), dict["endPos"]["y"].GetDouble());
				p->besizerPos1 = Vec2(dict["bezierPos1"]["x"].GetDouble(), dict["bezierPos1"]["y"].GetDouble());
				p->besizerPos2 = Vec2(dict["bezierPos2"]["x"].GetDouble(), dict["bezierPos2"]["y"].GetDouble());
				p->delay = dict["delay"].GetDouble();
				p->time = dict["time"].GetDouble();
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

MonmentEightRoute MonmetEightRoutedata::getRouteBytag(int tag)
{
	return map_TagToRoute[tag];
}