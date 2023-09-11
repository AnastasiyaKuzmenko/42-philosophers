/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:53:22 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/07/26 17:35:47 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_spaces(const char *nptr)
{
	int	index;

	index = 0;
	while (nptr[index] == ' '
		|| nptr[index] == '\n' || nptr[index] == '\t'
		|| nptr[index] == '\f' || nptr[index] == '\r' || nptr[index] == '\v')
	{
		index++;
	}
	return (index);
}

static int	ft_overflow(int sign)
{
	if (sign > 0)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

long int	ft_atoi(const char *nptr)
{
	int				index;
	int				sign;
	long long int	result;

	index = ft_spaces(nptr);
	sign = 1;
	result = 0;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign = -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		result *= 10;
		result += (nptr[index] - '0');
		if (result < 0)
			return (ft_overflow(sign));
		index++;
	}
	return ((long int)(sign * result));
}
