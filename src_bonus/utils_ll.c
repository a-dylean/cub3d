#include "../includes/cub3d_bonus.h"

t_txtr	*new_txtr(char *orientation, char *path)
{
	t_txtr	*new;

	new = malloc(sizeof(t_txtr));
	if (!new)
		return (NULL);
	new->orientation = orientation;
	new->path = path;
	new->next = NULL;
	return (new);
}

void add_txtr_back(t_txtr **txtr, t_txtr *new)
{
	t_txtr	*last;

	if (!*txtr)
	{
		*txtr = new;
		return ;
	}
	last = *txtr;
	while (last->next)
		last = last->next;
	last->next = new;
}