#pragma once
#include"common.h"
#include"Devices.h"

class LightDetector : public Devices
{
public:
	LightDetector(MQTTClient client, string topic);
	virtual ~LightDetector();
	virtual void Event(Devices* dev);
protected:
	static void* run(void *);
	virtual void Commands();
private:
	int Illuminance;
	int IlluminanceMin;
	bool Enabled;
};

