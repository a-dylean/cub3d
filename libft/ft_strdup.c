/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:31 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 15:19:05 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, size);
	return (dest);
}
