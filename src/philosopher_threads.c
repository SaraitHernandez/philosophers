/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:16:58 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_lifecycle(void *philosopher_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher_ptr;
	if (philo->philo_id % 2 == 0)
		sleep_for_duration(10);
	while (1)
	{
		take_forks(philo);
		eat_spaghetti(philo);
		release_forks(philo);
		sleep_philosopher(philo);
		think_philosopher(philo);
	}
}

void	create_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->total_philos)
	{
		philos[i].sim_start_time = current_time();
		pthread_create(&philos[i].thread, NULL,
			philosopher_lifecycle, &philos[i]);
		pthread_detach(philos[i].thread);
		i++;
	}
}
