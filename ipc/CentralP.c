#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "MessageHeader.h"

int main(int args, char *argv[]) {
	int i;
	int stableFlag = 0;
	int centralTemp = stringToInteger(argv[1]);
	int externalTemp[4] = {0, 0, 0, 0};

	int cMsgQId;
	int eMsgQId[4];
	tMsg msg;

	//create mailbox
	if((cMsgQId = msgget(C_KEY, 0600|IPC_CREAT)) == -1) {
		perror("c_msgget");
		exit(1);
	}
printf("debug1 cMsgQId : %d\n", cMsgQId);
	for(i=0; i<4; ++i) {
		if((eMsgQId[i]=msgget(E_KEYS[i], 0600|IPC_CREAT)) == -1) {
			perror("c_msgget_e");
			exit(1);
		}
printf("debug2 cMsgQId : %d\n", eMsgQId[i]);
	}

	while(!stableFlag) {
		stableFlag = 1;

		//receive message from external process
		for(i=0; i<4; ++i) {
			if((msgrcv(eMsgQId[i], &msg, sizeof(tMsg)-sizeof(0), 2, 0)) == -1) {
				perror("c_msgrcv_e");
				exit(1);
			}
			printf("receive message from external process %d\n", i);
			if(externalTemp[i] != msg.temp) {
				stableFlag = 0;
				externalTemp[i] = (externalTemp[i]*3 + centralTemp*2)/5;
			}
		}
		centralTemp = (centralTemp*2 + externalTemp[0] + externalTemp[1] + externalTemp[2] + externalTemp[3])/6;
		
		//send message to external process
		for(i=0; i<4; ++i) {
			msg.priority = 2;
			msg.temp = externalTemp[i];
			msg.pid = i;
			msg.stable = stableFlag;

			if(msgsnd(eMsgQId[i], &msg, sizeof(tMsg)-sizeof(long), 0) == -1) {
				perror("c_msgsnd_e");
				exit(1);
			}
			printf("send message to external process %d\n", i);
		}
	}

	//system is stable
	printf("central process temperature : %d\n", centralTemp);
	if(msgctl(cMsgQId, IPC_RMID, 0) == -1) {
		perror("c_msgctl");
		exit(1);
	}

	return 0;
}

