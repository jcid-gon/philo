/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:17:58 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/12/15 14:16:15 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <unistd.h>

void	*ft_monitor(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (philos->limit < ft_get_time())
		{
			philos->state = 4;
			ft_print_message(philos);
			philos->base->death = 1;
			return (NULL);
		}
		if (philos->iter > philos->base->iter_max
			&& philos->base->iter_max != -1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	ft_philo_assing(t_philos *philos)
{
	philos->state = 0;
	ft_print_message(philos);
	philos->iter = 1;
	philos->last_ate = ft_get_time();
	philos->limit = philos->last_ate + philos->base->death_time;
}

void	*ft_routine(void *arg)
{
	t_philos	*philos;
	pthread_t	tid;

	philos = (t_philos *)arg;
	ft_philo_assing(philos);
	pthread_create(&tid, NULL, &ft_monitor, arg);
	pthread_detach(tid);
	usleep(10);
	while (philos->base->death == 0)
	{
		ft_eat(philos);
		philos->state = 0;
		if (philos->base->philo_num != 1)
			ft_print_message(philos);
		philos->iter++;
		if (philos->iter > philos->base->iter_max
			&& philos->base->iter_max != -1)
			return (NULL);
		if (philos->base->philo_num % 2 == 1)
			usleep(philos->base->eat_time * 1000);
		else
			usleep(philos->base->eat_time);
	}
	return (NULL);
}

void	philos_start(t_base *base)
{
	int		i;
	void	*philo;

	i = 0;
	while (i < base->philo_num)
	{
		base->philos[i].pos = i;
		base->philos[i].base = base;
		base->is_free[i] = 0;
		philo = ((void *) &base->philos[i]);
		pthread_mutex_init(&base->forks[i], NULL);
		pthread_create(&base->pit[i], NULL, &ft_routine, philo);
		i++;
	}
	i = 0;
	while (i < base->philo_num)
	{
		pthread_join(base->pit[i], NULL);
		i++;
	}
}
