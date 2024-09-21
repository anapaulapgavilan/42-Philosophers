/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:18:31 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/21 17:44:58 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		return (error(TIME_ERROR, NULL));
	}
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->general->write);
	time = get_time() - philo->general->start_time;
	pthread_mutex_lock(&philo->general->general_lock);
	if (ft_strcmp(DIED, str) == 0 && philo->general->is_dead == 0)
	{
		printf("%i %d %s\n", time, philo->id, str);
		philo->general->is_dead = 1;
	}
	if (philo->general->is_dead == 0)
	{
		printf("%i %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->general->general_lock);
	pthread_mutex_unlock(&philo->general->write);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		usleep(100);
		pthread_mutex_lock(philo->right_fork);
		messages(TAKE_FORKS, philo);
		usleep(100);
		pthread_mutex_lock(philo->left_fork);
		messages(TAKE_FORKS, philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		messages(TAKE_FORKS, philo);
		pthread_mutex_lock(philo->right_fork);
		messages(TAKE_FORKS, philo);
	}
}

void	drop_forks(t_philo *philo)
{
		if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->is_eating = 1;
	philo->philo_time_to_die = get_time() + philo->general->time_to_die;
	messages(EATING, philo);
	philo->eating_count++;
	ft_usleep(philo->general->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->philo_lock);
	drop_forks(philo);
}
