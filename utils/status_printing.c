/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:40 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status_message(t_philo *philo, char *action)
{
	char	*colors[6];

	colors[0] = RED;
	colors[1] = GREEN;
	colors[2] = YELLOW;
	colors[3] = BLUE;
	colors[4] = MAGENTA;
	colors[5] = CYAN;
	write(1, colors[philo->philo_id % 6],
		string_length(colors[philo->philo_id % 6]));
	print_number_fd(current_time()
		- philo->sim_start_time, 1);
	write(1, "\t", 1);
	print_number_fd(philo->philo_id, 1);
	write(1, "\t", 1);
	write(1, action, string_length(action));
	write(1, RESET, string_length(RESET));
	write(1, "\n", 1);
}

void	announce_death(int philo_id, long long elapsed_time)
{
	print_number_fd(elapsed_time, 1);
	write(1, "\t", 1);
	print_number_fd(philo_id, 1);
	write(1, "\t", 1);
	write(1, "died", 4);
	write(1, "\n", 1);
}
