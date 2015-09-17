#ifndef __MSGH__
#define __MSGH__

const int C_KEY = 1234;
const int E_KEYS[4] = {1235, 1236, 1237, 1238};

typedef struct {
	long priority;
	int temp;
	int pid;
	int stable;
} tMsg;

int stringToInteger(char* str) {
	int result = 0;
	int i;
	for(i=0; str[i]!='\0'; ++i) {
		result *= 10;
		result += str[i]-'0';
	}
	return result;
}

#endif
