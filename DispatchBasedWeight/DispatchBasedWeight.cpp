#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CacheTime 5 //5 seconde
#define NORMAL 1
#define DISABLE 0


typedef struct _accessServer{
	unsigned int	serverId;
	 	 	 int	weight;
			 int	state;
} accessServer;

void updateAccessServerArray(accessServer arrAccSvr[],unsigned int eleNum)
{
	return;
}

accessServer * getAccessServer(accessServer arrAccSvr[], unsigned int eleNum)
{
	static unsigned int lastUpdateTime = 0;
	static int allWeight = 0;
	unsigned int tNow = time(NULL);
	int iRandWeight;

	if(!arrAccSvr || eleNum <=0)
	{
		return NULL;
	}
	//sataic, sum of weight, so no need to sum every request
	if (tNow - lastUpdateTime > CacheTime)
	{
		lastUpdateTime = tNow;
		updateAccessServerArray(arrAccSvr, eleNum);

		allWeight = 0;
		for(int i = 0; i < eleNum; i++)
		{
			if (arrAccSvr[i].state != NORMAL) continue;
			allWeight += arrAccSvr[i].weight;
		}
	}

	iRandWeight = rand()%allWeight;

	for(int i = 0; i < eleNum; i++)
	{
		if (arrAccSvr[i].state != NORMAL) continue;
		iRandWeight = iRandWeight - arrAccSvr[i].weight;

		if (iRandWeight <= 0)
		{
			return &arrAccSvr[i];
		}
	}

	return NULL;
}


int main(int argc, char **argv) {
	accessServer a[100];
	unsigned int aNum = sizeof(a)/sizeof(accessServer);
	accessServer *dstSvr = NULL;

	srand(time(NULL));
	for(int i = 0; i < aNum; i++)
	{
		a[i].state = NORMAL;
		a[i].weight = 10 * 10;
		a[i].serverId = i;
	}

	for (int i = 0; i < 100; i++)
	{
		dstSvr = getAccessServer(a, aNum);
		if(dstSvr)
		{
			printf("Get Server:%d\n", dstSvr->serverId);
		}
	}
	return 0;
}
