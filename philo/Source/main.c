/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:16:42 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/16 13:55:30 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Philosophers.h"

int	case_one(t_general *general)
{
	general->start_time = get_time();
	if (pthread_create(&general->thread_id[0], NULL,
			&philosophers_routine, &general->philos[0]))
	{
		return (error(THREAD_ERROR, general));
	}
	pthread_detach(general->thread_id[0]);
	while (general->is_dead == 0)
	{
		ft_usleep(10);
	}
	thread_cleanup(general);
	return (0);
}

void	data_cleanup(t_general	*general)
{
	if (general->thread_id)
	{
		free(general->thread_id);
	}
	if (general->forks)
	{
		free(general->forks);
	}
	if (general->philos)
	{
		free(general->philos);
	}
}

void	thread_cleanup(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->philo_number)
	{
		pthread_mutex_destroy(&general->forks[i]);
		pthread_mutex_destroy(&general->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&general->write);
	pthread_mutex_destroy(&general->general_lock);
	data_cleanup(general);
}

int	error(char *str, t_general *general)
{
	printf("%s\n", str);
	if (general)
	{
		thread_cleanup(general);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_general	general;

	if (argc < 5 || argc > 6)
	{
		printf("%s\n", ARGUMENT_ERROR);
		return (1);
	}
	if (!check_arguments(argv))
	{
		return (1);
	}
	if (!init_structures(&general, argv, argc))
	{
		return (1);
	}
	if (general.philo_number == 1)
	{
		return (case_one(&general));
	}
	if (thread_init(&general))
	{
		return (1);
	}
	thread_cleanup(&general);
	return (0);
}
