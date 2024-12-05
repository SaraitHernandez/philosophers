/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:40:58 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:30 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void sleep_philosopher(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->state_mutex);
	print_status_message(philosopher, "is sleeping");
	pthread_mutex_unlock(philosopher->state_mutex);
	sleep_for_duration(philosopher->sleeping_duration);
}

void think_philosopher(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->state_mutex);
	print_status_message(philosopher, "is thinking");
	pthread_mutex_unlock(philosopher->state_mutex);
}
