/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:55 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 19:03:52 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_strdup(char *src)
{
	int		len;
	int		i;
	char	*dup;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	*lookup(t_dict *dict, char *key)
{
	int	i;
	int	match;

	while (dict)
	{
		i = 0;
		match = 1;
		while (key[i] || dict->key[i])
		{
			if (key[i] != dict->key[i])
			{
				match = 0;
				break ;
			}
			i++;
		}
		if (match)
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}
