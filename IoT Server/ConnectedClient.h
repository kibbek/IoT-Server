#pragma once
#include "common.h"
#include "Server.h"

class server;

class ConnectedClient
{
public:
	ConnectedClient(server* Server, int connected_socket, uint32_t ip, uint16_t port);
	virtual ~ConnectedClient();
	virtual void disconnect();
	virtual void putline(string str);
	virtual string getline();

protected:
	static void* run(void *);

private:
	uint32_t ip;
	uint16_t port;
	int connected_socket;
	string user, pass;
	pthread_t thread_id;
	server* Server;
};