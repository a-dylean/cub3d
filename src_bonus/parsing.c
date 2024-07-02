#include "../includes/cub3d_bonus.h"

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
	close(fd);
	return (height);
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

void	create_texture(t_cub *cub, char *line)
{
	char	*orientation;
	char	*path;

	orientation = ft_split(line, ' ')[0];
	path = ft_split(line, ' ')[1];
	add_txtr_back(&cub->txtr, new_txtr(orientation, path));
	free(orientation);
	free(path);
}

void	parse_textures(char *line, t_cub *cub)
{
	if (line[0] == 'N' && line[1] == 'O')
		create_texture(cub, line);
	else if (line[0] == 'S' && line[1] == 'O')
		create_texture(cub, line);
	else if (line[0] == 'W' && line[1] == 'E')
		create_texture(cub, line);
	else if (line[0] == 'E' && line[1] == 'A')
		create_texture(cub, line);
	else if (line[0] == 'S' && line[1] == ' ')
		create_texture(cub, line);
	else if (line[0] == 'F' && line[1] == ' ')
		cub->textures.floor_color = ft_atoi(ft_split(line, ' ')[1]);
	else if (line[0] == 'C' && line[1] == ' ')
		cub->textures.ceiling_color = ft_atoi(ft_split(line, ' ')[1]);
	free(line);
}

void	parse_input(char *path, t_cub *cub)
{
	int fd;
	char *new_line;
	int i = 0;

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
			parse_textures(new_line, cub);
		}
		if (new_line && (new_line[0] == '1' || new_line[0] == ' '))
			populate_map(new_line, cub, &i);
	}
	//for testing purposes
	// for (int i = 0; i < cub->map_height; i++)
	// {
	// 	printf("%s", cub->map[i]);
	// }
	// printf("\n");
	// printf("Floor color: %d\n", cub->textures.floor_color);
	// printf("Ceiling color: %d\n", cub->textures.ceiling_color);
	// for (int j = 0; cub->txtr; j++)
	// {
	// 	printf("Orientation: %s\n", cub->txtr->orientation);
	// 	printf("Path: %s\n", cub->txtr->path);
	// 	cub->txtr = cub->txtr->next;
	// }
	close(fd);
}

