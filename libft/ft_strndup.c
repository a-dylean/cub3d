/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:56:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/09 18:58:13 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
