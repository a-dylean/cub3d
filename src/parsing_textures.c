#include "cub3d.h"

int	is_texture(char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "NO", 3) == 0 || ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0 || ft_strncmp(id, "EA", 3) == 0);
}

char	*get_path(char *line)
{
	int	fd;

	fd = open(line, O_RDONLY);
	if (fd >= 0)
		return (line);
	return (NULL);
}

void	parse_texture(char **nodes, t_cub *cub)
{
	char	*id;
	char	*path;

	if (array_len(nodes) != 2)
	{
		free_array(nodes);
		exit_with_error("Invalid texture declaration");
	}
	id = nodes[0];
	path = get_path(nodes[1]);
	if (!path)
	{
		free_array(nodes);
		exit_with_error("Invalid texture path");
	}
	add_txtr_back(&cub->txtr, new_txtr(id, path));
}

void	textures_errors_check(t_cub *cub)
{
	if (!cub->txtr)
		exit_with_error("No textures found");
	if (list_len(cub->txtr) != 4)
		exit_with_error("Invalid number of textures");
	if (has_duplicates(cub->txtr))
		exit_with_error("Duplicate texture definitions found");
}