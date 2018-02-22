#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <setjmp.h>
#include <sys/utsname.h>

char header[104];
struct utsname unameData;
int utserror = 0; //system name, 0=no error, 1=error

typedef struct 
{
	int *time;
	char *valid;

} GET_LOCAL_TIME;

typedef struct
{
	char *os;
	char *valid;
} GET_LOCAL_OS;

void GetLocalTime(GET_LOCAL_TIME *ds);
{
	time_t localT;
	struct tm * tInfo;

	time (&localT);
	tInfo = localtime (&localT);
	ds.time = asctime(tInfo);
}

void GetLocalOS(GET_LOCAL_OS *os)
{
	if(uname(&unameData) == -1)
	{
		printf("error on uname: %s\n", errno);
		utserror = 1;
	}

}

void *CmdProcessor()
{

}

int main()
{
	char *hostname;
	char buffer[32], *buff;
	int beacSock;
	int port = *((int*)tcpPort);
	int response;
	int sLength;
	struct sockaddr_in servAddress;
	struct hostent *server;
 	beacon currentBeac = newBeacon(port);
 	//printf("%d\n", currentBeac.StartUpTime);
	buff = serialize_beac(buffer, &currentBeac);
	
	bzero((char *) &servAddress, sizeof(servAddress));
	servAddress.sin_family = AF_INET;
	servAddress.sin_port = htons(12800);
	servAddress.sin_addr.s_addr = INADDR_ANY;
	sLength = sizeof(servAddress);

	beacSock = socket(AF_INET, SOCK_DGRAM, 0);
	if(beacSock < 0)
	{
		error("error opening the beacon socket\n");
	}

	while(keepLooping == 1)
	{
		printf("Beacon sent to Manager\n");
		response = sendto(beacSock, buffer, buff - buffer, 0, (struct sockaddr *) &servAddress, sLength);
		if(response < 0)
		{
			error("error in sendto\n");
		}
		sleep(10);
	}
	return 0;
}