#include "cub3d.h"

t_txtr	*new_txtr(char *orientation, char *path)
{
	t_txtr	*new;

	new = malloc(sizeof(t_txtr));
	if (!new)
		return (NULL);
	new->orientation = ft_strdup(orientation);
	if (!new->orientation)
	{
		free(new);
		return (NULL);
	}
	new->path = ft_strdup(path);
	if (!new->path)
	{
		free(new->orientation);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_txtr_back(t_txtr **tokens, t_txtr *new_node)
{
	t_txtr	*current;

	if (!new_node)
		return ;
	if (*tokens == NULL)
		*tokens = new_node;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}