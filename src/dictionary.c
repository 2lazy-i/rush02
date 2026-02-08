/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 21:54:23 by 2lazy            ###   ########.fr       */
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
    int		pos[4];
    char	*key;
    char	*value;

    i = skip_spaces(line, 0);
    pos[0] = i;
    pos[1] = find_key_end(line, i);
    if (pos[1] == pos[0])
        return (NULL);
    i = skip_spaces(line, pos[1]);
    if (line[i] != ':')
        return (NULL);
    i = skip_spaces(line, i + 1);
    pos[2] = i;
    pos[3] = find_value_end(line, pos[2]);
    if (pos[3] == pos[2])
        return (NULL);
    key = ft_substr(line, pos[0], pos[1] - pos[0]);
    value = ft_substr(line, pos[2], pos[3] - pos[2]);
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
