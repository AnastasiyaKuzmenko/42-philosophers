/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:14:42 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/27 14:36:05 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->right_fork_idx]);
	pthread_mutex_lock(&philo->data->mtx_eating);
	print_status(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->mtx_eating);
	pthread_mutex_lock(&philo->data->fork[philo->left_fork_idx]);
	pthread_mutex_lock(&philo->data->mtx_eating);
	print_status(philo->data, philo->id, "has taken a fork");
	print_status(philo->data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->mtx_eating);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->mtx_eating);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->data->mtx_eating);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork_idx]);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork_idx]);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;
	int			index;

	philo = (t_philo *)arg;
	index = 0;
	if (philo->id % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(philo->data->mtx_eating));
	while (!(philo->data->flag_end) && !(philo->data->flag_all_eat))
	{
		pthread_mutex_unlock(&(philo->data->mtx_eating));
		philo_eat(philo);
		pthread_mutex_lock(&(philo->data->mtx_eating));
		print_status(philo->data, philo->id, "is sleeping");
		pthread_mutex_unlock(&(philo->data->mtx_eating));
		ft_usleep(philo->data->time_to_sleep, philo->data);
		pthread_mutex_lock(&(philo->data->mtx_eating));
		print_status(philo->data, philo->id, "is thinking");
		index++;
	}
	pthread_mutex_unlock(&(philo->data->mtx_eating));
	return (NULL);
}
