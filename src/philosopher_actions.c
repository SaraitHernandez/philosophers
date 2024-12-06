/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:11:17 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutexes[philo->philo_id - 1]);
	if (philo->philo_id == 1)
		pthread_mutex_lock(&philo->fork_mutexes[philo->total_philos - 1]);
	else
		pthread_mutex_lock(&philo->fork_mutexes[philo->philo_id - 2]);
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "has taken a fork");
	pthread_mutex_unlock(philo->state_mutex);
}

void	eat_spaghetti(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is eating");
	philo->last_meal_time[philo->philo_id - 1] = current_time();
	philo->meals_count[philo->philo_id - 1]++;
	pthread_mutex_unlock(philo->state_mutex);
	sleep_for_duration(philo->time_to_eat);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutexes[philo->philo_id - 1]);
	if (philo->philo_id == 1)
		pthread_mutex_unlock(&philo->fork_mutexes[philo->total_philos - 1]);
	else
		pthread_mutex_unlock(&philo->fork_mutexes[philo->philo_id - 2]);
}
