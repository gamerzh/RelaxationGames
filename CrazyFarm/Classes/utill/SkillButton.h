/** 
    ʵ�ּ�����ȴЧ�� 

    Notice:���childʱҪע�����²��ϵ
    ���·��ǰ�ť ����ǰ�͸����ģ��ͼƬ ���Ϸ���CCProgressTimer����������
*/
#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
#include "lobby/shop/payLayer.h"
#include "domain/logevent/LogEventUseSkill.h"
USING_NS_CC;
class SkillButton : public Node
{
public:
    SkillButton();
    virtual ~SkillButton();

    /** ����һ��SkillButton����
        */
    static SkillButton* createSkillButton(int skillID,
                                        const char* stencil_file_name, 
                                        const char* button_normal_name, 
                                        const char* button_click_name
										);

	void setEnable(bool isEnable){ mItemSkill->setEnabled(isEnable); };
	/** ���ܰ�ť����ص� */
	virtual void    skillClickCallBack(Ref* obj);
	void skillButonUi(int cdTime);

protected:
	void useSkill();

	void ToPayShopCallBack(Ref*psend);
   void update(float dt);
    /** ������ȴ��ϻص�*/
   virtual void    skillCoolDownCallBack();
   void LackVipCallBack(Ref*psend);

   virtual int  JudgeUseSkill();  //-1����ʹ�ã�1��vip�ȼ����㣬2�������ȼ����� 3:���Ϲ������� 0��ֱ��ʹ��
   /** ��ʼ�� */
   bool    init(int skillID, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);
	int m_skillID;
private:
    MenuItemImage*   mItemSkill;     // ���ܰ�ť
    Menu*            mMenuSkill;     // ���ܰ�ť����menu
    Sprite*          mStencil;       // �ɰ徫��,��ɫ��͸��(�����Ϊ����ʾһ����ȴ��ʱЧ��)
    ProgressTimer*   mProgressTimer; // ʱ�����������(360����ת)
    float            mCDTime;          // CDʱ��
	
	
};


#endif
