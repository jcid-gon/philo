/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:17:11 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/12/22 13:53:39 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <unistd.h>

void	ft_take_forks(t_philos *philos)
{
	philos->base->is_free[philos->pos] = 1;
	philos->base->is_free[(philos->pos + 1) % philos->base->philo_num] = 1;
	pthread_mutex_lock(&philos->base->forks[philos->pos]);
	philos->state = 1;
	ft_print_message(philos);
	if (philos->base->philo_num == 1)
		return ;
	pthread_mutex_lock(&philos->base->forks[(philos->pos + 1)
		% philos->base->philo_num]);
	ft_print_message(philos);
}

void	ft_leave_forks(t_philos *philos)
{
	pthread_mutex_unlock(&philos->base->forks[philos->pos]);
	pthread_mutex_unlock(&philos->base->forks[(philos->pos + 1)
		% philos->base->philo_num]);
	philos->base->is_free[philos->pos] = 0;
	philos->base->is_free[(philos->pos + 1) % philos->base->philo_num] = 0;
}

void	ft_eat(t_philos *philos)
{
	while (philos->base->is_free[philos->pos] == 1
		|| philos->base->is_free[(philos->pos + 1)
			% philos->base->philo_num])
	{
		usleep(1);
		if (philos->base->death != 0)
			return ;
	}
	ft_monitor(philos->base);
	ft_take_forks(philos);
	if (philos->base->philo_num == 1)
		ft_wait(ft_get_time() + philos->base->death_time + 1);
	else
	{
		philos->state = 2;
		philos->last_ate = ft_get_time();
		philos->limit = philos->last_ate + philos->base->death_time;
		ft_print_message(philos);
		ft_wait(ft_get_time() + philos->base->eat_time);
		ft_monitor(philos->base);
		philos->state = 3;
		ft_print_message(philos);
		ft_leave_forks(philos);
		ft_wait(ft_get_time() + philos->base->sleep_time);
	}
}

void	ft_throw_forks(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->philo_num)
	{
		ft_leave_forks(&base->philos[i]);
		i++;
	}
	usleep(base->death_time * 100);
	base->stop = 1;
	pthread_mutex_unlock(&base->writing);
}
