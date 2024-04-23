/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:06:55 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/07 15:05:12 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	long	storage;

	storage = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		storage *= 10;
		storage += *str++ - '0';
	}
	return (storage);
}
