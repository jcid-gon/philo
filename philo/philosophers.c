/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:40 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/01/12 13:48:23 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_error_check(t_base *base)
{
	if (base->philo_num <= 0)
		return (-1);
	if (base->eat_time <= 0 || base->sleep_time <= 0)
		return (-1);
	if (base->iter_max == -2 || base->iter_max == 0)
		return (-1);
	return (0);
}

void	ft_assing_var(int argc, char **argv, t_base *base)
{
	base->philo_num = ft_atoi(argv[1]);
	base->forks = malloc(base->philo_num * sizeof(pthread_mutex_t));
	base->is_free = malloc(base->philo_num * sizeof(int));
	base->pit = malloc(base->philo_num * sizeof(pthread_t));
	base->philos = malloc(base->philo_num * sizeof(t_philos));
	base->death_time = ft_atoi(argv[2]);
	base->eat_time = ft_atoi(argv[3]);
	base->sleep_time = ft_atoi(argv[4]);
	base->death = 0;
	base->stop = 0;
	base->end = 0;
	if (argc == 6)
		base->iter_max = ft_atoi(argv[5]);
	else
		base->iter_max = -1;
	pthread_mutex_init(&base->writing, NULL);
	base->time = ft_get_time();
}

void	ft_destroy_forks(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->philo_num)
	{
		ft_leave_forks(&base->philos[i]);
		i++;
	}
	i = 0;
	while (i < base->philo_num)
	{
		pthread_mutex_destroy(&base->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&base->writing);
}

void	ft_clean(t_base *base)
{
	ft_destroy_forks(base);
	if (base->forks)
		free(base->forks);
	if (base->pit)
		free(base->pit);
	if (base->is_free)
		free(base->is_free);
	if (base->philos)
		free(base->philos);
}

int	main(int argc, char **argv)
{
	t_base		base;

	if (argc != 5 && argc != 6)
	{
		ft_putstr("Invalid number of arguments\n");
		return (-1);
	}
	ft_assing_var(argc, argv, &base);
	if (ft_error_check(&base) != 0)
	{
		ft_putstr("Invalid arguments\n");
		return (-1);
	}
	ft_philos_start(&base);
	ft_clean(&base);
}
