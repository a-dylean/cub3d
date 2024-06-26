#include "cub3d.h"

int is_color(char *id)
{
	if (!id)
		return (0);	
	return (ft_strcmp(id, "F") == 0 || ft_strcmp(id, "C") == 0);
}

int get_rgb_int(char **colors)
{
	int int_colors[3];
	int i;

	i = 0;
	//change this condition
	while (i < 3)
	{
		int_colors[i] = ft_atoi(colors[i]);
		if (int_colors[i] < 0 || int_colors[i] > 255)
		{
			free_array(colors);
			exit_with_error("Invalid color value");
		}
		i++;
	}
	return ((int_colors[0] << 16) | (int_colors[1] << 8) | int_colors[2]);
}

void parse_color(char *line, t_cub *cub)
{
	char **nodes;
	char **colors;
	char *temp;
	int i;

	i = 0;
	temp = ft_strtrim(line, "FC");
	nodes = ft_split(temp, ',');
	if (!nodes)
		exit_with_error("Memory allocation failed");
	if (array_len(nodes) != 3)
	{
		free_array(nodes);
		exit_with_error("Invalid color declaration");
	}
	colors = malloc(sizeof(char *) * 3);
	while (nodes[i])
	{
		temp = ft_strtrim(nodes[i], SPACES);
		colors[i] = ft_strdup(temp);
		if (!colors[i])
		{
			free_array(nodes);
			exit_with_error("Memory allocation failed");
		}
		free(temp);
		i++;
	}
	if (line[0] == 'F')
		cub->textures.floor_color = get_rgb_int(colors);
	else if (line[0] == 'C')
		cub->textures.ceiling_color = get_rgb_int(colors);
	else
	{
		free_array(nodes);
		exit_with_error("Invalid color identifier");
	}
}

