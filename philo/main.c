/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:36:36 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/08 10:15:21 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philos_env(t_philo *philo)
{
	philo->philosophers = philo->env->philosophers;
	philo->meals = philo->env->meals;
	philo->death_timer = philo->env->death_timer;
	philo->eat_timer = philo->env->eat_timer;
	philo->sleep_timer = philo->env->sleep_timer;
	philo->thinking = philo->id % 2;
	if (philo->env->eat_timer < philo->env->sleep_timer)
		philo->think_timer = philo->env->eat_timer;
	else
		philo->think_timer = philo->env->sleep_timer;
	if (0 == (philo->id % 2))
	{
		philo->left_fork = (philo->id + 1) % philo->philosophers;
		philo->right_fork = (philo->id) % philo->philosophers;
	}
	else
	{
		philo->left_fork = (philo->id) % philo->philosophers;
		philo->right_fork = (philo->id + 1) % philo->philosophers;
	}
}

static int	create_philos(t_env *env)
{
	t_philo			*philo;
	int				i;

	i = -1;
	philo = malloc(sizeof(t_philo) * env->philosophers);
	if (!philo)
		return (1);
	env->philos = philo;
	while (++i < env->philosophers)
	{
		philo[i].env = env;
		philo[i].id = i;
		philo[i].meals_taken = 0;
		philo[i].starvation = 0;
		philo[i].time_start = get_time();
		philo[i].time_current = 0;
		philo[i].is_full = 0;
		create_philos_env(&philo[i]);
		if (pthread_create(&philo[i].tid, NULL, taskmaster, &philo[i]) != 0)
			return (liberator(env, "Threads creation error.\n", 1));
	}
	return (0);
}

static int	create_forks(t_env *env)
{
	int	i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->philosophers);
	if (env->forks == NULL)
		return (liberator(env, "Malloc on Forks error\n", 1));
	while (i < env->philosophers)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (liberator(env, "forks_mutex init error\n", 1));
		i++;
	}
	return (0);
}

static int	process_args(int argc, char **argv, t_env *env)
{
	env->philosophers = ft_atoi(argv[1]);
	env->death_timer = ft_atoi(argv[2]);
	env->eat_timer = ft_atoi(argv[3]);
	env->sleep_timer = ft_atoi(argv[4]);
	env->sleep_timer = ft_atoi(argv[4]);
	env->time_start = get_time();
	env->death = 0;
	env->meals_finished = 0;
	if (argc == 6)
		env->meals = ft_atoi(argv[5]);
	else
		env->meals = -1;
	if (!env->philosophers || !env->death_timer || !env->eat_timer || \
			!env->sleep_timer || !env->meals)
		return (ft_error(HELP));
	if (pthread_mutex_init(&env->death_mutex, NULL) != 0)
		return (liberator(env, "death_mutex init error\n", 1));
	if (pthread_mutex_init(&env->meal_mutex, NULL) != 0)
		return (liberator(env, "meal_mutex init error\n", 1));
	if (0 != create_forks(env))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env		env;
	int			i;

	i = -1;
	if (argc >= 5 && argc <= 6)
	{
		if (0 != process_args(argc, argv, &env))
			return (1);
	}
	else
		return (ft_error(HELP));
	if (0 != create_philos(&env))
		return (1);
	while (++i < env.philosophers)
		pthread_join(env.philos[i].tid, NULL);
	if (env.meals_finished == env.philosophers)
		printf(FINISHED);
	liberator(&env, NULL, 0);
	return (0);
}

/*
 a philo should die
./philo 1 800 200 200
./philo 4 200 205 200
./philo 4 310 200 100
no one should die, simulation should stop after X eats
./philo 5 800 200 200 7
./philo 4 410 200 200 10
no one should die
./philo 5 800 200 200
./philo 5 600 150 150
./philo 4 410 200 200
./philo 100 800 200 200
./philo 105 800 200 200
./philo 200 800 200 200
*/

/*
 Arguments:	number_of_philosophers	time_to_die	time_to_eat	time_to_sleep
	[number_of_times_each_philosopher_must_eat]

 memset usleep, gettimeofday
 pthread_detach
 pthread_mutex_destroy

 Description Philosophers with threads and mutexes

 The specific rules for the mandatory part are:
 • Each philosopher should be a thread.
 • There is one fork between each pair of philosophers.
 Therefore, if there are several philosophers,
 each philosopher has a fork on their left side and a fork on their right side.
   If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks,
you should protect the forks state with a mutex for each of them.
*/
