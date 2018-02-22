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

typedef struct 
{
	int *time;
	char *valid;
} GET_LOCAL_TIME;

void GetLocalTime(GET_LOCAL_TIME *ds);

class GetLocalTime
{
	c_int time;
	c_char valid;

	public int execute(string IP, int port);
}

class c_int
{
	byte[] buf = byte[4]; // little endian

	public int getSize();
	public int getValue();
	public void setValue(byte[] buf);
	public void setValue(int v);
	public byte[] toByte();
}