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

int is_texure(char *id)
{
	printf("id: %s\n", id);
	return (ft_strncmp(id, "NO", 3) == 0 || ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0 || ft_strncmp(id, "EA", 3) == 0);
}

int is_color(char *id)
{
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
	// str = trim_spaces(str);
	// printf("str: %s\n", str);
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

void	parse_info(char *line, t_cub *cub)
{
	char	*space_pos;
	char	*id;
	char	*value;

	line = trim_spaces(line);
	space_pos = ft_strchr(line, ' ');
	if (!space_pos)
		return ;
	id = ft_strndup(line, space_pos - line);
	value = trim_spaces(space_pos + 1);
	if (is_texure(id))
		add_txtr_back(&cub->txtr, new_txtr(id, value));
	if (is_color(id))
	{
		printf("color is found\n");
		// if (ft_strncmp(id, "F", 1) == 0)
		// 	cub->textures.floor_color = str_to_color("220,100,0");
		// if (ft_strncmp(id, "C", 1) == 0)
		// 	cub->textures.ceiling_color = ft_atoi_base(value, "0123456789ABCDEF");
	}
	
	free(id);
}

void	parse_input(char *path, t_cub *cub)
{
	int		fd;
	char	*new_line;
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
		if (new_line && new_line[0] != '1' && new_line[0] != ' ')
		{
			parse_info(new_line, cub);
		}
		if (new_line && (new_line[0] == '1' || new_line[0] == ' '))
			populate_map(new_line, cub, &i);
	}
	// for testing purposes
	// for (int i = 0; i < cub->map_height; i++)
	// {
	// 	printf("%s\n", cub->map[i]);
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
	close(fd);
}
