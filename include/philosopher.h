/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:06:37 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/06 11:55:32 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

// Color Definitions for Logs
# define RESET      "\033[0m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"

// philo Struct
typedef struct s_philosopher
{
	int				philo_id;
	int				*meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		*last_meal_time;
	int				total_forks;
	int				total_philos;
	pthread_t		thread;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*state_mutex;
	long long		sim_start_time;
}	t_philo;

// Action Functions
void			take_forks(t_philo *philo);
void			eat_spaghetti(t_philo *philo);
void			release_forks(t_philo *philo);

// State Management
void			sleep_philosopher(t_philo *philo);
void			think_philosopher(t_philo *philo);

// Thread Management
void			*philosopher_lifecycle(void *philo);
void			create_philosopher_threads(t_philo *philos);

// Initialization
pthread_mutex_t	*initialize_fork_mutexes(int total_philos);
long long		*init_last_meal_time(int total_philos);
void			configure_philosopher_data(t_philo *configured_philos,
					t_philo *ini_settings,
					pthread_mutex_t *fork_mutexes,
					long long *last_meal_timestamps);
t_philo			*initialize_philosophers(t_philo *ini_settings);
t_philo			*setup_simulation(int argc, char **argv);

// Health Monitoring
t_philo			*initialize_health_monitor(t_philo *philo);
void			*monitor_philosopher_health(void *monitor_settings);
void			link_health_monitor_to_philosophers(t_philo *philos,
					t_philo *monitor);

// Argument Parsing and Validation
int				parse_arguments(int argc, char **argv, t_philo *ini_settings);
int				validate_philosopher_count(const char *arg);
int				validate_time_value(const char *arg);
int				validate_meals_required(const char *arg);

// Log and Status Printing
void			print_status_message(t_philo *philo, char *action);
void			announce_death(int philo_id, long long elapsed_time);
void			display_argument_error(void);
void			print_number_fd(int n, int fd);

// Utility Functions
void			print_string_fd(char *str, int fd);
int				string_to_integer(const char *str);
long long		current_time(void);
void			sleep_for_duration(long long duration);
size_t			string_length(char *str);
int				is_numeric_string(const char *str);
int				is_digit_character(int character);
void			cleanup_simulation_memory(t_philo *philos,
					t_philo *health_monitor);

#endif
