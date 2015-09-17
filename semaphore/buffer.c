#include "buffer.h"
#include <stdio.h>

buffer_item buffer[BUFFER_SIZE];
int first = 0;
int size = 0;

int insert_item(buffer_item item) {
	if(size == BUFFER_SIZE)
		return -1;

	buffer[(first+size)%BUFFER_SIZE] = item;
	size++;
	
	return 0;
}

int remove_item(buffer_item *item) {
	if(size == 0)
		return -1;

	*item = buffer[first];
	first = (first+1)%BUFFER_SIZE;
	size--;
	return 0;
}

void printBuffer(void) {
	int i;
	if(size == 0)
		printf("Buffer : empty\n\n");
	else {
		printf("Buffer : ");
		for(i=0; i<size; i++)
			printf("%d, ", buffer[(first+i)%BUFFER_SIZE]);
		printf("\n\n");
	}
}

		
