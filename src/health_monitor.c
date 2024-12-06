/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:06 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:34 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*initialize_health_monitor(t_philo *philo)
{
	t_philo	*monitor;

	monitor = malloc(sizeof(t_philo));
	if (!monitor)
		return (NULL);
	monitor->philo_id = 0;
	monitor->meals_count = philo->meals_count;
	monitor->time_to_die = philo->time_to_die;
	monitor->time_to_eat = philo->time_to_eat;
	monitor->time_to_sleep = philo->time_to_sleep;
	monitor->meals_required = philo->meals_required;
	monitor->last_meal_time = philo->last_meal_time;
	monitor->total_forks = philo->total_philos;
	monitor->total_philos = philo->total_philos;
	monitor->fork_mutexes = NULL;
	monitor->state_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor->state_mutex, NULL);
	return (monitor);
}

void	link_health_monitor_to_philosophers(t_philo *philos, t_philo *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->total_philos)
	{
		philos[i].state_mutex = monitor->state_mutex;
		i++;
	}
	monitor->sim_start_time = current_time();
}

int	check_meals_completion(t_philo *monitor)
{
	int	i;

	i = 0;
	if (monitor->meals_required == -1)
		return (1);
	while (i < monitor->total_philos)
	{
		pthread_mutex_lock(monitor->state_mutex);
		if (monitor->meals_count[i] < monitor->meals_required)
			return (pthread_mutex_unlock(monitor->state_mutex), 1);
		pthread_mutex_unlock(monitor->state_mutex);
		i++;
	}
	pthread_mutex_lock(monitor->state_mutex);
	return (0);
}

void	*monitor_philosopher_health(void *monitor_settings)
{
	t_philo			*monitor;
	int				i;
	long long		last_meal_time;

	monitor = (t_philo *)monitor_settings;
	i = 0;
	sleep_for_duration(10);
	while (i < monitor->total_philos && check_meals_completion(monitor))
	{
		pthread_mutex_lock(monitor->state_mutex);
		last_meal_time = current_time() - monitor->last_meal_time[i];
		pthread_mutex_unlock(monitor->state_mutex);
		if (last_meal_time >= monitor->time_to_die)
		{
			pthread_mutex_lock(monitor->state_mutex);
			announce_death(i + 1, current_time() - monitor->sim_start_time);
			return (NULL);
		}
		if (i + 1 == monitor->total_philos)
			i = -1;
		i++;
	}
	return (NULL);
}
