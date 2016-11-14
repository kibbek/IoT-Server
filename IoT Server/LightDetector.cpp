#include "LightDetector.h"

LightDetector::LightDetector(MQTTClient client, string topic)
{
	pubmsg = MQTTClient_message_initializer;
	this->client = client;
	Topic.push_back(Data(topic, ""));
	Topic.push_back(Data(topic + "/Enabled", "True"));
	Topic.push_back(Data(topic + "/iteration/Illuminance/value", "1"));
	Topic.push_back(Data(topic + "/iteration/IlluminanceMin/value", "0"));
	TopicEvent.push_back("/lampa");
	pthread_create(&thread_id, NULL, run, (void*)this);
}

LightDetector::~LightDetector()
{

}

void LightDetector::Event(Devices* dev)
{
	if (Enabled && !TopicEvent.empty()) {
		for (vector<char*>::iterator it = TopicEvent.begin(); it != TopicEvent.end(); ++it) {
			if (Illuminance < IlluminanceMin) {
				dev->Publish(dev, "wylacz", *it);
				Topic.at(1).Message = "False";
			}
		}
	}
}

void LightDetector::Commands() {
	for (vector<Data>::iterator it = Topic.begin(); it != Topic.end(); ++it) {
		if (Topic.at(1).Message == "True")
			Enabled = true;
		else Enabled = false;
		if (it->topic == Topic.begin()->topic + "/iteration/Illuminance/value") { try { Illuminance = stoi(it->Message); } catch (exception ex) { /*cout << ex.what() << endl; }*/ } }
		if (it->topic == Topic.begin()->topic + "/iteration/IlluminanceMin/value") { try { IlluminanceMin = stoi(it->Message); } catch (exception ex) { /*cout << ex.what() << endl; */ } }

	}
}

void* LightDetector::run(void* arg)
{
	LightDetector * clieent = (LightDetector*)arg;
	cout << clieent->Topic.at(1).Message << endl;
	for (vector<Data>::iterator it = clieent->Topic.begin(); it != clieent->Topic.end(); ++it)
		clieent->Subscribe(clieent, it->topic);
	string c("");
	do {
		clieent->ReadFile(clieent);
		clieent->Commands();
		clieent->Event(clieent);
	} while (c != "exit");

	clieent->disconnect();
	return NULL;
}