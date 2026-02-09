/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:00:00 by myapaten          #+#    #+#             */
/*   Updated: 2026/02/09 20:21:50 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** print_error - Outputs an error message and returns error code
** @msg: The error message to display
** 
** Returns 1 (error code) to allow direct return in main.
** This pattern reduces code duplication for error handling.
*/
static int	print_error(char *msg)
{
    ft_putstr(msg);
    return (1);
}

/*
** get_dict_path - Determines which dictionary file to use
** @ac: Argument count
** @av: Argument vector
** 
** If 3 args provided: ./rush-02 [dict] [number] -> use custom dict (av[1])
** If 2 args provided: ./rush-02 [number] -> use default "numbers.dict"
** This flexibility allows users to specify custom dictionaries.
*/
static char	*get_dict_path(int ac, char **av)
{
    if (ac == 3)
        return (av[1]);
    return ("numbers.dict");
}

/*
** get_number - Extracts the number argument from command line
** @ac: Argument count
** @av: Argument vector
** 
** Position of number depends on whether custom dict was provided:
** - 3 args: number is av[2] (after dict path)
** - 2 args: number is av[1] (only argument)
*/
static char	*get_number(int ac, char **av)
{
    if (ac == 3)
        return (av[2]);
    return (av[1]);
}

/*
** process_and_print - Main processing pipeline for number conversion
** @dict: Parsed dictionary linked list
** @num: Number string to convert
** 
** Pipeline:
** 1. clean_number: Remove leading zeros (e.g., "007" -> "7")
** 2. convert_number: Transform number to words using dictionary
** 3. Output result with newline
** 
** Memory management: Both clean and result are freed after use.
** Returns 1 on success, 0 on failure (for error handling in main).
*/
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

/*
** main - Entry point for rush-02 number-to-words converter
** 
** Usage: ./rush-02 [dictionary] number
** - dictionary is optional, defaults to "numbers.dict"
** 
** Flow:
** 1. Validate argument count (2 or 3 args only)
** 2. Validate number contains only digits
** 3. Parse dictionary file into linked list structure
** 4. Convert number and print result
** 5. Clean up all allocated memory
** 
** Error handling: Returns 1 with appropriate message on any failure.
*/
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
