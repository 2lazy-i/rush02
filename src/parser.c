/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:05 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 15:03:04 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

// Validate arguments
int validate_args(int argc, char **argv)
{
    int i;

    if (argc < 2 || argc > 3)
        return (0);

    i = 0;
    while (argv[1][i])
    {
        if (!ft_isdigit(argv[1][i]))
            return (0);
        i++;
    }
    return (1);
}

// Remove leading zeros
char *clean_number(char *str)
{
    int i = 0;
    while (str[i] == '0' && str[i + 1])
        i++;
    return ft_strdup(str + i);
}
