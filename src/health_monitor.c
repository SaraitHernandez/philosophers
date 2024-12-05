/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:29:06 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:05 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher *initialize_health_monitor(t_philosopher *philosopher)
{
	t_philosopher *monitor;

	monitor = malloc(sizeof(t_philosopher));
	if (!monitor)
		return (NULL);
	monitor->philosopher_id = 0;
	monitor->meals_count = philosopher->meals_count;
	monitor->time_until_death = philosopher->time_until_death;
	monitor->eating_duration = philosopher->eating_duration;
	monitor->sleeping_duration = philosopher->sleeping_duration;
	monitor->meals_required = philosopher->meals_required;
	monitor->last_meal_timestamp = philosopher->last_meal_timestamp;
	monitor->total_forks = philosopher->total_philosophers;
	monitor->total_philosophers = philosopher->total_philosophers;
	monitor->fork_mutexes = NULL;
	monitor->state_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor->state_mutex, NULL);
	return (monitor);
}

void link_health_monitor_to_philosophers(t_philosopher *philosophers, t_philosopher *monitor)
{
	int i;

	i = 0;
	while (i < monitor->total_philosophers)
	{
		philosophers[i].state_mutex = monitor->state_mutex;
		i++;
	}
	monitor->simulation_start_time = current_timestamp();
}

bool check_meals_completion(t_philosopher *monitor)
{
	int i;

	i = 0;
	if (monitor->meals_required == -1)
		return (true);
	while (i < monitor->total_philosophers)
	{
		pthread_mutex_lock(monitor->state_mutex);
		if (monitor->meals_count[i] < monitor->meals_required)
			return (pthread_mutex_unlock(monitor->state_mutex), true);
		pthread_mutex_unlock(monitor->state_mutex);
		i++;
	}
	pthread_mutex_lock(monitor->state_mutex);
	return (false);
}

void *monitor_philosopher_health(void *monitor_settings)
{
	t_philosopher   *monitor;
	int             i;
	long long       time_since_last_meal;

	monitor = (t_philosopher *)monitor_settings;
	i = 0;
	sleep_for_duration(10);
	while (i < monitor->total_philosophers && check_meals_completion(monitor))
	{
		pthread_mutex_lock(monitor->state_mutex);
		time_since_last_meal = current_timestamp() - monitor->last_meal_timestamp[i];
		pthread_mutex_unlock(monitor->state_mutex);
		if (time_since_last_meal >= monitor->time_until_death)
		{
			pthread_mutex_lock(monitor->state_mutex);
			announce_death(i + 1, current_timestamp() - monitor->simulation_start_time);
			return (NULL);
		}
		if (i + 1 == monitor->total_philosophers)
			i = -1;
		i++;
	}
	return (NULL);
}
