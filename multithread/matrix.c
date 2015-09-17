#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define M 3
#define N 2
int matrix1[M][N] = {{1,2},{3,4},{5,6}};
int matrix2[N][M] = {{7,8,9},{10,11,12}};
int result[M][M];

typedef struct
{
	int i;
	int j;
} matrixCell;

void *multiply(matrixCell *cell)
{
	int value = 0;
	int i;
printf("thread[%d][%d] run\n", cell->i, cell->j);
	for(i=0; i<M; i++)
		value += matrix1[cell->i][i]*matrix2[i][cell->j];
	result[cell->i][cell->j] = value;
printf("thread[%d][%d] end, result=%d\n", cell->i, cell->j, value);
}

void printMatrix()
{
	int i, j;
	for(i=0; i<M; i++)
	{
		for(j=0; j<M; j++)
			printf("%d ", result[i][j]);
		printf("\n");
	}
}

int main()
{
	matrixCell *cell[M][M];
	pthread_t thread[M][M];
	int i, j;
	for(i=0; i<M; i++)
	{
		for(j=0; j<M; j++)
		{
			cell[i][j] = (matrixCell*)malloc(sizeof(matrixCell));
			cell[i][j]->i = i;
			cell[i][j]->j = j;
			if(pthread_create(&thread[i][j], NULL, multiply, cell[i][j]) < 0)
			{
				perror("thread create error : ");
				exit(0);
			}
		}
	}

	for(i=0; i<M; i++)
		for(j=0; j<M; j++)
		{
			pthread_join(thread[i][j], NULL);
			free(cell[i][j]);
		}

	printMatrix(result);

	return 0;
}
