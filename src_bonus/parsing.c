#include "../includes/cub3d_bonus.h"

int	get_map_height(char **config)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (config[i])
	{
		if (map_line(config[i]) && !empty_or_spaces_only(config[i]))
			height++;
		i++;
	}
	return (height);
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

void	populate_map(t_cub *cub)
{
	int		i;
	char	**arr;
	int		flag;

	i = 0;
	arr = cub->config_info;
	flag = 0;
	while (1)
	{
		if (!*arr || i >= cub->map_height)
			break ;
		if (!flag && (*arr == NULL || **arr == '\0' || map_line(*arr) == 0))
		{
			arr++;
			continue ;
		}
		flag = 1;
		if (*arr == NULL || **arr == '\0' || map_line(*arr) == 0)
			clean_up(cub, "Invalid map declaration");
		cub->map[i] = ft_strdup(*arr);
		if (!cub->map[i])
			clean_up(cub, "Memory allocation failed");
		i++;
		arr++;
	}
}

void	parse_map(t_cub *cub)
{
	populate_map(cub);
	validate_map(cub->map, cub->map_height, cub->player, cub);
}

void	parse_textures_and_colors(char **nodes, char *line, t_cub *cub)
{
	if (!nodes)
	{
		free(line);
		free_array(nodes);
		clean_up(cub, "Memory allocation failed");
	}
	if (line && !is_texture(nodes[0]) && !is_color(nodes[0]))
	{
		free(line);
		free_array(nodes);
		clean_up(cub, "Invalid element found in config");
	}
	if (line && is_texture(nodes[0]))
	{
		free(line);
		parse_texture(nodes, cub);
	}
	if (line && is_color(nodes[0]))
	{
		parse_color(line, cub, nodes);
	}
}
		

void	parse_config(t_cub *cub)
{
	char	**nodes;
	char	*trimmed_line;
	char	**content;

	content = cub->config_info;
	while (1)
	{
		if (!*content)
			break ;
		//fix possible invalid read here
		trimmed_line = ft_strtrim(*content, SPACES);
		if (!trimmed_line || ft_strlen(trimmed_line) == 0)
		{
			free(trimmed_line), content++;
			continue ;
		}
		if (map_line(*content))
		{
			free(trimmed_line);
			break ;
		}
		nodes = ft_split(trimmed_line, ' ');
		parse_textures_and_colors(nodes, trimmed_line, cub);
		free_array(nodes);
		content++;
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

int	count_lines_in_file(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror(path), EXIT_FAILURE);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
		line = NULL;
	}
	close(fd);
	return (count);
}

int	read_file_into_memory(char *path, t_cub *cub)
{
	int	fd;
	int	i;
	int	line_len;
	int	rows_count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror(path), EXIT_FAILURE);
	rows_count = count_lines_in_file(path);
	cub->config_info = (char **)malloc(sizeof(char *) * (rows_count + 1));
	if (!cub->config_info)
		return (EXIT_FAILURE);
	i = 0;
	while (1)
	{
		cub->config_info[i] = get_next_line(fd);
		if (!cub->config_info[i])
			break ;
		line_len = ft_strlen(cub->config_info[i]);
		if (line_len > 0 && cub->config_info[i][line_len - 1] == '\n')
			cub->config_info[i][line_len - 1] = '\0';
		i++;
	}
	cub->config_info[i] = NULL;
	return (close(fd), EXIT_SUCCESS);
}

void	parsing(char *path, t_cub *cub)
{
	if (!valid_format(path))
		exit_with_error("Invalid file format");
	if (read_file_into_memory(path, cub))
		exit_with_error("Error while reading a file");
	parse_config(cub);
	cub->map_height = get_map_height(cub->config_info);
	init_empty_map(cub);
	parse_map(cub);
	textures_errors_check(cub);
	colors_errors_check(cub);
	// print_parsing(cub);
	free_array(cub->config_info);
}
