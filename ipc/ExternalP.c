#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "MessageHeader.h"

int main(int args, char* argv[]) {
	int pId = stringToInteger(argv[2]);
	int temperature = stringToInteger(argv[1]);
	int msgQId;
	tMsg msg;

	if((msgQId=msgget(E_KEYS[pId-1], 0600|IPC_CREAT)) == -1){
		perror("e_msgget");
		exit(1);
	}
printf("debug1 msgQId : %d\n", msgQId);

	do{
		msg.priority = 2;
		msg.temp = temperature;
		msg.pid = pId;
		msg.stable = 0;

		if(msgsnd(msgQId, &msg, sizeof(tMsg)-sizeof(long), 0) == -1) {
			perror("e_msgsnd");
			exit(1);
		}

		if(msgrcv(msgQId, &msg, sizeof(tMsg)-sizeof(long), 2, 0) == -1) {
			perror("e_msgrcv");
			exit(1);
		}
		temperature = msg.temp;
	}while(msg.stable == 0);

	printf("external process %d temperature : %d\n", pId, temperature);
	if(msgctl(msgQId, IPC_RMID, 0) == -1) {
		perror("e_msgctl");
		return 0;
	}

	return 0;
}
