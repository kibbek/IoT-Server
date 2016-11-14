#include "common.h"
#include "Server.h"
int main()
{
	Server server;
	server.start(19928);
	while (server.is_running())
	{
		Common::sleep(1);
	}

	return NULL;

}
