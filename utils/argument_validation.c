/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:15:41 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:24:57 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool is_numeric_string(const char *str)
{
    while (*str)
    {
        if (!is_digit_character(*str))
            return (false);
        str++;
    }
    return (true);
}

bool validate_philosopher_count(const char *arg)
{
    if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
    {
        print_string_fd("Error: Invalid number of philosophers argument\n", 2);
        return (false);
    }
    return (true);
}

bool validate_time_value(const char *arg)
{
    if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
    {
        print_string_fd("Error: Invalid time argument\n", 2);
        return (false);
    }
    return (true);
}

bool validate_meals_required(const char *arg)
{
    if (!is_numeric_string(arg) || string_to_integer(arg) <= 0)
    {
        print_string_fd("Error: Invalid number of times to eat argument\n", 2);
        return (false);
    }
    return (true);
}
