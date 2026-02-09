/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:55 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:23:06 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** ft_strlen - Calculates length of null-terminated string
** @str: String to measure
** 
** Standard strlen implementation. Returns 0 for NULL pointer
** for safety (though callers should avoid passing NULL).
*/
int	ft_strlen(char *str)
{
    int	i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

/*
** ft_isdigit - Checks if character is ASCII digit (0-9)
** @c: Character to check
** 
** Returns: 1 if digit, 0 otherwise
** Used for input validation of number arguments.
*/
int	ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

/*
** ft_strdup - Creates a duplicate of a string
** @src: String to duplicate
** 
** Allocates new memory and copies string content.
** Caller is responsible for freeing the returned string.
** Returns NULL if src is NULL or allocation fails.
*/
char	*ft_strdup(char *src)
{
    int		len;
    int		i;
    char	*dup;

    if (!src)
        return (NULL);
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
    dup[i] = '\0';
    return (dup);
}

/*
** ft_putstr - Outputs string to standard output
** @str: String to output
** 
** Uses write() system call for output (no printf).
** This is required for 42 projects that forbid standard library.
*/
void	ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

/*
** lookup - Searches dictionary for a key and returns its value
** @dict: Head of dictionary linked list
** @key: Key to search for
** 
** Linear search through linked list comparing keys character by character.
** 
** Why not use strcmp: Standard library restrictions at 42.
** Custom comparison ensures both strings match completely
** (same length and all characters equal).
** 
** Returns: Value string if found, NULL if not found
** Note: Returns pointer to dictionary's value string (not a copy),
** so caller should NOT free the returned string.
*/
char	*lookup(t_dict *dict, char *key)
{
    int	i;
    int	match;

    while (dict)
    {
        i = 0;
        match = 1;
        /* Compare character by character, including null terminators */
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
