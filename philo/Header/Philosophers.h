/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:56:06 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/21 17:39:36 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h> 

# define ARGUMENT_ERROR "WRONG NUMBER OF ARGUMENTS"
# define ALLOC_ERROR "ERROR WHILE ALLOCATING MEMORY"
# define INPUT_ERROR "INVALID INPUT"
# define THREAD_ERROR "ERROR HANDLING THREADS"
# define TIME_ERROR "ERROR HANDLING TIME"

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

struct	s_general;

typedef struct s_philo
{
	struct s_general	*general;
	int					id;
	int					eating_count;
	int					is_eating;
	int					philo_time_to_die;
	pthread_mutex_t		philo_lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			supervisor_thread;
}	t_philo;

typedef struct s_general
{
	int				philo_number;
	int				meals_number;
	int				is_dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	pthread_t		*thread_id;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	general_lock;
	pthread_mutex_t	write;
}	t_general;

//	UTILS
long		ft_atoi_long(const char *str);
int			ft_atoi(const char *str);
int			error(char *str, t_general *general);
int			ft_strcmp(char *s1, char *s2);
void		messages(char *str, t_philo *philo);
void		thread_cleanup(t_general *general);
int			get_time(void);
int			ft_usleep(int time);
void		philosopher_sleep(t_philo *philo);

//	INICIALIZACION
int			init_structures(t_general *general, char **argv, int argc);
int			thread_init(t_general *general);

//	VERIFICACION DE ARGUMENTOS
int			check_arguments(char **argv);
int			check_numbers(char **argv);

//	ACCIONES
void		eat(t_philo *philo);

//	RUTINA & MONITOREO
void		*philosophers_routine(void *philo_pointer);
void		*monitor_meals(void *general_pointer);
int			create_monitor_thread(t_general *general);
int			start_philo_threads(t_general *general);
int			join_philo_threads(t_general *general);

#endif