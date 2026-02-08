/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:00:00 by myapaten          #+#    #+#             */
/*   Updated: 2026/02/08 21:28:29 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

static int	print_error(char *msg)
{
    ft_putstr(msg);
    return (1);
}

static char	*get_dict_path(int ac, char **av)
{
    if (ac == 3)
        return (av[1]);
    return ("numbers.dict");
}

static char	*get_number(int ac, char **av)
{
    if (ac == 3)
        return (av[2]);
    return (av[1]);
}

static int	process_and_print(t_dict *dict, char *num)
{
    char	*result;
    char	*clean;

    clean = clean_number(num);
    if (!clean)
        return (0);
    result = convert_number(clean, dict);
    free(clean);
    if (!result)
        return (0);
    ft_putstr(result);
    ft_putstr("\n");
    free(result);
    return (1);
}

int	main(int ac, char **av)
{
    t_dict	*dict;
    char	*num;
    int		success;

    if (ac < 2 || ac > 3)
        return (print_error("Error\n"));
    num = get_number(ac, av);
    if (!validate_args(ac, av))
        return (print_error("Error\n"));
    dict = parse_dictionary(get_dict_path(ac, av));
    if (!dict)
        return (print_error("Dict Error\n"));
    success = process_and_print(dict, num);
    free_dictionary(dict);
    if (!success)
        return (print_error("Dict Error\n"));
    return (0);
}
