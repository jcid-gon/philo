/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:17:58 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/01/12 13:56:27 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <unistd.h>

void	*ft_monitor(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->philo_num)
	{
		if (base->philos[i].iter > base->iter_max
			&& base->iter_max != -1)
		{
			base->end = 1;
			return (NULL);
		}
		if (base->philos[i].limit < ft_get_time() && base->end != 1)
		{
			base->philos[i].state = 4;
			ft_print_message(&base->philos[i]);
			base->death = 1;
			ft_throw_forks(base);
			return (NULL);
		}
		i++;
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

	philos = (t_philos *)arg;
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
			ft_wait(ft_get_time() + philos->base->eat_time, philos->base);
	}
	return (NULL);
}

void	ft_thread_create(t_base *base)
{
	int		i;
	void	*philo;

	i = 0;
	while (i < base->philo_num)
	{
		philo = ((void *) &base->philos[i]);
		if (pthread_create(&base->pit[i], NULL, &ft_routine, philo) != 0)
		{
			ft_putstr("Error creating threads.");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < base->philo_num)
	{
		pthread_join(base->pit[i], NULL);
		i++;
	}
}

void	ft_philos_start(t_base *base)
{
	int		i;

	i = 0;
	while (i < base->philo_num)
	{
		base->philos[i].pos = i;
		base->philos[i].base = base;
		base->is_free[i] = 0;
		ft_philo_assing(&base->philos[i]);
		pthread_mutex_init(&base->forks[i], NULL);
		i++;
	}
	ft_thread_create(base);
}
