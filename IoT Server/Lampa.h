#pragma once
#include "common.h"
#include "Devices.h"

class Lampa : public Devices
{
public:
	Lampa(MQTTClient client,string topic);
	virtual ~Lampa();
	virtual void Event(Devices* dev);
protected:
	static void* run(void *);
	virtual void Commands();
private:
	bool Enabled;
};

