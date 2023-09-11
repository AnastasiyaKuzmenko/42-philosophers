/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:28:52 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/28 14:32:41 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input(t_data *data, int argc)
{
	if (data->number_of_philo <= 0 || data->number_of_philo > 250)
	{
		printf("Error: Number of philo must be more than 0 and less than 250\n");
		return (FAIL);
	}
	else if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
	{
		printf("Error: Time arguments must be greater than zero.\n");
		return (FAIL);
	}
	else if (data->time_to_die > 2147483647 || data->time_to_eat > 2147483647
		|| data->time_to_sleep > 2147483647)
	{
		printf("Error: Time arguments must be less.\n");
		return (FAIL);
	}
	else if (argc == 6 && (data->must_eat_count <= 0
			|| data->must_eat_count > 2147483647))
	{
		printf("Error: Invalid parameter must eat count.\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static int	init_fork_mutex(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->fork[index], NULL) != 0)
		{
			printf("Error: Failed to create mutex!\n");
			return (FAIL);
		}
		index++;
	}
	return (SUCCESS);
}

t_philo	*init_philo(t_data *data)
{
	int			index;
	t_philo		*philo;

	philo = malloc(data->number_of_philo * sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	index = 0;
	while (index < data->number_of_philo)
	{
		philo[index].data = data;
		philo[index].id = index + 1;
		philo[index].left_fork_idx = index;
		philo[index].right_fork_idx = index - 1;
		philo[index].meal_counter = 0;
		philo[index].last_eat_time = data->start_time;
		index++;
	}
	philo[0].right_fork_idx = data->number_of_philo - 1;
	return (philo);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = (int)ft_atoi(argv[5]);
	data->flag_end = 0;
	data->flag_all_eat = 0;
	if (check_input(data, argc) == FAIL)
		return (FAIL);
	data->fork = malloc(data->number_of_philo * sizeof(pthread_mutex_t));
	if (!data->fork)
		return (FAIL);
	if (init_fork_mutex(data) == FAIL
		|| pthread_mutex_init(&data->mtx_writing, NULL)
		|| pthread_mutex_init(&data->mtx_eating, NULL))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

int	create_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->number_of_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, philo_life, &philo[i]))
		{
			printf("Error: Failed to create thread!\n");
			return (FAIL);
		}
		pthread_mutex_lock(&(data->mtx_eating));
		philo[i].last_eat_time = get_time();
		pthread_mutex_unlock(&(data->mtx_eating));
		i++;
	}
	check_philos_death(data, philo);
	kill_philos(data, philo);
	return (SUCCESS);
}
