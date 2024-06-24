/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:28:24 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/02 12:34:55 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_whitespaces(const char *str)
{
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	return (str);
}

static const char	*handle_sign(const char *str, int *sign)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign *= -1;
		str++;
	}
	return (str);
}

static long	handle_overflow(long ret, long sign, char current)
{
	if (sign > 0 && ret > (LONG_MAX - (current - '0')) / 10)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	else if (sign < 0 && - ret < (LONG_MIN + (current - '0')) / 10)
	{
		errno = ERANGE;
		return (LONG_MIN);
	}
	return ((ret * 10) + (current - '0'));
}

long	ft_atol(const char *str)
{
	long int	ret;
	int			sign;
	int			i;

	i = 0;
	ret = 0;
	sign = 1;
	str = skip_whitespaces(str);
	str = handle_sign(str, &sign);
	while (ft_isdigit(str[i]) == 1)
	{
		ret = handle_overflow(ret, sign, str[i]);
		if (ret == LONG_MAX || ret == LONG_MIN)
			return (ret);
		i++;
	}
	if (i == 0)
		errno = ERANGE;
	return (ret * sign);
}
