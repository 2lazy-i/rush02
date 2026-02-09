/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triad.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:44 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:22:20 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** add_space_word - Appends a word to result with space separator
** @result: Current result string (will be freed if free needed)
** @word: Word to append (from dictionary lookup)
** 
** Handles three cases:
** 1. word is NULL -> dictionary lookup failed, return NULL (error)
** 2. result is empty -> just duplicate the word (no space needed)
** 3. result has content -> add space then word
** 
** Memory: Uses ft_strjoin_free to automatically free intermediate result.
** This prevents memory leaks in chained string operations.
*/
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

/*
** handle_tens - Converts tens and ones place for numbers 20-99
** @result: Current accumulated result (may have hundreds)
** @triad: 3-character triad string
** @dict: Dictionary for lookups
** 
** Called when tens digit is 2-9 (not 0 or 1).
** Numbers 20-99 are expressed as: [tens word] [ones word]
** Example: "45" -> "forty" + "five"
** 
** Logic:
** 1. If tens digit != 0, lookup tens place (20, 30, 40, etc.)
** 2. If ones digit != 0, lookup ones place (1-9)
** 
** This handles cases like "40" (just "forty") and "05" (just "five").
*/
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

/*
** convert_triad - Converts a 3-digit group to English words
** @triad: 3-character string representing digits (e.g., "123")
** @dict: Dictionary linked list for word lookups
** 
** English number structure for 3 digits:
** - Hundreds: [digit] + "hundred" (e.g., "1" -> "one hundred")
** - Teens (10-19): Special words looked up directly (e.g., "12" -> "twelve")
** - Tens + Ones (20-99): Separate words (e.g., "45" -> "forty five")
** 
** Algorithm:
** 1. Handle hundreds place: lookup digit, then "100" for "hundred"
** 2. Check for teens (tens digit is '1'): lookup as two-digit key
** 3. Otherwise: handle tens and ones separately via handle_tens
** 
** Returns empty string for "000" triads (no words needed).
*/
char	*convert_triad(char *triad, t_dict *dict)
{
    char	*result;
    char	key[4];

    result = ft_strdup("");
    /* Handle hundreds place: e.g., "5" in "523" -> "five hundred" */
    if (triad[0] != '0')
    {
        key[0] = triad[0];
        key[1] = '\0';
        result = add_space_word(result, lookup(dict, key));
        result = add_space_word(result, lookup(dict, "100"));
    }
    /* Handle teens (10-19): these have unique names in English */
    if (triad[1] == '1')
    {
        key[0] = triad[1];
        key[1] = triad[2];
        key[2] = '\0';
        return (add_space_word(result, lookup(dict, key)));
    }
    /* Handle case where tens and ones are both zero (e.g., "100") */
    if (triad[1] == '0' && triad[2] == '0')
        return (result);
    /* Handle regular tens (20-90) and ones (1-9) */
    return (handle_tens(result, triad, dict));
}
