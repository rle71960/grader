#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFF_SIZE 1024

float avg;
float min;
float max;
float med;
int passed;

void *runner(void *param);

int main()
{
	pthread_t tid; /* thread */
	pthread_attr_t attr; /* thread attributes */
	
	FILE *file;
	char *mode = "r";

	file = fopen("grades.txt", mode);

	if (file == NULL)
	{
		fprintf(stderr, "Can't open file 'grades.txt'\n");
		exit(1);
	}

}
