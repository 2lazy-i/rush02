/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:30:00 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:30:16 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

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
