/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:11:17 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:21 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void take_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->fork_mutexes[philosopher->philosopher_id - 1]);
	if (philosopher->philosopher_id == 1)
		pthread_mutex_lock(&philosopher->fork_mutexes[philosopher->total_philosophers - 1]);
	else
		pthread_mutex_lock(&philosopher->fork_mutexes[philosopher->philosopher_id - 2]);
	pthread_mutex_lock(philosopher->state_mutex);
	print_status_message(philosopher, "has taken a fork");
	pthread_mutex_unlock(philosopher->state_mutex);
}

void eat_spaghetti(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->state_mutex);
	print_status_message(philosopher, "is eating");
	philosopher->last_meal_timestamp[philosopher->philosopher_id - 1] = current_timestamp();
	philosopher->meals_count[philosopher->philosopher_id - 1]++;
	pthread_mutex_unlock(philosopher->state_mutex);
	sleep_for_duration(philosopher->eating_duration);
}

void release_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->fork_mutexes[philosopher->philosopher_id - 1]);
	if (philosopher->philosopher_id == 1)
		pthread_mutex_unlock(&philosopher->fork_mutexes[philosopher->total_philosophers - 1]);
	else
		pthread_mutex_unlock(&philosopher->fork_mutexes[philosopher->philosopher_id - 2]);
}
