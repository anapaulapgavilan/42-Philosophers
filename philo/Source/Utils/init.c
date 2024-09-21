/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:05 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/21 17:39:19 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

int	dynamic_alloc(t_general *general)
{
	general->thread_id = malloc(sizeof(pthread_t) * general->philo_number);
	if (!general->thread_id)
	{
		return (error(ALLOC_ERROR, general));
	}
	general->forks = malloc(sizeof(pthread_mutex_t) * general->philo_number);
	if (!general->forks)
	{
		return (error(ALLOC_ERROR, general));
	}
	general->philos = malloc(sizeof(t_philo) * general->philo_number);
	if (!general->philos)
	{
		return (error(ALLOC_ERROR, general));
	}
	return (0);
}

int	init_forks(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->philo_number)
	{
		pthread_mutex_init(&general->forks[i], NULL);
		i++;
	}
	i = 0;
	general->philos[0].left_fork = &general->forks[0];
	general->philos[0].right_fork = &general->forks[general->philo_number - 1];
	i = 1;
	while (i < general->philo_number)
	{
		general->philos[i].left_fork = &general->forks[i];
		general->philos[i].right_fork = &general->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->philo_number)
	{
		general->philos[i].general = general;
		general->philos[i].id = i + 1;
		general->philos[i].philo_time_to_die = general->time_to_die;
		general->philos[i].eating_count = 0;
		general->philos[i].is_eating = 0;
		pthread_mutex_init(&general->philos[i].philo_lock, NULL);
		i++;
	}
}

int	init_data(t_general *general, char **argv, int argc)
{
	general->philo_number = ft_atoi(argv[1]);
	general->time_to_die = ft_atoi(argv[2]);
	general->time_to_eat = ft_atoi(argv[3]);
	general->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		general->meals_number = ft_atoi(argv[5]);
	}
	else
	{
		general->meals_number = -1;
	}
	if (general->philo_number <= 0 || general->philo_number > 200
		|| general->time_to_die < 0 || general->time_to_eat < 0
		|| general->time_to_sleep < 0)
	{
		return (error(ALLOC_ERROR, general));
	}
	general->is_dead = 0;
	pthread_mutex_init(&general->write, NULL);
	pthread_mutex_init(&general->general_lock, NULL);
	return (0);
}

int	init_structures(t_general *general, char **argv, int argc)
{
	if (init_data(general, argv, argc))
	{
		return (0);
	}
	if (dynamic_alloc(general))
	{
		return (0);
	}
	if (init_forks(general))
	{
		return (0);
	}
	init_philos(general);
	return (1);
}
