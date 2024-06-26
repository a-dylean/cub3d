#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
	// add freeing of all the allocated memory?
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

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*trim_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	char *end = str + strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = 0;
	return (str);
}