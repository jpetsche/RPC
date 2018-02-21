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

int keepLooping = 1;

struct BEACON {
	int ID;
	int StartUpTime;
	char IP[4];
	int CmdPort;
};
typedef struct BEACON beacon;

void error(char *msg) {
	perror(msg);
	exit(0);
}

beacon newBeacon(int tcpPort)
{
	int port = 12800;
	int tcpSocket;
	srand(time(0));
	beacon udpBeac;
	udpBeac.ID = 100000+(rand())%900000;
	udpBeac.StartUpTime = (int)time(NULL);
	udpBeac.IP[0] = 127;
	udpBeac.IP[1] = 0;
	udpBeac.IP[2] = 0;
	udpBeac.IP[3] = 1;
	udpBeac.CmdPort = tcpPort;
	return udpBeac;
}

unsigned char *serialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
	buffer[0] = value >> 24;
  	buffer[1] = value >> 16;
  	buffer[2] = value >> 8;
  	buffer[3] = value;
  	return buffer + 4;
}

unsigned char *serialize_char(unsigned char *buffer, char value)
{
  	buffer[0] = value;
  	return buffer + 1;
}

unsigned char *serialize_beac(unsigned char *buffer, beacon *beac)
{
 	buffer = serialize_int(buffer, beac->ID);
 	buffer = serialize_int(buffer, beac->StartUpTime);
 	buffer = serialize_int(buffer, beac->CmdPort);
 	buffer = serialize_char(buffer, beac->IP[0]);
  	buffer = serialize_char(buffer, beac->IP[1]);
  	buffer = serialize_char(buffer, beac->IP[2]);
  	buffer = serialize_char(buffer, beac->IP[3]);
  	return buffer;
}

unsigned char *serialize_outMsg(unsigned char *buffer, char *msg, int size)
{
	for(int i = 0; i < size; i++)
	{

	}
	return buffer;
}

void printMessage(char *mes)
{
	printf("message: %s\n", mes);
}


void *BeaconSender(void *tcpPort)
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

	return NULL;
}

void GetLocalOS(char OS[16], int *valid) 
{

}

void GetLocalTime(int *time, int *valid)
{

}

void *CmdAgent(void *port)
{
	int servSock = 0;
	int acpt = 0;
	struct sockaddr_in tcpServAdd;
	char tcpBuff[1025];
	time_t timings;

	servSock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&tcpServAdd, '0', sizeof(tcpServAdd));
	memset(tcpBuff, '0', sizeof(tcpBuff));
	//printf("%d\n", *((int*)port));

	tcpServAdd.sin_family = AF_INET;
	tcpServAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	tcpServAdd.sin_port = htons(*((int*)port));

	bind(servSock, (struct sockaddr*)&tcpServAdd, sizeof(tcpServAdd));

	if(listen(servSock, 10) < 0)
	{
		error("error on listen\n");
	}

	int rec = 0;
	while(1)
	{
		acpt = accept(servSock, (struct sockaddr*)NULL, NULL);
		if(acpt < 0)
		{
			error("error on accept\n");
		}
		if(acpt > 0)
		{

			printf("Connected to Manager via TCP\n");
			
			//printf((string)acpt);

			rec = recv(acpt, tcpBuff, sizeof(tcpBuff), 0);
			printMessage(tcpBuff);
			

			char resp[1056] = "OS result: 1\nLocal Time result: 1\r\n\0";

			timings = time(NULL);
			// snprintf(tcpBuff, sizeOf(tcpBuff), "%.24s\r\n", timings);
			//write(servSock, resp, strlen(resp));

			int sentFail = 0;
			//write(acpt, resp, sizeof(resp)+1);
			//send(acpt, resp, sizeof(resp), 0);
			close(acpt);
			printf("TCP connection closed\n");
		}

		sleep(1);

	}
	return NULL;
}

int main()
{
	srand(time(0));
	int tcpPort = 13000+rand()%30001;
	void *v = malloc(sizeof(int));
	*((int*)v) = tcpPort;

	pthread_t beaconThread;
	pthread_t cmdThread;
	pthread_create(&cmdThread, NULL, CmdAgent, v);
	pthread_create(&beaconThread, NULL, BeaconSender, v);


	pthread_join(beaconThread, NULL);
	pthread_join(cmdThread, NULL);


	return 0;
}