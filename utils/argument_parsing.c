/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:47:39 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_argument_error(void)
{
	print_string_fd("Error: Invalid number of arguments\n", 2);
	write(2, "\n", 1);
	print_string_fd("Usage: ./philo [number_of_philo] [time_to_die] ", 2);
	print_string_fd("[time_to_eat] [time_to_sleep] ", 2);
	print_string_fd("[number_of_times_each_philo_must_eat (optional)]\n", 2);
	write(2, "\n", 1);
	print_string_fd("Example: ./philo 5 800 200 200 3\n", 2);
	write(2, "\n", 1);
}

int	parse_arguments(int argc, char **argv, t_philo *ini_settings)
{
	if (argc < 5 || argc > 6)
	{
		display_argument_error();
		return (0);
	}
	if (!validate_philosopher_count(argv[1])
		|| !validate_time_value(argv[2])
		|| !validate_time_value(argv[3])
		|| !validate_time_value(argv[4])
		|| (argc == 6 && !validate_meals_required(argv[5])))
	{
		return (0);
	}
	ini_settings->total_philos = string_to_integer(argv[1]);
	ini_settings->time_to_die = string_to_integer(argv[2]);
	ini_settings->time_to_eat = string_to_integer(argv[3]);
	ini_settings->time_to_sleep = string_to_integer(argv[4]);
	if (argc == 6)
		ini_settings->meals_required = string_to_integer(argv[5]);
	else
		ini_settings->meals_required = -1;
	return (1);
}
