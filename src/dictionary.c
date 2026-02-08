/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 21:36:05 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

char	*ft_substr(char *str, int start, int len)
{
	char	*res;
	int		i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[start + i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

t_dict	*create_node(char *key, char *value)
{
	t_dict	*node;

	node = malloc(sizeof(t_dict));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_dict	*parse_line(char *line)
{
    int		i;
    int		key_start;
    int		key_end;
    int		val_start;
    int		val_end;
    char	*key;
    char	*value;

    i = skip_spaces(line, 0);
    key_start = i;
    key_end = find_key_end(line, i);
    if (key_end == key_start)
        return (NULL);
    i = skip_spaces(line, key_end);
    if (line[i] != ':')
        return (NULL);
    i = skip_spaces(line, i + 1);
    val_start = i;
    val_end = find_value_end(line, val_start);
    if (val_end == val_start)
        return (NULL);
    key = ft_substr(line, key_start, key_end - key_start);
    value = ft_substr(line, val_start, val_end - val_start);
    return (create_node(key, value));
}

void	free_dictionary(t_dict *dict)
{
	t_dict	*temp;

	while (dict)
	{
		temp = dict->next;
		free(dict->key);
		free(dict->value);
		free(dict);
		dict = temp;
	}
}
