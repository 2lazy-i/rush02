/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:42:18 by myapaten         ###   ########.fr       */
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

int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
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
	int	i;
	int	key_start;
	int	key_end;
	int	val_start;
	int	val_end;

	i = skip_spaces(line, 0);
	key_start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ':')
		i++;
	key_end = i;
	i = skip_spaces(line, i);
	if (line[i] != ':')
		return (NULL);
	i++;
	i = skip_spaces(line, i);
	val_start = i;
	while (line[i] && line[i] != '\n')
		i++;
	val_end = i;
	while (val_end > val_start && (line[val_end - 1] == ' ' || line[val_end
			- 1] == '\t'))
		val_end--;
	return (create_node(ft_substr(line, key_start, key_end - key_start),
			ft_substr(line, val_start, val_end - val_start)));
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
