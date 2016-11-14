#include "Devices.h"


Devices::Devices()
{

}

Devices::~Devices()
{
	disconnect();
}

void Devices::Publish(Devices* dev, char* str, string _topic)
{
	pubmsg.payload = str;
	pubmsg.payloadlen = strlen(str);
	try 
	{
		MQTTClient_publishMessage(client, _topic.c_str() , &pubmsg, &token);
	}
	catch (exception ex) { cout << ex.what() << endl; }
}

void Devices::Subscribe(Devices* dev, string _topic) {
	try
	{
		MQTTClient_subscribe(dev->client, _topic.c_str(), NULL);
	}
	catch (exception ex)	{ cout << ex.what() << endl; }
}

void Devices::ReadFile(Devices* dev) {
	fstream plik; string linia;
	if (!dev->Topic.empty()) {
		for (vector<Data>::iterator it = dev->Topic.begin(); it != dev->Topic.end(); ++it) {
			string filename = it->topic;
			replace(filename.begin(), filename.end(), '/', '&');
			plik.open(filename + ".txt", ios::in);
			if (plik.good() && (plik.peek() != std::ifstream::traits_type::eof()))
			{
				while (!plik.eof())
				{	
					getline(plik, linia);
				}
				plik.close();
				plik.open(filename + ".txt", ios::out | ios::trunc);
				it->Message = linia;
				cout <<"Message: "<< it->Message << " " <<"Topic: "<< it->topic << endl;
			}
			plik.close();
		}
	}
}

void Devices::disconnect()
{
	Topic.clear();
	TopicEvent.clear();
}