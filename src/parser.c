/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:05 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:29:52 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

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

int	validate_args(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (0);
	if (argc == 2)
		return (is_all_digits(argv[1]));
	return (is_all_digits(argv[2]));
}

char	*clean_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0' && str[i + 1])
		i++;
	return (ft_strdup(str + i));
}
