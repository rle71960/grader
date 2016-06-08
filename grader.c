#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFF_SIZE 1024


void* averageGrade(void * params);
void *runner(void *param);

struct thread_args
{
	/* The count/size of arr */
	int count;
	/* The array of grades */
	int *arr[];
};

int main()
{
	pthread_t average; /* thread */
	pthread_t minimum;
	pthread_t maximum;
	pthread_t median;
	pthread_t numPassed;

	pthread_attr_t attr; /* thread attributes */
	
	/* Read the file, load grades into str array */
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

	/* TODO: comment me */
	for( i = 0; i < (n_spaces); ++i)
	{
		fprintf(stdout, "%d=%s\n", i, array[i]);
	}

	int arr[n_spaces];
	for ( i = 0; i < n_spaces; ++i)
	{
		arr[i] = atoi(array[i]);
	}

	/* TODO: comment me */
	for ( i = 0; i < n_spaces; ++i)
	{
		fprintf(stdout, "%d=%d\n", i, arr[i]);
	}

	/* Array loaded, spawn threads for functions */

	/*
	 * average = 
	 * minimum = 
	 * maximum = 
	 * median = 
	 * numPassed = 
	 */

	/* Hold return values */
	void* avg;
	int min;
	int max;
	float med;
	int passed;

        struct thread_args *averageArgs = malloc(sizeof (struct thread_args) + sizeof (int)*n_spaces);
	averageArgs->count = n_spaces;
	averageArgs->arr = *arr;

	pthread_create(&average, NULL, &averageGrade, &averageArgs);

	pthread_join(average, &avg);
/*
	pthread_join(minimum, min);
	pthread_join(maximum, max);
	pthread_join(median, med);
	pthread_join(numPassed, passed);
*/
	float avg_f = *(float*) avg;
	fprintf( stdout, "\n\nAverage reported: %f\n", avg_f );
	free(array);
	return 0;
}

void* averageGrade(void* params)
{
	struct thread_args* args = (struct thread_args*) params;
	int total = 0;

	for (int i = 0; i < args->count; ++i)
	{
		total += (int)args->arr[i];
	}
	float avg = total/args->count;
}

int minimumGrade(int arr[], int count)
{
}
