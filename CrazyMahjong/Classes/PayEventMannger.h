#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#define CC_SYNTHESIZELOCALINT(KeyName, funName,initValue)\
public: int get##funName(void) const { return UserDefault::getInstance()->getIntegerForKey(KeyName,initValue); }\
public: void set##funName(int var){ UserDefault::getInstance()->setIntegerForKey(KeyName,var); }



#define CC_SYNTHESIZELOCALFLOAT(KeyName, funName,initValue)\
public: float get##funName(void) const { return UserDefault::getInstance()->getFloatForKey(KeyName,initValue); }\
public: void set##funName(float var){ UserDefault::getInstance()->setFloatForKey(KeyName,var); }

enum EventToPoint
{
	Event_1 = 1,
	Event_2,
	Event_3,
	Event_4,
	Event_5,
	Event_6,
	Event_7,
	Event_8,
	Event_9,
	Event_10,
	Event_11,
	Event_12,
	Event_13,
	Event_14,
	Event_15
};
//����������������
//	json/event2pay.json
class PayEventMannger{
public:
	static PayEventMannger* getInstance();
private:
	PayEventMannger();
	static PayEventMannger* _instance;
	void init();
public:
	void RecordInfoOnGamestart();
	void RecordInfoOnGameend(bool IsDelevel, bool IsGainAlms, bool isWin, bool isCouldUpdateRoom);
	bool isSatisfied_Event_5(bool isPickGood);//һ�ֽ��������������˷������Ҹպ����꣬������ʾ
	bool isSatisfied_Event_8(bool isPickGood);//ʹ����ѷ����ƺ�ʤ��������
	bool isSatisfied_Event_9();//�״ν��뵯��
	bool isSatisfied_Event_10(int roomCoin);//���ҵ��ڷ�������������ֵʱ����
	bool isSatisfied_Event_7();//��һ�ֽ�������
	bool isSatisfied_Event_11();//ÿ��12�̣����û���δ���ѳɹ���������
	bool isSatisfied_Event_12();//�����һ���Ƿ��併��+��һ�ֽ�������ȼý�+��ҵ�ǰӮ+��ҵ�ǰ�Ľ�����������������䣬֮ǰ�Ѿ�2��������4��������������������
	bool isSatisfied_Event_13();//��ҵ����ʼ��Ϸ��ť�����Ҳ���1000������������ȼ����������¼���
	bool isSatisfied_Event_14();//�����һ���Ƿ��併��+��һ�ֽ�������ȼý�+��ҵ�ǰӮ+��ҵ�ǰ�Ľ�����������������䣬ÿ��һ������������4��������������������
	bool isSatisfied_Event_15();//������������+�����ƴ�������+��Ϸ�䣬���ϸ�Ҫ���ÿ3�̣�����
public://ͳ����Ϣ
	CC_SYNTHESIZELOCALINT("_Gamecount", Gamecount, 0); //��Ϸ����
	CC_SYNTHESIZELOCALINT("_IsPay", IsPay, 0); //�Ƿ�֧����
	CC_SYNTHESIZELOCALINT("_IsPay_Coin", IsPay_Coin, 0); //�Ƿ�֧�����������
	CC_SYNTHESIZELOCALINT("_IsPay_PickGood", IsPay_PickGood, 0); //�Ƿ�֧����������
	CC_SYNTHESIZELOCALINT("isSatisfied_Event_15_count", isSatisfied_Event_15_count, 0); //�Ƿ������¼���15�Ĵ���
	CC_SYNTHESIZELOCALINT("isSatisfied_Event_12or14_count", isSatisfied_Event_12or14_count, 0); //�����¼���12��14�Ĵ���

	CC_SYNTHESIZE(bool, isLastGameDelevel, _isLastGameDelevel);//��һ���Ƿ񽵼�
	CC_SYNTHESIZE(bool, isLastGainAlms, _isLastGainAlms);//��һ���Ƿ���ȡ���ȼý�

	CC_SYNTHESIZE(bool, isSatisfied_Event12, _isSatisfied_Event12);//�Ƿ�����Ʒѵ�12
	CC_SYNTHESIZE(bool, isSatisfied_Event14, _isSatisfied_Event14);//�Ƿ�����Ʒѵ�14
	CC_SYNTHESIZE(bool, isSatisfied_Event15, _isSatisfied_Event15);//�Ƿ�����Ʒѵ�15

};

	