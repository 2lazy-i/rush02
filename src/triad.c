/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triad.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:44 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:29:58 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

static char	*add_space_word(char *result, char *word)
{
	char	*tmp;

	if (!word)
	{
		if (result)
			free(result);
		return (NULL);
	}
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free(result);
		return (ft_strdup(word));
	}
	tmp = ft_strjoin_free(result, " ", 1);
	if (!tmp)
		return (NULL);
	return (ft_strjoin_free(tmp, word, 1));
}

static char	*handle_tens(char *result, char *triad, t_dict *dict)
{
	char	key[3];

	if (triad[1] != '0')
	{
		key[0] = triad[1];
		key[1] = '0';
		key[2] = '\0';
		result = add_space_word(result, lookup(dict, key));
	}
	if (triad[2] != '0')
	{
		key[0] = triad[2];
		key[1] = '\0';
		result = add_space_word(result, lookup(dict, key));
	}
	return (result);
}

char	*convert_triad(char *triad, t_dict *dict)
{
	char	*result;
	char	key[4];

	result = ft_strdup("");
	if (triad[0] != '0')
	{
		key[0] = triad[0];
		key[1] = '\0';
		result = add_space_word(result, lookup(dict, key));
		result = add_space_word(result, lookup(dict, "100"));
	}
	if (triad[1] == '1')
	{
		key[0] = triad[1];
		key[1] = triad[2];
		key[2] = '\0';
		return (add_space_word(result, lookup(dict, key)));
	}
	if (triad[1] == '0' && triad[2] == '0')
		return (result);
	return (handle_tens(result, triad, dict));
}
