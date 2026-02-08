/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:28 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:29:28 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

static char	*get_scale(int zeros, t_dict *dict)
{
	char	key[50];
	int		i;

	if (zeros < 3)
		return (NULL);
	key[0] = '1';
	i = 1;
	while (i <= zeros)
	{
		key[i] = '0';
		i++;
	}
	key[i] = '\0';
	return (lookup(dict, key));
}

static char	*append_result(char *result, char *triad_str, char *scale)
{
	if (!triad_str || triad_str[0] == '\0')
	{
		if (triad_str)
			free(triad_str);
		return (result);
	}
	if (result && result[0] != '\0')
		result = ft_strjoin_free(result, " ", 1);
	result = ft_strjoin_free(result, triad_str, 1);
	free(triad_str);
	if (scale)
	{
		result = ft_strjoin_free(result, " ", 1);
		result = ft_strjoin_free(result, scale, 1);
	}
	return (result);
}

static void	fill_first_triad(char *triad, char *num, int *pos, int first_len)
{
	triad[0] = '0';
	triad[1] = '0';
	triad[2] = '0';
	triad[3] = '\0';
	if (first_len == 1)
		triad[2] = num[(*pos)++];
	else if (first_len == 2)
	{
		triad[1] = num[(*pos)++];
		triad[2] = num[(*pos)++];
	}
	else
	{
		triad[0] = num[(*pos)++];
		triad[1] = num[(*pos)++];
		triad[2] = num[(*pos)++];
	}
}

static char	*process_triads(char *num, t_dict *dict, int len)
{
	char	*result;
	char	triad[4];
	char	*triad_str;
	int		pos;
	int		first_len;

	result = ft_strdup("");
	pos = 0;
	first_len = len % 3;
	if (first_len == 0)
		first_len = 3;
	fill_first_triad(triad, num, &pos, first_len);
	triad_str = convert_triad(triad, dict);
	result = append_result(result, triad_str, get_scale(len - pos, dict));
	while (pos < len)
	{
		triad[0] = num[pos++];
		triad[1] = num[pos++];
		triad[2] = num[pos++];
		triad_str = convert_triad(triad, dict);
		result = append_result(result, triad_str, get_scale(len - pos, dict));
	}
	return (result);
}

char	*convert_number(char *num, t_dict *dict)
{
	char	*result;
	int		len;

	len = ft_strlen(num);
	if (len == 0)
		return (ft_strdup(lookup(dict, "0")));
	result = process_triads(num, dict, len);
	if (result[0] == '\0')
	{
		free(result);
		return (ft_strdup(lookup(dict, "0")));
	}
	return (result);
}
