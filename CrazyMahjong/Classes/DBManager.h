#pragma once

#include "cocos2d.h"
USING_NS_CC;

/************************************************************************/
/* ���ݿ��������                                                     */
/************************************************************************/

class DBManager
{


public:
	static DBManager* GetInstance();
	~DBManager(void);

	
public:	//��������

	//��ȡ������������
	float GetBgmVolume();

	//���ñ�����������
	void SetBgmVolume(float volume);


public:
	int GetDayGameTimes();
	void AddDayGameTimes();
	void initDayGameTimes();

public:	//�Ʒѵ����
	CC_SYNTHESIZE(int, _longLineEventCount, LongLineEventCount);

	//�

	CC_SYNTHESIZE(std::string, HDname, HDNAME);
	bool  getISTaskSuccess();
private:
	DBManager(void);

};

