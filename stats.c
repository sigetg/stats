#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>


void usage();
int is_valid_int(char *s);
int *generate_population(int size, int lower, int upper);
void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev);

int is_valid_int(char *s)
{
        if (s == NULL)
        {
                return -1;
        }
        if (*s == '-')
        {
                ++s;
        }
        while (*s != '\0')
        {
                if (!isdigit(*s))
                {
                        return 0;
                }
                ++s;
        }
        return 1;
}

int *generate_population(int size, int lower, int upper)
{
	int *nums = (int *)malloc(size * sizeof(int));
	if (nums == NULL)
	{
		printf("Memory error!\n");
		usage();
	}
	for (int i = 0; i < size; ++i)
	{
		nums[i] = rand() % (upper + 1 - lower) + lower;
	}
	return nums;
}

void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev)
{
	double total = 0;
	*min = a[0];
	*max= a[0];
	for (int i = 0; i < size; ++i)
	{
		if (a[i] > *max)
		{
			*max = a[i];
		}
		if (a[i] < *min)
		{
			*min = a[i];
		}
		total += a[i];
	}
	*mean = total / size;
	double stddev_total = 0;
	for (int i = 0; i < size; ++i)
	{
		stddev_total += (a[i] - *mean) * (a[i] - *mean);
	}
	*stddev = sqrt((stddev_total / size));
}

void usage()
{
	printf("\nusage: stats samples population lowerbound upperbound\n");
	printf("       samples: number of samples\n");
       	printf("       population: number of random values to generate in each sample\n");
       	printf("       lowerbound: bottom of random number range\n");
       	printf("       upperbound: top of random number range\n");
	exit(0);

}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("incorrect number of arguments\n");
		usage();
	}
        for (int i = 2; i < argc; i++)
        {
		int is_number = is_valid_int(argv[i]);
        	if (is_number == 0)
        	{
                	printf("all arguments must be integers\n");
			usage();
       		}
        }	
	srand(time(NULL));
	int runs = atoi(argv[1]);
	if (runs <= 0)
	{
		printf("samples must be a positive integer\n");
		usage();
	}
	int size = atoi(argv[2]);
	if (size <= 0)
	{
		printf("population must be a positive integer\n");
		usage();
	}
	int lower = atoi(argv[3]);
	int minimum = 0;
	int *min = &minimum;
	int upper = atoi(argv[4]);
	if (upper < lower)
	{
		printf("upperbound must be >= lowerbound\n");
		usage();
	}
	int maximum = 0;
	int *max = &maximum;
	double mean = 0;
	double *m = &mean;
	double stddev = 0;
	double *std = &stddev;
	for (int i = 0; i < runs; ++i)
	{	
		int *nums = generate_population(size, lower, upper); 
		printf("Sample %i: ", i+1);
		get_stats(nums, size, min, max, m, std);
		printf("min=%i, max=%i, mean=%g, stddev=%g\n", minimum, maximum, mean, stddev);
		free(nums);
	}
	return 0;
}

