/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:46:28 by jlabonde          #+#    #+#             */
/*   Updated: 2024/07/03 09:46:29 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

int	list_len(t_txtr *list)
{
	int		i;
	t_txtr	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	has_duplicates(t_txtr *list)
{
	t_txtr	*tmp;
	t_txtr	*tmp2;

	tmp = list;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->orientation, tmp2->orientation, 3) == 0)
				return (1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	free_textures(t_txtr *txtr)
{
	t_txtr	*tmp;

	while (txtr)
	{
		tmp = txtr;
		txtr = txtr->next;
		free(tmp->orientation);
		free(tmp->path);
		free(tmp);
	}
}
