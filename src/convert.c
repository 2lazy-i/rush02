/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:28 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:22:05 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** get_scale - Retrieves scale word (thousand, million, etc.) from dictionary
** @zeros: Number of remaining zeros/digits after current triad
** @dict: Dictionary linked list
** 
** Scale is determined by position in number:
** - 3 zeros remaining = thousand (10^3)
** - 6 zeros remaining = million (10^6)
** - etc.
** 
** Builds key dynamically: "1" followed by 'zeros' number of "0"s
** Example: zeros=6 -> key="1000000" -> returns "million"
** 
** Returns NULL if zeros < 3 (no scale needed for ones position)
*/
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

/*
** append_result - Appends converted triad and its scale to result string
** @result: Current accumulated result string
** @triad_str: Converted triad words (e.g., "one hundred twenty three")
** @scale: Scale word (e.g., "thousand") or NULL
** 
** Logic:
** 1. Skip empty triads (e.g., "000" in "1000000" middle section)
** 2. Add space separator if result already has content
** 3. Append the triad words
** 4. Append scale word if applicable
** 
** Memory: Frees intermediate strings and triad_str to prevent leaks.
** Uses ft_strjoin_free to chain operations while managing memory.
*/
static char	*append_result(char *result, char *triad_str, char *scale)
{
    if (!triad_str || triad_str[0] == '\0')
    {
        if (triad_str)
            free(triad_str);
        return (result);
    }
    if (result && result[0] != '\0')
    {
        result = ft_strjoin_free(result, " ", 1);
        if (!result)
            return (free(triad_str), NULL);
    }
    result = ft_strjoin_free(result, triad_str, 1);
    if (!result)
        return (free(triad_str), NULL);
    if (scale)
    {
        result = ft_strjoin_free(result, " ", 1);
        if (result)
            result = ft_strjoin_free(result, scale, 1);
    }
    return (free(triad_str), result);
}

/*
** fill_first_triad - Handles the first (potentially incomplete) triad
** @triad: Output buffer for 3-digit triad
** @num: Input number string
** @pos: Current position pointer (updated after reading)
** @first_len: Length of first triad (1, 2, or 3 digits)
** 
** Numbers are processed in groups of 3 (triads) from left to right.
** The first triad may have 1, 2, or 3 digits depending on total length.
** Example: "12345" -> first triad is "12" (2 digits), then "345"
** 
** Pads with leading zeros to always produce a 3-char triad for uniform
** processing in convert_triad function.
** Example: first_len=2 with "12" -> triad="012"
*/
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

/*
** process_triads - Converts number by processing 3-digit groups (triads)
** @num: Number string to convert
** @dict: Dictionary for lookups
** @len: Length of number string
** 
** Algorithm: Process number from left to right in groups of 3 digits.
** This matches how we read numbers: "123,456,789" = "123 million 456 thousand 789"
** 
** Steps:
** 1. Calculate first triad length (may be 1-3 digits)
** 2. Convert first triad and append with appropriate scale
** 3. Loop through remaining full triads (always 3 digits each)
** 
** Scale is determined by remaining digits: len - pos gives position,
** which maps to thousand (3), million (6), billion (9), etc.
*/
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

/*
** convert_number - Main entry point for number-to-words conversion
** @num: Cleaned number string (no leading zeros)
** @dict: Parsed dictionary linked list
** 
** Special cases:
** - Empty string: return "zero"
** - All zeros result (e.g., input "000"): return "zero"
** 
** Delegates to process_triads for actual conversion logic.
** This separation allows clean handling of edge cases.
*/
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
