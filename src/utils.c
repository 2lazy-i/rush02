/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:55 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 14:54:42 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

char *ft_strdup(char *src)
{
    int len = ft_strlen(src);
    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
    for (int i = 0; i < len; i++)
        dup[i] = src[i];
    dup[len] = '\0';
    return dup;
}

void ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}
