/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:13:48 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:37:42 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher *setup_simulation(int argc, char **argv)
{
	t_philosopher *simulation_settings;
	t_philosopher *configured_philosophers;

	simulation_settings = malloc(sizeof(t_philosopher));
	if (!simulation_settings)
		return (NULL);
	if (!parse_arguments(argc, argv, simulation_settings))
	{
		free(simulation_settings);
		return (NULL);
	}
	configured_philosophers = initialize_philosophers(simulation_settings);
	if (!configured_philosophers)
	{
		free(simulation_settings);
		return (NULL);
	}
	return (configured_philosophers);
}

t_philosopher *initialize_philosophers(t_philosopher *simulation_settings)
{
	t_philosopher     *configured_philosophers;
	pthread_mutex_t   *fork_mutexes;
	long long         *last_meal_timestamps;

	configured_philosophers = malloc(sizeof(t_philosopher) * simulation_settings->total_philosophers);
	if (!configured_philosophers)
		return (NULL);
	fork_mutexes = initialize_fork_mutexes(simulation_settings->total_philosophers);
	last_meal_timestamps = initialize_last_meal_timestamps(simulation_settings->total_philosophers);
	configure_philosopher_data(configured_philosophers, simulation_settings,
							   fork_mutexes, last_meal_timestamps);
	return (configured_philosophers);
}

pthread_mutex_t *initialize_fork_mutexes(int total_philosophers)
{
	int             i;
	pthread_mutex_t *fork_mutexes;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * total_philosophers);
	if (!fork_mutexes)
		return (NULL);
	while (i < total_philosophers)
	{
		pthread_mutex_init(&fork_mutexes[i], NULL);
		i++;
	}
	return (fork_mutexes);
}

long long *initialize_last_meal_timestamps(int total_philosophers)
{
	int         i;
	long long   *last_meal_timestamps;

	i = 0;
	last_meal_timestamps = malloc(sizeof(long long) * total_philosophers);
	if (!last_meal_timestamps)
		return (NULL);
	while (i < total_philosophers)
	{
		last_meal_timestamps[i] = current_timestamp();
		i++;
	}
	return (last_meal_timestamps);
}

void configure_philosopher_data(t_philosopher *configured_philosophers,
								t_philosopher *simulation_settings,
								pthread_mutex_t *fork_mutexes,
								long long *last_meal_timestamps)
{
	int i;
	int *meals;

	meals = malloc(sizeof(int) * simulation_settings->total_philosophers);
	if (!meals)
		return;
	memset(meals, 0, sizeof(int) * simulation_settings->total_philosophers);
	i = 0;
	while (i < simulation_settings->total_philosophers)
	{
		configured_philosophers[i].philosopher_id = i + 1;
		configured_philosophers[i].meals_count = meals;
		configured_philosophers[i].time_until_death = simulation_settings->time_until_death;
		configured_philosophers[i].eating_duration = simulation_settings->eating_duration;
		configured_philosophers[i].sleeping_duration = simulation_settings->sleeping_duration;
		configured_philosophers[i].meals_required = simulation_settings->meals_required;
		configured_philosophers[i].last_meal_timestamp = last_meal_timestamps;
		configured_philosophers[i].total_forks = simulation_settings->total_philosophers;
		configured_philosophers[i].total_philosophers = simulation_settings->total_philosophers;
		configured_philosophers[i].fork_mutexes = fork_mutexes;
		i++;
	}
	free(simulation_settings);
}
