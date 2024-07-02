#include "cub3d.h"

int	top_and_bottom_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	empty_or_spaces_only(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		while (SPACES[j])
		{
			if (str[i] != SPACES[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	first_and_last_char_check(char *str)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = ft_strlen(str);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '1')
		return (0);
	while (i < line_len)
	{
		if (str[i] == ' ')
		{
			if (str[i + 1] != ' ' && str[i + 1] != '1')
				return (0);
		}
		i++;
	}
	while (line_len > 0 && ft_isspace(str[line_len - 1]))
		line_len--;
	if (str[line_len - 1] != '1')
		return (0);
	return (1);
}

int	length_check(char *row_to_compare, char *curr_row, int i)
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

int	spaces_check(char *row_to_compare, char *curr_row, int i)
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

int	check_player(char **arr, int rows)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < rows)
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'W' || arr[i][j] == 'E'
				|| arr[i][j] == 'S')
			{
				player.x = j;
				player.y = i;
				player.letter = arr[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

void	validate_map(char **map, int height, t_cub *cub)
{
	int	i;

	i = 0;
	if (height == 0)
		clean_up(cub, "Empty map!");
	while (i < height)
	{
		if (i == 0 || i == height - 1)
		{
			if (!top_and_bottom_check(map[i]))
				clean_up(cub, "Invalid top or bottom border");
		}
		else if (!first_and_last_char_check(map[i]))
			clean_up(cub, "Invalid border");
		i++;
	}
	if (!check_conditions(map, height))
		clean_up(cub, "Invalid border");
	if (!check_player(map, height))
		clean_up(cub, "Invalid player position");
}
