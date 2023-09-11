/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:20:47 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/27 14:45:46 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] == '+' || argv[i][j] == ' ')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	cleanup(t_data *data, t_philo *philo)
{
	if (data != NULL)
		free(data);
	if (philo != NULL)
		free(philo);
	return (FAIL);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;

	if (check_isdigit(argv) == FAIL || (argc != 5 && argc != 6))
	{
		printf("Error: Invalid input data\n");
		return (FAIL);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL || init_data(argc, argv, data) == FAIL)
		return (cleanup(data, NULL));
	philo = init_philo(data);
	if (philo == NULL)
		return (cleanup(data, NULL));
	if (create_threads(philo, data) == FAIL)
		return (cleanup(data, NULL));
	return (0);
}
