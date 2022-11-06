#ifndef _SERVER_H_
#define _SERVER_H_

#include "cocos2d.h"
#include "pomelo.h"
#include "pomelo_trans.h"
#include "server/MsgObserver.h"
USING_NS_CC;
#define EV_HANDLER_EX ((void*)0x44)

#define REQ_ROUTE "connector.entryHandler.enter"

#define REQ_EX ((void*)0x22)
#define REQ_TIMEOUT 10

#define REQ_NEWEVENTS "game.gameHandler.newevents"
#define REQ_NEWEVENTS_EX ((void*)0x33)

#define REQ_USERINFOCHANGE "game.gameHandler.userinfochange"
#define REQ_USERINFOCHANGE_EX ((void*)0x55)

#define REQ_ROUTE_LEVELUPDATE "game.gameHandler.levelchange"
#define REQ_LEVELUPDATE_EX ((void*)0x66)

#define REQ_ROUTE_USESKILL "gate.gateHandler.queryEntry"
#define REQ_USESKILL_EX ((void*)0x77)
#define REQ_ROUTE_BOUNSPOOL "game.gameHandler.bonuspool"
#define REQ_BOUNSPOOL_EX ((void*)0x88)

#define REQ_ROUTE_BANKRUPTREBIRTH "game.gameHandler.bankruptRebirth"
#define REQ_BANKRUPTREBIRTH_EX ((void*)0x99)

#define REQ_ROUTE_PAYRESULT "game.gameHandler.payresult"
#define REQ_PAYRESULT_EX ((void*)0x98)


class Server{
public:
	static Server* getInstance();
	void conConnect(const char* host, int port);
	void quit();

	void add_observer(MsgObserver *o);
	void remove_observer(MsgObserver *o);
	
	void sendRequest(EnumRequestID request,char* msgBody);

private:
	static void notify_cb(const pc_notify_t* noti, int rc);
	void notify_observer(EnumRequestID request, const char* msgBody);
	void notify_observer(const char* request, const char* msgBody);
	//test example
public:
	void sendNewEvents(const char* params);


	//��������
public:
	void reqTurrentLevelUpdate();
private:
	static void levelupdate_cb(const pc_request_t* req, int rc, const char* resp);



	//ʹ�ü���
public:
	void sendUseSkill(int itemid);
private:
	static void useSkill_cb(const pc_request_t* req, int rc, const char* resp);


	//�齱
public:
	void sendBounsPool();
private:
	static void bounsPool_cb(const pc_request_t* req, int rc, const char* resp);


	//�Ʋ���ȡ
public:
	void sendBankruptRebirth();
private:
	static void bankruptRebirth_cb(const pc_request_t* req, int rc, const char* resp);

	//��ѯ����
public:
	void sendCheckPayresult(std::string order_id,int paythirdtype);
private:
	static void Paysult_cb(const pc_request_t* req, int rc, const char* resp);

private:
	Server();
	static Server* _instance;

	bool onConnecting = false;

	int handler_id;
	pc_client_t* workingClient;

	void doConnect();



	static void event_cb(pc_client_t* client, int ev_type, void* ex_data, const char* arg1, const char* arg2);

	static void connect_cb(const pc_request_t* req, int rc, const char* resp);

	std::string username;

	int _room_id;

	std::vector<MsgObserver*> msgObserver;
};

#endif
