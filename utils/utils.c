/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:47:23 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:38:20 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t string_length(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void print_string_fd(char *str, int fd)
{
	while (*str != '\0')
	{
		write(fd, str, 1);
		str++;
	}
}

int skip_spaces_and_sign(const char *str, int *i)
{
	int sign;

	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

int string_to_integer(const char *str)
{
	int         sign;
	int         i;
	long long   result;
	long long   prev_result;
	long long   temp;

	i = 0;
	result = 0;
	sign = skip_spaces_and_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result = result * 10 + str[i] - '0';
		temp = result / 10;
		if (temp != prev_result)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		i++;
	}
	return (sign * result);
}

void print_number_fd(int n, int fd)
{
	char c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		print_number_fd(n / 10, fd);
		print_number_fd(n % 10, fd);
	}
}

int is_digit_character(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

long long current_timestamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void sleep_for_duration(long long duration)
{
	long long start_time;

	start_time = current_timestamp();
	while (current_timestamp() - start_time < duration)
		usleep(100);
}

void cleanup_simulation_memory(t_philosopher *philosophers, t_philosopher *health_monitor)
{
	int i;

	i = 0;
	sleep_for_duration(philosophers->time_until_death + philosophers->eating_duration
					   + philosophers->sleeping_duration + 100);
	while (i < philosophers->total_philosophers)
	{
		pthread_mutex_destroy(&philosophers[i].fork_mutexes[i]);
		pthread_mutex_destroy(philosophers[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(health_monitor->state_mutex);
	free(philosophers->fork_mutexes);
	free(philosophers->meals_count);
	free(philosophers->last_meal_timestamp);
	free(philosophers->state_mutex);
	free(philosophers);
	philosophers = NULL;
	free(health_monitor);
}
