#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

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

	char buff[BUFF_SIZE];
	fgets(buff,BUFF_SIZE, file);
	/*fprintf(stdout, "String read: %s\n", buff);*/

	fclose(file);

	/*
	 * String splitting taken from
	 * stackoverflow.com/questions/11198604/c-split-string-into-an-array-of-strings
	 */

	char ** array = NULL;
	char * p = strtok(buff, ","); /* split string on ',' */
	int n_spaces = 0, i;

	while (p)
	{
		array = realloc(array, sizeof (char *) * ++n_spaces);

		if (array == NULL)
		{
			exit(1); /* memory allocation failed */
		}

		array[n_spaces-1] = p;

		p = strtok(NULL, ",");
	}

	array = realloc(array,sizeof (char*) * (n_spaces+1));
	array[n_spaces] = 0;

	for( i = 0; i < (n_spaces); ++i)
	{
		fprintf(stdout, "%d=%s\n", i, array[i]);
	}

	free(array);

	return 0;
}
