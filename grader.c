#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

float avg;
float min;
float max;
float med;
int passed;

void *runner(void *param);

int main(int argc, char *argv[])
{
}
