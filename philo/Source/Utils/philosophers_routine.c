/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:21:29 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/21 17:48:21 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

void	meals(t_philo *philo, int *all_fed, int meals_number)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->eating_count < meals_number)
		*all_fed = 0;
	pthread_mutex_unlock(&philo->philo_lock);
}

void	*monitor_meals(void *general_pointer)
{
	t_general	*general;
	int			i;
	int			all_fed;

	general = (t_general *)general_pointer;
	while (general->is_dead == 0)
	{
		i = -1;
		all_fed = 1;
		if (general->meals_number > 0)
		{
			while (++i < general->philo_number)
			{
				meals(&general->philos[i], &all_fed, general->meals_number);
			}
			if (all_fed)
			{
				pthread_mutex_lock(&general->write);
				general->is_dead = 1;
				pthread_mutex_unlock(&general->write);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->general->general_lock);
		if (philo->general->is_dead == 1)
        {
            pthread_mutex_unlock(&philo->general->general_lock);
            break;
        }
		pthread_mutex_unlock(&philo->general->general_lock);
		pthread_mutex_lock(&philo->philo_lock);
        if ((get_time() >= philo->philo_time_to_die) && philo->is_eating == 0)
        {
            messages(DIED, philo);
        }
        pthread_mutex_unlock(&philo->philo_lock);
        usleep(100);
	}
	return ((void *)0);
}

void	*philosophers_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->philo_time_to_die = philo->general->time_to_die + get_time();
	if (philo->id % 2 == 1)
		usleep(100);
	else
		usleep(200);
	if (pthread_create(&philo->supervisor_thread, NULL,
			&supervisor, (void *)philo))
		return ((void *)1);
	while (philo->general->is_dead == 0)
	{
		eat(philo);
		philosopher_sleep(philo);
	}
	if (pthread_join(philo->supervisor_thread, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_general *general)
{
	general->start_time = get_time();
	if (general->meals_number > 0 && create_monitor_thread(general))
		return (1);
	if (start_philo_threads(general))
		return (1);
	if (join_philo_threads(general))
		return (1);
	return (0);
}
