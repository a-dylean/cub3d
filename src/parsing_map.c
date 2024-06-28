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

int	ft_strspn(const char *s, const char *accept)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
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

int	check_conditions(char **arr, int rows)
{
	for (int i = 1; i < rows; i++)
	{
		char *curr_row = arr[i];       
		char *row_on_top = arr[i - 1]; 
		char *row_on_bottom = arr[i + 1];
		for (int j = 0; curr_row[j] != '\0'; j++)
		{
			if (row_on_top && (int)ft_strlen(curr_row) > (int)ft_strlen(row_on_top)
				&& j - 1 > (int)ft_strlen(row_on_top))
			{
				if (curr_row[j] != '1')
                    return (0);
			}
			if (row_on_bottom
				&& (int)ft_strlen(curr_row) > (int)ft_strlen(row_on_bottom) && j
				+ 1 > (int)ft_strlen(row_on_bottom))
			{
				if (curr_row[j] != '1')
                    return (0);
			}
			if ((row_on_top && ft_isspace(row_on_top[j])))
			{
				if (curr_row[j] != '1' && curr_row[j] != ' ')
                    return (0);
			}
            if ((row_on_bottom && ft_isspace(row_on_bottom[j])))
			{
				if (curr_row[j] != '1' && curr_row[j] != ' ')
                    return (0);
			}
		}
	}
    return (1);
}

void	validate_map(char **map, int height)
{
	int i;
	// int j;

	i = 0;
	// j = 0;
	if (height == 0)
		exit_with_error("Empty map!");
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
}