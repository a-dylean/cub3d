#include "../includes/cub3d_bonus.h"
void	clean_up(t_cub *cub, char *error)
{
	if (cub->config_info)
		free_array(cub->config_info);
	if (cub->map)
		free_map(cub->map);
	if (cub->txtr)
		free_textures(cub->txtr);
	exit_with_error(error);
}

void	free_and_exit(char *msg, t_cub *cub, char *new_line)
{
	if (ft_strlen(new_line) > 0)
		free(new_line);
	free_map(cub->map);
	exit_with_error(msg);
}

void	exit_with_error(char *error)
{
	printf("Error\n");
	printf("%s\n", error);
	exit(1);
}

int	valid_format(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", ft_strlen(filename)) == 0);
}

int	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	invalid_commas(char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	return (commas != 2);
}

int	map_line(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S' || line[i] == 'N')
			i++;
		else
			return (0);
	}
	return (1);
}