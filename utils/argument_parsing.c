/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:29:00 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:52 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void display_argument_error(void)
{
	write(2, RED, string_length(RED));
	print_string_fd("Error: Invalid number of arguments\n", 2);
	write(2, RESET, string_length(RESET));
	write(2, "\n", 1);
	write(2, GREEN, string_length(GREEN));
	print_string_fd("Usage: ./philo [number_of_philosophers] [time_to_die] ", 2);
	print_string_fd("[time_to_eat] [time_to_sleep] ", 2);
	print_string_fd("[number_of_times_each_philosopher_must_eat (optional)]\n", 2);
	write(2, RESET, string_length(RESET));
	write(2, "\n", 1);
	write(2, YELLOW, string_length(YELLOW));
	print_string_fd("Example: ./philo 5 800 200 200 3\n", 2);
	write(2, RESET, string_length(RESET));
	write(2, "\n", 1);
	write(2, RESET, string_length(RESET));
}

bool parse_arguments(int argc, char **argv, t_philosopher *simulation_settings)
{
	if (argc < 5 || argc > 6)
	{
		display_argument_error();
		return (false);
	}
	if (!validate_philosopher_count(argv[1])
		|| !validate_time_value(argv[2])
		|| !validate_time_value(argv[3])
		|| !validate_time_value(argv[4])
		|| (argc == 6 && !validate_meals_required(argv[5])))
	{
		return (false);
	}
	simulation_settings->total_philosophers = string_to_integer(argv[1]);
	simulation_settings->time_until_death = string_to_integer(argv[2]);
	simulation_settings->eating_duration = string_to_integer(argv[3]);
	simulation_settings->sleeping_duration = string_to_integer(argv[4]);
	if (argc == 6)
		simulation_settings->meals_required = string_to_integer(argv[5]);
	else
		simulation_settings->meals_required = -1;
	return (true);
}
