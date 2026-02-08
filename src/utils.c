/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: 2lazy <2lazy@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 14:33:55 by 2lazy         #+#    #+#                 */
/*   Updated: 2026/02/08 11:59:27 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

//int		ft_strcmp(const char *s1, const char *s2)
//{
//	while (*s2 == *s1)
//	{
//		printf("strcmp>%c == %c\n", s2[0], s1[0]);
//		s2++;
//		s1++;
//	}
//	printf("returning>%d", (unsigned char)*s1 - (unsigned char)*s2);
//	return ((unsigned char)*s1 - (unsigned char)*s2);
//}

char *lookup(t_dict *dict, char *num)
{
	while (dict->next)
	{
		//printf("comparing: %s == %s\n", dict->key, num);
		if (strcmp(dict->key, num) == 0)
			return (dict->value);
		else
			dict = dict->next;
	}
	return (0);
}

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


int ft_strlen2(char const *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	len_str;
	int				i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len_str = ft_strlen2(s1) + ft_strlen2(s2);
	str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}