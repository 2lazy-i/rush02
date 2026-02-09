/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:05 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:22:56 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** is_all_digits - Validates that string contains only digit characters
** @str: String to validate
** 
** Used to ensure command line argument is a valid non-negative integer.
** Rejects empty strings as invalid.
** Does not allow signs (+/-) - only pure digit sequences.
** 
** Returns: 1 if valid (all digits), 0 if invalid
*/
static int	is_all_digits(char *str)
{
    int	i;

    if (!str || str[0] == '\0')
        return (0);
    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/*
** validate_args - Validates command line arguments
** @argc: Argument count
** @argv: Argument vector
** 
** Expected usages:
** - ./rush-02 [number]           (argc == 2)
** - ./rush-02 [dict] [number]    (argc == 3)
** 
** Validates:
** 1. Correct number of arguments (2 or 3)
** 2. Number argument contains only digits
** 
** Note: Does not validate dictionary file existence here -
** that's handled during parse_dictionary to provide better error messages.
*/
int	validate_args(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
        return (0);
    if (argc == 2)
        return (is_all_digits(argv[1]));
    return (is_all_digits(argv[2]));
}

/*
** clean_number - Removes leading zeros from number string
** @str: Number string potentially with leading zeros
** 
** Examples:
** - "007" -> "7"
** - "000" -> "0"
** - "100" -> "100"
** 
** Why needed: Leading zeros don't affect numeric value but would
** cause incorrect triad alignment in conversion algorithm.
** 
** Loop skips zeros while ensuring at least one digit remains.
** The condition str[i + 1] prevents stripping the final zero in "0" or "000".
** 
** Returns: New allocated string without leading zeros
*/
char	*clean_number(char *str)
{
    int	i;

    i = 0;
    while (str[i] == '0' && str[i + 1])
        i++;
    return (ft_strdup(str + i));
}
