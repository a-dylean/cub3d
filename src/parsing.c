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

void	init_empty_map(t_cub *cub)
{
	int	i;

	i = 0;
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
	free(line);
	(*i)++;
}

void	parse_textures_and_colors(char *new_line, char *trimmed_line,
		t_cub *cub, char **nodes)
{
	nodes = ft_split(trimmed_line, ' ');
	if (!nodes)
		free_and_exit("Memory allocation failed", cub, new_line);
	if (trimmed_line && !is_texture(nodes[0]) && !is_color(nodes[0]))
		free_and_exit("Invalid element found in config", cub, new_line);
	if (trimmed_line && is_texture(nodes[0]))
		parse_texture(nodes, cub);
	if (trimmed_line && is_color(nodes[0]))
		parse_color(trimmed_line, cub);
	// free_array(nodes);
}

void	parse_config(int fd, t_cub *cub, char *new_line, char *trimmed_line)
{
	char	**nodes;
	int		i;

	i = 0;
	nodes = NULL;
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		trimmed_line = ft_strtrim(new_line, SPACES);
		if (!trimmed_line)
			continue ;
		while (trimmed_line && new_line && map_line(new_line))
		{
			populate_map(new_line, cub, &i);
			new_line = get_next_line(fd);
			if (!new_line)
				return (free(nodes), free(trimmed_line), free(new_line));
		}
		parse_textures_and_colors(new_line, trimmed_line, cub, nodes);
		// free(trimmed_line);
		// free(new_line);
	}
}

void	print_parsing(t_cub *cub)
{
	t_txtr	*current;

	printf("Map height: %d\n", cub->map_height);
	printf("Map width: %d\n", cub->map_width);
	printf("Map:\n");
	for (int i = 0; i < cub->map_height; i++)
	{
		printf("map line[%d]: %s\n", i, cub->map[i]);
	}
	printf("Floor color: %d\n", cub->textures.floor_color);
	printf("Ceiling color: %d\n", cub->textures.ceiling_color);
	current = cub->txtr;
	while (current)
	{
		printf("Texture orientation: %s\n", current->orientation);
		printf("Texture path: %s\n", current->path);
		current = current->next;
	}
}

void	parsing(char *path, t_cub *cub)
{
	int		fd;
	char	*new_line;
	char	*trimmed_line;

	new_line = NULL;
	trimmed_line = NULL;
	if (!valid_format(path))
		exit_with_error("Invalid file format");
	init_empty_map(cub);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("No such file or directory");
	parse_config(fd, cub, new_line, trimmed_line);
	textures_errors_check(cub);
	colors_errors_check(cub);
	print_parsing(cub);
	close(fd);
	// return (free(new_line), free(trimmed_line));
}
