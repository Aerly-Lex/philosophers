/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:50:12 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/08 10:15:03 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_forks_take(t_philo *philo)
{
	int	start;

	start = get_time();
	if (philo->death_timer - philo->starvation > philo->eat_timer)
		ft_usleep(philo, 1);
	if (0 != pthread_mutex_lock(&philo->env->forks[philo->left_fork]))
		return (liberator(philo->env, "Mutex lock error\n", 1));
	if (ft_usleep(philo, 0))
		return (1);
	printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, FORK);
	if (0 != pthread_mutex_lock(&philo->env->forks[philo->right_fork]))
		return (liberator(philo->env, "Mutex lock error\n", 1));
	philo->starvation += get_time() - start;
	if (ft_usleep(philo, 0))
		return (1);
	printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, FORK);
	return (0);
}

int	ft_forks_drop(t_philo *philo)
{
	if (0 != pthread_mutex_unlock(&philo->env->forks[philo->left_fork]))
		(liberator(philo->env, "Mutex unlock error\n", 1));
	if (0 != pthread_mutex_unlock(&philo->env->forks[philo->right_fork]))
		return (liberator(philo->env, "Mutex unlock error\n", 1));
	return (0);
}
