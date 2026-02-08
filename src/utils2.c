/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:30:00 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 19:23:43 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

char	*ft_strjoin(char *s1, char *s2)
{
    char	*res;
    int		i;
    int		j;

    if (!s1 || !s2)
        return (NULL);
    res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
        res[i++] = s2[j++];
    res[i] = '\0';
    return (res);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
    char	*res;

    res = ft_strjoin(s1, s2);
    if (free_s1 && s1)
        free(s1);
    return (res);
}

int	skip_spaces(char *str, int i)
{
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    return (i);
}

int	find_key_end(char *line, int i)
{
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ':')
        i++;
    return (i);
}

int	find_value_end(char *line, int start)
{
    int	end;

    end = start;
    while (line[end] && line[end] != '\n')
        end++;
    while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
        end--;
    return (end);
}
