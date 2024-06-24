/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:28:11 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 15:20:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]) && (i == 0
				|| ft_strchr(charset, s[i - 1])))
			count++;
		i++;
	}
	return (count);
}

static char	*get_word(char const *s, char *charset)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && !ft_strchr(charset, s[i]))
		i++;
	str = malloc((i + 1) * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && !ft_strchr(charset, s[i]))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**fill_arr(char const *s, char *charset, char **strs)
{
	int		i;
	int		j;
	char	*word_to_add;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]) && (i == 0
				|| ft_strchr(charset, s[i - 1])))
		{
			word_to_add = get_word(&s[i], charset);
			if (!word_to_add)
			{
				free_array(strs);
				return (NULL);
			}
			strs[j++] = word_to_add;
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_charset(char const *s, char *charset)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc((count_words(s, charset) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = fill_arr(s, charset, strs);
	if (!strs)
	{
		free_array(strs);
		return (NULL);
	}
	return (strs);
}
