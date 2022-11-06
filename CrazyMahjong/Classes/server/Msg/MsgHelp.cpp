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
		//�Ͽ�����
		base = new Msg_ConError();
		base->setBody(msgBody);
		base->setMsgId(MsgConError);
		
	}
	if (strcmp(msgId, "init") == 0)
	{
		//�ͻ��˳�ʼ��
		base = new Msg_onInit();
		base->setBody(msgBody);
		base->setMsgId(MsgInit);
		
	}
	if (strcmp(msgId, "onAdd") == 0)
	{
		//ĳ�˽���
		base = new Msg_onAdd();
		base->setBody(msgBody);
		base->setMsgId(MsgOnAdd);
	}
	if (strcmp(msgId, "onLeave") == 0)
	{
		//ĳ���뿪
		base = new Msg_onLeave();
		base->setBody(msgBody);
		base->setMsgId(MsgOnLeave);
		
	}
	if (strcmp(msgId, "onFishes") == 0)
	{
		
		//��Ⱥ�·�
		base = new Msg_OnFishes();
		base->setBody(msgBody);
		base->setMsgId(MsgOnFishes);

	}
	if (strcmp(msgId, "level_update") == 0)
	{
		//��������
		base = new Msg_OnUpdateTurrent();
		base->setBody(msgBody);
		base->setMsgId(MsgOnUpdateTurrent);

	}
	if (strcmp(msgId, "expUpdate") == 0)
	{
		//��������
		base = new Msg_OnExpUpdate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnExpUpdate);

	}
	if (strcmp(msgId, "useSkill") == 0)
	{
		//ʹ�ü���
		base = new Msg_UseSkill();
		base->setBody(msgBody);
		base->setMsgId(MsgUseSkill);

	}
	if (strcmp(msgId, "BonuspoolInfo") == 0)
	{
		//ͬ��������Ϣ
		base = new Msg_OnGetBounsPool();
		base->setBody(msgBody);
		base->setMsgId(MsgOnGetBounsPool);

	}
	if (strcmp(msgId, "LuckDraw") == 0)
	{
		//�齱
		base = new Msg_LuckDraw();
		base->setBody(msgBody);
		base->setMsgId(MsgLuckDraw);

	}
	if (strcmp(msgId, "magnate") == 0)
	{
		//����
		base = new Msg_OnMagnate();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMagnate);

	}
	if (strcmp(msgId, "bankruptBroke") == 0)
	{
		//�Ʋ�����
		base = new Msg_OnBankrupt();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBankrupt);

	}
	if (strcmp(msgId, "bankruptRebirth") == 0)
	{
		//�Ʋ���ȡ
		base = new Msg_OnBankruptRebirth();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBankruptRebirth);

	}
	if (strcmp(msgId, "payresult") == 0)
	{
		//֧�����
		base = new Msg_Payresult();
		base->setBody(msgBody);
		base->setMsgId(MsgPayresult);

	}
	if (strcmp(msgId, "boss") == 0)
	{
		//boss��������
		base = new Msg_OnBossDead();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBossDead);

	}
	if (strcmp(msgId, "marquee") == 0)
	{
		//�����
		base = new Msg_OnMarquee();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMarquee);

	}
	if (strcmp(msgId, "mermaidTask") == 0)
	{
		//�����㿪ʼ
		base = new Msg_OnBeginMarried();
		base->setBody(msgBody);
		base->setMsgId(MsgOnBeginMarried);

	}
	if (strcmp(msgId, "updateMermaid") == 0)
	{
		//�������������
		base = new Msg_OnCatchMarriedFish();
		base->setBody(msgBody);
		base->setMsgId(MsgOnCatchMarriedFish);

	}
	if (strcmp(msgId, "successMermaid") == 0)
	{
		//����������ɹ�
		base = new Msg_OnMarriedSuccess();
		base->setBody(msgBody);
		base->setMsgId(MsgOnMarriedSuccess);

	}
	return base;
}
