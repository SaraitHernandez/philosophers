/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:28:01 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_digit_character(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_for_duration(long long duration)
{
	long long	start_time;

	start_time = current_time();
	while (current_time() - start_time < duration)
		usleep(100);
}

void	cleanup_simulation_memory(t_philo *philos,
			t_philo *health_monitor)
{
	int	i;

	i = 0;
	sleep_for_duration(philos->time_to_die + philos->time_to_eat
		+ philos->time_to_sleep + 100);
	while (i < philos->total_philos)
	{
		pthread_mutex_destroy(&philos[i].fork_mutexes[i]);
		pthread_mutex_destroy(philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(health_monitor->state_mutex);
	free(philos->fork_mutexes);
	free(philos->meals_count);
	free(philos->last_meal_time);
	free(philos->state_mutex);
	free(philos);
	philos = NULL;
	free(health_monitor);
}
