#include "MsgHelp.h"
Msg_Base*MsgHelp::getInfoByMsg(const char* msgId, const char* msgBody)
{
	Msg_Base* base = nullptr; 
	if (!msgBody)
	{
		return nullptr;
	}
	if (strcmp(msgId, "conError") == 0)
	{
		//断开连接
		base = new Msg_ConError();
		base->setBody(msgBody);
		base->setMsgId(MsgConError);
		
	}
	if (strcmp(msgId, "init") == 0)
	{
		//客户端初始化
		base = new Msg_onInit();
		base->setBody(msgBody);
		base->setMsgId(MsgInit);
		
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		//某人进来
		base = new Msg_onAdd();
		base->setBody(msgBody);
		base->setMsgId(MsgOnAdd);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//某人离开
		base = new Msg_onLeave();
		base->setBody(msgBody);
		base->setMsgId(MsgOnLeave);
		
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		
		//鱼群下发
		base = new Msg_OnFishes();
		base->setBody(msgBody);
		base->setMsgId(MsgOnFishes);

	}
	if (strcmp(msgId, "level_update") == 0)
	{
		//炮塔升级
		base = new Msg_OnUpdateTurrent();
		base->setBody(msgBody);
		base->setMsgId(MsgOnUpdateTurrent);

	}
	if (strcmp(msgId, "expUpdate") == 0)
	{
		//人物升级
		base = new Msg_OnExpUpdate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnExpUpdate);

	}
	if (strcmp(msgId, "useSkill") == 0)
	{
		//使用技能
		base = new Msg_UseSkill();
		base->setBody(msgBody);
		base->setMsgId(MsgUseSkill);

	}
	if (strcmp(msgId, "BonuspoolInfo") == 0)
	{
		//同步奖池信息
		base = new Msg_OnGetBounsPool();
		base->setBody(msgBody);
		base->setMsgId(MsgOnGetBounsPool);

	}
	if (strcmp(msgId, "LuckDraw") == 0)
	{
		//抽奖
		base = new Msg_LuckDraw();
		base->setBody(msgBody);
		base->setMsgId(MsgLuckDraw);

	}
	if (strcmp(msgId, "magnate") == 0)
	{
		//赠送
		base = new Msg_OnMagnate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMagnate);

	}
	if (strcmp(msgId, "bankruptBroke") == 0)
	{
		//破产箱子
		base = new Msg_OnBankrupt();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBankrupt);

	}
	if (strcmp(msgId, "bankruptRebirth") == 0)
	{
		//破产领取
		base = new Msg_OnBankruptRebirth();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBankruptRebirth);

	}
	if (strcmp(msgId, "payresult") == 0)
	{
		//支付结果
		base = new Msg_Payresult();
		base->setBody(msgBody);
		base->setMsgId(MsgPayresult);

	}
	if (strcmp(msgId, "boss") == 0)
	{
		//boss鱼死掉落
		base = new Msg_OnBossDead();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBossDead);

	}
	if (strcmp(msgId, "marquee") == 0)
	{
		//跑马灯
		base = new Msg_OnMarquee();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMarquee);

	}
	if (strcmp(msgId, "mermaidTask") == 0)
	{
		//美人鱼开始
		base = new Msg_OnBeginMarried();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBeginMarried);

	}
	if (strcmp(msgId, "updateMermaid") == 0)
	{
		//美人鱼任务更新
		base = new Msg_OnCatchMarriedFish();
		base->setBody(msgBody);
		base->setMsgId(MsgOnCatchMarriedFish);

	}
	if (strcmp(msgId, "successMermaid") == 0)
	{
		//美人鱼任务成功
		base = new Msg_OnMarriedSuccess();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMarriedSuccess);

	}
	return base;
}
