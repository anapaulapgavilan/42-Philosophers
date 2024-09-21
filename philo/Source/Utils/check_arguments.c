/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:19:06 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/16 13:26:06 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

int	arguments_outside_limits(char *str)
{
	long	value;

	value = ft_atoi_long(str);
	if (value > INT_MAX || value < INT_MIN)
	{
		return (0);
	}
	return (1);
}

int	no_arguments_outside_limits(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!arguments_outside_limits(argv[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_arguments(char **argv)
{
	if (!check_numbers(argv))
	{
		printf("%s\n", INPUT_ERROR);
		return (0);
	}
	if (!no_arguments_outside_limits(argv))
	{
		printf("%s\n", INPUT_ERROR);
		return (0);
	}
	return (1);
}
