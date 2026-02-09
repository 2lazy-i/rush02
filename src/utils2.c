/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:30:00 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:23:15 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** ft_strjoin - Concatenates two strings into new allocated string
** @s1: First string
** @s2: Second string
** 
** Allocates memory for combined length of both strings plus null terminator.
** Neither input string is modified or freed.
** 
** Returns: New string containing s1 followed by s2
** Returns NULL if either input is NULL or allocation fails.
*/
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

/*
** ft_strjoin_free - Concatenates strings and optionally frees first string
** @s1: First string (may be freed based on free_s1)
** @s2: Second string (never freed)
** @free_s1: If non-zero, s1 is freed after joining
** 
** Convenience function for chaining string operations without leaks.
** Common pattern: result = ft_strjoin_free(result, " ", 1);
** This appends " " to result and frees the old result in one call.
** 
** Why only free s1: In our usage, s1 is typically accumulated result
** that we own, while s2 is often a literal or dictionary value we don't own.
*/
char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
    char	*res;

    res = ft_strjoin(s1, s2);
    if (free_s1 && s1)
        free(s1);
    return (res);
}

/*
** skip_spaces - Advances index past whitespace characters
** @str: String to scan
** @i: Starting index
** 
** Skips spaces and tabs (common whitespace in text files).
** Used in dictionary parsing to handle flexible formatting.
** 
** Returns: Index of first non-whitespace character (or end of string)
*/
int	skip_spaces(char *str, int i)
{
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    return (i);
}

/*
** find_key_end - Finds end of dictionary key
** @line: Line being parsed
** @i: Starting index (first char of key)
** 
** Key ends at first whitespace, colon, or end of string.
** Keys are expected to be numeric (e.g., "100", "1000000").
** 
** Returns: Index one past the last key character
*/
int	find_key_end(char *line, int i)
{
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ':')
        i++;
    return (i);
}

/*
** find_value_end - Finds end of dictionary value, trimming trailing whitespace
** @line: Line being parsed
** @start: Starting index of value
** 
** Two-phase approach:
** 1. Find absolute end (newline or null terminator)
** 2. Back up past any trailing whitespace
** 
** This allows dictionary values like "  one hundred  " to be trimmed to
** "one hundred" without leading/trailing spaces.
** 
** Returns: Index one past last non-whitespace value character
*/
int	find_value_end(char *line, int start)
{
    int	end;

    end = start;
    /* Phase 1: Find end of line */
    while (line[end] && line[end] != '\n')
        end++;
    /* Phase 2: Trim trailing whitespace */
    while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
        end--;
    return (end);
}
