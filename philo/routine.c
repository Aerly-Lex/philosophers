/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:38:49 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/08 10:15:32 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_think(t_philo *philo)
{
	if (philo->philosophers == 1)
	{
		printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, THINK);
		ft_usleep(philo, philo->death_timer + 1);
		return (death_check(philo));
	}
	if (philo->thinking == 0)
	{
		printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, THINK);
		philo->thinking = 1;
		if (philo->death_timer - philo->starvation > philo->think_timer)
			ft_usleep(philo, philo->think_timer);
		else if (philo->death_timer < philo->eat_timer * 2)
			ft_usleep(philo, philo->eat_timer);
	}
	else
		philo->thinking = 0;
	return (death_check(philo));
}

static int	ft_eat(t_philo *philo)
{
	int	start;

	start = get_time();
	if (1 == ft_forks_take(philo))
		return (1);
	philo->starvation += get_time() - start;
	printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, EAT);
	philo->starvation = 0;
	if (ft_usleep(philo, philo->eat_timer))
		return (1);
	philo->meals_taken++;
	ft_forks_drop(philo);
	return (death_check(philo));
}

static int	ft_sleep(t_philo *philo)
{
	if (1 == death_check(philo))
		return (1);
	printf("%ld\t%d %s", get_time() - philo->time_start, philo->id, SLEEP);
	ft_usleep(philo, philo->sleep_timer);
	return (death_check(philo));
}

void	*taskmaster(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (1 == ft_meals(philo) || 1 == ft_think(philo))
			break ;
		if (1 == ft_meals(philo) || 1 == ft_eat(philo))
			break ;
		if (1 == ft_meals(philo))
			break ;
		if (1 == ft_meals(philo) || 1 == ft_sleep(philo))
			break ;
	}
	return (0);
}

// printf("%ld\t%d has left the party\n",
// get_time() - philo->time_start, philo->id);
