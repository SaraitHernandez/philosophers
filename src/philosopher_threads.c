/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:16:58 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:36 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philosopher_lifecycle(void *philosopher_ptr)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)philosopher_ptr;
	if (philosopher->philosopher_id % 2 == 0)
		sleep_for_duration(10);
	while (1)
	{
		take_forks(philosopher);
		eat_spaghetti(philosopher);
		release_forks(philosopher);
		sleep_philosopher(philosopher);
		think_philosopher(philosopher);
	}
}

void create_philosopher_threads(t_philosopher *philosophers)
{
	int i;

	i = 0;
	while (i < philosophers->total_philosophers)
	{
		philosophers[i].simulation_start_time = current_timestamp();
		pthread_create(&philosophers[i].thread, NULL,
					   philosopher_lifecycle, &philosophers[i]);
		pthread_detach(philosophers[i].thread);
		i++;
	}
}
