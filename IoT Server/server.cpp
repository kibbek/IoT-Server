#include "server.h"


Server::Server()
{
}


Server::~Server()
{
}


void Server::stop()
{
	_is_running = false;
	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
}

bool Server::is_running()
{
	return _is_running;
}

void Server::addDevices(Devices * client)
{
	devices.push_back(client);
}

void Server::removeDevices(Devices * client)
{
	///todo: usun takze z wektora
	delete client;
}


void Server::start(uint16_t port)
{
	_is_running = true;
	pthread_create(&thread_id, NULL, run, (void*)this);
}



int Server::msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	char* payloadptr;
	string MessName, TopName = topicName;
	fstream plik;
	printf("Message arrived\n");
	payloadptr = (char*)message->payload;
	for (int i = 0; i<message->payloadlen; i++)
	{
		MessName += *payloadptr++;
	}
	replace(TopName.begin(), TopName.end(), '/', '&');
	plik.open(TopName+".txt", ios::app | ios::out);
	if (plik.good() == true)
	{
		plik <<endl<< MessName;
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
	plik.close();
	MQTTClient_freeMessage(&message);	
	MQTTClient_free(topicName);
	return 1;
}


void* Server::run(void* arg) {
	Server* MqttServer = (Server *)arg;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	int rc;
	MQTTClient_create(&MqttServer->client, "m20.cloudmqtt.com:19928", "kibbek",
		MQTTCLIENT_PERSISTENCE_NONE, NULL);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.password = "X17PdC9LRURL";
	conn_opts.username = "napengcd";
	MQTTClient_setCallbacks(MqttServer->client, NULL, NULL,MqttServer->msgarrvd, NULL);
	if ((rc = MQTTClient_connect(MqttServer->client, &conn_opts)) != MQTTCLIENT_SUCCESS)
	{
		printf("Failed to connect, return code %d\n", rc);
		MqttServer->stop();
		return NULL;
	}else printf("Connected to server, return code %d\n", rc);


	MqttServer->addDevices(new Lampa(MqttServer->client,"/lampa"));
	MqttServer->addDevices(new LightDetector(MqttServer->client, "/czujnik"));
	while (MqttServer->is_running()) {

	}
	MqttServer->stop();
	return NULL;
}



