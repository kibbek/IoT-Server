#pragma once
#include "common.h"


class Devices
{
public:
	Devices();
	virtual ~Devices();
	virtual void disconnect();
	virtual void Publish(Devices* dev,char* str,string _topic);
	virtual void Subscribe(Devices* dev,string _topic);
protected:
	MQTTClient client;
	pthread_t thread_id;
	vector<char *> TopicEvent;
	struct Data {
		string topic;
		string Message;
		Data(string topic,string Message) : topic(topic),Message(Message){}
	};
	vector<Data> Topic;
	MQTTClient_message pubmsg;
	virtual void ReadFile(Devices* dev);
	virtual void Event(Devices* dev) = 0;
	virtual void Commands() = 0;
private:
	MQTTClient_deliveryToken token;
};

