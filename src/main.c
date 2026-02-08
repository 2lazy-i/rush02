/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:31:53 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:29:37 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

int	main(int argc, char **argv)
{
	char	*number;
	t_dict	*dict;
	char	*result;

	if (!validate_args(argc, argv))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (argc == 3)
	{
		dict = parse_dictionary(argv[1]);
		number = clean_number(argv[2]);
	}
	else
	{
		dict = parse_dictionary("numbers.dict");
		number = clean_number(argv[1]);
	}
	if (!dict)
	{
		write(1, "Dict Error\n", 11);
		free(number);
		return (1);
	}
	result = convert_number(number, dict);
	if (!result)
	{
		write(1, "Dict Error\n", 11);
		free(number);
		free_dictionary(dict);
		return (1);
	}
	ft_putstr(result);
	write(1, "\n", 1);
	free(result);
	free(number);
	free_dictionary(dict);
	return (0);
}
