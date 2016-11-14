#pragma once

#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<algorithm>
#include<memory>
#include <ctime>
#include <exception> 
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include "MQTTClient.h"


#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <cstdint>
#define SHUT_RDWR SD_BOTH
typedef int	socklen_t;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

class Common
{
public:
	Common();
	~Common();
	static void sleep(uint32_t s);
};


using namespace std;
