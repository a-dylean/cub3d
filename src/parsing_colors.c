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
	while (colors[i] != NULL)
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

void set_color_value(char *line, char **colors, char **nodes, t_cub *cub)
{
	if ((cub->textures.ceiling_color > 0 && line[0] == 'C')||(cub->textures.floor_color > 0 && line[0] == 'F'))
		exit_with_error("Duplicate color definitions found");
	int color;

	color = get_rgb_int(colors);
	if (color == -1)
	{
		free_array(nodes);
		exit_with_error("Invalid color value");
	}
	if (line[0] == 'F')
		cub->textures.floor_color = color;
	else if (line[0] == 'C')
		cub->textures.ceiling_color = color;
	else
	{
		free_array(nodes);
		exit_with_error("Invalid color identifier");
	}
}

void parse_color(char *line, t_cub *cub)
{
	char **nodes;
	char **colors;
	char *temp;
	int i;

	printf("line: %s\n", line);
	i = 0;
	if (invalid_commas(line))
		exit_with_error("Invalid color declaration");
	temp = ft_strtrim(line, "FC");
	nodes = ft_split(temp, ',');
	if (!nodes)
		exit_with_error("Memory allocation failed");
	if (array_len(nodes) != 3)
	{
		free_array(nodes);
		exit_with_error("Invalid color declaration");
	}
	colors = malloc(sizeof(char *) * array_len(nodes) + 1);
	if (!colors)
		exit_with_error("Memory allocation failed");
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
	set_color_value(line, colors, nodes, cub);
}
void colors_errors_check(t_cub *cub)
{
	if (cub->textures.floor_color <= 0 || cub->textures.ceiling_color <= 0)
		exit_with_error("Missing color(s) definition");
	return;
}