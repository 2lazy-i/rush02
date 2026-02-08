/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:55 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 17:15:19 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

int	ft_strlen(char *str)
{
    int	i;

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
    dup[len] = '\0';
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

char	*ft_strjoin(char *s1, char *s2)
{
    char	*res;
    int		len1;
    int		len2;
    int		i;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = malloc(len1 + len2 + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        res[i] = s1[i];
        i++;
    }
    i = 0;
    while (i < len2)
    {
        res[len1 + i] = s2[i];
        i++;
    }
    res[len1 + len2] = '\0';
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