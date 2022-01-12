/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:18:26 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/01/12 14:02:47 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	return (str);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnbr(uint64_t num)
{
	char	number;

	if (num >= 10)
		ft_putnbr(num / 10);
	number = (num % 10) + '0';
	write (1, &number, 1);
}

uint64_t	ft_atoi(char *str)
{
	int			index;
	uint64_t	num;

	index = 0;
	num = 0;
	if (str[0] == '-')
		return (-2);
	while (str[index])
	{
		num = (num * 10) + (str[index] - '0');
		index++;
	}
	return (num);
}
