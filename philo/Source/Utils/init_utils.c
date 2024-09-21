/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:46:13 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/16 19:58:05 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

int	create_monitor_thread(t_general *general)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor_meals, (void *)general))
		return (error(THREAD_ERROR, general));
	pthread_detach(monitor_thread);
	return (0);
}

int	start_philo_threads(t_general *general)
{
	int	i;

	i = -1;
	while (++i < general->philo_number)
	{
		if (pthread_create(&general->thread_id[i], NULL,
				&philosophers_routine, &general->philos[i]))
			return (error(THREAD_ERROR, general));
		ft_usleep(1);
	}
	return (0);
}

int	join_philo_threads(t_general *general)
{
	int	i;

	i = -1;
	while (++i < general->philo_number)
	{
		if (pthread_join(general->thread_id[i], NULL))
			return (error(THREAD_ERROR, general));
	}
	return (0);
}

void	philosopher_sleep(t_philo *philo)
{
	int	time;

	time = get_time();
	messages(SLEEPING, philo);
	while (1)
	{
		if (philo->general->is_dead == 1)
		{
			return ;
		}
		if (get_time() - time >= philo->general->time_to_sleep)
		{
			break ;
		}
		ft_usleep(1);
	}
}
