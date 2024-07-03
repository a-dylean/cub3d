/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:57:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/03 09:48:34 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	valid_format(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", ft_strlen(filename)) == 0);
}

int	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	map_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S' || line[i] == 'N')
			i++;
		else
			return (0);
	}
	return (1);
}
