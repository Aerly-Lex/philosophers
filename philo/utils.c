/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:23:34 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/08 08:54:04 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	current_time;
	int				time_diff;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time_diff);
}

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death_mutex);
	if (0 != philo->env->death)
	{
		ft_forks_drop(philo);
		pthread_mutex_unlock(&philo->env->death_mutex);
		return (1);
	}
	else if (philo->starvation > philo->death_timer)
	{
		philo->env->death = 1;
		printf(DEATH, get_time() - philo->time_start, philo->id);
		ft_forks_drop(philo);
		pthread_mutex_unlock(&philo->env->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return (0);
}

int	ft_meals(t_philo *philo)
{
	int	finished;

	finished = 0;
	pthread_mutex_lock(&philo->env->meal_mutex);
	if (philo->meals_taken == philo->meals && !philo->is_full)
	{
		philo->env->meals_finished++;
		philo->is_full = 1;
	}
	if (philo->env->meals_finished == philo->env->philosophers)
		finished = 1;
	pthread_mutex_unlock(&philo->env->meal_mutex);
	return (finished);
}

int	ft_usleep(t_philo *philo, int timer)
{
	int	start;

	start = get_time();
	death_check(philo);
	while (get_time() - start < timer && \
			philo->starvation + get_time() - start <= philo->death_timer)
		usleep(50);
	philo->starvation += get_time() - start;
	if (1 == death_check(philo))
		return (1);
	pthread_mutex_lock(&philo->env->death_mutex);
	if (philo->starvation > philo->death_timer && philo->env->death == 0)
	{
		philo->env->death = 1;
		printf(DEATH, get_time() - philo->time_start, philo->id);
		ft_forks_drop(philo);
		pthread_mutex_unlock(&philo->env->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return (0);
}
