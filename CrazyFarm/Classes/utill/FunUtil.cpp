#include "utill/FunUtil.h"


bool collision(Rect rectA, Rect rectB)
{
	const float scaleMultiple = 0.7;
	rectA.setRect(rectA.getMinX() + rectA.size.width / 2 * (1 - scaleMultiple), rectA.getMinY() + rectA.size.height / 2 * (1 - scaleMultiple), rectA.size.width*scaleMultiple, rectA.size.height*scaleMultiple);

	rectB.setRect(rectB.getMinX() + rectB.size.width / 2 * (1 - scaleMultiple), rectB.getMinY() + rectB.size.height / 2 * (1 - scaleMultiple), rectB.size.width*scaleMultiple, rectB.size.height*scaleMultiple);

	return rectA.intersectsRect(rectB);
}



bool collision(Sprite*spA, Sprite*spB)
{

	const float scaleMultiple = 0.7;
	auto rect1 = spA->getBoundingBox();
	rect1.setRect(rect1.getMinX() + rect1.size.width / 2 * (1 - scaleMultiple), rect1.getMinY() + rect1.size.height / 2 * (1 - scaleMultiple), rect1.size.width*scaleMultiple, rect1.size.height*scaleMultiple);
	auto rect2 = spB->getBoundingBox();
	rect2.setRect(rect2.getMinX() + rect2.size.width / 2 * (1 - scaleMultiple), rect2.getMinY() + rect2.size.height / 2 * (1 - scaleMultiple), rect2.size.width*scaleMultiple, rect2.size.height*scaleMultiple);

#if 0
	auto draw = DrawNode::create();
	addChild(draw, 10);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::YELLOW);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::RED);
#endif
	return rect1.intersectsRect(rect2);
}


float  getAngleByPos(Vec2 pos)
{
	auto k = (pos.y - 270.0) / (pos.x - 480);
	if (pos.x>480)
	{
		return 180+CC_RADIANS_TO_DEGREES(atan(k));
	}
	return CC_RADIANS_TO_DEGREES(atan(k));
}


Vec2 CalculateDiffMarginPos(Vec2 pos,float diff)
{
	if (pos.x<=0)
	{
		return Vec2(pos.x - diff, pos.y);
	}
	if (pos.x>=960)
	{
		return Vec2(pos.x + diff, pos.y);
	}
	if (pos.y>=540)
	{
		return Vec2(pos.x, pos.y + diff);
	}
	if (pos.y<=0)
	{
		return Vec2(pos.x, pos.y - diff);
	}

	return pos;
}



float getRandonNumByAtoB(float A, float B)
{	
	return  A + (B - A)*rand() / (float)RAND_MAX;
}

int getintRandonNumByAtoB(int A, int B, int interval)
{
	auto temp = (B - A) / interval+1;
	return A+interval*(rand()%temp);
}


int getCurrencyRankByRange(int startRank, int endRank, int startValue, int endValue, int curValue)
{
	float fTemp = ((float)curValue) / ((float)(endValue - startValue));
	auto currrRank = endRank - (endRank - startRank)*fTemp;
	return currrRank;
}

std::string SpliceDataForPostHttp(std::vector<std::string> strs)
{
	std::string s;
	for (auto var:strs)
	{
		s += "&";
		s += var.c_str();
	}
	return s;
}

std::string  SpliceDataForPostHttp(std::string str1, ...)
{
//	std:string s;
//	va_list args;
//	va_start(args, str1);
//
//	while (1){
//		auto s1 = va_arg(args, std::string);
//		if (s1 == "-1")
//		{
//			return s;
//		}
//		s += "&";
//		s += s1.c_str();
//	}
	return "";
}

std::string NewAtoI(int num)
{
	auto str = String::createWithFormat("%d", num);
	return str->getCString();
}
std::string NewAtoI(long num)
{
	auto str = String::createWithFormat("%ld", num);
	return str->getCString();
}


std::string myWrap(std::string str, int length)
{
	unsigned int beginPos = 0;  //�ַ����ĳ�ʼλ��
	std::string resultStr;		//���ص��ַ���


	std::vector<std::string > str_vec;  //����һ���ַ������͵�˳������
	do
	{
		str_vec.push_back(str.substr(beginPos, length)); //substr�������������Ƽ�������str�д�beginPos��length֮����ַ������������������������� 
		if (beginPos + length > str.size())
		{
			break;  //��Ҫ�ü��ĳ��ȳ���str�ĳ��ȣ����˳�ѭ��
		}
		else
		{
			beginPos += length;
		}

	} while (true);

	for (unsigned int i = 0; i < str_vec.size(); ++i)
	{
		resultStr.append(str_vec.at(i)).append("\n"); //��������һȡ��֮ǰ�ü��õ�һ�ζ��ַ������ֱ����ַ���������ϻ��з���append()���ƽ�ˮ����\nճ���ַ������� 
	}


	//   resultStr.pop_back();  //��һ���ǽ����һ�������\n��ɾ��


	return resultStr;
}

int getRandValueInVec(std::vector<int> vec)
{
	int size = vec.size();
	return vec.at(rand() % size);
}

Action* getForeverAcByNameAndInterval(const char* name, float interval)
{
	auto ac = RepeatForever::create(Sequence::create(DelayTime::create(interval), AnimationUtil::getInstance()->getAnimate(name), nullptr)); 
		return ac;

}

float getTurretRotation(Point start_pos, Point pos){
	//��������֮��ĽǶ�

	//float len_y = pos.y - start_pos.y;
	//float len_x = pos.x - start_pos.x;

	//float tan_yx = abs(len_y) / abs(len_x);
	//float angle = 0;
	//if (len_y > 0 && len_x < 0) {
	//	angle = atan(tan_yx) * 180 / 3.1415926 - 90;
	//}
	//else if (len_y > 0 && len_x > 0) {
	//	angle = 90 - atan(tan_yx) * 180 / 3.1415926;
	//}
	//else if (len_y < 0 && len_x < 0) {
	//	angle = -atan(tan_yx) * 180 / 3.1415926 - 90;
	//}
	//else if (len_y < 0 && len_x > 0) {
	//	angle = atan(tan_yx) * 180 / 3.1415926 + 90;
	//}
	return 270-CC_RADIANS_TO_DEGREES((start_pos-pos).getAngle());
	//CCLOG("********************");
	//CCLOG("pos A X:%f,Y:%f", start_pos.x, start_pos.y);
	//CCLOG("pos B X:%f,Y:%f", pos.x, pos.y);
	//CCLOG("angle : %f",angle);
	//CCLOG("********************");
	//return angle;
}

unsigned long getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
