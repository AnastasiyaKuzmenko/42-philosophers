/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:35:17 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/28 14:35:21 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&(data->mtx_writing));
	if (!(data->flag_end))
		printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&(data->mtx_writing));
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start;
	long long	stop;

	start = get_time();
	stop = start + time;
	pthread_mutex_lock(&(data->mtx_eating));
	while ((start < stop) && !(data->flag_end))
	{
		pthread_mutex_unlock(&(data->mtx_eating));
		usleep(500);
		start = get_time();
		pthread_mutex_lock(&(data->mtx_eating));
	}
	pthread_mutex_unlock(&(data->mtx_eating));
}
