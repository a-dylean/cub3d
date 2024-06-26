#include "cub3d.h"

int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*new_line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("No such file or directory");
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		while (new_line && (new_line[0] == '1' || new_line[0] == ' '))
		{
			height++;
			free(new_line);
			new_line = get_next_line(fd);
			if (!new_line)
				break ;
		}
		if (new_line)
			free(new_line);
	}
	return (close(fd), height);
}

static void	init_empty_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cub->map = malloc(sizeof(char *) * (cub->map_height + 1));
	if (!cub->map)
	{
		free(cub->map);
		exit_with_error("Memory allocation failed");
	}
	while (i <= cub->map_height)
	{
		cub->map[i] = NULL;
		i++;
	}
}

void	populate_map(char *line, t_cub *cub, int *i)
{
	cub->map[*i] = ft_strdup(line);
	if (!cub->map[*i])
		free_and_exit("Memory allocation failed", cub, line);
	// cub->map_width = (int)ft_strlen(line);
	free(line);
	(*i)++;
}
	
void	parse_input(char *path, t_cub *cub)
{
	int		fd;
	char	*new_line;
	char *trimmed_line;
	char **nodes;
	int		i;

	i = 0;
	if (!valid_format(path))
		exit_with_error("Invalid file format");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("No such file or directory");
	init_empty_map(cub);
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		trimmed_line = ft_strtrim(new_line, SPACES);
		if (!trimmed_line)
			continue;
		nodes = ft_split(trimmed_line, ' ');	
		if (!nodes)
			free_and_exit("Memory allocation failed", cub, new_line);
		if (trimmed_line && is_texture(nodes[0]))
			parse_texture(nodes, cub);
		if (trimmed_line && is_color(nodes[0]))
			parse_color(nodes, cub);
		if (trimmed_line && (trimmed_line[0] == '1' || trimmed_line[0] == ' '))
			populate_map(new_line, cub, &i);
	}
	// for testing purposes
	// for (int i = 0; i < cub->map_height; i++)
	// {
	// 	printf("line[%d]: %s\n", i, cub->map[i]);
	// }
	// printf("Floor color: %d\n", cub->textures.floor_color);
	// printf("Ceiling color: %d\n", cub->textures.ceiling_color);
	t_txtr *current = cub->txtr;
	while (current)
	{
		printf("Orientation: %s\n", current->orientation);
		printf("Path: %s\n", current->path);
		current = current->next;
	}
	// free(new_line);
	close(fd);
}
