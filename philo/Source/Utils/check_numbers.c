/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:19:41 by ana-pper          #+#    #+#             */
/*   Updated: 2024/09/16 13:27:49 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Philosophers.h"

int	is_numeric(int count)
{
	if (count >= 48 && count <= 57)
	{
		return (1);
	}
	return (0);
}

int	string_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_numeric(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!string_is_numeric(argv[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
