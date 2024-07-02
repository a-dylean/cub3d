#include "cub3d.h"

int	is_color(char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "F", 2) == 0 || ft_strncmp(id, "C", 2) == 0);
}

int	get_rgb_int(char **colors)
{
	int	int_colors[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!str_is_numeric(colors[i]))
			return (-1);
		int_colors[i] = ft_atoi(colors[i]);
		if (int_colors[i] < 0 || int_colors[i] > 255)
			return (-1);
		i++;
	}
	return ((int_colors[0] << 16) | (int_colors[1] << 8) | int_colors[2]);
}

void	set_color_value(char *line, char **colors, char **nodes, t_cub *cub)
{
	int	color;

	if ((cub->textures.ceiling_color > 0 && line[0] == 'C')
		|| (cub->textures.floor_color > 0 && line[0] == 'F'))
	{
		free_array(nodes);
		free_array(colors);
		free(line);
		clean_up(cub, "Duplicate color definitions found");
	}
	color = get_rgb_int(colors);
	if (color == -1)
	{
		free_array(nodes);
		free_array(colors);
		free(line);
		clean_up(cub, "Invalid color value");
	}
	if (line[0] == 'F')
		cub->textures.floor_color = color;
	else if (line[0] == 'C')
		cub->textures.ceiling_color = color;
	else
	{
		free_array(nodes);
		free_array(colors);
		clean_up(cub, "Invalid color identifier");
	}
	// free_array(colors);
}

void	parse_color(char *line, t_cub *cub, char** color_ids)
{
	char	**nodes;
	char	**colors;
	char	*temp;
	int		i;

	i = 0;
	if (invalid_commas(line))
	{
		free(line);
		free_array(color_ids);
		clean_up(cub, "Invalid color declaration");
	}
	temp = ft_strtrim(line, "FC");
	nodes = ft_split(temp, ',');
	free(temp);
	if (!nodes)
	{
		free(line);
		free_array(color_ids);
		clean_up(cub, "Memory allocation failed");
	}
	if (array_len(nodes) != 3)
	{
		free_array(nodes);
		free_array(color_ids);
		free(line);
		clean_up(cub, "Invalid color declaration");
	}
	colors = ft_calloc(sizeof(char *) * array_len(nodes) + 1, sizeof(char *));
	if (!colors)
	{
		free_array(color_ids);
		clean_up(cub, "Memory allocation failed");
	}
	while (nodes[i])
	{
		temp = ft_strtrim(nodes[i], SPACES);
		colors[i] = ft_strdup(temp);
		if (!colors[i])
		{
			free_array(nodes);
			free_array(color_ids);
			clean_up(cub, "Memory allocation failed");
		}
		free(temp);
		i++;
	}
	set_color_value(line, colors, nodes, cub);
	free_array(colors);
	free_array(nodes);
	free(line);
}
void	colors_errors_check(t_cub *cub)
{
	//change the condition here, because color can be 0
	if (cub->textures.floor_color <= 0 || cub->textures.ceiling_color <= 0)
		clean_up(cub, "Missing color(s) definition");
	return ;
}