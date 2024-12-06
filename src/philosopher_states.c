/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:40:58 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:47:39 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleep_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is sleeping");
	pthread_mutex_unlock(philo->state_mutex);
	sleep_for_duration(philo->time_to_sleep);
}

void	think_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is thinking");
	pthread_mutex_unlock(philo->state_mutex);
}
