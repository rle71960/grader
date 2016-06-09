#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>

#define BUFF_SIZE 1024

int n_spaces = 0;
float avg = 0.0;
int min;
int max;
float med;
int passed = 0;

void* averageGrade(void * params);
void* minimumGrade(void * params);
void* maximumGrade(void * params);
void* medianGrade(void * params);
void* numberPassed(void * params);

int compare(const void * a, const void * b);

int main()
{
	/* our threads */
	pthread_t average;
	pthread_t minimum;
	pthread_t maximum;
	pthread_t median;
	pthread_t numPassed;

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

	fclose(file);

	/*
	 * String splitting taken from
	 * stackoverflow.com/questions/11198604/c-split-string-into-an-array-of-strings
	 */
	char ** array = NULL;
	char * p = strtok(buff, ","); /* split string on ',' */
	int i;

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

	fprintf(stdout, "Read grades: ");
	int arr[n_spaces];
	for ( i = 0; i < n_spaces; ++i)
	{
		arr[i] = atoi(array[i]);
		fprintf(stdout, "%d ", arr[i]);
	}
	fprintf(stdout, "\n");

	/* Array loaded, spawn threads for functions */
	pthread_create(&average, NULL, &averageGrade, (void*)arr);
	pthread_create(&minimum, NULL, &minimumGrade, (void*)arr);
	pthread_create(&maximum, NULL, &maximumGrade, (void*)arr);
	pthread_create(&median, NULL, &medianGrade, (void*)arr);
	pthread_create(&numPassed, NULL, &numberPassed, (void*)arr);

	pthread_join(average, NULL);
	pthread_join(minimum, NULL);
	pthread_join(maximum, NULL);
	pthread_join(median, NULL);
	pthread_join(numPassed, NULL);

	fprintf( stdout, "Average is %.0f\n", avg );
	fprintf( stdout, "Minimum is %d\n", min );
	fprintf( stdout, "Maximum is %d\n", max );
	fprintf( stdout, "Median is %.0f\n", med );
	fprintf( stdout, "Number of Students Who Pass: %d\n", passed );

	free(array);
	return 0;
}

int compare(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

void* averageGrade(void* args)
{
	int *val_p = (int *) args;
	int total = 0;

	for (int i = 0; i < n_spaces; ++i)
	{
		total += (int)val_p[i];
	}
	avg = total/n_spaces;
}

void* minimumGrade(void* args)
{
	int *val_p = (int *) args;
	min = INT_MAX;
	
	for (int i = 0; i < n_spaces; ++i)
	{
		if( val_p[i] < min )
		{
			min = val_p[i];
		}
	}
}

void* maximumGrade(void* args)
{
	int *val_p = (int *) args;
	max = INT_MIN;

	for (int i = 0; i < n_spaces; ++i)
	{
		if( max < val_p[i] )
		{
			max = val_p[i];
		}
	}
}

void* medianGrade(void* args)
{
	int *val_p = (int *) args;
	int tmp[n_spaces];
	/* We must sort but first we make a
	 * tmp array to avoid shared memory
	 * problems
	 */
	for (int i = 0; i < n_spaces; ++i)
	{
		tmp[i] = val_p[i];
	}
	/* Let's use the stdlib quicksort */
	qsort(tmp, n_spaces, sizeof(int), compare);
	if (n_spaces % 2 == 0)
	{
		int mid = n_spaces/2;
		med = (tmp[mid] + tmp[mid+1])/2;
	}
	else
	{
		med = tmp[n_spaces/2];
	}
}

void* numberPassed(void* args)
{
	int *val_p = (int *) args;
	/* ensure avg has been calculated */
	while(avg == 0.0)
	{
		wait(10);
	}
	
	for (int i = 0; i < n_spaces; ++i)
	{
		if( val_p[i] > avg )
		{
			passed++;
		}
	}
}
