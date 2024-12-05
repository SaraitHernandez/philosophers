/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:09:29 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:13 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
	t_philosopher *philosophers;
	t_philosopher *health_monitor;

	philosophers = setup_simulation(argc, argv);
	if (!philosophers)
	{
		write(2, RED, string_length(RED));
		print_string_fd("Simulation initialization failed.\n", 2);
		write(2, RESET, string_length(RESET));
		return (1);
	}
	health_monitor = initialize_health_monitor(philosophers);
	if (!health_monitor)
	{
		write(2, RED, string_length(RED));
		print_string_fd("Health monitor initialization failed.\n", 2);
		write(2, RESET, string_length(RESET));
		return (1);
	}
	link_health_monitor_to_philosophers(philosophers, health_monitor);
	create_philosopher_threads(philosophers);
	pthread_create(&health_monitor->thread, NULL,
		monitor_philosopher_health, health_monitor);
	pthread_join(health_monitor->thread, NULL);
	return (cleanup_simulation_memory(philosophers, health_monitor), 0);
}
