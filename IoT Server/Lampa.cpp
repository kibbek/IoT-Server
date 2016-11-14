#include "Lampa.h"


Lampa::Lampa(MQTTClient client, string topic) {
	pubmsg = MQTTClient_message_initializer;
	this->client = client;
	Topic.push_back(Data(topic,""));
	pthread_create(&thread_id, NULL, run, (void*)this);
}
Lampa::~Lampa()
{
}
void Lampa::Event(Devices* dev)
{
	
}
void Lampa::Commands() {
	// if () Enabled = true;
	// else Enabled = false;
}

void* Lampa::run(void* arg)
{
	Lampa * clieent = (Lampa*)arg;
	for(vector<Data>::iterator it = clieent->Topic.begin(); it != clieent->Topic.end(); ++it)
		clieent->Subscribe(clieent,it->topic);
	string c("");
	do {
		clieent->ReadFile(clieent);
	} while (c != "exit");

	clieent->disconnect();
	//client->server->removeClient(client);
	return NULL;
}
