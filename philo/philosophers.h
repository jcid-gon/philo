/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:14:06 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/12/14 13:06:41 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>

struct	s_base;

typedef struct s_philos{
	int				pos;
	int				state;
	int				iter;
	uint64_t		last_ate;
	uint64_t		limit;
	struct s_base	*base;
	pthread_mutex_t	mutex;
}	t_philos;

typedef struct s_base{
	int				philo_num;
	int				death;
	int				*is_free;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				iter_max;
	uint64_t		time;
	pthread_t		*pit;
	pthread_mutex_t	writing;
	int				stop;
}	t_base;

int			ft_strlen(char *str);
int			ft_error_check(t_base *base);
int			main(int argc, char **argv);
char		*ft_strjoin(char *s1, char *s2);
uint64_t	ft_atoi(char *str);
uint64_t	ft_get_time(void);
void		ft_putstr(char *str);
void		ft_putnbr(uint64_t num);
void		ft_print_message(t_philos *philos);
void		ft_take_forks(t_philos *philos);
void		ft_leave_forks(t_philos *philos);
void		ft_eat(t_philos *philos);
void		*ft_monitor(void *arg);
void		*ft_routinr(void *arg);
void		philos_start(t_base *base);
void		ft_assing_var(int argc, char **argv, t_base *base);

#endif
