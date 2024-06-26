#include "cub3d.h"


int is_color(char *id)
{
	if (!id)
		return (0);	
	return (ft_strcmp(id, "F") == 0 || ft_strcmp(id, "C") == 0);
}

int str_to_color(char *str)
{
	int	i;
	static int	color;
	int	tmp;

	i = 0;
	color = 0;
	printf("str: %s\n", str);
	char **split = ft_split(str, ',');
	while (split[i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
		i++;
	}
	return (color);
}

void parse_color(char **nodes, t_cub *cub)
{
	(void)cub;
	char	*id = NULL;
	char	*value = NULL;
	if (array_len(nodes) != 2)
	{
		free_array(nodes);
		exit_with_error("Invalid color declaration");
	}
	printf("Found color!\n");
	// id = line[0];
	// value = ft_strtrim(line + 1, SPACES);
	// if (!value)
	// {
	// 	free(line);
	// 	exit_with_error("Invalid color value");
	// }
	// if (ft_strncmp(id, "F", 1) == 0)
	// 	cub->textures.floor_color = str_to_color(value);
	// if (ft_strncmp(id, "C", 1) == 0)
	// 	cub->textures.ceiling_color = str_to_color(value);

	free(id);
	free(value);
}