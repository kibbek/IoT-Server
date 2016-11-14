#pragma once
#include "common.h"
#include "Devices.h"
#include "lampa.h"
#include"LightDetector.h"

class Server
{
public:
	Server();
	virtual ~Server();
	virtual void start(uint16_t port);
	virtual void stop();
	virtual bool is_running();
	static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
protected:
	friend class Devices;
	virtual void addDevices(Devices * client);
	virtual void removeDevices(Devices * client);
	static void* run(void*);
private:
	MQTTClient client;
	volatile MQTTClient_deliveryToken deliveredtoken;
	volatile bool _is_running;
	pthread_t thread_id;
	vector < Devices* > devices;
};

