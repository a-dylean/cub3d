/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:24:23 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/02 15:26:13 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	length_check(char *row_to_compare, char *curr_row, int i)
{
	if (i > (int)ft_strlen(row_to_compare) || i > (int)ft_strlen(curr_row))
	{
		return (1);
	}
	if (row_to_compare
		&& (int)ft_strlen(curr_row) > (int)ft_strlen(row_to_compare)
		&& i >= (int)ft_strlen(row_to_compare))
	{
		if (curr_row[i] != '1')
			return (0);
	}
	return (1);
}

static int	spaces_check(char *row_to_compare, char *curr_row, int i)
{
	if (i > (int)ft_strlen(row_to_compare) || i > (int)ft_strlen(curr_row))
	{
		return (1);
	}
	if ((row_to_compare && ft_isspace(row_to_compare[i])))
	{
		if (curr_row[i] != '1' && curr_row[i] != ' ')
			return (0);
	}
	return (1);
}

int	check_conditions(char **arr, int rows)
{
	int	i;
	int	j;

	i = 1;
	while (i < rows)
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i - 1] && !length_check(arr[i - 1], arr[i], j))
				return (0);
			if (arr[i + 1] && !length_check(arr[i + 1], arr[i], j))
				return (0);
			if (arr[i - 1] && !spaces_check(arr[i - 1], arr[i], j))
				return (0);
			if (arr[i + 1] && !spaces_check(arr[i + 1], arr[i], j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
