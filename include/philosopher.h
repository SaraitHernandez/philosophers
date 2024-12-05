/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:06:37 by zelhajou          #+#    #+#             */
/*   Updated: 2024/12/05 09:36:55 by sarherna         ###   ########.fr       */
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
# include <stdbool.h>

// Color Definitions for Logs
# define RESET      "\033[0m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"

// Philosopher Struct
typedef struct s_philosopher
{
	int             philosopher_id;
	int             *meals_count;
	int             time_until_death;
	int             eating_duration;
	int             sleeping_duration;
	int             meals_required;
	long long       *last_meal_timestamp;
	int             total_forks;
	int             total_philosophers;
	pthread_t       thread;
	pthread_mutex_t *fork_mutexes;
	pthread_mutex_t *state_mutex;
	long long       simulation_start_time;
}   t_philosopher;

// Action Functions
void            take_forks(t_philosopher *philosopher);
void            eat_spaghetti(t_philosopher *philosopher);
void            release_forks(t_philosopher *philosopher);

// State Management
void            sleep_philosopher(t_philosopher *philosopher);
void            think_philosopher(t_philosopher *philosopher);

// Thread Management
void            *philosopher_lifecycle(void *philosopher);
void            create_philosopher_threads(t_philosopher *philosophers);

// Initialization
pthread_mutex_t *initialize_fork_mutexes(int total_philosophers);
long long       *initialize_last_meal_timestamps(int total_philosophers);
void            configure_philosopher_data(t_philosopher *configured_philosophers,
					t_philosopher *simulation_settings,
					pthread_mutex_t *fork_mutexes,
					long long *last_meal_timestamps);
t_philosopher   *initialize_philosophers(t_philosopher *simulation_settings);
t_philosopher   *setup_simulation(int argc, char **argv);

// Health Monitoring
t_philosopher   *initialize_health_monitor(t_philosopher *philosopher);
void            *monitor_philosopher_health(void *monitor_settings);
void            link_health_monitor_to_philosophers(t_philosopher *philosophers,
					t_philosopher *monitor);

// Argument Parsing and Validation
bool            parse_arguments(int argc, char **argv, t_philosopher *simulation_settings);
bool            validate_philosopher_count(const char *arg);
bool            validate_time_value(const char *arg);
bool            validate_meals_required(const char *arg);

// Log and Status Printing
void            print_status_message(t_philosopher *philosopher, char *action);
void            announce_death(int philosopher_id, long long elapsed_time);
void            display_argument_error(void);
void            print_number_fd(int n, int fd);

// Utility Functions
void            print_string_fd(char *str, int fd);
int             string_to_integer(const char *str);
long long       current_timestamp(void);
void            sleep_for_duration(long long duration);
size_t          string_length(char *str);
bool            is_numeric_string(const char *str);
int             is_digit_character(int character);
void            cleanup_simulation_memory(t_philosopher *philosophers,
					t_philosopher *health_monitor);

#endif
