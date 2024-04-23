/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:28:41 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/07 15:05:11 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief
 *
 * @param env
 * @param str is the output message
 * @param error if parameter is 1 - call ft_error with given str
 */
int	liberator(t_env *env, char *str, int error)
{
	int	i;

	i = 0;
	while (i < env->philosophers)
	{
		pthread_mutex_destroy(env->forks);
		i++;
	}
	if (NULL != env->forks)
		free(env->forks);
	if (NULL != env->philos)
		free(env->philos);
	if (1 == error)
		return (ft_error(str));
	return (0);
}

int	ft_error(char *str)
{
	if (NULL != str)
		printf("%s", str);
	return (1);
}
