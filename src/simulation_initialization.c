/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:13:48 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:52:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*setup_simulation(int argc, char **argv)
{
	t_philo	*ini_settings;
	t_philo	*configured_philos;

	ini_settings = malloc(sizeof(t_philo));
	if (!ini_settings)
		return (NULL);
	if (!parse_arguments(argc, argv, ini_settings))
	{
		free(ini_settings);
		return (NULL);
	}
	configured_philos = initialize_philosophers(ini_settings);
	if (!configured_philos)
	{
		free(ini_settings);
		return (NULL);
	}
	return (configured_philos);
}

t_philo	*initialize_philosophers(t_philo *ini_settings)
{
	t_philo			*configured_philos;
	pthread_mutex_t	*fork_mutexes;
	long long		*last_meal_timestamps;

	configured_philos = malloc(sizeof(t_philo) * ini_settings->total_philos);
	if (!configured_philos)
		return (NULL);
	fork_mutexes = initialize_fork_mutexes(ini_settings->total_philos);
	last_meal_timestamps = init_last_meal_time(ini_settings->total_philos);
	configure_philosopher_data(configured_philos, ini_settings,
		fork_mutexes, last_meal_timestamps);
	return (configured_philos);
}

pthread_mutex_t	*initialize_fork_mutexes(int total_philos)
{
	int				i;
	pthread_mutex_t	*fork_mutexes;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * total_philos);
	if (!fork_mutexes)
		return (NULL);
	while (i < total_philos)
	{
		pthread_mutex_init(&fork_mutexes[i], NULL);
		i++;
	}
	return (fork_mutexes);
}

long long	*init_last_meal_time(int total_philos)
{
	int			i;
	long long	*last_meal_timestamps;

	i = 0;
	last_meal_timestamps = malloc(sizeof(long long) * total_philos);
	if (!last_meal_timestamps)
		return (NULL);
	while (i < total_philos)
	{
		last_meal_timestamps[i] = current_time();
		i++;
	}
	return (last_meal_timestamps);
}

void	configure_philosopher_data(t_philo *configured_philos,
			t_philo *ini_settings,
			pthread_mutex_t *fork_mutexes,
			long long *last_meal_timestamps)
{
	int	i;
	int	*meals;

	meals = malloc(sizeof(int) * ini_settings->total_philos);
	if (!meals)
		return ;
	memset(meals, 0, sizeof(int) * ini_settings->total_philos);
	i = 0;
	while (i < ini_settings->total_philos)
	{
		configured_philos[i].philo_id = i + 1;
		configured_philos[i].meals_count = meals;
		configured_philos[i].time_to_die = ini_settings->time_to_die;
		configured_philos[i].time_to_eat = ini_settings->time_to_eat;
		configured_philos[i].time_to_sleep = ini_settings->time_to_sleep;
		configured_philos[i].meals_required = ini_settings->meals_required;
		configured_philos[i].last_meal_time = last_meal_timestamps;
		configured_philos[i].total_forks = ini_settings->total_philos;
		configured_philos[i].total_philos = ini_settings->total_philos;
		configured_philos[i].fork_mutexes = fork_mutexes;
		i++;
	}
	free(ini_settings);
}
