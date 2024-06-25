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
				// Fetch a new line for the next iteration
			if (!new_line)
				break ; // Break out of the loop if no more lines are available
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

void	populate_map(int fd, t_cub *cub)
{
	char	*new_line;
	int		i;

	i = 0;
	init_empty_map(cub);
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		while (new_line && (new_line[0] == '1' || new_line[0] == ' ')
			&& i < cub->map_height)
		{
			cub->map[i] = ft_strdup(new_line);
			if (!cub->map[i])
				free_and_exit("Memory allocation failed", cub, new_line);
			cub->map_width = (int)ft_strlen(new_line);
			free(new_line);
			i++;
		}
	}
}

void	parse_textures(int fd, t_cub *cub)
{
	char	*new_line;

	(void)cub;
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		if (new_line[0] == 'N' && new_line[1] == 'O')
			printf("NO\n");
		else if (new_line[0] == 'S' && new_line[1] == 'O')
			printf("SO\n");
		else if (new_line[0] == 'W' && new_line[1] == 'E')
			printf("WE\n");
		else if (new_line[0] == 'E' && new_line[1] == 'A')
			printf("EA\n");
		else if (new_line[0] == 'S' && new_line[1] == ' ')
			printf("S\n");
		free(new_line);
	}
}

void	parse_input(char *path, t_cub *cub)
{
	int fd;

	if (!valid_format(path))
		exit_with_error("Invalid file format");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("No such file or directory");
	parse_textures(fd, cub);
	// parse_colors(fd, cub);
	populate_map(fd, cub);
	close(fd);
}