/** 
    实现技能冷却效果 

    Notice:添加child时要注意上下层关系
    最下方是按钮 其次是半透明的模版图片 最上方是CCProgressTimer进度条精灵
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

    /** 创建一个SkillButton对象
        */
    static SkillButton* createSkillButton(int skillID,
                                        const char* stencil_file_name, 
                                        const char* button_normal_name, 
                                        const char* button_click_name
										);

	void setEnable(bool isEnable){ mItemSkill->setEnabled(isEnable); };
	/** 技能按钮点击回调 */
	virtual void    skillClickCallBack(Ref* obj);
	void skillButonUi(int cdTime);

protected:
	void useSkill();

	void ToPayShopCallBack(Ref*psend);
   void update(float dt);
    /** 技能冷却完毕回调*/
   virtual void    skillCoolDownCallBack();
   void LackVipCallBack(Ref*psend);

   virtual int  JudgeUseSkill();  //-1不能使用，1：vip等级不足，2：炮塔等级不够 3:符合购买条件 0：直接使用
   /** 初始化 */
   bool    init(int skillID, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);
	int m_skillID;
private:
    MenuItemImage*   mItemSkill;     // 技能按钮
    Menu*            mMenuSkill;     // 技能按钮所在menu
    Sprite*          mStencil;       // 蒙板精灵,黑色半透明(这个是为了显示一个冷却计时效果)
    ProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)
    float            mCDTime;          // CD时间
	
	
};


#endif
