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

// int	ft_strspn(const char *s, const char *accept)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (ft_strchr(accept, s[i]) == 0)
// 			break ;
// 		++i;
// 	}
// 	return (i);
// }

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
	int		i;
	int		j;
	char	*curr_row;
	char	*row_on_top;
	char	*row_on_bottom;

	i = 1;
	while (i < rows)
	{
		curr_row = arr[i];
		row_on_top = arr[i - 1];
		row_on_bottom = arr[i + 1];
		j = 0;
		while (curr_row[j])
		{
			if (row_on_top && !length_check(row_on_top, curr_row, j))
				return (0);
			if (row_on_bottom && !length_check(row_on_bottom, curr_row, j))
				return (0);
			if (row_on_top && !spaces_check(row_on_top, curr_row, j))
				return (0);
			if (row_on_bottom && !spaces_check(row_on_bottom, curr_row, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player(char **arr, int rows, t_player player)
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
			if (arr[i][j] == 'N' || arr[i][j] == 'O' || arr[i][j] == 'W'
				|| arr[i][j] == 'E')
			{
				player.x = j;
				player.y = i;
				player.letter = arr[i][j];
				count++;
			}
			if (count > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	validate_map(char **map, int height, t_player player)
{
	int	i;

	i = 0;
	if (height == 0)
	{
		// free mem alloc for map here
		exit_with_error("Empty map!");
	}
	while (i < height)
	{
		printf("LINE[%d]: %s\n", i, map[i]);
		if (i == 0 || i == height - 1)
		{
			if (!top_and_bottom_check(map[i]))
				exit_with_error("Invalid top or bottom border");
		}
		else if (!first_and_last_char_check(map[i]))
			exit_with_error("Invalid border");
		i++;
	}
	if (!check_conditions(map, height))
		exit_with_error("Invalid border");
	if (!check_player(map, height, player))
		exit_with_error("Invalid player position");
}
