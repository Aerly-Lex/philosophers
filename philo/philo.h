/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dscheffn <dscheffn@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:27:15 by Dscheffn          #+#    #+#             */
/*   Updated: 2024/02/08 08:54:20 by Dscheffn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define HELP "Invalid Input\n\
4 or 5 positive Parameters are needed:\n\n\
\"Number of Philosophers\"\t\"Death-timer\"\t\"Eat-timer\"\t\"Sleep-timer\"\n\
Optional parameter: \"Number of Meals\"\n\n"

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FINISHED "The Philosophers came to the conclusion, \
that meaning of life is 42.\n"
# define DEATH "%ld\t%d has died before figuring out the meaning of life.\n"

# define TAKE 0
# define DROP 1

typedef struct s_env {
	int				philosophers;
	int				death_timer;
	int				eat_timer;
	int				sleep_timer;
	int				meals;
	int				meals_finished;
	long			time_start;
	int				death;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_env;

// struct for invidual philos
typedef struct s_philo {
	int				philosophers;
	t_env			*env;
	pthread_t		tid;
	int				id;
	int				meals;
	int				death_timer;
	int				eat_timer;
	int				sleep_timer;
	int				think_timer;
	int				thinking;
	int				is_full;

	int				starvation;
	int				meals_taken;
	long			time_start;
	long			time_current;
	int				left_fork;
	int				right_fork;
}	t_philo;

//		MAIN			//

int		main(int argc, char **argv);

//		ROUTINE			//

void	*taskmaster(void *data);

//		FT_FORKS		//

int		ft_forks_take(t_philo *philo);
int		ft_forks_drop(t_philo *philo);

//		UTILS			//

int		get_time(void);
int		death_check(t_philo *philo);
int		ft_meals(t_philo *philo);
int		ft_usleep(t_philo *philo, int timer);

//		LIBFT			//

int		ft_atoi(char *str);
int		ft_isdigit(int i);

//		FT_ERROR		//

int		liberator(t_env *env, char *str, int error);
int		ft_error(char *str);

#endif
