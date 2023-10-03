#include "philo.h"

long	timestamp(void)
{
	struct timeval	current_time;
	long			stamp;

	stamp = 0;
	gettimeofday(&current_time, NULL);
	stamp = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (stamp);
}

long	passed_time(long start)
{
	struct timeval	current_time;
	long			current;

	gettimeofday(&current_time, NULL);
	current = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (current - start);
}
