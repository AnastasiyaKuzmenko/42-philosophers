/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:27:29 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/27 11:47:57 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define FAIL 1
# define SUCCESS 0

typedef struct s_data
{
	int				number_of_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat_count;
	int				flag_end;
	int				flag_all_eat;
	long long		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mtx_writing;
	pthread_mutex_t	mtx_eating;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork_idx;
	int				right_fork_idx;
	int				meal_counter;
	long long		last_eat_time;
	pthread_t		thread;
	t_data			*data;

}	t_philo;

// libft functions
long int	ft_atoi(const char *nptr);
// init.c functions
t_philo		*init_philo(t_data *data);
int			init_data(int argc, char **argv, t_data *data);
int			create_threads(t_philo *philo, t_data *data);
// utils.c functions
void		print_status(t_data *data, int id, char *status);
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
//philo_life.c functions
void		*philo_life(void *arg);
//kill_philos.c functions
void		check_philos_death(t_data *data, t_philo *philo);
void		kill_philos(t_data *data, t_philo *philo);

#endif
