/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:24:02 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/27 15:04:05 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	delete_fork_mutex(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->fork[index]);
		index++;
	}
}

static void	check_philo(int philo_index, t_data *data, t_philo *philo)
{
	while (philo_index < data->number_of_philo && !(data->flag_end))
	{
		if ((get_time() - philo[philo_index].last_eat_time) > data->time_to_die)
		{
			print_status(data, philo_index + 1, "died");
			data->flag_end = 1;
		}
		philo_index++;
	}
}

void	check_philos_death(t_data *data, t_philo *philo)
{
	int	philo_index;

	while (!(data->flag_all_eat))
	{
		pthread_mutex_lock(&(data->mtx_eating));
		philo_index = 0;
		check_philo(philo_index, data, philo);
		if (data->flag_end)
		{
			pthread_mutex_unlock(&(data->mtx_eating));
			break ;
		}
		while (philo_index < data->number_of_philo && data->must_eat_count != -1
			&& philo[philo_index].meal_counter >= data->must_eat_count)
			philo_index++;
		if (philo_index == data->number_of_philo)
			data->flag_all_eat = 1;
		pthread_mutex_unlock(&(data->mtx_eating));
		usleep(50);
	}
}

void	kill_philos(t_data *data, t_philo *philo)
{
	int	index;

	index = 0;
	if (data->number_of_philo == 1)
		pthread_mutex_unlock(&data->fork[philo->right_fork_idx]);
	while (index < data->number_of_philo)
	{
		pthread_join(philo[index].thread, NULL);
		index++;
	}
	pthread_mutex_destroy(&data->mtx_writing);
	pthread_mutex_destroy(&data->mtx_eating);
	delete_fork_mutex(data);
	free(data->fork);
	free(data);
	free(philo);
}
