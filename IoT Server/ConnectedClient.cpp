#include "ConnectedClient.h"

ConnectedClient::ConnectedClient(server* Server, int connected_socket, uint32_t ip, uint16_t port)
{
	this->Server = Server;
	this->connected_socket = connected_socket;
	this->ip = ip;
	this->port = port;
	pthread_create(&thread_id, NULL, run, (void*)this);
}

void ConnectedClient::putline(string str)
{
	send(connected_socket, str.c_str(), str.length(), 0);
}

ConnectedClient::~ConnectedClient()
{
	disconnect();
}

void ConnectedClient::disconnect()
{
	shutdown(connected_socket, SHUT_RDWR);
}

string ConnectedClient::getline()
{
	string line("");
	char c;
	size_t rxbytes;
	do {
		rxbytes = recv(connected_socket, &c, 1, 0);
		if (rxbytes == 1 && c >= 32)
		{
			line += c;
		}
	} while (rxbytes == 1 && c != '\r');
	return line;
}

void* ConnectedClient::run(void* arg)
{
	ConnectedClient * client = (ConnectedClient*)arg;

	client->putline("User: ");
	client->user = client->getline();
	cout << client->user << endl;

	client->putline("\r\nPass: ");
	client->pass = client->getline();
	cout << client->pass << endl;
	
	string c("");
	do {
		client->putline("\r\nCmd: ");
		c = client->getline();
		cout << client->user << ": " << c << endl;
	} while (c != "exit");

	client->disconnect();
	//client->Server->removeClient(client);
	return NULL;
}
