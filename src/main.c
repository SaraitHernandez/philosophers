/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:09:29 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:49:19 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_philo	*health_monitor;

	philos = setup_simulation(argc, argv);
	if (!philos)
	{
		print_string_fd("Simulation initialization failed.\n", 2);
		return (1);
	}
	health_monitor = initialize_health_monitor(philos);
	if (!health_monitor)
	{
		print_string_fd("Health monitor initialization failed.\n", 2);
		return (1);
	}
	link_health_monitor_to_philosophers(philos, health_monitor);
	create_philosopher_threads(philos);
	pthread_create(&health_monitor->thread, NULL,
		monitor_philosopher_health, health_monitor);
	pthread_join(health_monitor->thread, NULL);
	return (cleanup_simulation_memory(philos, health_monitor), 0);
}
