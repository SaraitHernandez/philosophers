/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:41 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:49:19 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_numeric_string(const char *str)
{
	while (*str)
	{
		if (!is_digit_character(*str))
			return (0);
		str++;
	}
	return (1);
}

int	validate_philosopher_count(const char *arg)
{
	if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
	{
		print_string_fd("Error: Invalid number of philos argument\n", 2);
		return (0);
	}
	return (1);
}

int	validate_time_value(const char *arg)
{
	if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
	{
		print_string_fd("Error: Invalid time argument\n", 2);
		return (0);
	}
	return (1);
}

int	validate_meals_required(const char *arg)
{
	if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
	{
		print_string_fd("Error: Invalid number of times to eat argument\n", 2);
		return (0);
	}
	return (1);
}
